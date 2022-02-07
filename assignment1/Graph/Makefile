.SUFFIXES:
	
CC := gcc
PROJ_DIR := $(realpath $(CURDIR))
BUILD_DIR := $(PROJ_DIR)/build
SRC_DIRS := $(PROJ_DIR)/src
OUTPUT_LIB_DIR := $(PROJ_DIR)/lib
INC_DIRS := $(PROJ_DIR)/include

DEST_DIR := /usr

ifeq ($(OS), Windows_NT)
	RM := del /f /q
	RMDIR := rmdir /s /q
	MKDIR := mkdir
	ERRIGNORE := 2>NUL || true
	SEP := \\
	LIB_EXT := lib
else
	RM := rm -rf
	RMDIR := rm -rf
	MKDIR := mkdir -p
	ERRIGNORE := 2>/dev/null
	SEP := /
	LIB_EXT := a
endif
PSEP := $(strip $(SEP))
TARGET := libGraph.$(LIB_EXT)
VERBOSE = 0

OTHER_PARAMS := -g -I./extras/include -L./extras/lib
INCLUDE_PARAM := $(foreach dir, $(INC_DIRS), $(addprefix -I,$(dir)) )
VPATH := $(SRC_DIRS)

SOURCES := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))

OBJS := $(foreach dir,$(SRC_DIRS),$(subst $(dir),$(BUILD_DIR),$(SOURCES:.c=.o)) )

ifeq ($(VERBOSE), 1)
	HIDE =
else
	HIDE = @
endif

$(BUILD_DIR)/%.o: %.c
	$(HIDE)echo Building $@
	$(HIDE)$(CC) -c $(INCLUDE_PARAM) $(OTHER_PARAMS) -o $(subst /,$(PSEP), $@) $(subst /,$(PSEP), $<)

all: directories $(TARGET)

install: all
ifeq ($(OS),Windows_NT)

else
	install -m 755 ./lib/libGraph.a $(DEST_DIR)/lib
	install -m 644 ./include/graph.h $(DEST_DIR)/include
endif

uninstall:
ifeq ($(OS),Windows_NT)

else
	rm $(DEST_DIR)/lib/libGraph.a
	rm $(DEST_DIR)/include/graph.h
endif

$(TARGET): $(OBJS)
	$(HIDE)echo Creating $@
	$(HIDE)ar rcs $(OUTPUT_LIB_DIR)$(PSEP)$(TARGET) $(OBJS) 

directories:
	$(HIDE)$(MKDIR) $(subst /,$(PSEP),$(BUILD_DIR) $(OUTPUT_LIB_DIR)) $(ERRIGNORE)

clean:
	$(HIDE)$(RMDIR) $(subst /,$(PSEP),$(BUILD_DIR) $(OUTPUT_LIB_DIR)) $(ERRIGNORE)
	$(HIDE)echo "Cleaning done!"

.PHONY: all directories clean install uninstall
