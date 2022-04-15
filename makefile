CC = gcc
LIBS = -lncurses
TARGET ?= snake

SOURCES = $(wildcard src/*.c)
OBJETCS = $(patsubst %, bin/%.o, $(notdir $(basename $(SOURCES))))
HEADERS = $(wildcard src/*.h)
VPATH += src

# ------------------------------------------------------------------------------

.PHONY: all
all: $(TARGET)

.PHONY: clean
clean:
	rm -rf  bin/*.o snake

$(TARGET): main.c $(OBJETCS) $(HEADERS)
	$(CC) $< $(OBJETCS) -o $@ $(LIBS)
	@echo "[\033[33mSnake\033[0m]: \033[4m\033[32mBuilded\033[0m"

$(OBJETCS): bin/%.o: %.c %.h
	$(CC) -c $< -o $@ $(LIBS)
	@echo "[\033[33mSnake\033[0m]: \033[4m$@\033[0m"