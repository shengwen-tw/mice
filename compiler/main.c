#include <stdio.h>
#include <stdlib.h>
#include "lex_scanner.h"

int main(void)
{
	char src[512] = "+-/*while if";

	lexeme_t *lexeme_list;
	lex_scanner(src, &lexeme_list);

	print_lex_tree(lexeme_list);

	return 0;
}
