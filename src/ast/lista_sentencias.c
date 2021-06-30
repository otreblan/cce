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

#include "lista_sentencias.h"
#include "sentencia.h"

static ast_lista_sentencias* ast_lista_sentencias_alloc();

static ast_lista_sentencias* ast_lista_sentencias_alloc()
{
	ast_lista_sentencias* lista_sentencias = malloc(sizeof(ast_lista_sentencias));

	if(lista_sentencias)
	{
		*lista_sentencias = (ast_lista_sentencias)
		{
			.next      = NULL,
			.sentencia = NULL
		};
	}

	return lista_sentencias;
}

ast_lista_sentencias* ast_lista_sentencias1(
	ast_lista_sentencias* next,
	ast_sentencia*        sentencia
)
{
	ast_lista_sentencias* lista_sentencias = ast_lista_sentencias_alloc();

	if(lista_sentencias)
	{
		lista_sentencias->next      = next;
		lista_sentencias->sentencia = sentencia;
	}

	return lista_sentencias;
}

ast_lista_sentencias* ast_lista_sentencias2()
{
	return ast_lista_sentencias_alloc();
}

void ast_lista_sentencias_free(ast_lista_sentencias* lista_sentencias)
{
	if(lista_sentencias)
	{
		ast_lista_sentencias_free(lista_sentencias->next);
		ast_sentencia_free(lista_sentencias->sentencia);
	}
	free(lista_sentencias);
}
