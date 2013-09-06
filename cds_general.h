/*!
 * \file            cds_general.h
 * \brief           Interface to general data structure helper functions.
 * \details         Interface to general data structure helper functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_CDS_GENERAL_H
#define PG_CDS_GENERAL_H


/*  Function declarations  */

#ifdef __cplusplus
extern "C" {
#endif

void * cds_new_int(const int n);
void * cds_new_uint(const unsigned int n);
void * cds_new_long(const long n);
void * cds_new_ulong(const unsigned long n);
void * cds_new_string(const char * str);

int cds_compare_int(const void * data, const void * cmp);
int cds_compare_uint(const void * data, const void * cmp);
int cds_compare_long(const void * data, const void * cmp);
int cds_compare_ulong(const void * data, const void * cmp);
int cds_compare_string(const void * data, const void * cmp);

#ifdef __cplusplus
}
#endif

#endif          /*  PG_CDS_GENERAL_H  */
