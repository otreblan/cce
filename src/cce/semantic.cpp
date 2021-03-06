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
#include <iostream>
#include <string_view>
#include <vector>
#include <string>

#include <fmt/core.h>
#include <fmt/compile.h>

#include "ast.h"
#include "semantic.hpp"


// Tabla de id y tipo
//std::vector<table_elem> table_id;

std::map <std::string_view, table_elem> table_id;
int n_errors = 0;

template <typename T>
static void print_node (FILE* file, int n, const T& t);
static void print_edge (FILE* file, int n, int i);

static int str_graph  (FILE* file, int n, std::string_view str);
static int id_graph   (FILE* file, int n, std::string_view str);
static int char_graph (FILE* file, int n, char c);
static int num_graph  (FILE* file, int n, int num);

static int args_graph                (FILE* file, int n, const ast_args& args);
static int call_graph                (FILE* file, int n, const ast_call& call);
static int declaracion_graph         (FILE* file, int n, const ast_declaracion& declaracion, cce::label_t &next_label);
static int declaracion_local_graph   (FILE* file, int n, const ast_declaracion_local& declaracion_local);
static int expresion_graph           (FILE* file, int n, const ast_expresion& expresion);
static int fun_declaracion_graph     (FILE* file, int n, const ast_fun_declaracion& fun_declaracion, cce::label_t &next_label);
static int lista_arg_graph           (FILE* file, int n, const ast_lista_arg& lista_arg);
static int lista_declaracion_graph   (FILE* file, int n, const ast_lista_declaracion& lista_declaracion, cce::label_t &next_label);
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
	//fmt::print(file, "\t{} [label=\"{}\"];\n", n, t);
}

static void print_edge(FILE* file, int n, int i)
{
	//fmt::print(file, "\t{} -> {};\n", n, i);
}

static int args_graph(FILE* file, int n, const ast_args& args)
{
	int i = n;

	if(args.lista_arg)
	{
		i = lista_arg_graph(file, i+1, *args.lista_arg);
	}
	else
	{
		i = str_graph(file, i+1, "\u03B5");
	}

	return i;
}

int get_number_args(ast_args args){
	int ans = 0;

	if (args.lista_arg){
		ans ++;
	}
	auto lista_args = args.lista_arg;


	while (true)
	{
		if (lista_args->next){
			lista_args = lista_args->next;
			ans ++;
		}else{
			break;	
		}
	}
	return ans;

}

static int call_graph(FILE* file, int n, const ast_call& call)
{
	int i = n;
	
	if (call.ID and call.args){
		// revisar si existe la declaración
		
		std::string_view id_name{call.ID};
		
		
		// verificar los args
		

		if (table_id.find(id_name) != table_id.end()){
			
			table_elem element = table_id.find(id_name)->second;
			
			//std::cout << " id call in table: " << id_name << std::endl;

			// elementos sin 
			//if (element.simb_tipo == )

			int n_args1 = element.args.size();

			int n_args2 = get_number_args(*call.args);
			
			//std::cout <<"n2: " <<n_args2 << std::endl;

			// numero de argumentos diferentes
			if (n_args1 != n_args2 ) n_errors ++;

 
		}else{
			if (id_name != "entrada" and id_name != "salida"){
				n_errors ++;
			}
		}

	}

	if(call.ID)
	{
		i = id_graph(file, i+1, call.ID);
	}

	i = char_graph(file, i+1, '(');

	if(call.args)
	{
		i = args_graph(file, i+1, *call.args);
	}

	i = char_graph(file, i+1, ')');

	return i;
}

static int declaracion_graph(FILE* file, int n, const ast_declaracion& declaracion, cce::label_t &next_label)
{
	int i = n;
	
	switch(declaracion.tipo)
	{
	case AST_VAR_DECLARACION:
		if(declaracion.var)
		{
			i = var_declaracion_graph(file, i+1, *declaracion.var);
		}
		break;

	case AST_FUN_DECLARACION:
		if(declaracion.fun)
		{
			i = fun_declaracion_graph(file, i+1, *declaracion.fun, next_label);
		}
		break;
	}
	return i;
}

static int declaracion_local_graph(FILE* file, int n, const ast_declaracion_local& declaracion_local)
{
	int i = n;
	
	if(declaracion_local.var_declaracion && declaracion_local.next)
	{
		if(declaracion_local.var_declaracion)
		{
			i = var_declaracion_graph(file, i+1, *declaracion_local.var_declaracion);
		}

		if(declaracion_local.next)
		{
			i = declaracion_local_graph(file, i+1, *declaracion_local.next);
		}
	}
	else
	{
		i = str_graph(file, i+1, "\u03B5");
	}

	return i;
}

static int expresion_graph(FILE* file, int n, const ast_expresion& expresion)
{
	int i = n;

	switch(expresion.tipo)
	{
	case AST_ASIGNACION:
		if(expresion.asignacion.var)
		{
			i = var_graph(file, i+1, *expresion.asignacion.var);
		}

		i = char_graph(file, i+1, '=');

		if(expresion.asignacion.expresion)
		{
			i = expresion_graph(file, i+1, *expresion.asignacion.expresion);
		}
		break;

	case AST_EXPRESION_SIMPLE:
		if(expresion.expresion1)
		{
			i = expresion_graph(file, i+1, *expresion.expresion1);
		}

		i = op_graph(file, i+1, expresion.op);

		if(expresion.expresion1)
		{
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

std::vector<arg_elem> get_params(const ast_params& params){
	
	std::vector<arg_elem> ans;

	if (params.lista_params){

		auto lista_params = *params.lista_params;
		
		bool has_next = true;
		while (true)
		{
			auto param = *lista_params.param;

			if (param.tipo and param.ID){
				arg_elem elem;
				elem.id        = param.ID;
				elem.tipo      = (*param.tipo).tipo;
				elem.simb_tipo = simbolo_tipo::VARIABLE;
				elem.isArray   = param.arreglo;
				elem.size      = 1;
				ans.push_back(elem);
			}
			if (!lista_params.next){
				break;
			}
			lista_params = *lista_params.next;
		}	
	}
	
	return ans;
}

std::vector<arg_elem> get_local_vars(const ast_sent_compuesta & sent_compuesta){

	std::vector<arg_elem> ans;	

	if(sent_compuesta.declaracion_local)
	{	
		auto current_declaracion_local = sent_compuesta.declaracion_local;
		while (true)
		{
			if (current_declaracion_local->var_declaracion and current_declaracion_local->next){
				
				// añadir var declaracion al verctor ans

				ast_var_declaracion var_declaracion = *current_declaracion_local->var_declaracion;
				
				if (var_declaracion.tipo and var_declaracion.id){
					arg_elem elem;
					elem.id        = var_declaracion.id;
					elem.tipo      = (*var_declaracion.tipo).tipo;
					elem.isArray   = var_declaracion.es_arreglo;
					elem.size      = elem.isArray ? var_declaracion.num : 1;
					elem.simb_tipo = simbolo_tipo::VARIABLE;
					ans.push_back(elem);
				}  

				current_declaracion_local = current_declaracion_local->next;

			}else{
				break;
			}
			
		}
	}
	return ans;

	
}

static int fun_declaracion_graph(FILE* file, int n, const ast_fun_declaracion& fun_declaracion, cce::label_t &next_label)
{
	int i = n;

    // Si tiene un id asociado
    
    if (fun_declaracion.tipo and fun_declaracion.ID){
        table_elem elem;
        elem.id_name = fun_declaracion.ID;
        elem.tipo = (*fun_declaracion.tipo).tipo;
		elem.simb_tipo = simbolo_tipo::FUNCION;
		elem.isArray = false;
		elem.label = next_label++; // alloc label


		if (fun_declaracion.params){
			elem.args = get_params(*fun_declaracion.params); 
		}
		// añadir parametros 
		if (fun_declaracion.sent_compuesta){
			elem.local_vars = get_local_vars(*fun_declaracion.sent_compuesta);

		}

			
        table_id.insert({elem.id_name, elem});
    }
    

	if(fun_declaracion.tipo)
	{
		i = tipo_graph(file, i+1, *fun_declaracion.tipo);
	}

	if(fun_declaracion.ID)
	{
		i = id_graph(file, i+1, fun_declaracion.ID);
	}

	i = char_graph(file, i+1, '(');

	if(fun_declaracion.params)
	{
		i = params_graph(file, i+1, *fun_declaracion.params);
	}

	i = char_graph(file, i+1, ')');

	if(fun_declaracion.sent_compuesta)
	{
		i = sent_compuesta_graph(file, i+1, *fun_declaracion.sent_compuesta);
	}

	return i;
}

static int lista_arg_graph(FILE* file, int n, const ast_lista_arg& lista_arg)
{
	int i = n;

	if(lista_arg.expresion)
	{
		i = expresion_graph(file, i+1, *lista_arg.expresion);
	}
	
	if(lista_arg.next)
	{
		i = char_graph(file, i+1, ',');

		i = lista_arg_graph(file, i+1, *lista_arg.next);
	}

	return i;
}

static int lista_declaracion_graph(FILE* file, int n, const ast_lista_declaracion& lista_declaracion, cce::label_t &next_label)
{
	int i = n;

	
	if(lista_declaracion.declaracion)
	{
		i = declaracion_graph(file, i+1, *lista_declaracion.declaracion, next_label);
	}

	if(lista_declaracion.next)
	{
		i = lista_declaracion_graph(file, i+1, *lista_declaracion.next, next_label);
	}

	return i;
}

static int lista_params_graph(FILE* file, int n, const ast_lista_params& lista_params)
{
	int i = n;

	if(lista_params.param)
	{
		i = param_graph(file, i+1, *lista_params.param);
	}

	if(lista_params.next)
	{
		i = lista_params_graph(file, i+1, *lista_params.next);
	}

	return i;
}

static int lista_sentencias_graph(FILE* file, int n, const ast_lista_sentencias& lista_sentencias)
{
	int i = n;

	if(lista_sentencias.sentencia && lista_sentencias.next)
	{
		if(lista_sentencias.sentencia)
		{
			i = sentencia_graph(file, i+1, *lista_sentencias.sentencia);
		}

		if(lista_sentencias.next)
		{
			i = lista_sentencias_graph(file, i+1, *lista_sentencias.next);
		}
	}
	else
	{
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


    if (param.tipo and param.ID){
        table_elem elem;
        elem.id_name = param.ID;
        elem.tipo = (*param.tipo).tipo;
		elem.simb_tipo = simbolo_tipo::VARIABLE;
		elem.isArray = param.arreglo;
        table_id.insert({ elem.id_name ,elem});
    }

	if(param.tipo)
	{
		i = tipo_graph(file, i+1, *param.tipo);
	}
    
	if(param.ID)
	{
		i = id_graph(file, i+1, param.ID);
	}

	if(param.arreglo)
	{
		i = char_graph(file, i+1, '[');

		i = char_graph(file, i+1, ']');
	}

	return i;
}



static int params_graph(FILE* file, int n, const ast_params& params)
{
	int i = n;

	if(params.lista_params)
	{
		i = lista_params_graph(file, i+1, *params.lista_params);
	}
	else
	{
        // 
		i = str_graph(file, i+1, "sin_tipo");
	}

	return i;
}

static int sent_compuesta_graph(FILE* file, int n, const ast_sent_compuesta& sent_compuesta)
{
	int i = n;

	
	i = char_graph(file, i+1, '{');

	if(sent_compuesta.declaracion_local)
	{
		i = declaracion_local_graph(file, i+1, *sent_compuesta.declaracion_local);
	}

	if(sent_compuesta.lista_sentencias)
	{
		i = lista_sentencias_graph(file, i+1, *sent_compuesta.lista_sentencias);
	}
	i = char_graph(file, i+1, '}');

	return i;
}

static int sentencia_expresion_graph(FILE* file, int n, const ast_sentencia_expresion& sentencia_expresion)
{
	int i = n;

	if(sentencia_expresion.expresion)
	{
		i = expresion_graph(file, i+1, *sentencia_expresion.expresion);
	}

	
	i = char_graph(file, i+1, ';');

	return i;
}

static int sentencia_graph(FILE* file, int n, const ast_sentencia& sentencia)
{
	int i = n;

	switch(sentencia.tipo)
	{
	case AST_SENTENCIA_EXPRESION:
		if(sentencia.expresion)
		{
			i = sentencia_expresion_graph(file, i+1, *sentencia.expresion);
		}
		break;

	case AST_SENTENCIA_SELECCION:
		if(sentencia.seleccion)
		{
			i = sentencia_seleccion_graph(file, i+1, *sentencia.seleccion);
		}
		break;

	case AST_SENTENCIA_ITERACION:
		if(sentencia.iteracion)
		{
			i = sentencia_iteracion_graph(file, i+1, *sentencia.iteracion);
		}
		break;

	case AST_SENTENCIA_RETORNO:
		if(sentencia.retorno)
		{
			i = sentencia_retorno_graph(file, i+1, *sentencia.retorno);
		}
		break;
	}

	return i;
}

static int sentencia_iteracion_graph(FILE* file, int n, const ast_sentencia_iteracion& sentencia_iteracion)
{
	int i = n;

	i = str_graph(file, i+1, "mientras");

	i = char_graph(file, i+1, '(');

	if(sentencia_iteracion.expresion)
	{
		i = expresion_graph(file, i+1, *sentencia_iteracion.expresion);
	}

	i = char_graph(file, i+1, ')');

	i = char_graph(file, i+1, '{');

	if(sentencia_iteracion.lista_sentencias)
	{
		i = lista_sentencias_graph(file, i+1, *sentencia_iteracion.lista_sentencias);
	}

	i = char_graph(file, i+1, '}');

	return i;
}

static int sentencia_retorno_graph(FILE* file, int n, const ast_sentencia_retorno& sentencia_retorno)
{
	int i = n;

	i = str_graph(file, i+1, "retorno");

	if(sentencia_retorno.expresion)
	{
		i = expresion_graph(file, i+1, *sentencia_retorno.expresion);
	}

	
	i = char_graph(file, i+1, ';');

	return i;
}

static int sentencia_seleccion_graph(FILE* file, int n, const ast_sentencia_seleccion& sentencia_seleccion)
{
	int i = n;


	i = str_graph(file, i+1, "si");

	i = char_graph(file, i+1, '(');

	if(sentencia_seleccion.expresion)
	{
		i = expresion_graph(file, i+1, *sentencia_seleccion.expresion);
	}

	i = char_graph(file, i+1, ')');

	if(sentencia_seleccion.sentencia1)
	{
		i = sentencia_graph(file, i+1, *sentencia_seleccion.sentencia1);
	}

	return i;
}

static int tipo_graph(FILE* file, int n, const ast_tipo& tipo)
{
	int i = n;

	switch(tipo.tipo)
	{
	case AST_SIN_TIPO:
		i = str_graph(file, i+1, "sin_tipo");
		break;

	case AST_ENTERO:
		i = str_graph(file, i+1, "entero");
		break;
	}

	return i;
}

static int var_declaracion_graph(FILE* file, int n, const ast_var_declaracion& var_declaracion)
{
	int i = n;
	
    if (var_declaracion.tipo and var_declaracion.id){
        table_elem elem;
        elem.id_name = var_declaracion.id;
        elem.tipo = (*var_declaracion.tipo).tipo;
        elem.isArray = var_declaracion.es_arreglo;
		elem.simb_tipo = simbolo_tipo::VARIABLE;
		
		table_id.insert({elem.id_name, elem});
	}  

	if(var_declaracion.tipo)
	{
		i = tipo_graph(file, i+1, *var_declaracion.tipo);
	}

	if(var_declaracion.id)
	{
		i = id_graph(file, i+1, var_declaracion.id);
	}

	if(var_declaracion.es_arreglo)
	{
		i = char_graph(file, i+1, '[');

		i = num_graph(file, i+1, var_declaracion.num);

		i = char_graph(file, i+1, ']');
	}


	i = char_graph(file, i+1, ';');

	return i;
}

static int var_graph(FILE* file, int n, const ast_var& var)
{
	int i = n;


	if(var.ID)
	{
		i = id_graph(file, i+1, var.ID);
	}

	if(var.expresion)
	{
		i = char_graph(file, i+1, '[');

		i = expresion_graph(file, i+1, *var.expresion);

		i = char_graph(file, i+1, ']');
	}

	return i;
}

static int str_graph(FILE* file, int n, std::string_view str)
{
	return n;
}

static int id_graph(FILE* file, int n, std::string_view str)
{
	return n;
}

static int char_graph(FILE* file, int n, char c)
{
	return n;
}

static int num_graph(FILE* file, int n, int num)
{
	return n;
}

std::map<std::string_view ,table_elem> cce::ast_semantic(FILE* file, const ast_programa* programa, int & errors, cce::label_t &next_label)
{
	int n = 0;
	int i = n;

	if(programa)
	{
		if(programa->lista_declaraciones)
		{
			i = lista_declaracion_graph(file, i+1, *programa->lista_declaraciones, next_label);
		}
	}
    
	errors = n_errors;

    return table_id;
}
