#ifndef __LEXER_H__
#define __LEXER_H__

#include <stdint.h>

#define IDENTIFIER_STR_MAX_LEN 50

#define DEF_LEX_NAME(token) #token,

/* enumerate all tokens */
enum {
	INT_TOKEN,
	IDENTIFIER_TOKEN,
	NUM_TOKEN,
	CHAR_TOKEN,
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
	uint32_t token_type;
	uint64_t token_val;
	struct _lext_token *next;
} lex_token;

void lex_scanner(char *s, lex_token **lexeme_list);
char *token_name_str(uint32_t token_type);
void print_lex_list(lex_token *lexeme_list);

#endif
