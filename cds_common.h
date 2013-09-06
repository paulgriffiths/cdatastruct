/*!
 * \file            cds_common.h
 * \brief           Common data types and data for C data structures library.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_CDS_COMMON_H
#define PG_CDS_COMMON_H


/*!
 * \brief           Enumeration of return error codes.
 */

typedef enum cds_error {
    CDSERR_ERROR = -1,          /*!< Unspecified error */
    CDSERR_OUTOFRANGE = -2,     /*!< Index out of range */
    CDSERR_NOTFOUND = -3,       /*!< Data element not found */
    CDSERR_BADITERATOR = -4     /*!< Invalid iterator */
} cds_error;

#endif          /*  PG_CDS_COMMON_H  */
