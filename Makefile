TARGET		= graphing_wars

CC		= 
LINCC		= gcc
WINCC		= x86_64-w64-mingw32-gcc

CFLAGS		= -std=c11
DCFLAGS		= -g -ggdb3 -O0 -Wall -Werror
RCFLAGS		= -O2 -march=native -ftree-vectorize -finline-functions -funswitch-loops

LD		= 
LINLD		= gcc
WINLD		= x86_64-w64-mingw32-gcc

LDFLAGS		= 
DLDFLAGS	= $(DCFLAGS)
RLDFLAGS	= -s $(RCFLAGS)

LIBS		= 
DLIBS		= -lm -lpthread -lSDL2 -lSDL2_ttf
SLIBS		= -lm -lpthread -ldl -lasound -lpng -ljpeg -ltiff -lwebp -lX11 -lXext -lXcursor \
		  -lXinerama -lXi -lXrandr -lXxf86vm -lgbm -ldrm -lrt -lfreetype \
		  -Wl,-Bstatic -lSDL2 -lSDL2_ttf -Wl,-Bdynamic

SRCDIR		= ./src

SRC		= $(wildcard $(SRCDIR)/*.c)
INC		= $(wildcard $(SRCDIR)/*.h)

PREFIX		= build

OS ?=linux
BUILD ?=debug
ifeq ($(OS),linux)
PREFIX:=$(PREFIX)/linux
CC=$(LINCC)
LD=$(LINLD)
else ifeq ($(OS),windows)
PREFIX:=$(PREFIX)/windows
CC=$(WINCC)
LD=$(WINLD)
else
$(error $(OS) not a supported OS target)
endif

ifeq ($(BUILD),debug)
PREFIX:=$(PREFIX)/debug
CFLAGS+=$(DCFLAGS)
LDFLAGS+=$(DLDFLAGS)
LIBS+=$(DLIBS)
else ifeq ($(BUILD),release)
PREFIX:=$(PREFIX)/release
CFLAGS+=$(RCFLAGS)
LDFLAGS+=$(RLDFLAGS)
LIBS+=$(SLIBS)
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

.PHONY: run
run:
	./$(PREFIX)/bin/$(TARGET)

.PHONY: valgrind
valgrind:
	valgrind ./$(PREFIX)/bin/$(TARGET)

.PHONY: gdb
gdb:
	gdb ./$(PREFIX)/bin/$(TARGET)

.PHONY: clean
clean:
	rm -rf ./build
