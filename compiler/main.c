#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "syntax_parser.h"

int main(void)
{
	char src[512] = "if(1 + 1) {print('A');}";

	printf("generate lex token list...\n");
	lex_token *lex_list;
	lex_scanner(src, &lex_list);

	print_lex_list(lex_list);

	printf("\ngenerate abstract symbol tree...\n");
	syntax_node *syntax_tree;
	init_syntax_parser(lex_list);
	generate_ast(&syntax_tree);

	print_ast(syntax_tree);


	return 0;
}
