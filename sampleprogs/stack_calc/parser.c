/*!
 * \file            parser.c
 * \brief           Implementation of expression parsing functions.
 * \details         Implementation of expression parsing functions.
 * \author          Paul Griffiths
 * \copyright       Copyright 2013 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */


#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <paulgrif/chelpers.h>
#include <paulgrif/cdatastruct.h>
#include "parser.h"


/*!
 * \brief           Array of known operator token definitions.
 */

static const token_t token_defs[] = {
    {TOK_OPAREN, '(', 99, 0},
    {TOK_CPAREN, ')', 98, 0},
    {TOK_ADDITION, '+', 1, 0},
    {TOK_SUBTRACTION, '-', 1, 0},
    {TOK_MULTIPLICATION, '*', 2, 0},
    {TOK_DIVISION, '/', 2, 0},
    {TOK_MODULO, '%', 2, 0}
};


/*  Function prototypes  */

static const char * get_next_token(const char * input, token_t * token);
static void copy_token(token_t * dest, const token_t * src);


/*!
 * \brief           Parses a line of inputs into tokens.
 * \param input     The line of input to parse.
 * \param list      A pointer to a dl_list in which to store the tokens.
 * \returns         'true' on successful parsing, 'false' if an unrecognized
 * token was encountered.
 */

bool parse_input(const char * input, dl_list list) {
    const char * inp_ptr = input;
    bool unrecognized_token = false;
    token_t token;

    while ( *inp_ptr ) {
        if ( isspace(*inp_ptr) ) {
            ++inp_ptr;
        } else {
            inp_ptr = get_next_token(inp_ptr, &token);
            dl_list_append(list, token_dup(&token));
            if ( token.type == TOK_UNKNOWN ) {
                unrecognized_token = true;
            }
        }
    }

    return unrecognized_token;
}


/*!
 * \brief           Gets the next token from a line of input.
 * \param input     The line of input to parse.
 * \param token     A pointer to a token_t in which to store the result.
 * \returns         A pointer to the next character of input.
 */

const char * get_next_token(const char * input, token_t * token) {
    bool operator_token = false;
    bool number_token = false;
    const char * next_input = input;

    /*  Initialize token to unknown token  */

    token->type = TOK_UNKNOWN;
    token->c = '\0';
    token->prec = -1;
    token->value = 0;

    /*  Check for operator token  */

    for ( size_t i = 0;
          !operator_token && i < sizeof(token_defs) / sizeof(*token_defs);
          ++i ) {
        if ( *input == token_defs[i].c ) {
            copy_token(token, &token_defs[i]);
            operator_token = true;
            ++next_input;
        }
    }

    /*  Check for number token  */

    if ( !operator_token ) {
        char * endptr;
        double value = strtod(input, &endptr);
        if ( input != endptr ) {
            token->type = TOK_NUMBER;
            token->c = '\0';
            token->prec = -1;
            token->value = value;
            next_input = endptr;
            number_token = true;
        }
    }

    /*  Respond to unknown token  */

    if ( !operator_token && !number_token ) {
        token->c = *input;
        ++next_input;
    }

    return next_input;
}


/*!
 * \brief           Copies one token_t to another.
 * \param dest      A pointer to the destination token.
 * \param src       A pointer to the source token.
 */

void copy_token(token_t * dest, const token_t * src) {
    dest->type = src->type;
    dest->c = src->c;
    dest->prec = src->prec;
    dest->value = src->value;
}


/*!
 * \brief           Allocates memory for a new token, and copies an
 * existing token into it.
 * \param src       A pointer to the token to copy.
 * \returns         A `void` pointer to the newly allocated token. The
 * caller is responsible for `free()`ing this memory.
 */

void * token_dup(const token_t * src) {
    token_t * new_token = term_malloc(sizeof(*new_token));
    copy_token(new_token, src);
    return new_token;
}
