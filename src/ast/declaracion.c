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

#include <stdlib.h>

#include "declaracion.h"
#include "fun_declaracion.h"
#include "var_declaracion.h"

static ast_declaracion* ast_declaracion_alloc();

static ast_declaracion* ast_declaracion_alloc()
{
	ast_declaracion* declaracion = malloc(sizeof(ast_declaracion));

	return declaracion;
}

ast_declaracion* ast_declaracion1(ast_var_declaracion* var_declaracion)
{
	ast_declaracion* declaracion = ast_declaracion_alloc();

	if(declaracion)
	{
		declaracion->tipo = AST_VAR_DECLARACION;
		declaracion->var  = var_declaracion;
	}

	return declaracion;
}

ast_declaracion* ast_declaracion2(ast_fun_declaracion* fun_declaracion)
{
	ast_declaracion* declaracion = ast_declaracion_alloc();

	if(declaracion)
	{
		declaracion->tipo = AST_FUN_DECLARACION;
		declaracion->fun  = fun_declaracion;
	}

	return declaracion;
}

void ast_declaracion_free(ast_declaracion* declaracion)
{
	if(declaracion)
	{
		switch(declaracion->tipo)
		{
			case AST_VAR_DECLARACION:
				ast_var_declaracion_free(declaracion->var);
				break;

			case AST_FUN_DECLARACION:
				ast_fun_declaracion_free(declaracion->fun);
				break;
		}
	}
	free(declaracion);
}
