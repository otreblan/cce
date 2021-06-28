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
#include "lista_declaracion.h"

static ast_lista_declaracion* ast_lista_declaracion_alloc();

static ast_lista_declaracion* ast_lista_declaracion_alloc()
{
	ast_lista_declaracion* lista_declaracion = malloc(sizeof(ast_lista_declaracion));

	if(lista_declaracion)
	{
		*lista_declaracion = (ast_lista_declaracion)
		{
			.next        = NULL,
			.declaracion = NULL
		};
	}

	return lista_declaracion;
}

ast_lista_declaracion* ast_lista_declaracion1(ast_lista_declaracion* next, ast_declaracion* declaracion)
{
	ast_lista_declaracion* lista_declaracion = ast_lista_declaracion2(declaracion);

	if(lista_declaracion)
	{
		lista_declaracion->next = next;
	}

	return lista_declaracion;
}

ast_lista_declaracion* ast_lista_declaracion2(ast_declaracion* declaracion)
{
	ast_lista_declaracion* lista_declaracion = ast_lista_declaracion_alloc();

	if(lista_declaracion)
	{
		lista_declaracion->declaracion = declaracion;
	}

	return lista_declaracion;
}

void ast_lista_declaracion_free(ast_lista_declaracion* lista_declaracion)
{
	if(lista_declaracion)
	{
		ast_lista_declaracion_free(lista_declaracion->next);
		ast_declaracion_free(lista_declaracion->declaracion);
	}
	free(lista_declaracion);
}
