#ifndef ASM_OVER_LANG_TOKENS_H
#define ASM_OVER_LANG_TOKENS_H
#include "../common.h"

enum Tokens
{
    Left_SB,
    Right_SB,
    Expl,       /* `!` */
    SemiColon,
    EqualSign,
    RAW_keyword,
    END_keyword,
    CODE,
    EndOfFile
};

typedef struct ASM_OVER_LANG_Tokens
{
    enum Tokens     id;
    puint8          token_value;
} _ASM_OVER_LANG_Tokens;

void init_token(_ASM_OVER_LANG_Tokens *token, enum Tokens id, puint8 value);
void destroy_token(_ASM_OVER_LANG_Tokens *token);

#endif