#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lexer.h"

const char *lex_token_name[] = {
	DEF_LEX_NAME(INT_TOKEN)
	DEF_LEX_NAME(IDENTIFIER_TOKEN)
	DEF_LEX_NAME(NUM_TOKEN)
	DEF_LEX_NAME(OP_TOKEN)
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

static void lex_append_new(lex_token **last, lex_token **start, uint32_t token_type, uint64_t token_val)
{
	//allocate new lex token
	lex_token *lex_next = (lex_token *)malloc(sizeof(lex_token));
	lex_next->token_type = token_type;
	lex_next->token_val = token_val;
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

		if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c == '_')) { //parse for identifier
			identifier_buf[identifier_curr] = c;
			identifier_curr++;

			if(identifier_curr >= IDENTIFIER_STR_MAX_LEN) {
				printf("error, identifier name should be larger than %d!\n",
				       IDENTIFIER_STR_MAX_LEN);
				exit(0);
			}

			if(strcmp("int", identifier_buf) == 0) {
				lex_append_new(&last, &start, INT_TOKEN, 0);
				memset(identifier_buf, 0, IDENTIFIER_STR_MAX_LEN);
				identifier_curr = 0;
			} else if(strcmp("if", identifier_buf) == 0) {
				lex_append_new(&last, &start, IF_TOKEN, 0);
				memset(identifier_buf, 0, IDENTIFIER_STR_MAX_LEN);
				identifier_curr = 0;
			} else if(strcmp("else", identifier_buf) == 0) {
				lex_append_new(&last, &start, ELSE_TOKEN, 0);
				memset(identifier_buf, 0, IDENTIFIER_STR_MAX_LEN);
				identifier_curr = 0;
			} else if(strcmp("while", identifier_buf) == 0) {
				lex_append_new(&last, &start, WHILE_TOKEN, 0);
				memset(identifier_buf, 0, IDENTIFIER_STR_MAX_LEN);
				identifier_curr = 0;
			} else if(strcmp("print", identifier_buf) == 0) {
				lex_append_new(&last, &start, PRINT_TOKEN, 0);
				memset(identifier_buf, 0, IDENTIFIER_STR_MAX_LEN);
				identifier_curr = 0;
			} else {
				char next_c = *(s+1); //lookahead for 1 char
				if(!(next_c >= 'a' && next_c <= 'z') && !(next_c >= 'A' && next_c <= 'Z') && (next_c != '_')) {
					char *id_str = (char *)malloc(sizeof(char) * identifier_curr+1);
					strncpy(id_str, identifier_buf, identifier_curr);
					lex_append_new(&last, &start, IDENTIFIER_TOKEN, (uint64_t)id_str);
					memset(identifier_buf, 0, IDENTIFIER_STR_MAX_LEN);
					identifier_curr = 0;
					s++;
				}
			}
		} else if(c >= '0' && c <= '9') { //parse for integer
			identifier_buf[identifier_curr] = c;
			identifier_curr++;

			char next_c = *(s+1); //lookahead for 1 char
			if(!(next_c >= '0' && next_c <= '9')) {
				int token_num_val = atoi(identifier_buf);
				lex_append_new(&last, &start, NUM_TOKEN, token_num_val);
				memset(identifier_buf, 0, IDENTIFIER_STR_MAX_LEN);
				identifier_curr = 0;
				s++;
			}
		}

		switch(c) {
		case '\0': /* end of stream */
			*lex_list = start;
			return;
		case ' ':
			break;
		case ':': //colon token ':'
			lex_append_new(&last, &start, COLON_TOKEN, 0);
			break;
		case ';': //semicolon token ';'
			lex_append_new(&last, &start, SEMICOLON_TOKEN, 0);
			break;
		case '(': //left parentheses token '('
			lex_append_new(&last, &start, LEFT_PARAN_TOKEN, 0);
			break;
		case ')': //right parentheses token ')'
			lex_append_new(&last, &start, RIGHT_PARAN_TOKEN, 0);
			break;
		case '{': //left brace token '{'
			lex_append_new(&last, &start, LEFT_BRACE_TOKEN, 0);
			break;
		case '}': //right brace token '}'
			lex_append_new(&last, &start, RIGHT_BRACE_TOKEN, 0);
			break;
		case '=':
			if(*(s+1) == '=') { //equal token '=='
				lex_append_new(&last, &start, EQUAL_TOKEN, 0);
				s++;
			} else { //assign token '='
				lex_append_new(&last, &start, ASSIGN_TOKEN, 0);
			}
			break;
		case '+': //add token '+'
			lex_append_new(&last, &start, ADD_TOKEN, 0);
			break;
		case '-': //subtract token '-'
			lex_append_new(&last, &start, SUB_TOKEN, 0);
			break;
		case '*': //multiply token '*'
			lex_append_new(&last, &start, MULT_TOKEN, 0);
			break;
		case '/':
			if(*(s+1) == '/') { //comment token '//'
				lex_append_new(&last, &start, LINE_COMMENT_TOKEN, 0);
				s++;
			} else { //divide token '/'
				lex_append_new(&last, &start, DIV_TOKEN, 0);
			}
			break;
		case '%': //mod token
			lex_append_new(&last, &start, MOD_TOKEN, 0);
			break;
		case '!':
			if(*(s+1) == '=') { //not equal token '!='
				lex_append_new(&last, &start, NOT_EQUAL_TOKEN, 0);
				s++;
			} else { //not token '!'
				lex_append_new(&last, &start, NOT_TOKEN, 0);
			}
			break;
		case '>':
			if(*(s+1) == '=') { //greater equal token '>='
				lex_append_new(&last, &start, GREATER_EQUAL_TOKEN, 0);
				s++;
			} else { //greater token '>'
				lex_append_new(&last, &start, GREATER_EQUAL_TOKEN, 0);
			}
			break;
		case '<':
			if(*(s+1) == '=') { //less equal token '<='
				lex_append_new(&last, &start, LESS_EQUAL_TOKEN, 0);
				s++;
			} else { //less token '<'
				lex_append_new(&last, &start, LESS_TOKEN, 0);
			}
			break;
		case '&': //and token '&'
			lex_append_new(&last, &start, AND_TOKEN, 0);
			break;
		case '|': //or token '|'
			lex_append_new(&last, &start, OR_TOKEN, 0);
			break;
		}

		s++; //point to next char
	}
}

void print_lex_list(lex_token *lex_list)
{
	printf("[lex token list:]\n");
	while(lex_list != NULL) {
		if(lex_list->token_type == IDENTIFIER_TOKEN) {
			printf("%s -> \"%s\"\n", lex_token_name[lex_list->token_type], (char *)lex_list->token_val);
		} else if(lex_list->token_type == NUM_TOKEN) {
			printf("%s -> %ld\n", lex_token_name[lex_list->token_type], lex_list->token_val);
		} else {
			printf("%s\n", lex_token_name[lex_list->token_type]);
		}
		lex_list = lex_list->next;
	}
}
