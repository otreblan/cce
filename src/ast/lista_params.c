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

#include "lista_params.h"
#include "param.h"

static ast_lista_params* ast_lista_params_alloc();

static ast_lista_params* ast_lista_params_alloc()
{
	ast_lista_params* lista_params = malloc(sizeof(ast_lista_params));

	if(lista_params)
	{
		*lista_params = (ast_lista_params)
		{
			.next  = NULL,
			.param = NULL
		};
	}

	return lista_params;
}

ast_lista_params* ast_lista_params1(ast_lista_params* next, ast_param* param)
{
	ast_lista_params* lista_params = ast_lista_params2(param);

	if(lista_params)
		lista_params->next = next;

	return lista_params;
}

ast_lista_params* ast_lista_params2(ast_param* param)
{
	ast_lista_params* lista_params = ast_lista_params_alloc();

	if(lista_params)
		lista_params->param = param;

	return lista_params;
}

void ast_lista_params_free(ast_lista_params* lista_params)
{
	if(lista_params)
	{
		ast_lista_params_free(lista_params->next);
		ast_param_free(lista_params->param);
	}
	free(lista_params);
};
