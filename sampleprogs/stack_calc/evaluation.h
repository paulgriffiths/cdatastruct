/*!
 * \file            evaluation.h
 * \brief           Interface to expression evaluation functions.
 * \details         Interface to expression evaluation functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_STACK_CALC_EXPRESSION_H
#define PG_STACK_CALC_EXPRESSION_H

void infix_to_postfix(dl_list list);
double evaluate_postfix(const dl_list list);

#endif          /*  PG_STACK_CALC_EXPRESSION_H  */
