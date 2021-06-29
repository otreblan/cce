%{
#include <stdio.h>

#include "cce/parser.h"

typedef struct _ast_programa ast_programa;

int yylex();
void yyerror(ast_programa** programa, const char* s);
%}

%require "3.4"
%code requires {
#include "ast.h"
}

%parse-param {ast_programa** programa}
%define parse.lac full
%define parse.error verbose

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

%destructor { }                                 <intval>
%destructor { free($$); }                       <strval>
%destructor { ast_declaracion_free($$); }       <declaracion>
%destructor { ast_lista_declaracion_free($$); } <lista_declaracion>
%destructor { ast_tipo_free($$); }              <tipo>
%destructor { ast_var_declaracion_free($$); }   <var_declaracion>

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
%type <lista_declaracion> lista_declaracion
%type <declaracion>       declaracion
%type <var_declaracion>   var_declaracion
%type <tipo>              tipo

// Literales
%token <intval> NUM
%token <strval> ID

%%
programa
	: lista_declaracion {
		if(programa)
			*programa = ast_programa1($1);
		else
			ast_lista_declaracion_free($1);
	}
	;

lista_declaracion
	: declaracion lista_declaracion { $$ = ast_lista_declaracion1($2, $1); }
	| declaracion                   { $$ = ast_lista_declaracion2($1); }
	;

declaracion
	: var_declaracion { $$ = ast_declaracion1($1); }
	| fun_declaracion { $$ = NULL; } // TODO
	;

var_declaracion
	: tipo ID ';'             { $$ = ast_var_declaracion1($1, $2); }
	| tipo ID '[' NUM ']' ';' { $$ = ast_var_declaracion2($1, $2, $4); }
	;

tipo
	: entero   {$$ = ast_tipo_entero(); }
	| sin_tipo {$$ = ast_tipo_sin_tipo(); }
	;

fun_declaracion
	: tipo ID '(' params ')' sent_compuesta
	;

params
	: lista_params
	| sin_tipo
	;

lista_params
	: param ',' lista_params
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

void yyerror(__attribute__((unused)) ast_programa** programa, const char* s)
{
	fprintf(stderr, "Parser error: %s\n", s);
}

ast_programa* parse_file(FILE* infile, int* _yynerrs)
{
	ast_programa* programa = NULL;
	__parse_file_init(infile);

	yyparse(&programa);
	if(yynerrs)
		*_yynerrs = yynerrs;

	__parse_file_free();
	return programa;
}
