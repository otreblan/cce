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
typedef struct _ast_lista_sentencias ast_lista_sentencias;

typedef struct _ast_sentencia_iteracion
{
	ast_expresion*        expresion;
	ast_lista_sentencias* lista_sentencias;
} ast_sentencia_iteracion;

ast_sentencia_iteracion* ast_sentencia_iteracion1(
	ast_expresion*        expresion,
	ast_lista_sentencias* lista_sentencias
);

void ast_sentencia_iteracion_free(ast_sentencia_iteracion* sentencia_iteracion);

#ifdef __cplusplus
} // extern "C"
#endif
