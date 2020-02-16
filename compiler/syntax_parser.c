#include <stdio.h>
#include <stdlib.h>
#include "lexer.h"
#include "syntax_parser.h"

lex_token *lex_list;

static void parse_branch(syntax_node **syntax_tree);
static void parse_loop(syntax_node **syntax_tree);
static void parse_expr(syntax_node **syntax_tree);

void init_syntax_parser(lex_token *p)
{
	lex_list = p;
}

static lex_token *lex_lookahead(void)
{
	return lex_list;
}

static lex_token *next_token()
{
	lex_token *ret_val = lex_list;
	lex_list = lex_list->next;
	return ret_val;
}

static void match_token(int token)
{
	lex_token *new_token = next_token();
	if(new_token == NULL) return;

	if(new_token->token_type != token) {
		printf("can't match %s\n", token_name_str(token));
		exit(0);
	}
}

static void match_op()
{
	lex_token *new_token = next_token();
	if(new_token == NULL) return;

	switch(new_token->token_type) {
	case ASSIGN_TOKEN:
	case ADD_TOKEN:
	case SUB_TOKEN:
	case MULT_TOKEN:
	case DIV_TOKEN:
	case MOD_TOKEN:
	case EQUAL_TOKEN:
	case NOT_EQUAL_TOKEN:
	case GREATER_TOKEN:
	case GREATER_EQUAL_TOKEN:
	case LESS_TOKEN:
	case LESS_EQUAL_TOKEN:
	case AND_TOKEN:
	case OR_TOKEN:
	case NOT_TOKEN:
		break;
	default:
		printf("can't match any operator symbol, %s should not appeared here!\n",
		       token_name_str(new_token->token_type));
		exit(0);
	}
}

static void parse_branch(syntax_node **syntax_tree)
{
	lex_token *new_token = lex_lookahead();
	if(new_token == NULL) return;

	//printf("S\n");

	switch(new_token->token_type) {
	case IF_TOKEN:
		match_token(IF_TOKEN);
		match_token(LEFT_PARAN_TOKEN);
		parse_expr(syntax_tree);
		match_token(RIGHT_PARAN_TOKEN);
		parse_loop(syntax_tree);
		break;
	case WHILE_TOKEN:
		break;
	case LEFT_BRACE_TOKEN:
		match_token(LEFT_BRACE_TOKEN);
		parse_loop(syntax_tree);
		match_token(RIGHT_BRACE_TOKEN);
		break;
	case PRINT_TOKEN:
		match_token(PRINT_TOKEN);
		match_token(LEFT_PARAN_TOKEN);
		match_token(CHAR_TOKEN);
		match_token(RIGHT_PARAN_TOKEN);
		break;
	default:
		printf("syntax error, %s should not appeared here!\n",
		       token_name_str(new_token->token_type));
		exit(0);
	}
}

static void parse_loop(syntax_node **syntax_tree)
{
	lex_token *new_token = lex_lookahead();
	if(new_token == NULL) return;

	//printf("L\n");

	switch(new_token->token_type) {
	case RIGHT_BRACE_TOKEN:
		break;
	case IF_TOKEN:
	case WHILE_TOKEN:
	case LEFT_BRACE_TOKEN:
		parse_branch(syntax_tree);
		break;
	case PRINT_TOKEN:
		parse_branch(syntax_tree);
		match_token(SEMICOLON_TOKEN);
		parse_loop(syntax_tree);
		break;
	default:
		printf("syntax error, %s should not appeared here!\n",
		       token_name_str(new_token->token_type));
		exit(0);
	}
}

static void parse_expr(syntax_node **syntax_tree)
{
	lex_token *new_token = lex_lookahead();
	if(new_token == NULL) return;

	//printf("E\n");

	switch(new_token->token_type) {
	case NUM_TOKEN:
		match_token(NUM_TOKEN);
		match_op();
		match_token(NUM_TOKEN);
		break;
	default:
		printf("syntax error, %s should not appeared here!\n",
		       token_name_str(new_token->token_type));
		exit(0);
	}
}

void generate_ast(syntax_node **syntax_tree)
{
	parse_loop(syntax_tree);
}

static void print_indent(int cnt)
{
	int i;
	for(i = 0; i < cnt; i++) {
		puts("  ");
	}
}

static void syntax_tree_traversal(syntax_node *syntax_tree, int recursive_depth)
{
	recursive_depth++;

	if(syntax_tree != NULL) {
		print_indent(recursive_depth - 1);

		switch(syntax_tree->node_type) {
		case EXPRESSION_NODE:
			printf("> EXPRESSION_NODE\n");
			break;
		case BLOCK_NODE:
			printf("> BLOCK_NODE\n");
			break;
		}

		syntax_tree_traversal(syntax_tree->left, recursive_depth);
		syntax_tree_traversal(syntax_tree->right, recursive_depth);
	}
}

void print_ast(syntax_node *syntax_tree)
{
	syntax_tree_traversal(syntax_tree, 0);	
}
