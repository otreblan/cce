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

typedef struct _ast_var_declaracion   ast_var_declaracion;
typedef struct _ast_declaracion_local ast_declaracion_local;

typedef struct _ast_declaracion_local
{
	ast_declaracion_local* next;
	ast_var_declaracion*   var_declaracion;
} ast_declaracion_local;

ast_declaracion_local* ast_declaracion_local1(
	ast_declaracion_local* next,
	ast_var_declaracion*   var_declaracion
);

ast_declaracion_local* ast_declaracion_local2();

void ast_declaracion_local_free(ast_declaracion_local* declaracion_local);

#ifdef __cplusplus
} // extern "C"
#endif
