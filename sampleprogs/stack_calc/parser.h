/*!
 * \file            parser.h
 * \brief           Interface to expression parsing functions.
 * \details         Interface to expression parsing functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#ifndef PG_STACK_CALC_PARSER_H
#define PG_STACK_CALC_PARSER_H


#include <stdbool.h>
#include <stddef.h>


/*!
 * \brief           Enumeration of types of recognized tokens.
 */

typedef enum token_type {
    TOK_OPAREN,
    TOK_CPAREN,
    TOK_ADDITION,
    TOK_SUBTRACTION,
    TOK_MULTIPLICATION,
    TOK_DIVISION,
    TOK_MODULO,
    TOK_NUMBER,
    TOK_UNKNOWN
} token_type;


/*!
 * \brief           Struct to hold a token.
 */

typedef struct token_t {
    token_type type;        /*!< The type of the token */
    char c;                 /*!< The character representation for operators */
    int prec;               /*!< The precedence of the token */
    double value;           /*!< The value of the token, for numbers */
} token_t;


/*  Function prototypes  */

bool parse_input(const char * input, dl_list list);
void * token_dup(const token_t * src);


#endif          /*  PG_STACK_CALC_PARSER_H  */
