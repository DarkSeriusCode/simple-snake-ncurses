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

$(OBJETCS): bin/%.o: %.c %.h
	mkdir bin -p
	$(CC) -c $< -o $@ $(LIBS)
