%{
#include <stdio.h>

typedef struct _ast_programa ast_programa;

int yylex();
void yyerror(ast_programa** programa, const char* s);
%}

%code requires {
#include "ast.h"
}

%parse-param {ast_programa** programa}

%union {
	// Literales
	int   intval;
	char* strval;

	// Nodos
	ast_declaracion*       declaracion;
	ast_lista_declaracion* lista_declaracion;
	ast_tipo*              tipo;
	ast_var_declaracion*   var_declaracion;
}

%left '+' '-'
%left '*' '/'

%nonassoc "entonces"
%nonassoc sino

// Reservados
%token entero
%token main
%token mientras
%token retorno
%token sin_tipo
%token si
%token sino

// Nodos

// Literales
%token <intval> NUM
%token <strval> ID

%%
programa
	: lista_declaracion {
		if(programa)
			*programa = ast_programa1(NULL);
		else
			ast_lista_declaracion_free(NULL);
	}
	;

lista_declaracion
	: lista_declaracion declaracion
	| declaracion
	;

declaracion
	: var_declaracion
	| fun_declaracion
	;

var_declaracion
	: tipo ID ';'
	| tipo ID '[' NUM ']' ';'
	;

tipo
	: entero
	| sin_tipo
	;

fun_declaracion
	: tipo ID '(' params ')' sent_compuesta
	;

params
	: lista_params
	| sin_tipo
	;

lista_params
	: lista_params ',' param
	| param
	;

param
	: tipo ID
	| tipo ID '[' ']'
	;

sent_compuesta
	: '{' declaracion_local lista_sentencias '}'
	;

declaracion_local
	: declaracion_local var_declaracion
	| vacio
	;

lista_sentencias
	: lista_sentencias sentencia
	| vacio
	;

sentencia
	: sentencia_expresion
	| sentencia_seleccion
	| sentencia_iteracion
	| sentencia_retorno
	;

sentencia_expresion
	: expresion ';'
	| ';'
	;

sentencia_seleccion
	: si '(' expresion ')' sentencia %prec "entonces"
	| si '('expresion ')' sentencia sino sentencia
	;

sentencia_iteracion
	: mientras '(' expresion ')' '{' lista_sentencias '}'
	;

sentencia_retorno
	: retorno ';'
	| retorno expresion ';'
	;

expresion
	: var '=' expresion
	| expresion_simple
	;

var
	: ID
	| ID '[' expresion ']'
	;

expresion_simple
	: expresion_aditiva relop expresion_aditiva
	| expresion_aditiva
	;

relop
	: "<"
	| "<="
	| ">"
	| ">="
	| "=="
	| "!="
	;

expresion_aditiva
	: expresion_aditiva addop term
	| term
	;

addop
	: '+'
	| '-'
	;

term
	: term mulop factor
	| factor
	;

mulop
	: '*'
	| '/'
	;

factor
	: '(' expresion ')'
	| var
	| call
	| NUM
	;

call
	:ID '(' args ')'
	;

args
	:lista_arg
	| vacio
	;

lista_arg
	:lista_arg ',' expresion
	| expresion
	;

vacio: %empty;
%%

void yyerror(ast_programa** programa, const char* s)
{
	fprintf(stderr, "Parser error: %s\n", s);
	if(programa)
		ast_programa_free(*programa);
}
