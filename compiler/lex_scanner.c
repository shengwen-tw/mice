#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lex_scanner.h"

const char *lex_token_name[] = {
	DEF_LEX_NAME(DATA_TYPE_TOKEN)
	DEF_LEX_NAME(COLON_TOKEN)
	DEF_LEX_NAME(SEMICOLON_TOKEN)
	DEF_LEX_NAME(LEFT_PARAN_TOKEN)
	DEF_LEX_NAME(RIGHT_PARAN_TOKEN)
	DEF_LEX_NAME(LEFT_BRACE_TOKEN)
	DEF_LEX_NAME(RIGHT_BRACE_TOKEN)
	DEF_LEX_NAME(ASSIGN_TOKEN)
	DEF_LEX_NAME(ADD_TOKEN)
	DEF_LEX_NAME(SUB_TOKEN)
	DEF_LEX_NAME(MULT_TOKEN)
	DEF_LEX_NAME(DIV_TOKEN)
	DEF_LEX_NAME(MOD_TOKEN)
	DEF_LEX_NAME(EQUAL_TOKEN)
	DEF_LEX_NAME(NOT_EQUAL_TOKEN)
	DEF_LEX_NAME(GREATER_TOKEN)
	DEF_LEX_NAME(GREATER_EQUAL_TOKEN)
	DEF_LEX_NAME(LESS_TOKEN)
	DEF_LEX_NAME(LESS_EQUAL_TOKEN)
	DEF_LEX_NAME(AND_TOKEN)
	DEF_LEX_NAME(OR_TOKEN)
	DEF_LEX_NAME(NOT_TOKEN)
	DEF_LEX_NAME(IF_TOKEN)
	DEF_LEX_NAME(ELSE_TOKEN)
	DEF_LEX_NAME(WHILE_TOKEN)
	DEF_LEX_NAME(PRINT_TOKEN)
	DEF_LEX_NAME(LINE_COMMENT_TOKEN)
};

static void lex_append_new(lex_token **last, lex_token **start, int token_type)
{
	//allocate new lex token
	lex_token *lex_next = (lex_token *)malloc(sizeof(lex_token));
	lex_next->token_type = token_type;
	lex_next->next = NULL;

	if(*last == NULL) {
		//first item in the list
		*start = lex_next;
		*last = lex_next;
	} else {
		//update the list last pointer
		(*last)->next = lex_next;
		*last = (*last)->next;
	}
}

void lex_scanner(char *s, lex_token **lex_list)
{
	char c;
	char identifier_buf[IDENTIFIER_STR_MAX_LEN] = {0};
	char identifier_curr = 0;

	lex_token *last = NULL;
	lex_token *start = NULL;

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
				lex_append_new(&last, &start, IF_TOKEN);
				memset(identifier_buf, 0, IDENTIFIER_STR_MAX_LEN);
			} else if(strcmp("else", identifier_buf) == 0) {
				lex_append_new(&last, &start, ELSE_TOKEN);
				memset(identifier_buf, 0, IDENTIFIER_STR_MAX_LEN);
			} else if(strcmp("while", identifier_buf) == 0) {
				lex_append_new(&last, &start, WHILE_TOKEN);
				memset(identifier_buf, 0, IDENTIFIER_STR_MAX_LEN);
			} else if(strcmp("print", identifier_buf) == 0) {
				lex_append_new(&last, &start, PRINT_TOKEN);
				memset(identifier_buf, 0, IDENTIFIER_STR_MAX_LEN);
			} else {
				//lookahead
				char next_c = *(s+1);
				if(!(next_c >= 'a' && next_c <= 'z') && !(next_c >= 'A' && next_c <= 'Z')) {
					//XXX: finish me!
					memset(identifier_buf, 0, IDENTIFIER_STR_MAX_LEN);
					s++;
				}
			}
		}

		switch(c) {
		case '\0': /* end of stream */
			*lex_list = start;
			return;
		case ' ':
			break;
		case ':': //colon token ':'
			lex_append_new(&last, &start, COLON_TOKEN);
			break;
		case ';': //semicolon token ';'
			lex_append_new(&last, &start, SEMICOLON_TOKEN);
			break;
		case '(': //left parentheses token '('
			lex_append_new(&last, &start, LEFT_PARAN_TOKEN);
			break;
		case ')': //right parentheses token ')'
			lex_append_new(&last, &start, RIGHT_PARAN_TOKEN);
			break;
		case '{': //left brace token '{'
			lex_append_new(&last, &start, LEFT_BRACE_TOKEN);
			break;
		case '}': //right brace token '}'
			lex_append_new(&last, &start, RIGHT_BRACE_TOKEN);
			break;
		case '=':
			if(*(s+1) == '=') { //equal token '=='
				lex_append_new(&last, &start, EQUAL_TOKEN);
				s++;
			} else { //assign token '='
				lex_append_new(&last, &start, ASSIGN_TOKEN);
			}
			break;
		case '+': //add token '+'
			lex_append_new(&last, &start, ADD_TOKEN);
			break;
		case '-': //subtract token '-'
			lex_append_new(&last, &start, SUB_TOKEN);
			break;
		case '*': //multiply token '*'
			lex_append_new(&last, &start, MULT_TOKEN);
			break;
		case '/':
			if(*(s+1) == '/') { //comment token '//'
				lex_append_new(&last, &start, LINE_COMMENT_TOKEN);
				s++;
			} else { //divide token '/'
				lex_append_new(&last, &start, DIV_TOKEN);
			}
			break;
		case '%': //mod token
			lex_append_new(&last, &start, MOD_TOKEN);
			break;
		case '!':
			if(*(s+1) == '=') { //not equal token '!='
				lex_append_new(&last, &start, NOT_EQUAL_TOKEN);
				s++;
			} else { //not token '!'
				lex_append_new(&last, &start, NOT_TOKEN);
			}
			break;
		case '>':
			if(*(s+1) == '=') { //greater equal token '>='
				lex_append_new(&last, &start, GREATER_EQUAL_TOKEN);
				s++;
			} else { //greater token '>'
				lex_append_new(&last, &start, GREATER_EQUAL_TOKEN);
			}
			break;
		case '<':
			if(*(s+1) == '=') { //less equal token '<='
				lex_append_new(&last, &start, LESS_EQUAL_TOKEN);
				s++;
			} else { //less token '<'
				lex_append_new(&last, &start, LESS_TOKEN);
			}
			break;
		case '&': //and token '&'
			lex_append_new(&last, &start, AND_TOKEN);
			break;
		case '|': //or token '|'
			lex_append_new(&last, &start, OR_TOKEN);
			break;
		}

		s++; //point to next char
	}
}

void print_lex_list(lex_token *lex_list)
{
	printf("[lex token list:]\n");
	while(lex_list != NULL) {
		printf("%s\n", lex_token_name[lex_list->token_type]);
		lex_list = lex_list->next;
	}
}
