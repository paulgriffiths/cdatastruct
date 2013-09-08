# stack_calc Makefile
# ===================
# Copyright 2013 Paul Griffiths
# Email: mail@paulgriffiths.net
#
# Distributed under the terms of the GNU General Public License.
# http://www.gnu.org/licenses/

CC=gcc
CFLAGS=-std=c11 -pedantic -Wall -Wextra
#CFLAGS+=-ggdb -DDEBUG -DDEBUG_ALL
LDFLAGS=

stack_calc: stack_calc.c
	@echo "Compiling and building $<..."
	@$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
