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

typedef struct _ast_expresion ast_expresion;
typedef struct _ast_lista_arg ast_lista_arg;

typedef struct _ast_lista_arg
{
	ast_expresion* expresion;
	ast_lista_arg* next;
} ast_lista_arg;

ast_lista_arg* ast_lista_arg1(ast_expresion* expresion, ast_lista_arg* next);
ast_lista_arg* ast_lista_arg2(ast_expresion* expresion);

void ast_lista_arg_free(ast_lista_arg* lista_arg);

#ifdef __cplusplus
} // extern "C"
#endif
