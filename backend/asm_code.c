#include "asm_code.h"

void raw_add(puint8 icode)
{
    if(code == NULL)
        code = (puint8)calloc(strlen(icode), sizeof(*code));
    else
        code = (puint8)realloc(
            code,
            (strlen(code) + strlen(icode)) * sizeof(*code));
    
    strcpy(code, icode);
}

void write_code()
{
    FILE *f = fopen((const char *)"test.asm", "w");

    fwrite((void *)code, strlen(code), sizeof(*code), f);
    fclose(f);

    free((void *)code);
}