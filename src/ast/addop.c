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

static ast_addop* ast_addop_alloc();

static ast_addop* ast_addop_alloc()
{
	return malloc(sizeof(ast_addop));
}

ast_addop* ast_addop_suma()
{
	ast_addop* addop = ast_addop_alloc();

	if(addop)
		addop->tipo = '+';

	return addop;
}

ast_addop* ast_addop_resta()
{
	ast_addop* addop = ast_addop_alloc();

	if(addop)
		addop->tipo = '-';

	return addop;
}

void ast_addop_free(ast_addop* addop)
{
	free(addop);
}
