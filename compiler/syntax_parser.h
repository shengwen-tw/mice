#ifndef __SYNTAX_PARSER_H__
#define __SYNTAX_PARSER_H__

#include "lexer.h"

enum {
	EXPRESSION_NODE,
	BLOCK_NODE
} SYNTAX_NODE_TYPE;

typedef struct _syntax_node {
	int node_type;
	struct _syntax_node *left;
	struct _syntax_node *right;	
} syntax_node;

void init_syntax_parser(lex_token *p);
void generate_ast(syntax_node **syntax_tree);
void print_ast(syntax_node *syntax_tree);

#endif
