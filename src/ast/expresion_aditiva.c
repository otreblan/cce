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

#include "addop.h"
#include "expresion_aditiva.h"
#include "term.h"

static ast_expresion_aditiva* ast_expresion_aditiva_alloc();

static ast_expresion_aditiva* ast_expresion_aditiva_alloc()
{
	ast_expresion_aditiva* expresion_aditiva = malloc(sizeof(ast_expresion_aditiva));

	if(expresion_aditiva)
	{
		*expresion_aditiva = (ast_expresion_aditiva)
		{
			.expresion_aditiva = NULL,
			.addop             = NULL,
			.term              = NULL
		};
	}

	return expresion_aditiva;
}

ast_expresion_aditiva* ast_expresion_aditiva1(
	ast_expresion_aditiva* expresion_aditiva,
	ast_addop*             addop,
	ast_term*              term
)
{
	ast_expresion_aditiva* _expresion_aditiva = ast_expresion_aditiva2(term);

	if(_expresion_aditiva)
	{
		_expresion_aditiva->expresion_aditiva = expresion_aditiva;
		_expresion_aditiva->addop             = addop;
	}

	return _expresion_aditiva;
}

ast_expresion_aditiva* ast_expresion_aditiva2(ast_term* term)
{
	ast_expresion_aditiva* expresion_aditiva = ast_expresion_aditiva_alloc();

	if(expresion_aditiva)
		expresion_aditiva->term = term;

	return expresion_aditiva;
}

void ast_expresion_aditiva_free(ast_expresion_aditiva* expresion_aditiva)
{
	if(expresion_aditiva)
	{
		ast_expresion_aditiva_free(expresion_aditiva->expresion_aditiva);
		ast_addop_free(expresion_aditiva->addop);
		ast_term_free(expresion_aditiva->term);
	}
	free(expresion_aditiva);
}
