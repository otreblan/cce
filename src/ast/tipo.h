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

typedef enum _ast_tipo_sin_tipo
{
	AST_ENTERO,
	AST_SIN_TIPO
} ast_tipo_kind;

typedef struct _ast_tipo
{
	ast_tipo_kind tipo;
} ast_tipo;

ast_tipo* ast_tipo_entero();
ast_tipo* ast_tipo_sin_tipo();

void ast_tipo_free(ast_tipo* tipo);

#ifdef __cplusplus
} // extern "C"
#endif
