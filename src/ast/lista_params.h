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

typedef struct _ast_param        ast_param;
typedef struct _ast_lista_params ast_lista_params;

typedef struct _ast_lista_params
{
	ast_lista_params* next;
	ast_param* param;
} ast_lista_params;

ast_lista_params* ast_lista_params1(ast_lista_params* next, ast_param* param);
ast_lista_params* ast_lista_params2(ast_param* param);

void ast_lista_params_free(ast_lista_params* lista_params);

#ifdef __cplusplus
} // extern "C"
#endif
