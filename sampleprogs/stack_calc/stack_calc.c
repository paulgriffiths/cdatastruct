/*!
 * \file            stack_calc.c
 * \brief           Entry point to stack_calc
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <paulgrif/cdatastruct.h>
#include "parser.h"
#include "evaluation.h"


/*!
 * \brief           Maximum character buffer length.
 */

#define MAX_BUFFER_LEN 1024


/*  Function prototypes  */

void print_token_list(const dl_list list);
void get_input(char * buffer, const size_t length);


/*!
 * \brief           `main()` function.
 * \returns         Exit status.
 */

int main(void) {
    dl_list list = dl_list_init(NULL, NULL);
    char buffer[MAX_BUFFER_LEN];

    get_input(buffer, sizeof(buffer));
    bool unrecognized_token = parse_input(buffer, list);

    printf("Infix token list:\n");
    print_token_list(list);

    if ( unrecognized_token ) {
        printf("Bad input - unrecognized tokens.\n");
    }

    infix_to_postfix(list);
    printf("\nPostfix token list:\n");
    print_token_list(list);

    double result = evaluate_postfix(list);

    printf("The result is: %f\n", result);

    dl_list_free(list);

    return EXIT_SUCCESS;
}


/*!
 * \brief           Prints a dump of the token list.
 * \param list      A pointer to the list.
 */

void print_token_list(const dl_list list) {
    int count = 1;
    dl_list_itr itr = dl_list_first(list);

    while ( itr ) {
        token_t * token = itr->data;

        switch ( token->type ) {
            case TOK_NUMBER:
                printf("%d: %f\n", count, token->value);
                break;

            case TOK_UNKNOWN:
                printf("%d: unknown token '%c'\n", count, token->c);
                break;

            default:
                printf("%d: %c\n", count, token->c);
        }

        ++count;
        itr = dl_list_next(itr);
    }
}


void get_input(char * buffer, const size_t length) {
    printf("Enter expression: ");
    fflush(stdout);
    if ( fgets(buffer, length, stdin) == NULL ) {
        fprintf(stderr, "stack_calc: error getting input\n");
        exit(EXIT_FAILURE);
    }
}
