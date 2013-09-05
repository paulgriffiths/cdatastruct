/*!
 * \file            general.c
 * \brief           Implementation of general data structure helper functions.
 * \details         Implementation of general data structure helper functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include <paulgrif/chelpers.h>
#include "cds_general.h"

void * new_int(const int n) {
    int * p_int = term_malloc(sizeof(*p_int));
    *p_int = n;
    return p_int;
}

void * new_uint(const unsigned int n) {
    unsigned int * p_int = term_malloc(sizeof(*p_int));
    *p_int = n;
    return p_int;
}

void * new_long(const long n) {
    long * p_long = term_malloc(sizeof(*p_long));
    *p_long = n;
    return p_long;
}

void * new_ulong(const unsigned long n) {
    unsigned long * p_long = term_malloc(sizeof(*p_long));
    *p_long = n;
    return p_long;
}

void * new_string(const char * str) {
    char * new_str = term_strdup(str);
    return new_str;
}
