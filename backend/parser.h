#ifndef ASM_OVER_LANG_PARSER_H
#define ASM_OVER_LANG_PARSER_H
#include "lexer.h"
#include "asm_code.h"

typedef struct ASM_OVER_LANG_Parser
{
    _ASM_OVER_LANG_Lexer        *lexer;
} _ASM_OVER_LANG_Parser;

_ASM_OVER_LANG_Parser *init_parser(_ASM_OVER_LANG_Lexer *lexer);
void parser_destroy(_ASM_OVER_LANG_Parser *parser);

#endif