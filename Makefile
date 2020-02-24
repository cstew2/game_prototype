TARGET		= graphing_wars

CC		= 
LINCC		= gcc
WINCC		= gcc
CFLAGS		= -std=c11 -I$(INCDIR)
DCFLAGS		= -g -ggdb3 -O0 -Wall -Werror
RCFLAGS		= -02 -march=native -ftree-vectorize finline-functions -funswitch-loops

LD		= gcc
LDFLAGS		= 
DLDFLAGS	=
RLDFLAGS	= -s 

LIBS		= -lSDL2 -lSDL2_image

SRCDIR		= ./src

SRC		= $(wildcard $(SRCDIR)/*.c)
INC		= $(wildcard $(SRCDIR)/*.h)

PREFIX		= build

OS=linux
BUILD=debug
ifeq ($(OS),linux)
PREFIX:=$(PREFIX)/linux
CC=$(LINCC)
else ifeq ($(OS),windows)
PREFIX:=$(PREFIX)windows
CC=$(WINCC)
else
$(error OS not found)
endif

ifeq ($(BUILD),debug)
PREFIX:=$(PREFIX)/debug
CFLAGS+=$(DCFLAGS)
LDFLAGS+=$(DLDFLAGS)
else ifeq ($(BUILD),release)
PREFIX:=$(PREFIX)/release
CFLAGS+=$(RCFLAGS)
LDFLAGS+=$(RLDFLAGS)
else
$(error BUILD not found)
endif

$(info $(shell mkdir -p $(PREFIX)/obj $(PREFIX)/bin))
$(info ${PREFIX})
OBJ=$(patsubst %.c,$(PREFIX)/obj/%.o,$(SRC:$(SRCDIR)/%=%))

$(PREFIX)/obj/%.o:$(SRCDIR)/%.c $(SRCDIR)/%.h
	$(CC) $(CFLAGS) -c $< -o $@

$(PREFIX)/bin/$(TARGET): $(OBJ)
	$(LD) $(LDFLAGS) $(OBJ) -o $@ $(LIBS)

run:
	./$(PREFIX)/bin/$(TARGET)

clean:
	rm -rf ./build
