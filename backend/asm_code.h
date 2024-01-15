#ifndef ASM_OVER_LANG_CODE_H
#define ASM_OVER_LANG_CODE_H
#include "../common.h"

static puint8 code = NULL;
static size_t code_size = 0;

typedef struct ASM_OVER_LANG_Code
{

} _ASM_OVER_LANG_Code;

void raw_add(puint8 icode);
void write_code();

#endif