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

#include "fun_declaracion.h"
#include "params.h"
#include "sent_compuesta.h"
#include "tipo.h"

static ast_fun_declaracion* ast_fun_declaracion_alloc();

static ast_fun_declaracion* ast_fun_declaracion_alloc()
{
	ast_fun_declaracion* fun_declaracion = malloc(sizeof(ast_fun_declaracion));

	if(fun_declaracion)
	{
		*fun_declaracion = (ast_fun_declaracion)
		{
			.tipo           = NULL,
			.ID             = NULL,
			.params         = NULL,
			.sent_compuesta = NULL
		};
	}

	return fun_declaracion;
}

ast_fun_declaracion* ast_fun_declaracion1(
	ast_tipo*           tipo,
	char*               ID,
	ast_params*         params,
	ast_sent_compuesta* sent_compuesta
)
{
	ast_fun_declaracion* fun_declaracion = ast_fun_declaracion_alloc();

	if(fun_declaracion)
	{
		fun_declaracion->tipo           = tipo;
		fun_declaracion->ID             = ID;
		fun_declaracion->params         = params;
		fun_declaracion->sent_compuesta = sent_compuesta;
	}

	return fun_declaracion;
}

void ast_fun_declaracion_free(ast_fun_declaracion* fun_declaracion)
{
	if(fun_declaracion)
	{
		ast_tipo_free(fun_declaracion->tipo);
		free(fun_declaracion->ID);
		ast_params_free(fun_declaracion->params);
		ast_sent_compuesta_free(fun_declaracion->sent_compuesta);
	}
	free(fun_declaracion);
}
