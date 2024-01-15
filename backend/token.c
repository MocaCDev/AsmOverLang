#include "token.h"

void init_token(_ASM_OVER_LANG_Tokens *token, enum Tokens id, puint8 value)
{
    token->id = id;
    token->token_value = value;
}

void destroy_token(_ASM_OVER_LANG_Tokens *token)
{
    if(token)
    {
        if(token->token_value)
            free((void *)token->token_value);

        free((void *)token);
    }
}