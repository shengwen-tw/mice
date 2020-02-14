#include "stdlib.h"
#include "lexer.h"
#include "syntax_parser.h"

lex_token *lex_list;

static void parse_start_sym(syntax_node **syntax_tree);
static void parse_expr(syntax_node **syntax_tree);
static void parse_end_sym(syntax_node **syntax_tree);

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

static void error(int token)
{
	exit(0);
}

static void match(int token)
{
	lex_token *new_token = next_token();
	if(new_token->token_type == token) {
	} else {
		error(token);
	}
}

static void parse_start_sym(syntax_node **syntax_tree)
{
	lex_token *new_token = lex_lookahead();

	switch(new_token->token_type) {
	case IF_TOKEN:
		match(IF_TOKEN);
		parse_expr(syntax_tree);
		parse_start_sym(syntax_tree);
		match(ELSE_TOKEN);
		parse_start_sym(syntax_tree);
		break;
	case WHILE_TOKEN:
		match(WHILE_TOKEN);
		parse_expr(syntax_tree);
		parse_start_sym(syntax_tree);
		break;
	case LEFT_BRACE_TOKEN:
		match(LEFT_BRACE_TOKEN);
		parse_end_sym(syntax_tree);
		match(RIGHT_BRACE_TOKEN);
		break;
	case PRINT_TOKEN:
		match(PRINT_TOKEN);
		parse_expr(syntax_tree);
		break;
	default:
		error(new_token->token_type);
	}
}

static void parse_expr(syntax_node **syntax_tree)
{
	lex_token *new_token = lex_lookahead();

	switch(new_token->token_type) {
	case NUM_TOKEN:
		match(NUM_TOKEN);
		match(OP_TOKEN);
		match(NUM_TOKEN);
		break;
	default:
		error(new_token->token_type);
	}
}

static void parse_end_sym(syntax_node **syntax_tree)
{
	lex_token *new_token = lex_lookahead();

	switch(new_token->token_type) {
	case RIGHT_BRACE_TOKEN:
		break;
	case IF_TOKEN:
	case LEFT_BRACE_TOKEN:
	case PRINT_TOKEN:
		parse_start_sym(syntax_tree);
		break;		
	default:
		error(new_token->token_type);	
	}
}

void generate_ast(syntax_node **syntax_tree)
{
	parse_start_sym(syntax_tree);
}
