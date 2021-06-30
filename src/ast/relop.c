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

#include "relop.h"

static ast_relop* ast_relop_alloc();
static ast_relop* ast_relop_tipo(int tipo);

static ast_relop* ast_relop_alloc()
{
	return malloc(sizeof(ast_relop));
}

static ast_relop* ast_relop_tipo(int tipo)
{
	ast_relop* relop = ast_relop_alloc();

	if(relop)
		relop->tipo = tipo;

	return relop;
}

ast_relop* ast_relop_le()
{
	return ast_relop_tipo(AST_LE);
}

ast_relop* ast_relop_lq()
{
	return ast_relop_tipo(AST_LQ);
}

ast_relop* ast_relop_ge()
{
	return ast_relop_tipo(AST_GE);
}

ast_relop* ast_relop_gq()
{
	return ast_relop_tipo(AST_GQ);
}

ast_relop* ast_relop_eq()
{
	return ast_relop_tipo(AST_EQ);
}

ast_relop* ast_relop_ne()
{
	return ast_relop_tipo(AST_NE);
}

void ast_relop_free(ast_relop* relop)
{
	free(relop);
}
