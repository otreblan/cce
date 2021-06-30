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
#include "lista_sentencias.h"
#include "sentencia_iteracion.h"

static ast_sentencia_iteracion* ast_sentencia_iteracion_alloc();

static ast_sentencia_iteracion* ast_sentencia_iteracion_alloc()
{
	ast_sentencia_iteracion* sentencia_iteracion = malloc(sizeof(ast_sentencia_iteracion));

	if(sentencia_iteracion)
	{
		*sentencia_iteracion = (ast_sentencia_iteracion)
		{
			.expresion        = NULL,
			.lista_sentencias = NULL
		};
	}

	return sentencia_iteracion;
}

ast_sentencia_iteracion* ast_sentencia_iteracion1(
	ast_expresion*        expresion,
	ast_lista_sentencias* lista_sentencias
)
{
	ast_sentencia_iteracion* sentencia_iteracion = ast_sentencia_iteracion_alloc();

	if(sentencia_iteracion)
	{
		sentencia_iteracion->expresion        = expresion;
		sentencia_iteracion->lista_sentencias = lista_sentencias;
	}

	return sentencia_iteracion;
}

void ast_sentencia_iteracion_free(ast_sentencia_iteracion* sentencia_iteracion)
{
	if(sentencia_iteracion)
	{
		ast_expresion_free(sentencia_iteracion->expresion);
		//ast_lista_sentencias_free(sentencia_iteracion->lista_sentencias);
	}
	free(sentencia_iteracion);
}
