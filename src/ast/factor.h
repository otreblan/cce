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

typedef struct _ast_expresion ast_expresion;
typedef struct _ast_var       ast_var;
typedef struct _ast_call      ast_call;

enum ast_factor_tipo
{
	AST_FACTOR_EXPRESION,
	AST_FACTOR_VAR,
	AST_FACTOR_CALL,
	AST_FACTOR_NUM,
};

typedef struct _ast_factor
{
	char tipo;
	union
	{
		ast_expresion* expresion;
		ast_var*       var;
		ast_call*      call;
		int            NUM;
	};
} ast_factor;

ast_factor* ast_factor1(ast_expresion* expresion);
ast_factor* ast_factor2(ast_var* var);
ast_factor* ast_factor3(ast_call* call);
ast_factor* ast_factor4(int NUM);

void ast_factor_free(ast_factor* factor);

#ifdef __cplusplus
} // extern "C"
#endif
