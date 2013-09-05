/*!
 * \file            main.c
 * \brief           Main function for cdatastruct.
 * \details         Main function for cdatastruct.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <paulgrif/cdatastruct.h>


/*!
 * \brief       Main function.
 * \details     Main function.
 * \returns     Exit status.
 */

int main(void) {

    sl_list list = sl_list_init();
    char * items[] = {"spam", "eggs", "bacon", "chicken", "yoghurt"};

    for ( size_t i = 0; i < sizeof(items) / sizeof(*items); ++i ) {
        sl_list_insert_front(list, new_string(items[i]));
    }

    printf("Before insertion...\n");
    sl_list_itr itr = sl_list_first(list);
    while ( itr ) {
        printf("%s\n", itr->data);
        itr = sl_list_next(itr);
    }

    printf("\nAfter insertion at 2...\n");
    sl_list_insert_at(list, 2, new_string("fries"));

    itr = sl_list_first(list);
    while ( itr ) {
        printf("%s\n", itr->data);
        itr = sl_list_next(itr);
    }

    printf("\nAfter insertion at 0...\n");
    sl_list_insert_at(list, 0, new_string("frosties"));

    itr = sl_list_first(list);
    while ( itr ) {
        printf("%s\n", itr->data);
        itr = sl_list_next(itr);
    }

    printf("\nAfter insertion at end...\n");
    sl_list_insert_at(list, sl_list_length(list), new_string("jaffa cakes"));

    itr = sl_list_first(list);
    while ( itr ) {
        printf("%s\n", itr->data);
        itr = sl_list_next(itr);
    }

    sl_list_free(list);

    return EXIT_SUCCESS;
}
