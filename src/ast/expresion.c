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

#include "call.h"
#include "expresion.h"
#include "var.h"

static ast_expresion* ast_expresion_alloc();

static ast_expresion* ast_expresion_alloc()
{
	return malloc(sizeof(ast_expresion));
}

ast_expresion* ast_expresion_asignacion(ast_var* var, ast_expresion* expresion)
{
	ast_expresion* _expresion = ast_expresion_alloc();

	if(_expresion)
	{
		*_expresion = (ast_expresion)
		{
			.tipo       = AST_ASIGNACION,
			.asignacion =
			{
				.var       = var,
				.expresion = expresion
			}
		};
	}

	return _expresion;
}

ast_expresion* ast_expresion_operacion(ast_expresion* expresion1, ast_op op, ast_expresion* expresion2)
{
	ast_expresion* expresion = ast_expresion_alloc();

	if(expresion)
	{
		*expresion = (ast_expresion)
		{
			.tipo       = AST_EXPRESION_SIMPLE,
			.expresion1 = expresion1,
			.op         = op,
			.expresion2 = expresion2
		};
	}

	return expresion;
}

ast_expresion* ast_expresion_var(ast_var* var)
{
	ast_expresion* expresion = ast_expresion_alloc();

	if(expresion)
	{
		*expresion = (ast_expresion)
		{
			.tipo = AST_VAR,
			.var  = var
		};
	}

	return expresion;
}

ast_expresion* ast_expresion_call(ast_call* call)
{
	ast_expresion* expresion = ast_expresion_alloc();

	if(expresion)
	{
		*expresion = (ast_expresion)
		{
			.tipo = AST_CALL,
			.call = call
		};
	}

	return expresion;
}

ast_expresion* ast_expresion_num(int NUM)
{
	ast_expresion* expresion = ast_expresion_alloc();

	if(expresion)
	{
		*expresion = (ast_expresion)
		{
			.tipo = AST_NUM,
			.NUM = NUM
		};
	}

	return expresion;
}


void ast_expresion_free(ast_expresion* expresion)
{
	if(expresion)
	{
		switch(expresion->tipo)
		{
			case AST_ASIGNACION:
				ast_var_free(expresion->asignacion.var);
				ast_expresion_free(expresion->asignacion.expresion);
				break;

			case AST_EXPRESION_SIMPLE:
				ast_expresion_free(expresion->expresion1);
				ast_expresion_free(expresion->expresion2);
				break;

			case AST_VAR:
				ast_var_free(expresion->var);
				break;

			case AST_CALL:
				ast_call_free(expresion->call);
				break;

			case AST_NUM:
				break;
		}
	}
	free(expresion);
}
