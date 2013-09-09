# stack_calc Makefile
# ===================
# Copyright 2013 Paul Griffiths
# Email: mail@paulgriffiths.net
#
# Distributed under the terms of the GNU General Public License.
# http://www.gnu.org/licenses/

CC=gcc
CFLAGS=-std=c11 -pedantic -Wall -Wextra
CFLAGS+=-ggdb -DDEBUG -DDEBUG_ALL
LDFLAGS=-lcdatastruct -lchelpers
OBJS=stack_calc.o parser.o evaluation.o

stack_calc: $(OBJS)
	@echo "Building $@..."
	@$(CC) -o $@ $(OBJS) $(LDFLAGS)

stack_calc.o: stack_calc.c parser.h evaluation.h
	@echo "Compiling and building $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

parser.o: parser.c parser.h
	@echo "Compiling and building $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

evaluation.o: evaluation.c evaluation.h parser.h
	@echo "Compiling and building $<..."
	@$(CC) $(CFLAGS) -c -o $@ $<

