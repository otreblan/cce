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
	ast_op                   op;
	ast_args*                args;
	ast_call*                call;
	ast_declaracion*         declaracion;
	ast_declaracion_local*   declaracion_local;
	ast_expresion*           expresion;
	ast_fun_declaracion*     fun_declaracion;
	ast_lista_arg*           lista_arg;
	ast_lista_declaracion*   lista_declaracion;
	ast_lista_params*        lista_params;
	ast_lista_sentencias*    lista_sentencias;
	ast_param*               param;
	ast_params*              params;
	ast_sent_compuesta*      sent_compuesta;
	ast_sentencia_expresion* sentencia_expresion;
	ast_sentencia*           sentencia;
	ast_sentencia_iteracion* sentencia_iteracion;
	ast_sentencia_retorno*   sentencia_retorno;
	ast_sentencia_seleccion* sentencia_seleccion;
	ast_tipo*                tipo;
	ast_var_declaracion*     var_declaracion;
	ast_var*                 var;
}

%destructor { }                                   <intval>
%destructor { }                                   <op>
%destructor { free($$); }                         <strval>
%destructor { ast_args_free($$); }                <args>
%destructor { ast_call_free($$); }                <call>
%destructor { ast_declaracion_free($$); }         <declaracion>
%destructor { ast_declaracion_local_free($$); }   <declaracion_local>
%destructor { ast_expresion_free($$); }           <expresion>
%destructor { ast_fun_declaracion_free($$); }     <fun_declaracion>
%destructor { ast_lista_arg_free($$); }           <lista_arg>
%destructor { ast_lista_declaracion_free($$); }   <lista_declaracion>
%destructor { ast_lista_params_free($$); }        <lista_params>
%destructor { ast_lista_sentencias_free($$); }    <lista_sentencias>
%destructor { ast_param_free($$); }               <param>
%destructor { ast_params_free($$); }              <params>
%destructor { ast_sent_compuesta_free($$); }      <sent_compuesta>
%destructor { ast_sentencia_expresion_free($$); } <sentencia_expresion>
%destructor { ast_sentencia_free($$); }           <sentencia>
%destructor { ast_sentencia_iteracion_free($$); } <sentencia_iteracion>
%destructor { ast_sentencia_retorno_free($$); }   <sentencia_retorno>
%destructor { ast_sentencia_seleccion_free($$); } <sentencia_seleccion>
%destructor { ast_tipo_free($$); }                <tipo>
%destructor { ast_var_declaracion_free($$); }     <var_declaracion>
%destructor { ast_var_free($$); }                 <var>

%left '+' '-'
%left '*' '/'

%nonassoc "entonces"
%nonassoc sino

// Reservados
%token entero
%token mientras
%token retorno
%token sin_tipo
%token si
%token sino

// Operadores
%token relop_ge
%token relop_le
%token relop_gq
%token relop_lq
%token relop_eq
%token relop_ne

// Nodos
%type <op>                  addop
%type <args>                args
%type <call>                call
%type <declaracion>         declaracion
%type <declaracion_local>   declaracion_local
%type <expresion>           expresion_aditiva
%type <expresion>           expresion
%type <expresion>           expresion_simple
%type <expresion>           factor
%type <fun_declaracion>     fun_declaracion
%type <lista_arg>           lista_arg
%type <lista_declaracion>   lista_declaracion
%type <lista_params>        lista_params
%type <lista_sentencias>    lista_sentencias
%type <op>                  mulop
%type <param>               param
%type <params>              params
%type <op>                  relop
%type <sent_compuesta>      sent_compuesta
%type <sentencia_expresion> sentencia_expresion
%type <sentencia>           sentencia
%type <sentencia_iteracion> sentencia_iteracion
%type <sentencia_retorno>   sentencia_retorno
%type <sentencia_seleccion> sentencia_seleccion
%type <expresion>           term
%type <tipo>                tipo
%type <var_declaracion>     var_declaracion
%type <var>                 var

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
	| fun_declaracion { $$ = ast_declaracion2($1); }
	;

var_declaracion
	: tipo ID ';'             { $$ = ast_var_declaracion1($1, $2); }
	| tipo ID '[' NUM ']' ';' { $$ = ast_var_declaracion2($1, $2, $4); }
	;

tipo
	: entero   { $$ = ast_tipo_entero(); }
	| sin_tipo { $$ = ast_tipo_sin_tipo(); }
	;

fun_declaracion
	: tipo ID '(' params ')' sent_compuesta { $$ = ast_fun_declaracion1($1, $2, $4, $6); }
	;

params
	: lista_params { $$ = ast_params1($1); }
	| sin_tipo     { $$ = ast_params2(); }
	;

lista_params
	: param ',' lista_params { $$ = ast_lista_params1($3, $1); }
	| param                  { $$ = ast_lista_params2($1); }
	;

param
	: tipo ID         { $$ = ast_param1($1, $2); }
	| tipo ID '[' ']' { $$ = ast_param2($1, $2); }
	;

sent_compuesta
	: '{' declaracion_local lista_sentencias '}' { $$ = ast_sent_compuesta1($2, $3); }
	;

declaracion_local
	: var_declaracion declaracion_local { $$ = ast_declaracion_local1($2, $1); }
	| vacio                             { $$ = ast_declaracion_local2(); }
	;

lista_sentencias
	: sentencia lista_sentencias { $$ = ast_lista_sentencias1($2, $1); }
	| vacio                      { $$ = ast_lista_sentencias2(); }
	;

sentencia
	: sentencia_expresion { $$ = ast_sentencia1($1); }
	| sentencia_seleccion { $$ = ast_sentencia2($1); }
	| sentencia_iteracion { $$ = ast_sentencia3($1); }
	| sentencia_retorno   { $$ = ast_sentencia4($1); }
	;

sentencia_expresion
	: expresion ';' { $$ = ast_sentencia_expresion1($1); }
	| ';'           { $$ = ast_sentencia_expresion2(); }
	;

sentencia_seleccion
	: si '(' expresion ')' sentencia %prec "entonces" { $$ = ast_sentencia_seleccion1($3, $5); }
	| si '(' expresion ')' sentencia sino sentencia   { $$ = ast_sentencia_seleccion2($3, $5, $7); }
	;

sentencia_iteracion
	: mientras '(' expresion ')' '{' lista_sentencias '}' { $$ = ast_sentencia_iteracion1($3, $6); }
	;

sentencia_retorno
	: retorno ';'           { $$ = ast_sentencia_retorno1(); }
	| retorno expresion ';' { $$ = ast_sentencia_retorno2($2); }
	;

expresion
	: var '=' expresion { $$ = ast_expresion_asignacion($1, $3); }
	| expresion_simple  { $$ = $1; }
	;

var
	: ID                   { $$ = ast_var1($1); }
	| ID '[' expresion ']' { $$ = ast_var2($1, $3); }
	;

expresion_simple
	: expresion_aditiva relop expresion_aditiva { $$ = ast_expresion_operacion($1, $2, $3); }
	| expresion_aditiva                         { $$ = $1; }
	;

relop
	: relop_le { $$ = AST_LE; }
	| relop_lq { $$ = AST_LQ; }
	| relop_ge { $$ = AST_GE; }
	| relop_gq { $$ = AST_GQ; }
	| relop_eq { $$ = AST_EQ; }
	| relop_ne { $$ = AST_NE; }
	;

expresion_aditiva
	: expresion_aditiva addop term { $$ = ast_expresion_operacion($1, $2, $3); }
	| term                         { $$ = $1; }
	;

addop
	: '+' { $$ = AST_SUMA; }
	| '-' { $$ = AST_RESTA; }
	;

term
	: term mulop factor { $$ = ast_expresion_operacion($1, $2, $3); }
	| factor            { $$ = $1; }
	;

mulop
	: '*' { $$ = AST_MULTIPLICACION; }
	| '/' { $$ = AST_DIVISION; }
	;

factor
	: '(' expresion ')' { $$ = $2; }
	| var               { $$ = ast_expresion_var($1); }
	| call              { $$ = ast_expresion_call($1); }
	| NUM               { $$ = ast_expresion_num($1); }
	;

call
	: ID '(' args ')' { $$ = ast_call1($1, $3); }
	;

args
	: lista_arg { $$ = ast_args1($1); }
	| vacio     { $$ = ast_args2(); }
	;

lista_arg
	: expresion ',' lista_arg { $$ = ast_lista_arg1($1, $3); }
	| expresion               { $$ = ast_lista_arg2($1); }
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
