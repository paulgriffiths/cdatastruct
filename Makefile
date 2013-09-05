# cdatastruct makefile
# ====================
# Copyright 2013 Paul Griffiths
# Email: mail@paulgriffiths.net
#
# Distributed under the terms of the GNU General Public License.
# http://www.gnu.org/licenses/


# Variables section
# =================

# Library and executable names
LIBNAME=cdatastruct
OUT=lib$(LIBNAME).a
SAMPLEOUT=sample

# Install paths and header files to deploy
INC_INSTALL_PREFIX=paulgrif
INC_INSTALL_PATH=$(HOME)/include/$(INC_INSTALL_PREFIX)
LIB_INSTALL_PATH=$(HOME)/lib/c
INSTALLHEADERS=

# Compiler and archiver executable names
AR=ar
CC=gcc

# Archiver flags
ARFLAGS=rcs

# Compiler flags
CFLAGS=-ansi -pedantic -Wall -Wextra
C_DEBUG_FLAGS=-ggdb -DDEBUG -DDEBUG_ALL
C_RELEASE_FLAGS=-O3 -DNDEBUG

# Linker flags
LDFLAGS=

# Object code files
OBJS=mainlib.o

# Source and clean files and globs
SRCS=$(wildcard *.c *.h)

SRCGLOB=*.c

CLNGLOB=$(OUT) $(SAMPLEOUT)
CLNGLOB+=*~ *.o *.gcov *.out *.gcda *.gcno


# Build targets section
# =====================

default: debug

# debug - builds objects with debugging info
.PHONY: debug
debug: CFLAGS+=$(C_DEBUG_FLAGS)
debug: main

# release - builds with optimizations and without debugging info
.PHONY: release
release: CFLAGS+=$(C_RELEASE_FLAGS)
release: main

# tests - builds unit tests
.PHONY: tests
tests: CFLAGS+=$(C_TEST_FLAGS)
tests: LDFLAGS+=$(LD_TEST_FLAGS)
tests: testmain

# install - installs library and headers
.PHONY: install
install:
	@if [ ! -d $(INC_INSTALL_PATH) ]; then \
		mkdir $(INC_INSTALL_PATH); fi
	@echo "Copying library to $(LIB_INSTALL_PATH)..."
	@cp $(OUT) $(LIB_INSTALL_PATH)
	@echo "Copying headers to $(INC_INSTALL_PATH)..."
	@cp $(INSTALLHEADERS) $(INC_INSTALL_PATH)
	@echo "Done."

# sample - makes sample program
.PHONY: sample
sample: LDFLAGS+=-l$(LIBNAME)
sample: main.o
	@echo "Linking sample program..."
	@$(CC) -o $(SAMPLEOUT) main.o $(LDFLAGS)
	@echo "Done."

# clean - removes ancilliary files from working directory
.PHONY: clean
clean:
	-@rm $(CLNGLOB) 2>/dev/null

# docs - makes Doxygen documentation:
.PHONY: docs
docs:
	@doxygen
	-@cd latex; make; cd ..
	@if [ ! -d docs ]; then \
		mkdir docs; fi
	@echo "Copying reference manual to docs..."
	@cp latex/refman.pdf docs 
	@echo "Done."

# lint - runs splint with specified options
.PHONY: lint
lint:
	@splint +unix-lib -unrecog $(SRCGLOB)

# linteasy - runs splint with weak checking
.PHONY: linteasy
linteasy:
	@splint -weak +unix-lib -unrecog $(SRCGLOB)


# Executable targets section
# ==========================

# Main library
main: $(OBJS)
	@echo "Building library..."
	@$(AR) $(ARFLAGS) $(OUT) $(OBJS)
	@echo "Done."


# Object files targets section
# ============================

# Sample program

main.o: main.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<


# Object files for library

mainlib.o: mainlib.c mainlib.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<
