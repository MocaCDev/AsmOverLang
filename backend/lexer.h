#ifndef ASM_OVER_LANG_LEXER_H
#define ASM_OVER_LANG_LEXER_H
#include "token.h"

static puint8 string = NULL;

typedef struct ASM_OVER_LANG_Lexer
{
    _ASM_OVER_LANG_Tokens   *token;
    size_t                  index;
    size_t                  file_size;
    puint8                  data;
    uint32                  line;
    uint8                   current_char;
} _ASM_OVER_LANG_Lexer;

_ASM_OVER_LANG_Lexer *init_lexer(const puint8 filename);
void destroy_lexer(_ASM_OVER_LANG_Lexer *lexer);
void get_token(_ASM_OVER_LANG_Lexer *lexer);
void get_code(_ASM_OVER_LANG_Lexer *lexer);

#endif
