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

#include "declaracion_local.h"
#include "lista_sentencias.h"
#include "sent_compuesta.h"

static ast_sent_compuesta* ast_sent_compuesta_alloc();

static ast_sent_compuesta* ast_sent_compuesta_alloc()
{
	ast_sent_compuesta* sent_compuesta = malloc(sizeof(ast_sent_compuesta));

	if(sent_compuesta)
	{
		*sent_compuesta = (ast_sent_compuesta)
		{
			.declaracion_local = NULL,
			.lista_sentencias  = NULL
		};
	}

	return sent_compuesta;
}

ast_sent_compuesta* ast_sent_compuesta1(
	ast_declaracion_local* declaracion_local,
	ast_lista_sentencias*  lista_sentencias
)
{
	ast_sent_compuesta* sent_compuesta = ast_sent_compuesta_alloc();

	if(sent_compuesta)
	{
		sent_compuesta->declaracion_local = declaracion_local;
		sent_compuesta->lista_sentencias  = lista_sentencias;
	}

	return sent_compuesta;
}

void ast_sent_compuesta_free(ast_sent_compuesta* sent_compuesta)
{
	if(sent_compuesta)
	{
		ast_declaracion_local_free(sent_compuesta->declaracion_local);
		ast_lista_sentencias_free(sent_compuesta->lista_sentencias);
	}
	free(sent_compuesta);
}
