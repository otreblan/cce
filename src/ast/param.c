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

#include "param.h"
#include "tipo.h"

static ast_param* ast_param_alloc();

static ast_param* ast_param_alloc()
{
	ast_param* param = malloc(sizeof(ast_param));

	if(param)
	{
		*param = (ast_param)
		{
			.tipo    = NULL,
			.ID      = NULL,
			.arreglo = false
		};
	}

	return param;
}

ast_param* ast_param1(ast_tipo* tipo, char* ID)
{
	ast_param* param = ast_param_alloc();

	if(param)
	{
		param->tipo = tipo;
		param->ID   = ID;
	}

	return param;
}

ast_param* ast_param2(ast_tipo* tipo, char* ID)
{
	ast_param* param = ast_param1(tipo, ID);

	if(param)
		param->arreglo = true;

	return param;
}

void ast_param_free(ast_param* param)
{
	if(param)
	{
		ast_tipo_free(param->tipo);
		free(param->ID);
	}
	free(param);
}
