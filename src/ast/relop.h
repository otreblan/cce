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

enum ast_relop_tipo
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
	AST_NE
};

typedef struct _ast_relop
{
	int tipo;
} ast_relop;

ast_relop* ast_relop_le();
ast_relop* ast_relop_lq();
ast_relop* ast_relop_ge();
ast_relop* ast_relop_gq();
ast_relop* ast_relop_eq();
ast_relop* ast_relop_ne();

void ast_relop_free(ast_relop* relop);

#ifdef __cplusplus
} // extern "C"
#endif
