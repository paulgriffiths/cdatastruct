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
TESTOUT=unittests
SAMPLEOUT=sample

# Install paths and header files to deploy
INC_INSTALL_PREFIX=paulgrif
INC_INSTALL_PATH=$(HOME)/include/$(INC_INSTALL_PREFIX)
LIB_INSTALL_PATH=$(HOME)/lib/c
INSTALLHEADERS=cdatastruct.h cds_common.h cds_general.h cds_sl_list.h
INSTALLHEADERS+=cds_stack.h cds_dl_list.h cds_queue.h

# Compiler and archiver executable names
AR=ar
CC=gcc
CXX=g++

# Archiver flags
ARFLAGS=rcs

# Compiler flags
CFLAGS=-std=c99 -pedantic -Wall -Wextra
C_DEBUG_FLAGS=-ggdb -DDEBUG -DDEBUG_ALL
C_RELEASE_FLAGS=-O3 -DNDEBUG
CXXFLAGS=-std=c++11 -pedantic -Wall -Wextra -Weffc++
CXX_TEST_FLAGS=-std=c++11 -pedantic -Wall -Wextra
CXX_DEBUG_FLAGS=-ggdb -DDEBUG -DDEBUG_ALL
CXX_RELEASE_FLAGS=-O3 -DNDEBUG

# Linker flags
LDFLAGS=
LD_TEST_FLAGS=-lboost_system -lboost_thread -lboost_unit_test_framework
LD_TEST_FLAGS+=-lstdc++
LD_TEST_FLAGS+=-l$(LIBNAME) -L$(CURDIR) -lchelpers

# Object code files
OBJS=general.o sl_list.o dl_list.o stack.o queue.o

TESTOBJS=tests/test_main.o
TESTOBJS+=tests/test_sl_list.o
TESTOBJS+=tests/test_dl_list.o
TESTOBJS+=tests/test_stack.o

# Source and clean files and globs
SRCS=$(wildcard *.c *.h)
SRCS=$(wildcard tests/*.cpp)

SRCGLOB=*.c
SRCGLOB+=tests/*.cpp

CLNGLOB=$(OUT) $(TESTOUT) $(SAMPLEOUT)
CLNGLOB+=*~ *.o *.gcov *.out *.gcda *.gcno
CLNGLOB+=tests/*~ tests/*.o tests/*.gcov tests/*.out tests/*.gcda tests/*.gcno


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
tests: CXXFLAGS=$(CXX_TEST_FLAGS)
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
sample: LDFLAGS+=-l$(LIBNAME) -lchelpers
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

# Unit tests executable
testmain: $(TESTOBJS)
	@echo "Linking unit tests..."
	@$(CXX) -o $(TESTOUT) $(TESTOBJS) $(LDFLAGS)

# Object files targets section
# ============================

# Sample program

main.o: main.c
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<


# Object files for library

general.o: general.c cds_general.h cds_common.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

sl_list.o: sl_list.c cds_sl_list.h sl_list.h cds_common.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

dl_list.o: dl_list.c cds_dl_list.h dl_list.h cds_common.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

stack.o: stack.c cds_stack.h sl_list.h cds_sl_list.h cds_common.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

queue.o: queue.c cds_queue.h dl_list.h cds_dl_list.h cds_common.h
	@echo "Compiling $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

# Unit tests

tests/test_main.o: tests/test_main.cpp
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_sl_list.o: tests/test_sl_list.cpp
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_dl_list.o: tests/test_dl_list.cpp
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_stack.o: tests/test_stack.cpp
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

tests/test_queue.o: tests/test_queue.cpp
	@echo "Compiling $<..."
	@$(CXX) $(CXXFLAGS) -c -o $@ $<

