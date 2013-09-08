# bstree_sort Makefile
# ====================
# Copyright 2013 Paul Griffiths
# Email: mail@paulgriffiths.net
#
# Distributed under the terms of the GNU General Public License.
# http://www.gnu.org/licenses/

CC=gcc
CFLAGS=-std=c11 -pedantic -Wall -Wextra
LDFLAGS=-lcdatastruct -lchelpers

bstree_sort: bstree_sort.c
	@echo "Compiling and building $<..."
	@$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
