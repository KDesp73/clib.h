CC = cc

CFLAGS = -Wall -ggdb -fPIC -Iinclude -O0 -g3 -DDEBUG
LDFLAGS = 

ifeq ($(OS),Windows_NT)
    CFLAGS += -DWINDOWS
endif

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
OBJECTS_DIR = $(BUILD_DIR)/objects
INSTALL_DIR = /usr/lib
INCLUDE_INSTALL_DIR = /usr/local/include

ifeq ($(OS),Windows_NT)
    INSTALL_DIR = C:\Program Files\clib\lib
    INCLUDE_INSTALL_DIR = C:\Program Files\clib\include
    DLL_NAME = $(BUILD_DIR)\output\clib.dll
    STATIC_LIB_NAME = $(BUILD_DIR)\output\libclib.lib
    INSTALL = install_windows
else
    INSTALL_DIR = /usr/lib/
    INCLUDE_INSTALL_DIR = /usr/local/include/clib
    DLL_NAME = $(BUILD_DIR)/output/clib.dll
    STATIC_LIB_NAME = $(BUILD_DIR)/output/libclib.a
    INSTALL = install_unix
endif

SRC_FILES := $(shell find $(SRC_DIR) -name '*.c')
OBJ_FILES = $(patsubst $(SRC_DIR)/%.c, $(OBJECTS_DIR)/%.o, $(SRC_FILES))

LIB_NAME = $(BUILD_DIR)/output/libclib.so
STATIC_LIB_NAME = $(BUILD_DIR)/output/libclib.a
DLL_NAME = $(BUILD_DIR)/output/clib.dll

all: $(BUILD_DIR) shared static dll

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)/output
	mkdir -p $(OBJECTS_DIR)

$(OBJECTS_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c -o $@ $<

shared: $(BUILD_DIR) $(OBJ_FILES)
	$(CC) -shared -o $(LIB_NAME) $(OBJ_FILES) $(LDFLAGS)
	chmod 755 $(LIB_NAME)

static: $(BUILD_DIR) $(OBJ_FILES)
	ar rcs $(STATIC_LIB_NAME) $(OBJ_FILES)
	chmod 644 $(STATIC_LIB_NAME)

dll: $(BUILD_DIR) $(OBJ_FILES)
	$(CC) -shared -o $(DLL_NAME) $(OBJ_FILES) -Wl,--out-implib,$(BUILD_DIR)/output/libclib.dll.a $(LDFLAGS)
	chmod 644 $(DLL_NAME)
	chmod 644 $(BUILD_DIR)/output/libclib.dll.a

install: all
	make $(INSTALL)

install_unix:
	# Install shared library
	sudo mkdir -p $(INSTALL_DIR)
	sudo cp $(LIB_NAME) $(INSTALL_DIR)
	sudo chmod 755 $(INSTALL_DIR)/libclib.so
	
	# Install static library
	sudo cp $(STATIC_LIB_NAME) $(INSTALL_DIR)
	sudo chmod 644 $(INSTALL_DIR)/libclib.a
	
	# Install header files
	sudo rm -rf $(INCLUDE_INSTALL_DIR)
	sudo mkdir -p $(INCLUDE_INSTALL_DIR)
	sudo cp -r $(INCLUDE_DIR)/* $(INCLUDE_INSTALL_DIR)
	sudo chmod 644 $(INCLUDE_INSTALL_DIR)/*.h

install_windows:
	# TODO
	# Install DLL and import library (Windows specific)
	mkdir -p $(INSTALL_DIR)
	cp $(DLL_NAME) $(INSTALL_DIR)
	cp $(BUILD_DIR)/output/libclib.dll.a $(INSTALL_DIR)
	chmod 644 $(INSTALL_DIR)/clib.dll
	chmod 644 $(INSTALL_DIR)/libclib.dll.a

clean:
	rm -rf $(BUILD_DIR)

compile_commands.json: $(SRC_FILES)
	bear -- make

.PHONY: all clean shared static dll install install_unix install_windows

