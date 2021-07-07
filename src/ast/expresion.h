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

typedef struct _ast_var       ast_var;
typedef struct _ast_expresion ast_expresion;
typedef struct _ast_call      ast_call;

typedef enum _ast_expresion_tipo
{
	AST_ASIGNACION,
	AST_EXPRESION_SIMPLE,
	AST_VAR,
	AST_CALL,
	AST_NUM
} ast_expresion_tipo;

typedef enum _ast_op
{
	// Less
	AST_LE,

	// Less equal
	AST_LQ,

	// Greater
	AST_GE,

	// Greater equal
	AST_GQ,

	// Equal
	AST_EQ,

	// Not equal
	AST_NE,

	AST_SUMA,
	AST_RESTA,

	AST_MULTIPLICACION,
	AST_DIVISION
} ast_op;

typedef struct _ast_expresion
{
	ast_expresion_tipo tipo;
	union
	{
		// Asignación
		struct
		{
			ast_var*       var;
			ast_expresion* expresion;
		} asignacion;

		// Expresión simple
		struct
		{
			ast_expresion* expresion1;
			ast_op         op;
			ast_expresion* expresion2;
		};

		// Factor
		ast_var*  var;
		ast_call* call;
		int       NUM;
	};
} ast_expresion;

ast_expresion* ast_expresion_asignacion(ast_var* var, ast_expresion* expresion);
ast_expresion* ast_expresion_operacion(ast_expresion* expresion1, ast_op op, ast_expresion* expresion2);
ast_expresion* ast_expresion_var(ast_var* var);
ast_expresion* ast_expresion_call(ast_call* call);
ast_expresion* ast_expresion_num(int NUM);

void ast_expresion_free(ast_expresion* expresion);

#ifdef __cplusplus
} // extern "C"
#endif
