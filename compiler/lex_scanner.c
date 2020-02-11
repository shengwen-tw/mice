#include <string.h>
#include "lex_scanner.h"

void lex_make_token()
{
}

void lex_lookahead()
{
}

void lex_scanner(char *s,lexeme_t *lexeme_list)
{
	char c;
	char identifier_buf[50] = {0}; //XXX:reset after matching
	char identifier_curr = 0;

	while(1) {
		c = *s; //read new char

		/* identifier state */
		if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
			identifier_buf[identifier_curr] = c;
			identifier_curr++;

			if(strcmp("if", identifier_buf) == 0) {
				(*lexeme_list).token_name = IF_TOKEN;
			} else if(strcmp("else", identifier_buf) == 0) {
				(*lexeme_list).token_name = ELSE_TOKEN;
			} else if(strcmp("while", identifier_buf) == 0) {
				(*lexeme_list).token_name = WHILE_TOKEN;
			} else if(strcmp("print", identifier_buf) == 0) {
				(*lexeme_list).token_name = PRINT_TOKEN;
			}
		}

		switch(c) {
		case '\0': /* end of stream */
			return;
		case ' ':
			break;
		case ':':
			(*lexeme_list).token_name = COLON_TOKEN;
			break;
		case ';':
			(*lexeme_list).token_name = SEMICOLON_TOKEN;
			break;
		case '(':
			(*lexeme_list).token_name = LEFT_PARAN_TOKEN;
			break;
		case ')':
			(*lexeme_list).token_name = RIGHT_PARAN_TOKEN;
			break;
		case '{':
			(*lexeme_list).token_name = LEFT_BRACE_TOKEN;
			break;
		case '}':
			(*lexeme_list).token_name = RIGHT_BRACE_TOKEN;
			break;
		case '=': /* = and == */
			if(*(s+1) == '=') {
				(*lexeme_list).token_name = EQUAL_TOKEN;
				lexeme_list++;
				s++;
			}
			break;
		case '+':
			(*lexeme_list).token_name = ADD_TOKEN;
			lexeme_list++;
			break;
		case '-':
			(*lexeme_list).token_name = SUB_TOKEN;
			lexeme_list++;
			break;
		case '*':
			(*lexeme_list).token_name = MULT_TOKEN;
			lexeme_list++;
			break;
		case '/': /* / and // */
			if(*(s+1) == '/') {
				(*lexeme_list).token_name = LINE_COMMENT_TOKEN;
				lexeme_list++;
				s++;
			}
			break;
		case '%':
			(*lexeme_list).token_name = MOD_TOKEN;
			break;
		case '!': /* ! and != */
			if(*(s+1) == '=') {
				(*lexeme_list).token_name = NOT_EQUAL_TOKEN;
				lexeme_list++;
				s++;
			}
			break;
		case '>': /* > and >= */
			if(*(s+1) == '/') {
				(*lexeme_list).token_name = GREATER_EQUAL_TOKEN;
				lexeme_list++;
				s++;
			}
			break;
		case '<': /* < and <= */
			if(*(s+1) == '/') {
				(*lexeme_list).token_name = LESS_EQUAL_TOKEN;
				lexeme_list++;
				s++;
			}
			break;
		case '&':
			(*lexeme_list).token_name = AND_TOKEN;
			lexeme_list++;
			break;
		case '|':
			(*lexeme_list).token_name = OR_TOKEN;
			lexeme_list++;
			break;
		}

		s++; //point to next char
	}
}

void print_lex_tree()
{
}
