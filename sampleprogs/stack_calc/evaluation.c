/*!
 * \file            evaluation.c
 * \brief           Implementation of expression evaluation functions.
 * \details         Implementation of expression evaluation functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include <stdlib.h>
#include <stddef.h>
#include <assert.h>
#include <paulgrif/cdatastruct.h>
#include <paulgrif/chelpers.h>
#include "parser.h"
#include "evaluation.h"


/*!
 * \brief           Converts an infix expression to a postfix expression.
 * \details         Deletes the items in the provided list, and adds the
 * new items to the end of it.
 *
 * Function logic:
 * - Loop through each item in the original list
 * - If it's a number, append it to the list
 * - If it's an opening parenthesis, push it onto the stack
 * - If it's a closing parenthesis, pop operators from the stack until
 *   we find the opening parenthesis, appending the operators to the
 *   list as we go
 * - If the stack is empty, push the operator onto the stack.
 * - It the stack is not empty, check the top of the stack, and:
 *   - If the top of the stack is an opening parenthesis, add the operator
 *     to the stack.
 *   - If the top of the stack is an operator with a lower precedence, add
 *     the operator to the stack.
 *   - If the top of the stack is an operator with an equal or higher
 *     precedence, remove operators from the stack and append them to
 *     the list until encountering an operator with a lower precedence,
 *     or an opening parenthesis, or until emptying the stack, and then
 *     push the current operator onto the stack.
 * - After looping through the list, pop any remaining operators from
 *   the stack and append them to the list.
 *
 * \param list      A pointer to the list containing the infix expression.
 */

void infix_to_postfix(dl_list list) {
    const size_t list_length = dl_list_length(list);
    stack stk = stack_init(NULL);

    for ( size_t i = 0; i < list_length; ++i ) {
        token_t * token = dl_list_data(list, 0);

        if ( token->type == TOK_NUMBER ) {

            /*  Always append numbers to output immediately  */

            dl_list_append(list, token_dup(token));
        } else if ( token->type == TOK_OPAREN ) {

            /*  Always push opening parentheses onto stack immediately  */

            stack_push(stk, token_dup(token));
        } else if ( token->type == TOK_CPAREN ) {
            token_type last_type;

            /*  Pop operators from stack to list until
                we find the matching opening parenthesis  */

            do {
                token_t * stk_top = stack_pop(stk);
                last_type = stk_top->type;
                if ( last_type != TOK_OPAREN ) {
                    dl_list_append(list, stk_top);
                } else {
                    free(stk_top);
                }
            } while ( last_type != TOK_OPAREN );
        } else {
            token_t * stk_top;

            /*  Pop and append any non-lower precedence operators  */

            while ( (stack_length(stk) > 0) &&
                    (stk_top = stack_peek(stk)) &&
                    (token->prec <= stk_top->prec) &&
                    (stk_top->type != TOK_OPAREN) ) {
                dl_list_append(list, stack_pop(stk));
            }

            /*  Push current operator onto stack  */

            stack_push(stk, token_dup(token));
        }

        dl_list_delete_at(list, 0);
    } 

    /*  Append any operators still left on stack  */

    while ( stack_length(stk) ) {
        dl_list_append(list, stack_pop(stk));
    }

    stack_free(stk);
}


/*!
 * \brief           Evaluates a postfix expression.
 * \details         Function logic:
 * - Loop through input tokens
 * - If a token is a number, push it onto the stack
 * - If a token is an operator:
 *   - Pop the top two numbers from the stack
 *   - Apply the operator to those numbers
 *   - Push the result back onto the stack
 *
 * With a well-formed expression, after looping through all the input
 * tokens, there will be one number remaining on the stack, which will
 * be the result of the expression, so return this value.
 *
 * \param list      A dl_list containing the tokens of the expression.
 * \returns         The result of the expression.
 */

double evaluate_postfix(const dl_list list) {
    dl_list_itr itr = dl_list_first(list);
    stack stk = stack_init(NULL);

    while ( itr ) {
        token_t * op_token = itr->data;

        if ( op_token->type == TOK_NUMBER ) {
            stack_push(stk, cds_new_double(op_token->value));
        } else {
            double * operands[2] = {stack_pop(stk), stack_pop(stk)};
            double result;

            switch ( op_token->type ) {
                case TOK_ADDITION:
                    result = *operands[1] + *operands[0];
                    break;

                case TOK_SUBTRACTION:
                    result = *operands[1] - *operands[0];
                    break;

                case TOK_MULTIPLICATION:
                    result = *operands[1] * *operands[0];
                    break;

                case TOK_DIVISION:
                    result = *operands[1] / *operands[0];
                    break;

                default:
                    assert(false);
            }

            free(operands[0]);
            free(operands[1]);
            stack_push(stk, cds_new_double(result));
        }

        itr = dl_list_next(itr);
    }

    double * p_result = stack_pop(stk);
    double result = *p_result;

    free(p_result);
    stack_free(stk);

    return result;
}
