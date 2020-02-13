#include <stdio.h>
#include <stdlib.h>
#include "lex_scanner.h"

int main(void)
{
	char src[512] = "+-/*while if";

	lex_token *lex_list;
	lex_scanner(src, &lex_list);

	print_lex_list(lex_list);

	return 0;
}
