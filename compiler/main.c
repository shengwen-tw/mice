#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "syntax_parser.h"

int main(void)
{
	char src[512] = "while() int  { if ()}";

	lex_token *lex_list;
	lex_scanner(src, &lex_list);

	print_lex_list(lex_list);

	syntax_node *syntax_tree;
	init_syntax_parser(lex_list);
	generate_ast(&syntax_tree);

	return 0;
}
