%{
#include <stdio.h>
#include <string.h>
#include "expression.h"
#include "lexer.h"

#define YYERROR_VERBOSE 1

void yyerror(const char *str)
{
    fprintf(stderr, "Parse error: %s\n", str);
}
int yywrap()
{
    return 1;
}

extern node_t *zfilter;

%}

%union {
    char *string_literal;
    struct node *expr;
}

%token '(' ')' T_AND T_OR
%token <string_literal> T_FIELD
%token T_EQ T_CT

%left T_OR
%left T_AND

%type <expr> filter
%type <expr> string_filter
%type <expr> filter_expr

%%

expression: filter_expr
	{
		zfilter = $1;
	}


filter_expr:
	filter_expr T_OR filter_expr
		{
			$$ = make_op_node(OR);
			$$->left_child = $1;
			$$->right_child = $3;
		}
	| filter_expr T_AND filter_expr
		{
			$$ = make_op_node(AND);
			$$->left_child = $1;
			$$->right_child = $3;
		}
	| '(' filter_expr ')'
		{
			$$ = $2;
		}
	| filter
		{
			$$ = $1;
		}
	;

filter: string_filter
		{
			$$ = $1;
		}
	;

string_filter:
	T_FIELD T_EQ T_FIELD
		{
			$$ = make_op_node(EQ);
			$$->left_child = make_left_node($1);
			$$->right_child = make_right_node($3);
		}
	|
	T_FIELD T_CT T_FIELD
		{
			$$ = make_op_node(CT);
			$$->left_child = make_left_node($1);
			$$->right_child = make_right_node($3);
		}
	;

%%
