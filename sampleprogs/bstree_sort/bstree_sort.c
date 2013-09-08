/*!
 * \file            bstree_sort.c
 * \brief           A demonstration of using a bs_tree to sort lines of text.
 * \details         Invoke from the command line specifying a file containing
 * lines of text. The example file `50_random_words` is provided as an
 * illustration.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <paulgrif/cdatastruct.h>
#include <paulgrif/chelpers.h>


/*!
 * \brief           Macro defining maximum `char` buffer size.
 */

#define MAX_BUFFER_SIZE 1024


/*  Function prototypes  */

static FILE * get_file_from_cmdline(int argc, char ** argv );
static void populate_tree(FILE * fp, bs_tree tree);
static void print_node(void * str, void * line);


/*!
 * \brief           `main()` function.
 * \param argc      The number of command line arguments.
 * \param argv      The command line arguments.
 * \returns         The exit status.
 */

int main(int argc, char ** argv) {
    int line = 1;

    /*  Open file specified on command line  */

    FILE * fp = get_file_from_cmdline(argc, argv);
    if ( fp == NULL ) {
        return EXIT_FAILURE;
    }

    /*  Initialize and populate binary search tree  */

    bs_tree tree = bs_tree_init(cds_compare_string, NULL);
    populate_tree(fp, tree);

    /*  Print sorted input via inorder left traverse of tree  */

    bst_inorder_left_traverse(tree, print_node, &line);

    /*  Free tree and close file  */

    bs_tree_free(tree);

    if ( fclose(fp) != 0 ) {
        fprintf(stderr, "bstree_sort: couldn't close file (%s)\n",
                    strerror(errno));
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


/*!
 * \brief           Opens a file specified on the command line.
 * \param argc      Number of command line arguments, from `main()`.
 * \param argv      Command line arguments, from `main()`.
 * \returns         A FILE pointer to the file opened for reading, or
 * NULL on failure.
 */

FILE * get_file_from_cmdline(int argc, char ** argv ) {
    static const char * usagemsg = "Usage: bstree_sort [filename]";

    /*  Fail unless exactly one command line argument is specified  */

    if ( argc != 2 ) {
        printf("%s\n", usagemsg);
        return NULL;
    }

    /*  Try to open the specified file for reading  */

    FILE * fp = fopen(argv[1], "r");
    if ( fp == NULL ) {
        fprintf(stderr, "bstree_sort: couldn't open file (%s)\n",
                    strerror(errno));
        return NULL;
    }

    return fp;
}


/*!
 * \brief           Populates a bs_tree with lines read from a file.
 * \param fp        A FILE pointer to the input file.
 * \param tree      A pointer to the bs_tree.
 */

void populate_tree(FILE * fp, bs_tree tree) {
    char buffer[MAX_BUFFER_SIZE];

    while ( fgets(buffer, sizeof(buffer), fp) ) {
        trim(buffer);
        bs_tree_insert(tree, cds_new_string(buffer));
    }
}


/*!
 * \brief           Function to print an indexed tree node.
 * \details         This function will be passed to a bs_tree traversal
 * function, and will be called for each individual node.
 * \param str       A `void` pointer to a string, which is the data
 * contained in each node.
 * \param line      A pointer to an `int` containing the current line
 * number.
 */

void print_node(void * str, void * line) {
    int * p_line = line;
    char * p_str = str;
    printf("%d: %s\n", *p_line, p_str);
    ++*p_line;
}
