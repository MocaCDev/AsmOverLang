#include "parser.h"

/* `parser.c` only. */
void parser_get_next(_ASM_OVER_LANG_Parser *);
void parser_get_code(_ASM_OVER_LANG_Parser *);
void parser_begin(_ASM_OVER_LANG_Parser *);
void parse_expl(_ASM_OVER_LANG_Parser *);

_ASM_OVER_LANG_Parser *init_parser(_ASM_OVER_LANG_Lexer *lexer)
{
    _ASM_OVER_LANG_Parser *parser = (_ASM_OVER_LANG_Parser *)calloc(1, sizeof(*parser));

    parser->lexer = lexer;
    get_token(parser->lexer);

    parser_begin(parser);

    return parser;
}

void parser_destroy(_ASM_OVER_LANG_Parser *parser)
{
    destroy_lexer(parser->lexer);
    //destroy_token(parser->lexer->token);
    free((void *)parser);
}

void parser_get_next(_ASM_OVER_LANG_Parser *parser)
{
    get_token(parser->lexer);
}

void parser_get_code(_ASM_OVER_LANG_Parser *parser)
{
    get_code(parser->lexer);
}

void parser_begin(_ASM_OVER_LANG_Parser *parser)
{
    while(!(parser->lexer->token->id == EndOfFile))
    {
        switch(parser->lexer->token->id)
        {
            case Expl: parse_expl(parser);break;
            default: break;
        }

        parser_get_next(parser);
    }

    parser_destroy(parser);
}

void parse_expl(_ASM_OVER_LANG_Parser *parser)
{
    parser_get_next(parser);

    ASM_OVER_LANG_ASSERT(parser->lexer->token->id == Left_SB,
        "Expected `[` after `!` but instead got `%s` on line %d\n",
        parser->lexer->token->token_value, parser->lexer->line)

    parser_get_next(parser);
    
    switch(parser->lexer->token->id)
    {
        case RAW_keyword:
        {
            parser_get_next(parser);
            ASM_OVER_LANG_ASSERT(parser->lexer->token->id == Right_SB,
                "Expected `]` at end of %d, instead got `%s`\n",
                parser->lexer->line, parser->lexer->token->token_value)
            
            parser_get_code(parser);
            raw_add(parser->lexer->token->token_value);
            write_code();

            memset(parser->lexer->token->token_value, 0, strlen(parser->lexer->token->token_value));
            free((void *)parser->lexer->token->token_value);
            
            parser_get_next(parser);
            ASM_OVER_LANG_ASSERT(parser->lexer->token->id == Expl,
                "Expected `!` on line %d, instead got `%s`\n",
                parser->lexer->line, parser->lexer->token->token_value)
            
            parser_get_next(parser);
            ASM_OVER_LANG_ASSERT(parser->lexer->token->id == Left_SB,
                "Expected `[` on line %d, instead got `%s`\n",
                parser->lexer->line, parser->lexer->token->token_value)
            
            parser_get_next(parser);
            ASM_OVER_LANG_ASSERT(parser->lexer->token->id == END_keyword,
                "Expected `END` on line %d, instead got `%s`\n",
                parser->lexer->line, parser->lexer->token->token_value)
            
            parser_get_next(parser);
            ASM_OVER_LANG_ASSERT(parser->lexer->token->id == Right_SB,
                "Expected `]` on line %d, instead got `%s`\n",
                parser->lexer->line, parser->lexer->token->token_value)
            
        }
        default: break;
    }

    return;
}