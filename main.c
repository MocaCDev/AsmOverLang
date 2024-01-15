#include "backend/parser.h"

uint32 main(int32 args, pint8 argv[])
{
	_ASM_OVER_LANG_Parser *parser = init_parser(init_lexer("test/test.oasm"));

	parser_destroy(parser);
	return 0;
}