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

#include "expresion_aditiva.h"
#include "expresion_simple.h"
#include "relop.h"

static ast_expresion_simple* ast_expresion_simple_alloc();

static ast_expresion_simple* ast_expresion_simple_alloc()
{
	ast_expresion_simple* expresion_simple = malloc(sizeof(ast_expresion_simple));

	if(expresion_simple)
	{
		*expresion_simple = (ast_expresion_simple)
		{
			.expresion_aditiva1 = NULL,
			.relop              = NULL,
			.expresion_aditiva2 = NULL
		};
	}

	return expresion_simple;
}

ast_expresion_simple* ast_expresion_simple1(
	ast_expresion_aditiva* expresion_aditiva1,
	ast_relop*             relop,
	ast_expresion_aditiva* expresion_aditiva2
)
{
	ast_expresion_simple* expresion_simple = ast_expresion_simple2(expresion_aditiva1);

	if(expresion_simple)
	{
		expresion_simple->relop              = relop;
		expresion_simple->expresion_aditiva2 = expresion_aditiva2;
	}

	return expresion_simple;
}

ast_expresion_simple* ast_expresion_simple2(ast_expresion_aditiva* expresion_aditiva1)
{
	ast_expresion_simple* expresion_simple = ast_expresion_simple_alloc();

	if(expresion_simple)
		expresion_simple->expresion_aditiva1 = expresion_aditiva1;

	return expresion_simple;
}

void ast_expresion_simple_free(ast_expresion_simple* expresion_simple)
{
	if(expresion_simple)
	{
		ast_expresion_aditiva_free(expresion_simple->expresion_aditiva1);
		ast_relop_free(expresion_simple->relop);
		ast_expresion_aditiva_free(expresion_simple->expresion_aditiva2);
	}
	free(expresion_simple);
}
