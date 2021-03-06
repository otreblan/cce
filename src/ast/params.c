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
#include "params.h"

static ast_params* ast_params_alloc();

static ast_params* ast_params_alloc()
{
	ast_params* params = malloc(sizeof(ast_params));

	if(params)
		params->lista_params = NULL;

	return params;
}

ast_params* ast_params1(ast_lista_params* lista_params)
{
	ast_params* params = ast_params_alloc();

	if(params)
		params->lista_params = lista_params;

	return params;
}

ast_params* ast_params2()
{
	return ast_params_alloc();
}

void ast_params_free(ast_params* params)
{
	if(params)
	{
		ast_lista_params_free(params->lista_params);
	}
	free(params);
}
