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

#include "factor.h"
#include "mulop.h"
#include "term.h"

static ast_term* ast_term_alloc();

static ast_term* ast_term_alloc()
{
	ast_term* term = malloc(sizeof(ast_term));

	if(term)
	{
		*term = (ast_term)
		{
			.term   = NULL,
			.mulop  = NULL,
			.factor = NULL
		};
	}

	return term;
}

ast_term* ast_term1(ast_term* term, ast_mulop* mulop, ast_factor* factor)
{
	ast_term* _term = ast_term2(factor);

	if(_term)
	{
		_term->term  = term;
		_term->mulop = mulop;
	}

	return _term;
}

ast_term* ast_term2(ast_factor* factor)
{
	ast_term* term = ast_term_alloc();

	if(term)
		term->factor = factor;

	return term;
}

void ast_term_free(ast_term* term)
{
	if(term)
	{
		ast_term_free(term->term);
		ast_mulop_free(term->mulop);
		ast_factor_free(term->factor);
	}
	free(term);
}
