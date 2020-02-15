#include <stdio.h>
#include <stdlib.h>
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

static void match_token(int token)
{
	lex_token *new_token = next_token();
	if(new_token == NULL) return;

	printf("[%s] ", token_name_str(token)); //XXX

	if(new_token->token_type == token) {
	} else {
		printf("can't match %s\n", token_name_str(token));
		exit(0);
	}
}

static void match_op()
{
	lex_token *new_token = next_token();
	if(new_token == NULL) return;

	switch(new_token->token_type) {
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

static void parse_start_sym(syntax_node **syntax_tree)
{
	lex_token *new_token = lex_lookahead();
	if(new_token == NULL) return;

	switch(new_token->token_type) {
	case IF_TOKEN:
		match_token(IF_TOKEN);
		parse_expr(syntax_tree);
		parse_start_sym(syntax_tree);
		match_token(ELSE_TOKEN);
		parse_start_sym(syntax_tree);
		break;
	case WHILE_TOKEN:
		match_token(WHILE_TOKEN);
		parse_expr(syntax_tree);
		parse_start_sym(syntax_tree);
		break;
	case LEFT_BRACE_TOKEN:
		match_token(LEFT_BRACE_TOKEN);
		parse_end_sym(syntax_tree);
		match_token(RIGHT_BRACE_TOKEN);
		break;
	case PRINT_TOKEN:
		match_token(PRINT_TOKEN);
		parse_expr(syntax_tree);
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

static void parse_end_sym(syntax_node **syntax_tree)
{
	lex_token *new_token = lex_lookahead();
	if(new_token == NULL) return;

	switch(new_token->token_type) {
	case RIGHT_BRACE_TOKEN:
		break;
	case IF_TOKEN:
	case LEFT_BRACE_TOKEN:
	case PRINT_TOKEN:
		parse_start_sym(syntax_tree);
		break;		
	default:
		printf("syntax error, %s should not appeared here!\n",
		       token_name_str(new_token->token_type));
		exit(0);
	}
}

void generate_ast(syntax_node **syntax_tree)
{
	parse_start_sym(syntax_tree);
}
