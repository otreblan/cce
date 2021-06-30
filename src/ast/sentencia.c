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

#include "sentencia.h"
#include "sentencia_expresion.h"
#include "sentencia_iteracion.h"
#include "sentencia_retorno.h"
#include "sentencia_seleccion.h"

static ast_sentencia* ast_sentencia_alloc();

static ast_sentencia* ast_sentencia_alloc()
{
	return malloc(sizeof(ast_sentencia));
}

ast_sentencia* ast_sentencia1(ast_sentencia_expresion* expresion)
{
	ast_sentencia* sentencia = ast_sentencia_alloc();

	if(sentencia)
	{
		*sentencia = (ast_sentencia)
		{
			.tipo      = AST_SENTENCIA_EXPRESION,
			.expresion = expresion
		};
	}

	return sentencia;
}

ast_sentencia* ast_sentencia2(ast_sentencia_seleccion* seleccion)
{
	ast_sentencia* sentencia = ast_sentencia_alloc();

	if(sentencia)
	{
		*sentencia = (ast_sentencia)
		{
			.tipo      = AST_SENTENCIA_SELECCION,
			.seleccion = seleccion
		};
	}

	return sentencia;
}

ast_sentencia* ast_sentencia3(ast_sentencia_iteracion* iteracion)
{
	ast_sentencia* sentencia = ast_sentencia_alloc();

	if(sentencia)
	{
		*sentencia = (ast_sentencia)
		{
			.tipo      = AST_SENTENCIA_ITERACION,
			.iteracion = iteracion
		};
	}

	return sentencia;
}

ast_sentencia* ast_sentencia4(ast_sentencia_retorno* retorno)
{
	ast_sentencia* sentencia = ast_sentencia_alloc();

	if(sentencia)
	{
		*sentencia = (ast_sentencia)
		{
			.tipo    = AST_SENTENCIA_RETORNO,
			.retorno = retorno
		};
	}

	return sentencia;
}

void ast_sentencia_free(ast_sentencia* sentencia)
{
	if(sentencia)
	{
		switch(sentencia->tipo)
		{
			case AST_SENTENCIA_RETORNO:
				ast_sentencia_retorno_free(sentencia->retorno);
				break;

			case AST_SENTENCIA_EXPRESION:
				ast_sentencia_expresion_free(sentencia->expresion);
				break;

			case AST_SENTENCIA_ITERACION:
				ast_sentencia_iteracion_free(sentencia->iteracion);
				break;

			case AST_SENTENCIA_SELECCION:
				ast_sentencia_seleccion_free(sentencia->seleccion);
				break;
		}
	}
	free(sentencia);
}
