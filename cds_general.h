/*!
 * \file            general.h
 * \brief           Interface to general data structure helper functions.
 * \details         Interface to general data structure helper functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_DS_GENERAL_H
#define PG_DS_GENERAL_H

void * new_int(const int n);
void * new_uint(const unsigned int n);
void * new_long(const long n);
void * new_ulong(const unsigned long n);
void * new_string(const char * str);

#endif          /*  PG_DS_GENERAL_H  */
