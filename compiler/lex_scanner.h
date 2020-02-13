#ifndef __LEX_PARSER_H__
#define __LEX_PARSER_H__

enum {
	DATA_TYPE_TOKEN = 0,
	COLON_TOKEN,
	SEMICOLON_TOKEN,
	LEFT_PARAN_TOKEN,
	RIGHT_PARAN_TOKEN,
	LEFT_BRACE_TOKEN,
	RIGHT_BRACE_TOKEN,
	ASSIGN_TOKEN,
	ADD_TOKEN,
	SUB_TOKEN,
	MULT_TOKEN,
	DIV_TOKEN,
	MOD_TOKEN,
	EQUAL_TOKEN,
	NOT_EQUAL_TOKEN,
	GREATER_TOKEN,
	GREATER_EQUAL_TOKEN,
	LESS_TOKEN,
	LESS_EQUAL_TOKEN,
	AND_TOKEN,
	OR_TOKEN,
	NOT_TOKEN,
	IF_TOKEN,
	ELSE_TOKEN,
	WHILE_TOKEN,
	PRINT_TOKEN,
	LINE_COMMENT_TOKEN,
} LEX_TOKEN_NAMES;

typedef struct _lexeme_ {
	int token_name;
	int token_val;
	struct _lexeme_ *next;
} lexeme_t;

void lex_scanner(char *s, lexeme_t **lexeme_list);
void print_lex_tree(lexeme_t *lexeme_list);

#endif
