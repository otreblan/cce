%{
#include <stdio.h>

void yyerror(void** tree, const char* s);
%}

%parse-param {void** tree}

%union {
	int intval;
	char* strval;
}

%token entero
%token main
%token mientras
%token retorno
%token sin_tipo
%token sisino

%token <intval> NUM
%token <strval> ID

%%
programa: %empty
%%

void yyerror(void** tree, const char* s)
{
	// TODO: tree
	fprintf(stderr, "Parser error: %s\n", s);
}
