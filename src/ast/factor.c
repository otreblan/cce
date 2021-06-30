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
#include "factor.h"
#include "var.h"

static ast_factor* ast_factor_alloc();

static ast_factor* ast_factor_alloc()
{
	return malloc(sizeof(ast_factor));
}

ast_factor* ast_factor1(ast_expresion* expresion)
{
	ast_factor* factor = ast_factor_alloc();

	if(factor)
	{
		*factor = (ast_factor)
		{
			.tipo      = AST_FACTOR_EXPRESION,
			.expresion = expresion
		};
	}

	return factor;
}

ast_factor* ast_factor2(ast_var* var)
{
	ast_factor* factor = ast_factor_alloc();

	if(factor)
	{
		*factor = (ast_factor)
		{
			.tipo = AST_FACTOR_EXPRESION,
			.var  = var
		};
	}

	return factor;
}

ast_factor* ast_factor3(ast_call* call)
{
	ast_factor* factor = ast_factor_alloc();

	if(factor)
	{
		*factor = (ast_factor)
		{
			.tipo = AST_FACTOR_EXPRESION,
			.call = call
		};
	}

	return factor;
}

ast_factor* ast_factor4(int NUM)
{
	ast_factor* factor = ast_factor_alloc();

	if(factor)
	{
		*factor = (ast_factor)
		{
			.tipo = AST_FACTOR_EXPRESION,
			.NUM  = NUM
		};
	}

	return factor;
}

void ast_factor_free(ast_factor* factor)
{
	if(factor)
	{
		switch(factor->tipo)
		{
			case AST_FACTOR_EXPRESION:
				ast_expresion_free(factor->expresion);
				break;

			case AST_FACTOR_VAR:
				ast_var_free(factor->var);
				break;

			case AST_FACTOR_CALL:
				ast_call_free(factor->call);
				break;

			case AST_FACTOR_NUM:
				break;
		}
	}
	free(factor);
}
