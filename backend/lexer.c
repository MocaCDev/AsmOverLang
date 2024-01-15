#include "lexer.h"

/* `lexer.c` only. */
void lexer_advance(_ASM_OVER_LANG_Lexer *lexer)
{
    if((lexer->index + 1) >= lexer->file_size)
    {
        lexer->index = lexer->file_size;
        goto assign;
    }

    lexer->index++;

    assign:
    lexer->current_char = lexer->data[lexer->index];
}

void lexer_go_back(_ASM_OVER_LANG_Lexer *lexer)
{
    if((lexer->index - 1) <= 0)
        return;

    lexer->index--;
    lexer->current_char = lexer->data[lexer->index];
}

bool lexer_peek(_ASM_OVER_LANG_Lexer *lexer, uint8 against)
{
    if((lexer->index + 1) >= lexer->file_size)
        if(lexer->data[lexer->file_size] == against) return true;
    
    if(lexer->data[lexer->index + 1] == against) return true;
    return false;
}

void skip_whitespace(_ASM_OVER_LANG_Lexer *lexer)
{
    while(lexer->current_char == ' ' || lexer->current_char == '\t' || lexer->current_char == '\n')
    {
        if(lexer->current_char == '\n')
            lexer->line++;
        lexer_advance(lexer);
    }
}

puint8 get_string(_ASM_OVER_LANG_Lexer *lexer)
{
    puint8 string = (puint8)calloc(1, sizeof(*string));
    uint32 index = 0;

    while(lexer->current_char != ']' && lexer->current_char != ' ' && lexer->current_char != '\n')
    {
        string[index] = lexer->current_char;
        index++;

        string = (puint8)realloc(
            string,
            (index + 1) * sizeof(*string)
        );
        lexer_advance(lexer);
    }

    return string;
}

puint8 get_code_as_string(_ASM_OVER_LANG_Lexer *lexer)
{
    puint8 code = (puint8)calloc(1, sizeof(*code));
    uint32 index = 0;

    if(lexer->current_char == '\n')
        skip_whitespace(lexer);

    while(lexer_peek(lexer, '!') != true)
    {
        code[index] = lexer->current_char;
        index++;

        code = (puint8)realloc(
            code,
            (index + 1) * sizeof(*code)
        );
        lexer_advance(lexer);

        if(lexer->current_char == '\0')
        {
            ASM_OVER_LANG_ERROR("Unexpected EOF")
        }
    }

    return code;
}

_ASM_OVER_LANG_Lexer *init_lexer(const puint8 filename)
{
    _ASM_OVER_LANG_Lexer *lexer = (_ASM_OVER_LANG_Lexer *)calloc(1, sizeof(*lexer));
    FILE *source_code = fopen(filename, "rb");

    ASM_OVER_LANG_ASSERT(source_code,
        "Error opening the file: %s\n", filename)

    fseek(source_code, 0, SEEK_END);
    lexer->file_size = ftell(source_code);
    fseek(source_code, 0, SEEK_SET);

    if(lexer->file_size < 1)
    {
        fclose(source_code);

        ASM_OVER_LANG_ERROR("The file %s is empty\n", filename)
    }

    lexer->data = (puint8)calloc(lexer->file_size, sizeof(*lexer->data));
    ASM_OVER_LANG_ASSERT(lexer->data != NULL,
        "Error allocating memory to read %s\n", filename)
    
    ASM_OVER_LANG_ASSERT(
        fread((void *)lexer->data, sizeof(*lexer->data), lexer->file_size, source_code) == lexer->file_size,
        "Error reading all data from %s\n", filename)
    
    fclose(source_code);

    lexer->index = 0;
    lexer->line = 1;
    lexer->current_char = lexer->data[lexer->index];

    lexer->token = (_ASM_OVER_LANG_Tokens *)calloc(1, sizeof(*lexer->token));

    return lexer;
}

void destroy_lexer(_ASM_OVER_LANG_Lexer *lexer)
{
    free((void *)lexer->token);
    free((void *)lexer->data);
    free((void *)lexer);
}

void get_token(_ASM_OVER_LANG_Lexer *lexer)
{
    if(lexer->current_char == ' ' || lexer->current_char == '\t' || lexer->current_char == '\n')
        skip_whitespace(lexer);

    if(!(ASCII(lexer->current_char)))
    {
        switch(lexer->current_char)
        {
            case '!': lexer_advance(lexer);init_token(lexer->token, Expl, "!");return;
            case '[': lexer_advance(lexer);init_token(lexer->token, Left_SB, "[");return;
            case ']': lexer_advance(lexer);init_token(lexer->token, Right_SB, "]");return;
            default:
            {
                ASM_OVER_LANG_ASSERT(lexer->current_char == '\0',
                    "Error: Invalid value (`%c`) on line %d\n",
                    lexer->current_char, lexer->line)
                
                init_token(lexer->token, EndOfFile, "\0");
                return;
            }
        }
    }

    string = get_string(lexer);
    if(strcmp((const char *)string, (const char *)"RAW") == 0)
        { free((void *)string); init_token(lexer->token, RAW_keyword, "RAW"); return; }
    if(strcmp((const char *)string, (const char *)"END") == 0)
        { free((void *)string); string=NULL;init_token(lexer->token, END_keyword, "END"); return; }

    ASM_OVER_LANG_ERROR("Unknown Error")
}

void get_code(_ASM_OVER_LANG_Lexer *lexer)
{
    puint8 code = get_code_as_string(lexer);

    init_token(lexer->token, CODE, "");
    lexer->token->token_value = (puint8)calloc(1, sizeof(*lexer->token->token_value));
    strcpy(lexer->token->token_value, code);
    free((void *)code);
}