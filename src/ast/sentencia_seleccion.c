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
#include "sentencia.h"
#include "sentencia_seleccion.h"

static ast_sentencia_seleccion* ast_sentencia_seleccion_alloc();

static ast_sentencia_seleccion* ast_sentencia_seleccion_alloc()
{
	ast_sentencia_seleccion* sentencia_seleccion = malloc(sizeof(ast_sentencia_seleccion));

	if(sentencia_seleccion)
	{
		*sentencia_seleccion = (ast_sentencia_seleccion)
		{
			.expresion  = NULL,
			.sentencia1 = NULL,
			.sentencia2 = NULL
		};
	}

	return sentencia_seleccion;
}

ast_sentencia_seleccion* ast_sentencia_seleccion1(
	ast_expresion* expresion,
	ast_sentencia* sentencia
)
{
	ast_sentencia_seleccion* sentencia_seleccion = ast_sentencia_seleccion_alloc();

	if(sentencia_seleccion)
	{
		sentencia_seleccion->expresion  = expresion;
		sentencia_seleccion->sentencia1 = sentencia;
	}

	return sentencia_seleccion;
}

ast_sentencia_seleccion* ast_sentencia_seleccion2(
	ast_expresion* expresion,
	ast_sentencia* sentencia1,
	ast_sentencia* sentencia2
)
{
	ast_sentencia_seleccion* sentencia_seleccion = ast_sentencia_seleccion1(expresion, sentencia1);

	if(sentencia_seleccion)
		sentencia_seleccion->sentencia2 = sentencia2;

	return sentencia_seleccion;
}

void ast_sentencia_seleccion_free(ast_sentencia_seleccion* sentencia_seleccion)
{
	if(sentencia_seleccion)
	{
		ast_expresion_free(sentencia_seleccion->expresion);
		//ast_sentencia_free(sentencia_seleccion->sentencia1);
		//ast_sentencia_free(sentencia_seleccion->sentencia2);
	}
	free(sentencia_seleccion);
}
