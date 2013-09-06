/*!
 * \file            main.c
 * \brief           Sample program for C data structures library.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <paulgrif/cdatastruct.h>


void print_list(sl_list list);

/*!
 * \brief       Main function.
 * \details     Main function.
 * \returns     Exit status.
 */

int main(void) {

    sl_list list = sl_list_init(cds_compare_string);
    char * items[] = {"spam", "eggs", "bacon", "chicken", "yoghurt"};

    for ( size_t i = 0; i < sizeof(items) / sizeof(*items); ++i ) {
        sl_list_prepend(list, cds_new_string(items[i]));
    }

    printf("Before insertion...\n");
    print_list(list);

    printf("\nAfter insertion at 2...\n");
    sl_list_insert_at(list, 2, cds_new_string("fries"));
    print_list(list);

    printf("\nAfter insertion at 0...\n");
    sl_list_insert_at(list, 0, cds_new_string("frosties"));
    print_list(list);

    printf("\nAfter insertion at end...\n");
    sl_list_insert_at(list, sl_list_length(list), cds_new_string("toffee"));
    print_list(list);

    int index = sl_list_find(list, "bacon");
    if ( index > 0 ) {
        printf("'bacon' found at index %d\n", index);
    } else {
        printf("'bacon' not found.\n");
    }

    index = sl_list_find(list, "gruel");
    if ( index > 0 ) {
        printf("'gruel' found at index %d\n", index);
    } else {
        printf("'gruel' not found.\n");
    }

    sl_list_itr itr = sl_list_index(list, 4);
    printf("Data at index 4 is %s.\n", (char *) itr->data);
    printf("Data at index 3 is %s.\n", (char *) sl_list_data(list, 3));

    sl_list_free(list);

    return EXIT_SUCCESS;
}

void print_list(sl_list list) {
    size_t index = 0;
    sl_list_itr itr = sl_list_first(list);

    while ( itr ) {
        printf("%zu: %s\n", index++, (char *) itr->data);
        itr = sl_list_next(itr);
    }
}

