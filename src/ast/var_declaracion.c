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

#include "tipo.h"
#include "var_declaracion.h"

static ast_var_declaracion* ast_var_declaracion_alloc();

static ast_var_declaracion* ast_var_declaracion_alloc()
{
	ast_var_declaracion* var_declaracion = malloc(sizeof(ast_var_declaracion));

	if(var_declaracion)
	{
		*var_declaracion = (ast_var_declaracion)
		{
			.tipo       = NULL,
			.id         = NULL,
			.es_arreglo = false,
			.num        = 0
		};
	}

	return var_declaracion;
}

ast_var_declaracion* ast_var_declaracion1(ast_tipo* tipo, char* id)
{
	ast_var_declaracion* var_declaracion = malloc(sizeof(ast_var_declaracion));

	if(var_declaracion)
	{
		var_declaracion->tipo = tipo;
		var_declaracion->id   = id;
	}

	return var_declaracion;
}

ast_var_declaracion* ast_var_declaracion2(ast_tipo* tipo, char* id, int num)
{
	ast_var_declaracion* var_declaracion = ast_var_declaracion1(tipo, id);

	if(var_declaracion)
	{
		var_declaracion->es_arreglo = true;
		var_declaracion->num        = num;
	}

	return var_declaracion;
}

void ast_var_declaracion_free(ast_var_declaracion* var_declaracion)
{
	if(var_declaracion)
	{
		free(var_declaracion->tipo);
		free(var_declaracion->id);
	}
	free(var_declaracion);
}
