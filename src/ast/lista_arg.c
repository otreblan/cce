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

#include "expresion.h"
#include "lista_arg.h"

static ast_lista_arg* ast_lista_alloc();

static ast_lista_arg* ast_lista_alloc()
{
	ast_lista_arg* lista_arg = malloc(sizeof(ast_lista_arg));

	if(lista_arg)
	{
		*lista_arg = (ast_lista_arg)
		{
			.expresion = NULL,
			.next      = NULL
		};
	}

	return lista_arg;
}

ast_lista_arg* ast_lista_arg1(ast_expresion* expresion, ast_lista_arg* next)
{
	ast_lista_arg* lista_arg = ast_lista_arg2(expresion);

	if(lista_arg)
		lista_arg->next = next;

	return lista_arg;
}

ast_lista_arg* ast_lista_arg2(ast_expresion* expresion)
{
	ast_lista_arg* lista_arg = ast_lista_alloc();

	if(lista_arg)
		lista_arg->expresion = expresion;

	return lista_arg;
}

void ast_lista_arg_free(ast_lista_arg* lista_arg)
{
	if(lista_arg)
	{
		//ast_expresion_free(lista_arg->expresion);
		ast_lista_arg_free(lista_arg->next);
	}
	free(lista_arg);
}
