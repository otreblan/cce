%{
#include <stdio.h>

void yyerror(void** tree, const char* s);
%}

%parse-param {void** tree}

%token entero

%%
programa: %empty
%%

void yyerror(void** tree, const char* s)
{
	// TODO: tree
	fprintf(stderr, "Parser error: %s\n", s);
}
