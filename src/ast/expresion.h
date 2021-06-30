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

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _ast_var              ast_var;
typedef struct _ast_expresion        ast_expresion;
typedef struct _ast_expresion_simple ast_expresion_simple;

enum ast_expresion_tipo
{
	AST_ASIGNACION,
	AST_EXPRESION_SIMPLE
};

typedef struct _ast_expresion
{
	int tipo;
	union
	{
		struct
		{
			ast_var*       var;
			ast_expresion* expresion;
		} asignacion;
		ast_expresion_simple* expresion_simple;
	} expresion;
} ast_expresion;

ast_expresion* ast_expresion1(ast_var* var, ast_expresion* expresion);
ast_expresion* ast_expresion2(ast_expresion_simple* expresion_simple);

void ast_expresion_free(ast_expresion* expresion);

#ifdef __cplusplus
} // extern "C"
#endif
