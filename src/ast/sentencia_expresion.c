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
#include "sentencia_expresion.h"

static ast_sentencia_expresion* ast_sentencia_expresion_alloc();

static ast_sentencia_expresion* ast_sentencia_expresion_alloc()
{
	ast_sentencia_expresion* sentencia_expresion = malloc(sizeof(ast_sentencia_expresion));

	if(sentencia_expresion)
		sentencia_expresion->expresion = NULL;

	return sentencia_expresion;
}

ast_sentencia_expresion* ast_sentencia_expresion1(ast_expresion* expresion)
{
	ast_sentencia_expresion* sentencia_expresion = ast_sentencia_expresion_alloc();

	if(sentencia_expresion)
		sentencia_expresion->expresion = expresion;

	return sentencia_expresion;
}

ast_sentencia_expresion* ast_sentencia_expresion2()
{
	return ast_sentencia_expresion_alloc();
}

void ast_sentencia_expresion_free(ast_sentencia_expresion* expresion)
{
	if(expresion)
	{
		ast_expresion_free(expresion->expresion);
	}
	free(expresion);
}
