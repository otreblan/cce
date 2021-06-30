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

#include "mulop.h"

static ast_mulop* ast_mulop_alloc();

static ast_mulop* ast_mulop_alloc()
{
	return malloc(sizeof(ast_mulop));
}

ast_mulop* ast_mulop_multiplicacion()
{
	ast_mulop* mulop = ast_mulop_alloc();

	if(mulop)
		mulop->tipo = '*';

	return mulop;
}

ast_mulop* ast_mulop_division()
{
	ast_mulop* mulop = ast_mulop_alloc();

	if(mulop)
		mulop->tipo = '/';

	return mulop;
}

void ast_mulop_free(ast_mulop* mulop)
{
	free(mulop);
}
