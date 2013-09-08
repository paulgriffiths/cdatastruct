/*!
 * \file            general.c
 * \brief           Implementation of general data structure helper functions.
 * \details         Implementation of general data structure helper functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include <string.h>
#include <paulgrif/chelpers.h>
#include "cds_general.h"


/*!
 * \brief           Dynamically allocates memory for a new `int`.
 * \param n         The new `int` for which to allocate.
 * \returns         A `void` pointer to the allocated memory.
 */

void * cds_new_int(const int n) {
    int * p_int = term_malloc(sizeof(*p_int));
    *p_int = n;
    return p_int;
}


/*!
 * \brief           Dynamically allocates memory for a new `unsigned int`.
 * \param n         The new `unsigned int` for which to allocate.
 * \returns         A `void` pointer to the allocated memory.
 */

void * cds_new_uint(const unsigned int n) {
    unsigned int * p_int = term_malloc(sizeof(*p_int));
    *p_int = n;
    return p_int;
}


/*!
 * \brief           Dynamically allocates memory for a new `long`.
 * \param n         The new `long` for which to allocate.
 * \returns         A `void` pointer to the allocated memory.
 */

void * cds_new_long(const long n) {
    long * p_long = term_malloc(sizeof(*p_long));
    *p_long = n;
    return p_long;
}


/*!
 * \brief           Dynamically allocates memory for a new `unsigned long`.
 * \param n         The new `unsigned long` for which to allocate.
 * \returns         A `void` pointer to the allocated memory.
 */

void * cds_new_ulong(const unsigned long n) {
    unsigned long * p_long = term_malloc(sizeof(*p_long));
    *p_long = n;
    return p_long;
}


/*!
 * \brief           Dynamically allocates memory for a new `long long`.
 * \param n         The new `long long` for which to allocate.
 * \returns         A `void` pointer to the allocated memory.
 */

void * cds_new_longlong(const long long n) {
    long long * p_longlong = term_malloc(sizeof(*p_longlong));
    *p_longlong = n;
    return p_longlong;
}


/*!
 * \brief           Allocates memory for a new `unsigned long long`.
 * \param n         The new `unsigned long long` for which to allocate.
 * \returns         A `void` pointer to the allocated memory.
 */

void * cds_new_ulonglong(const unsigned long long n) {
    unsigned long long * p_longlong = term_malloc(sizeof(*p_longlong));
    *p_longlong = n;
    return p_longlong;
}


/*!
 * \brief           Dynamically allocates memory for a new `float`.
 * \param f         The new `float` for which to allocate.
 * \returns         A `void` pointer to the allocated memory.
 */

void * cds_new_float(const float f) {
    float * p_float = term_malloc(sizeof(*p_float));
    *p_float = f;
    return p_float;
}


/*!
 * \brief           Dynamically allocates memory for a new `double`.
 * \param f         The new `double` for which to allocate.
 * \returns         A `void` pointer to the allocated memory.
 */

void * cds_new_double(const double f) {
    double * p_double = term_malloc(sizeof(*p_double));
    *p_double = f;
    return p_double;
}


/*!
 * \brief           Dynamically allocates memory for a new string.
 * \param str       The new string for which to allocate.
 * \returns         A `void` pointer to the allocated memory.
 */

void * cds_new_string(const char * str) {
    char * new_str = term_strdup(str);
    return new_str;
}


/*!
 * \brief           Compares two `int` via `void` pointers.
 * \param data      Pointer to the data to which to compare.
 * \param cmp       Pointer to the comparison data.
 * \returns         -1 if the comparison data is greater than the data,
 * 1 if the comparison data is less than the data, and 0 if the comparison
 * data is equal to the data.
 */

int cds_compare_int(const void * data, const void * cmp) {
    int result;
    int n_data = *((int *) data);
    int n_cmp = *((int *) cmp);

    if ( n_data < n_cmp ) {
        result = -1;
    } else if ( n_data > n_cmp ) {
        result = 1;
    } else {
        result = 0;
    }

    return result;
}


/*!
 * \brief           Compares two `unsigned int` via `void` pointers.
 * \param data      Pointer to the data to which to compare.
 * \param cmp       Pointer to the comparison data.
 * \returns         -1 if the comparison data is greater than the data,
 * 1 if the comparison data is less than the data, and 0 if the comparison
 * data is equal to the data.
 */

int cds_compare_uint(const void * data, const void * cmp) {
    int result;
    unsigned int n_data = *((unsigned int *) data);
    unsigned int n_cmp = *((unsigned int *) cmp);

    if ( n_data < n_cmp ) {
        result = -1;
    } else if ( n_data > n_cmp ) {
        result = 1;
    } else {
        result = 0;
    }

    return result;
}


/*!
 * \brief           Compares two `long` via `void` pointers.
 * \param data      Pointer to the data to which to compare.
 * \param cmp       Pointer to the comparison data.
 * \returns         -1 if the comparison data is greater than the data,
 * 1 if the comparison data is less than the data, and 0 if the comparison
 * data is equal to the data.
 */

int cds_compare_long(const void * data, const void * cmp) {
    int result;
    long n_data = *((long *) data);
    long n_cmp = *((long *) cmp);

    if ( n_data < n_cmp ) {
        result = -1;
    } else if ( n_data > n_cmp ) {
        result = 1;
    } else {
        result = 0;
    }

    return result;
}


/*!
 * \brief           Compares two `unsigned long` via `void` pointers.
 * \param data      Pointer to the data to which to compare.
 * \param cmp       Pointer to the comparison data.
 * \returns         -1 if the comparison data is greater than the data,
 * 1 if the comparison data is less than the data, and 0 if the comparison
 * data is equal to the data.
 */

int cds_compare_ulong(const void * data, const void * cmp) {
    int result;
    unsigned long n_data = *((unsigned long *) data);
    unsigned long n_cmp = *((unsigned long *) cmp);

    if ( n_data < n_cmp ) {
        result = -1;
    } else if ( n_data > n_cmp ) {
        result = 1;
    } else {
        result = 0;
    }

    return result;
}


/*!
 * \brief           Compares two `long long` via `void` pointers.
 * \param data      Pointer to the data to which to compare.
 * \param cmp       Pointer to the comparison data.
 * \returns         -1 if the comparison data is greater than the data,
 * 1 if the comparison data is less than the data, and 0 if the comparison
 * data is equal to the data.
 */

int cds_compare_longlong(const void * data, const void * cmp) {
    int result;
    long long n_data = *((long long *) data);
    long long n_cmp = *((long long *) cmp);

    if ( n_data < n_cmp ) {
        result = -1;
    } else if ( n_data > n_cmp ) {
        result = 1;
    } else {
        result = 0;
    }

    return result;
}


/*!
 * \brief           Compares two `unsigned long long` via `void` pointers.
 * \param data      Pointer to the data to which to compare.
 * \param cmp       Pointer to the comparison data.
 * \returns         -1 if the comparison data is greater than the data,
 * 1 if the comparison data is less than the data, and 0 if the comparison
 * data is equal to the data.
 */

int cds_compare_ulonglong(const void * data, const void * cmp) {
    int result;
    unsigned long long n_data = *((unsigned long long *) data);
    unsigned long long n_cmp = *((unsigned long long *) cmp);

    if ( n_data < n_cmp ) {
        result = -1;
    } else if ( n_data > n_cmp ) {
        result = 1;
    } else {
        result = 0;
    }

    return result;
}


/*!
 * \brief           Compares two `float` via `void` pointers.
 * \param data      Pointer to the data to which to compare.
 * \param cmp       Pointer to the comparison data.
 * \returns         -1 if the comparison data is greater than the data,
 * 1 if the comparison data is less than the data, and 0 if the comparison
 * data is equal to the data.
 */

int cds_compare_float(const void * data, const void * cmp) {
    int result;
    float n_data = *((float *) data);
    float n_cmp = *((float *) cmp);

    if ( n_data < n_cmp ) {
        result = -1;
    } else if ( n_data > n_cmp ) {
        result = 1;
    } else {
        result = 0;
    }

    return result;
}


/*!
 * \brief           Compares two `double` via `void` pointers.
 * \param data      Pointer to the data to which to compare.
 * \param cmp       Pointer to the comparison data.
 * \returns         -1 if the comparison data is greater than the data,
 * 1 if the comparison data is less than the data, and 0 if the comparison
 * data is equal to the data.
 */

int cds_compare_double(const void * data, const void * cmp) {
    int result;
    double n_data = *((double *) data);
    double n_cmp = *((double *) cmp);

    if ( n_data < n_cmp ) {
        result = -1;
    } else if ( n_data > n_cmp ) {
        result = 1;
    } else {
        result = 0;
    }

    return result;
}


/*!
 * \brief           Compares two strings via `void` pointers.
 * \param data      Pointer to the data to which to compare.
 * \param cmp       Pointer to the comparison data.
 * \returns         -1 if the comparison data is greater than the data,
 * 1 if the comparison data is less than the data, and 0 if the comparison
 * data is equal to the data.
 */

int cds_compare_string(const void * data, const void * cmp) {
    return strcmp(data, cmp);
}
