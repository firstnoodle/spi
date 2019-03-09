# compiler
CC = gcc

# directories
INCLUDE_DIR = include
OBJ_DIR = obj
SRC_DIR = src
LIB_DIR = lib

# compiler flags
CFLAGS = -I $(INCLUDE_DIR)

# heritage lib flag...
LIBS = -lm


# define dependencies / includes
_DEPENDENCY_LIST = spi.h oled.h SSD1306_Commands.h
DEPENDENCIES = $(patsubst %, $(INCLUDE_DIR)/%, $(_DEPENDENCY_LIST))
$(info ${DEPENDENCIES})


# define object files
_OBJECT_LIST = spi.o oled.o
OBJECT_FILES = $(patsubst %, $(OBJ_DIR)/%, $(_OBJECT_LIST))
$(info ${OBJECT_FILES})


# NOT USED, but keeping for future reference
# shell runs a regular shell command -> get all .c files in /src
SOURCES := $(shell find $(SRC_DIR) -name '*.c')
$(info ${SOURCES})


# build object files..?
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(DEPENDENCIES)
	$(CC) -c -o $@ $< $(CFLAGS)

# link object files into executable..?
spi: $(OBJECT_FILES)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)


# keeps make from doing something with a file named clean
.PHONY: clean

# remove object files
clean:
	rm -f $(OBJ_DIR)/*.o *~ core $(INCDIR)/*~
