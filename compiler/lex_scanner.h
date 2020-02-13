#ifndef __LEX_PARSER_H__
#define __LEX_PARSER_H__

#define IDENTIFIER_STR_MAX_LEN 50

#define DEF_LEX_NAME(token) #token,

/* enumerate all tokens */
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

typedef struct _lext_token {
	int token_type;
	int token_val;
	struct _lext_token *next;
} lex_token;

void lex_scanner(char *s, lex_token **lexeme_list);
void print_lex_list(lex_token *lexeme_list);

#endif
