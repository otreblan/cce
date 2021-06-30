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

typedef struct _ast_declaracion       ast_declaracion;
typedef struct _ast_lista_declaracion ast_lista_declaracion;

typedef struct _ast_lista_declaracion
{
	ast_lista_declaracion* next;
	ast_declaracion*       declaracion;
} ast_lista_declaracion;

ast_lista_declaracion* ast_lista_declaracion1(ast_lista_declaracion* next, ast_declaracion* declaracion);
ast_lista_declaracion* ast_lista_declaracion2(ast_declaracion* declaracion);

void ast_lista_declaracion_free(ast_lista_declaracion* lista_declaracion);

#ifdef __cplusplus
} // extern "C"
#endif
