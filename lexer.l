%{
#include <string.h>
#include "parser.h"
%}

%%
\n                              /* ignore end of line */
[ \t]+                          /* ignore whitespace */
"&&"                            return T_AND;
"||"                            return T_OR;
"=="                            return T_EQ;
"^^"                            return T_CT;
"("                             return '(';
")"                             return ')';
[a-zA-Z][a-zA-Z0-9]*            yylval.string_literal = strdup(yytext); return T_FIELD;
%%

