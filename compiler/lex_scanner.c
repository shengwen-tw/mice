#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex_scanner.h"

#define IDENTIFIER_STR_MAX_LEN 50

void lex_make_token(lexeme_t **token_list_last, lexeme_t **token_list_start, int token_name)
{
	//allocate new lex token
	lexeme_t *lex_next = (lexeme_t *)malloc(sizeof(lexeme_t));
	lex_next->token_name = token_name;
	lex_next->next = NULL;

	if(*token_list_last == NULL) {
		//first item in the list
		*token_list_start = lex_next;
		*token_list_last = lex_next;
	} else {
		//update the list last pointer
		(*token_list_last)->next = lex_next;
		*token_list_last = (*token_list_last)->next;
	}
}

void lex_scanner(char *s, lexeme_t **lexeme_list)
{
	char c;
	char identifier_buf[IDENTIFIER_STR_MAX_LEN] = {0}; //XXX:reset after matching
	char identifier_curr = 0;

	lexeme_t *token_list_last = NULL;
	lexeme_t *token_list_start = NULL;

	while(1) {
		c = *s; //read new char

		/* identifier state */
		if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
			identifier_buf[identifier_curr] = c;
			identifier_curr++;

			if(identifier_curr >= IDENTIFIER_STR_MAX_LEN) {
				printf("error, identifier name should be larger than %d!\n",
				       IDENTIFIER_STR_MAX_LEN);
				exit(0);
			}

			if(strcmp("if", identifier_buf) == 0) {
				lex_make_token(&token_list_last, &token_list_start, IF_TOKEN);
				memset(identifier_buf, 0, IDENTIFIER_STR_MAX_LEN);
			} else if(strcmp("else", identifier_buf) == 0) {
				lex_make_token(&token_list_last, &token_list_start, ELSE_TOKEN);
				memset(identifier_buf, 0, IDENTIFIER_STR_MAX_LEN);
			} else if(strcmp("while", identifier_buf) == 0) {
				lex_make_token(&token_list_last, &token_list_start, WHILE_TOKEN);
				memset(identifier_buf, 0, IDENTIFIER_STR_MAX_LEN);
			} else if(strcmp("print", identifier_buf) == 0) {
				lex_make_token(&token_list_last, &token_list_start, PRINT_TOKEN);
				memset(identifier_buf, 0, IDENTIFIER_STR_MAX_LEN);
			} else {
				//lookahead
				char next_c = *(s+1);
				if(!(next_c >= 'a' && next_c <= 'z') && !(next_c >= 'A' && next_c <= 'Z')) {
					//XXX: identifiers
					s++;
				}
			}
		}

		switch(c) {
		case '\0': /* end of stream */
			*lexeme_list = token_list_start;
			return;
		case ' ':
			break;
		case ':': //colon token ':'
			lex_make_token(&token_list_last, &token_list_start, COLON_TOKEN);
			break;
		case ';': //semicolon token ';'
			lex_make_token(&token_list_last, &token_list_start, SEMICOLON_TOKEN);
			break;
		case '(': //left parentheses token '('
			lex_make_token(&token_list_last, &token_list_start, LEFT_PARAN_TOKEN);
			break;
		case ')': //right parentheses token ')'
			lex_make_token(&token_list_last, &token_list_start, RIGHT_PARAN_TOKEN);
			break;
		case '{': //left brace token '{'
			lex_make_token(&token_list_last, &token_list_start, LEFT_BRACE_TOKEN);
			break;
		case '}': //right brace token '}'
			lex_make_token(&token_list_last, &token_list_start, RIGHT_BRACE_TOKEN);
			break;
		case '=':
			if(*(s+1) == '=') { //equal token '=='
				lex_make_token(&token_list_last, &token_list_start, EQUAL_TOKEN);
				s++;
			} else { //assign token '='
				lex_make_token(&token_list_last, &token_list_start, ASSIGN_TOKEN);
			}
			break;
		case '+': //add token '+'
			lex_make_token(&token_list_last, &token_list_start, ADD_TOKEN);
			break;
		case '-': //subtract token '-'
			lex_make_token(&token_list_last, &token_list_start, SUB_TOKEN);
			break;
		case '*': //multiply token '*'
			lex_make_token(&token_list_last, &token_list_start, MULT_TOKEN);
			break;
		case '/':
			if(*(s+1) == '/') { //comment token '//'
				lex_make_token(&token_list_last, &token_list_start, LINE_COMMENT_TOKEN);
				s++;
			} else { //divide token '/'
				lex_make_token(&token_list_last, &token_list_start, DIV_TOKEN);
			}
			break;
		case '%': //mod token
			lex_make_token(&token_list_last, &token_list_start, MOD_TOKEN);
			break;
		case '!':
			if(*(s+1) == '=') { //not equal token '!='
				lex_make_token(&token_list_last, &token_list_start, NOT_EQUAL_TOKEN);
				s++;
			} else { //not token '!'
				lex_make_token(&token_list_last, &token_list_start, NOT_TOKEN);
			}
			break;
		case '>':
			if(*(s+1) == '=') { //greater equal token '>='
				lex_make_token(&token_list_last, &token_list_start, GREATER_EQUAL_TOKEN);
				s++;
			} else { //greater token '>'
				lex_make_token(&token_list_last, &token_list_start, GREATER_EQUAL_TOKEN);
			}
			break;
		case '<':
			if(*(s+1) == '=') { //less equal token '<='
				lex_make_token(&token_list_last, &token_list_start, LESS_EQUAL_TOKEN);
				s++;
			} else { //less token '<'
				lex_make_token(&token_list_last, &token_list_start, LESS_TOKEN);
			}
			break;
		case '&': //and token '&'
			lex_make_token(&token_list_last, &token_list_start, AND_TOKEN);
			break;
		case '|': //or token '|'
			lex_make_token(&token_list_last, &token_list_start, OR_TOKEN);
			break;
		}

		s++; //point to next char
	}
}

void print_lex_tree(lexeme_t *lexeme_list)
{
	while(lexeme_list != NULL) {
		printf("token: %d\n", lexeme_list->token_name);
		lexeme_list = lexeme_list->next;
	}
}
