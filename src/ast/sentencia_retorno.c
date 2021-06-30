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
#include "sentencia_retorno.h"

static ast_sentencia_retorno* ast_sentencia_retorno_alloc();

static ast_sentencia_retorno* ast_sentencia_retorno_alloc()
{
	ast_sentencia_retorno* sentencia_retorno = malloc(sizeof(ast_sentencia_retorno));

	if(sentencia_retorno)
		sentencia_retorno->expresion = NULL;

	return sentencia_retorno;
}

ast_sentencia_retorno* ast_sentencia_retorno1()
{
	return ast_sentencia_retorno_alloc();
}

ast_sentencia_retorno* ast_sentencia_retorno2(ast_expresion* expresion)
{
	ast_sentencia_retorno* sentencia_retorno = ast_sentencia_retorno_alloc();

	if(sentencia_retorno)
		sentencia_retorno->expresion = expresion;

	return sentencia_retorno;
}

void ast_sentencia_retorno_free(ast_sentencia_retorno* retorno)
{
	if(retorno)
	{
		ast_expresion_free(retorno->expresion);
	}
	free(retorno);
}
