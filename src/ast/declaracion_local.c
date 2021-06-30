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
#include "var_declaracion.h"

static ast_declaracion_local* ast_declaracion_local_alloc();

static ast_declaracion_local* ast_declaracion_local_alloc()
{
	ast_declaracion_local* declaracion_local = malloc(sizeof(ast_declaracion_local));

	if(declaracion_local)
	{
		*declaracion_local = (ast_declaracion_local)
		{
			.next            = NULL,
			.var_declaracion = NULL
		};
	}

	return declaracion_local;
}

ast_declaracion_local* ast_declaracion_local1(
	ast_declaracion_local* next,
	ast_var_declaracion*   var_declaracion
)
{
	ast_declaracion_local* declaracion_local = ast_declaracion_local_alloc();

	if(declaracion_local)
	{
		declaracion_local->next            = next;
		declaracion_local->var_declaracion = var_declaracion;
	}

	return declaracion_local;
}

ast_declaracion_local* ast_declaracion_local2()
{
	return ast_declaracion_local_alloc();
}

void ast_declaracion_local_free(ast_declaracion_local* declaracion_local)
{
	if(declaracion_local)
	{
		ast_declaracion_local_free(declaracion_local->next);
		ast_var_declaracion_free(declaracion_local->var_declaracion);
	}
	free(declaracion_local);
}
