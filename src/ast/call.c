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

#include "args.h"
#include "call.h"

static ast_call* ast_call_alloc();

static ast_call* ast_call_alloc()
{
	ast_call* call = malloc(sizeof(ast_call));

	if(call)
	{
		*call = (ast_call)
		{
			.ID   = NULL,
			.args = NULL
		};
	}

	return call;
}

ast_call* ast_call1(char* ID, ast_args* args)
{
	ast_call* call = ast_call_alloc();

	if(call)
	{
		call->ID   = ID;
		call->args = args;
	}

	return call;
}

void ast_call_free(ast_call* call)
{
	if(call)
	{
		free(call->ID);
		ast_args_free(call->args);
	}
	free(call);
}
