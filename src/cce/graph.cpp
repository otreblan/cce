// Compilador
// Copyright © 2021 otreblan
//
// cce is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// cce is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with cce.  If not, see <http://www.gnu.org/licenses/>.

#include <cstdio>
#include <string_view>

#include <fmt/core.h>
#include <fmt/compile.h>

#include "ast.h"
#include "graph.hpp"

template <typename T>
static void print_node (FILE* file, int n, const T& t);
static void print_edge (FILE* file, int n, int i);

static int str_graph  (FILE* file, int n, std::string_view str);
static int id_graph   (FILE* file, int n, std::string_view str);
static int char_graph (FILE* file, int n, char c);
static int num_graph  (FILE* file, int n, int num);

static int args_graph                (FILE* file, int n, const ast_args& args);
static int call_graph                (FILE* file, int n, const ast_call& call);
static int declaracion_graph         (FILE* file, int n, const ast_declaracion& declaracion);
static int declaracion_local_graph   (FILE* file, int n, const ast_declaracion_local& declaracion_local);
static int expresion_graph           (FILE* file, int n, const ast_expresion& expresion);
static int fun_declaracion_graph     (FILE* file, int n, const ast_fun_declaracion& fun_declaracion);
static int lista_arg_graph           (FILE* file, int n, const ast_lista_arg& lista_arg);
static int lista_declaracion_graph   (FILE* file, int n, const ast_lista_declaracion& lista_declaracion);
static int lista_params_graph        (FILE* file, int n, const ast_lista_params& lista_params);
static int lista_sentencias_graph    (FILE* file, int n, const ast_lista_sentencias& lista_sentencias);
static int op_graph                  (FILE* file, int n, const ast_op& relop);
static int param_graph               (FILE* file, int n, const ast_param& param);
static int params_graph              (FILE* file, int n, const ast_params& params);
static int sent_compuesta_graph      (FILE* file, int n, const ast_sent_compuesta& sent_compuesta);
static int sentencia_expresion_graph (FILE* file, int n, const ast_sentencia_expresion& sentencia_expresion);
static int sentencia_graph           (FILE* file, int n, const ast_sentencia& sentencia);
static int sentencia_iteracion_graph (FILE* file, int n, const ast_sentencia_iteracion& sentencia_iteracion);
static int sentencia_retorno_graph   (FILE* file, int n, const ast_sentencia_retorno& sentencia_retorno);
static int sentencia_seleccion_graph (FILE* file, int n, const ast_sentencia_seleccion& sentencia_seleccion);
static int tipo_graph                (FILE* file, int n, const ast_tipo& tipo);
static int var_declaracion_graph     (FILE* file, int n, const ast_var_declaracion& var_declaracion);
static int var_graph                 (FILE* file, int n, const ast_var& var);

template <typename T>
static void print_node(FILE* file, int n, const T& t)
{
	fmt::print(file, "\t{} [label=\"{}\"];\n", n, t);
}

static void print_edge(FILE* file, int n, int i)
{
	fmt::print(file, "\t{} -> {};\n", n, i);
}

static int args_graph(FILE* file, int n, const ast_args& args)
{
	int i = n;

	print_node(file, n, "args");

	if(args.lista_arg)
	{
		print_edge(file, n, i+1);
		i = lista_arg_graph(file, i+1, *args.lista_arg);
	}
	else
	{
		print_edge(file, n, i+1);
		i = str_graph(file, i+1, "\u03B5");
	}

	return i;
}

static int call_graph(FILE* file, int n, const ast_call& call)
{
	int i = n;

	print_node(file, n, "call");

	if(call.ID)
	{
		print_edge(file, n, i+1);
		i = id_graph(file, i+1, call.ID);
	}

	print_edge(file, n, i+1);
	i = char_graph(file, i+1, '(');

	if(call.args)
	{
		print_edge(file, n, i+1);
		i = args_graph(file, i+1, *call.args);
	}

	print_edge(file, n, i+1);
	i = char_graph(file, i+1, ')');

	return i;
}

static int declaracion_graph(FILE* file, int n, const ast_declaracion& declaracion)
{
	int i = n;
	print_node(file, n, "declaracion");

	switch(declaracion.tipo)
	{
	case AST_VAR_DECLARACION:
		if(declaracion.var)
		{
			print_edge(file, n, i+1);
			i = var_declaracion_graph(file, i+1, *declaracion.var);
		}
		break;

	case AST_FUN_DECLARACION:
		if(declaracion.fun)
		{
			print_edge(file, n, i+1);
			i = fun_declaracion_graph(file, i+1, *declaracion.fun);
		}
		break;
	}
	return i;
}

static int declaracion_local_graph(FILE* file, int n, const ast_declaracion_local& declaracion_local)
{
	int i = n;
	print_node(file, n, "declaracion_local");

	if(declaracion_local.var_declaracion && declaracion_local.next)
	{
		if(declaracion_local.var_declaracion)
		{
			print_edge(file, n, i+1);
			i = var_declaracion_graph(file, i+1, *declaracion_local.var_declaracion);
		}

		if(declaracion_local.next)
		{
			print_edge(file, n, i+1);
			i = declaracion_local_graph(file, i+1, *declaracion_local.next);
		}
	}
	else
	{
		print_edge(file, n, i+1);
		i = str_graph(file, i+1, "\u03B5");
	}

	return i;
}

static int expresion_graph(FILE* file, int n, const ast_expresion& expresion)
{
	int i = n;

	print_node(file, n, "expresion");

	switch(expresion.tipo)
	{
	case AST_ASIGNACION:
		if(expresion.asignacion.var)
		{
			print_edge(file, n, i+1);
			i = var_graph(file, i+1, *expresion.asignacion.var);
		}

		print_edge(file, n, i+1);
		i = char_graph(file, i+1, '=');

		if(expresion.asignacion.expresion)
		{
			print_edge(file, n, i+1);
			i = expresion_graph(file, i+1, *expresion.asignacion.expresion);
		}
		break;

	case AST_EXPRESION_SIMPLE:
		if(expresion.expresion1)
		{
			print_edge(file, n, i+1);
			i = expresion_graph(file, i+1, *expresion.expresion1);
		}

		print_edge(file, n, i+1);
		i = op_graph(file, i+1, expresion.op);

		if(expresion.expresion1)
		{
			print_edge(file, n, i+1);
			i = expresion_graph(file, i+1, *expresion.expresion2);
		}
		break;

	case AST_VAR:
		if(expresion.var)
		{
			print_edge(file, n, i+1);
			i = var_graph(file, i+1, *expresion.var);
		}
		break;

	case AST_CALL:
		if(expresion.call)
		{
			print_edge(file, n, i+1);
			i = call_graph(file, i+1, *expresion.call);
		}
		break;

	case AST_NUM:
		print_edge(file, n, i+1);
		i = num_graph(file, i+1, expresion.NUM);
		break;
	}

	return i;
}

static int fun_declaracion_graph(FILE* file, int n, const ast_fun_declaracion& fun_declaracion)
{
	int i = n;

	print_node(file, n, "fun_declaracion");

	if(fun_declaracion.tipo)
	{
		print_edge(file, n, i+1);
		i = tipo_graph(file, i+1, *fun_declaracion.tipo);
	}

	if(fun_declaracion.ID)
	{
		print_edge(file, n, i+1);
		i = id_graph(file, i+1, fun_declaracion.ID);
	}

	print_edge(file, n, i+1);
	i = char_graph(file, i+1, '(');

	if(fun_declaracion.params)
	{
		print_edge(file, n, i+1);
		i = params_graph(file, i+1, *fun_declaracion.params);
	}

	print_edge(file, n, i+1);
	i = char_graph(file, i+1, ')');

	if(fun_declaracion.sent_compuesta)
	{
		print_edge(file, n, i+1);
		i = sent_compuesta_graph(file, i+1, *fun_declaracion.sent_compuesta);
	}

	return i;
}

static int lista_arg_graph(FILE* file, int n, const ast_lista_arg& lista_arg)
{
	int i = n;

	print_node(file, n, "lista_arg");

	if(lista_arg.expresion)
	{
		print_edge(file, n, i+1);
		i = expresion_graph(file, i+1, *lista_arg.expresion);
	}

	if(lista_arg.next)
	{
		print_edge(file, n, i+1);
		i = char_graph(file, i+1, ',');

		print_edge(file, n, i+1);
		i = lista_arg_graph(file, i+1, *lista_arg.next);
	}

	return i;
}

static int lista_declaracion_graph(FILE* file, int n, const ast_lista_declaracion& lista_declaracion)
{
	int i = n;

	print_node(file, n, "lista_declaracion");

	if(lista_declaracion.declaracion)
	{
		print_edge(file, n, i+1);
		i = declaracion_graph(file, i+1, *lista_declaracion.declaracion);
	}

	if(lista_declaracion.next)
	{
		print_edge(file, n, i+1);
		i = lista_declaracion_graph(file, i+1, *lista_declaracion.next);
	}

	return i;
}

static int lista_params_graph(FILE* file, int n, const ast_lista_params& lista_params)
{
	int i = n;
	print_node(file, n, "lista_params");

	if(lista_params.param)
	{
		print_edge(file, n, i+1);
		i = param_graph(file, i+1, *lista_params.param);
	}

	if(lista_params.next)
	{
		print_edge(file, n, i+1);
		i = lista_params_graph(file, i+1, *lista_params.next);
	}

	return i;
}

static int lista_sentencias_graph(FILE* file, int n, const ast_lista_sentencias& lista_sentencias)
{
	int i = n;
	print_node(file, n, "lista_sentencias");

	if(lista_sentencias.sentencia && lista_sentencias.next)
	{
		if(lista_sentencias.sentencia)
		{
			print_edge(file, n, i+1);
			i = sentencia_graph(file, i+1, *lista_sentencias.sentencia);
		}

		if(lista_sentencias.next)
		{
			print_edge(file, n, i+1);
			i = lista_sentencias_graph(file, i+1, *lista_sentencias.next);
		}
	}
	else
	{
		print_edge(file, n, i+1);
		i = str_graph(file, i+1, "\u03B5");
	}

	return i;
}

static int op_graph (FILE* file, int n, const ast_op& relop)
{
	switch(relop)
	{
	case AST_LE:
		str_graph(file, n, "<");
		break;

	case AST_LQ:
		str_graph(file, n, "<=");
		break;

	case AST_GE:
		str_graph(file, n, ">");
		break;

	case AST_GQ:
		str_graph(file, n, ">=");
		break;

	case AST_EQ:
		str_graph(file, n, "==");
		break;

	case AST_NE:
		str_graph(file, n, "!=");
		break;

	case AST_SUMA:
		str_graph(file, n, "+");
		break;

	case AST_RESTA:
		str_graph(file, n, "-");
		break;

	case AST_MULTIPLICACION:
		str_graph(file, n, "*");
		break;

	case AST_DIVISION:
		str_graph(file, n, "/");
		break;
	}
	return n;
}

static int param_graph(FILE* file, int n, const ast_param& param)
{
	int i = n;

	print_node(file, n, "param");

	if(param.tipo)
	{
		print_edge(file, n, i+1);
		i = tipo_graph(file, i+1, *param.tipo);
	}

	if(param.ID)
	{
		print_edge(file, n, i+1);
		i = id_graph(file, i+1, param.ID);
	}

	if(param.arreglo)
	{
		print_edge(file, n, i+1);
		i = char_graph(file, i+1, '[');

		print_edge(file, n, i+1);
		i = char_graph(file, i+1, ']');
	}

	return i;
}

static int params_graph(FILE* file, int n, const ast_params& params)
{
	int i = n;
	print_node(file, n, "params");

	if(params.lista_params)
	{
		print_edge(file, n, i+1);
		i = lista_params_graph(file, i+1, *params.lista_params);
	}
	else
	{
		print_edge(file, n, i+1);
		i = str_graph(file, i+1, "sin_tipo");
	}

	return i;
}

static int sent_compuesta_graph(FILE* file, int n, const ast_sent_compuesta& sent_compuesta)
{
	int i = n;

	print_node(file, n, "sent_compuesta");

	print_edge(file, n, i+1);
	i = char_graph(file, i+1, '{');

	if(sent_compuesta.declaracion_local)
	{
		print_edge(file, n, i+1);
		i = declaracion_local_graph(file, i+1, *sent_compuesta.declaracion_local);
	}

	if(sent_compuesta.lista_sentencias)
	{
		print_edge(file, n, i+1);
		i = lista_sentencias_graph(file, i+1, *sent_compuesta.lista_sentencias);
	}

	print_edge(file, n, i+1);
	i = char_graph(file, i+1, '}');

	return i;
}

static int sentencia_expresion_graph(FILE* file, int n, const ast_sentencia_expresion& sentencia_expresion)
{
	int i = n;
	print_node(file, n, "sentencia_expresion");

	if(sentencia_expresion.expresion)
	{
		print_edge(file, n, i+1);
		i = expresion_graph(file, i+1, *sentencia_expresion.expresion);
	}

	print_edge(file, n, i+1);
	i = char_graph(file, i+1, ';');

	return i;
}

static int sentencia_graph(FILE* file, int n, const ast_sentencia& sentencia)
{
	int i = n;

	print_node(file, n, "sentencia");

	switch(sentencia.tipo)
	{
	case AST_SENTENCIA_EXPRESION:
		if(sentencia.expresion)
		{
			print_edge(file, n, i+1);
			i = sentencia_expresion_graph(file, i+1, *sentencia.expresion);
		}
		break;

	case AST_SENTENCIA_SELECCION:
		if(sentencia.seleccion)
		{
			print_edge(file, n, i+1);
			i = sentencia_seleccion_graph(file, i+1, *sentencia.seleccion);
		}
		break;

	case AST_SENTENCIA_ITERACION:
		if(sentencia.iteracion)
		{
			print_edge(file, n, i+1);
			i = sentencia_iteracion_graph(file, i+1, *sentencia.iteracion);
		}
		break;

	case AST_SENTENCIA_RETORNO:
		if(sentencia.retorno)
		{
			print_edge(file, n, i+1);
			i = sentencia_retorno_graph(file, i+1, *sentencia.retorno);
		}
		break;
	}

	return i;
}

static int sentencia_iteracion_graph(FILE* file, int n, const ast_sentencia_iteracion& sentencia_iteracion)
{
	int i = n;

	print_node(file, n, "sentencia_iteracion");

	print_edge(file, n, i+1);
	i = str_graph(file, i+1, "mientras");

	print_edge(file, n, i+1);
	i = char_graph(file, i+1, '(');

	if(sentencia_iteracion.expresion)
	{
		print_edge(file, n, i+1);
		i = expresion_graph(file, i+1, *sentencia_iteracion.expresion);
	}

	print_edge(file, n, i+1);
	i = char_graph(file, i+1, ')');

	print_edge(file, n, i+1);
	i = char_graph(file, i+1, '{');

	if(sentencia_iteracion.lista_sentencias)
	{
		print_edge(file, n, i+1);
		i = lista_sentencias_graph(file, i+1, *sentencia_iteracion.lista_sentencias);
	}

	print_edge(file, n, i+1);
	i = char_graph(file, i+1, '}');

	return i;
}

static int sentencia_retorno_graph(FILE* file, int n, const ast_sentencia_retorno& sentencia_retorno)
{
	int i = n;

	print_node(file, n, "sentencia_retorno");

	print_edge(file, n, i+1);
	i = str_graph(file, i+1, "retorno");

	if(sentencia_retorno.expresion)
	{
		print_edge(file, n, i+1);
		i = expresion_graph(file, i+1, *sentencia_retorno.expresion);
	}

	print_edge(file, n, i+1);
	i = char_graph(file, i+1, ';');

	return i;
}

static int sentencia_seleccion_graph(FILE* file, int n, const ast_sentencia_seleccion& sentencia_seleccion)
{
	int i = n;

	print_node(file, n, "sentencia_seleccion");

	print_edge(file, n, i+1);
	i = str_graph(file, i+1, "si");

	print_edge(file, n, i+1);
	i = char_graph(file, i+1, '(');

	if(sentencia_seleccion.expresion)
	{
		print_edge(file, n, i+1);
		i = expresion_graph(file, i+1, *sentencia_seleccion.expresion);
	}

	print_edge(file, n, i+1);
	i = char_graph(file, i+1, ')');

	if(sentencia_seleccion.sentencia1)
	{
		print_edge(file, n, i+1);
		i = sentencia_graph(file, i+1, *sentencia_seleccion.sentencia1);
	}

	return i;
}

static int tipo_graph(FILE* file, int n, const ast_tipo& tipo)
{
	int i = n;
	print_node(file, n, "tipo");

	switch(tipo.tipo)
	{
	case AST_SIN_TIPO:
		print_edge(file, n, i+1);
		i = str_graph(file, i+1, "sin_tipo");
		break;

	case AST_ENTERO:
		print_edge(file, n, i+1);
		i = str_graph(file, i+1, "entero");
		break;
	}

	return i;
}

static int var_declaracion_graph(FILE* file, int n, const ast_var_declaracion& var_declaracion)
{
	int i = n;
	print_node(file, n, "var_declaracion");

	if(var_declaracion.tipo)
	{
		print_edge(file, n, i+1);
		i = tipo_graph(file, i+1, *var_declaracion.tipo);
	}

	if(var_declaracion.id)
	{
		print_edge(file, n, i+1);
		i = id_graph(file, i+1, var_declaracion.id);
	}

	if(var_declaracion.es_arreglo)
	{
		print_edge(file, n, i+1);
		i = char_graph(file, i+1, '[');

		print_edge(file, n, i+1);
		i = num_graph(file, i+1, var_declaracion.num);

		print_edge(file, n, i+1);
		i = char_graph(file, i+1, ']');
	}

	print_edge(file, n, i+1);
	i = char_graph(file, i+1, ';');

	return i;
}

static int var_graph(FILE* file, int n, const ast_var& var)
{
	int i = n;

	print_node(file, n, "var");

	if(var.ID)
	{
		print_edge(file, n, i+1);
		i = id_graph(file, i+1, var.ID);
	}

	if(var.expresion)
	{
		print_edge(file, n, i+1);
		i = char_graph(file, i+1, '[');

		print_edge(file, n, i+1);
		i = expresion_graph(file, i+1, *var.expresion);

		print_edge(file, n, i+1);
		i = char_graph(file, i+1, ']');
	}

	return i;
}

static int str_graph(FILE* file, int n, std::string_view str)
{
	fmt::print(file, "\t{} [label=\"{}\", fillcolor=9, style=filled];\n", n, str);
	return n;
}

static int id_graph(FILE* file, int n, std::string_view str)
{
	fmt::print(file, "\t{} [label=\"\\\"{}\\\"\", fillcolor=1, style=filled];\n", n, str);
	return n;
}

static int char_graph(FILE* file, int n, char c)
{
	fmt::print(file, "\t{} [label=\"'{}'\", fillcolor=5, style=filled];\n", n, c);
	return n;
}

static int num_graph(FILE* file, int n, int num)
{
	fmt::print(file, "\t{} [label=\"{}\", fillcolor=3, style=filled];\n", n, num);
	return n;
}

void cce::ast_graph(FILE* file, const ast_programa* programa)
{
	int n = 0;
	int i = n;
	fmt::print(file, "{}",
		"digraph D {\n"
		"node [colorscheme = paired9]\n"
	);

	if(programa)
	{
		print_node(file, n, "programa");
		if(programa->lista_declaraciones)
		{
			print_edge(file, n, i+1);
			i = lista_declaracion_graph(file, i+1, *programa->lista_declaraciones);
		}
	}

	fmt::print(file, "{}\n", "}");
}
