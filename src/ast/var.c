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
#include "var.h"

static ast_var* ast_var_alloc();

static ast_var* ast_var_alloc()
{
	ast_var* var = malloc(sizeof(ast_var));

	if(var)
	{
		*var = (ast_var)
		{
			.ID        = NULL,
			.expresion = NULL
		};
	}

	return var;
}

ast_var* ast_var1(char* ID)
{
	ast_var* var = ast_var_alloc();

	if(var)
		var->ID = ID;

	return var;
}

ast_var* ast_var2(char* ID, ast_expresion* expresion)
{
	ast_var* var = ast_var1(ID);

	if(var)
		var->expresion = expresion;

	return var;
}

void ast_var_free(ast_var* var)
{
	if(var)
	{
		free(var->ID);
		ast_expresion_free(var->expresion);
	}
	free(var);
}
