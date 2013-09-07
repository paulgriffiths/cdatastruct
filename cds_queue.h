/*!
 * \file            cds_queue.h
 * \brief           User interface to queue data structure
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_CDS_QUEUE_H
#define PG_CDS_QUEUE_H

#include <stddef.h>
#include <stdbool.h>

/*!
 * \brief           Typedef for queue pointer.
 */

typedef struct dl_list_t * queue;


/*  Function declarations  */

#ifdef __cplusplus
extern "C" {
#endif

queue queue_init(void (*free_func)(void *));
void queue_free(queue que);
size_t queue_length(const queue que);
bool queue_isempty(const queue que);
void * queue_pop(queue que);
void queue_pushback(queue que, void * data);

#ifdef __cplusplus
}
#endif


#endif          /*  PG_CDS_QUEUE_H  */
