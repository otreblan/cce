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

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _ast_tipo ast_tipo;

typedef struct _ast_var_declaracion
{
	ast_tipo* tipo;
	char* id;

	bool es_arreglo;
	int num;
} ast_var_declaracion;

ast_var_declaracion* ast_var_declaracion1(ast_tipo* tipo, char* id);
ast_var_declaracion* ast_var_declaracion2(ast_tipo* tipo, char* id, int num);

void ast_var_declaracion_free(ast_var_declaracion* var_declaracion);

#ifdef __cplusplus
} // extern "C"
#endif
