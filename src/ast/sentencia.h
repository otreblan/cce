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

typedef struct _ast_sentencia_expresion ast_sentencia_expresion;
typedef struct _ast_sentencia_seleccion ast_sentencia_seleccion;
typedef struct _ast_sentencia_iteracion ast_sentencia_iteracion;
typedef struct _ast_sentencia_retorno   ast_sentencia_retorno;

enum ast_sentencia_tipo
{
	AST_SENTENCIA_EXPRESION,
	AST_SENTENCIA_SELECCION,
	AST_SENTENCIA_ITERACION,
	AST_SENTENCIA_RETORNO
};

typedef struct _ast_sentencia
{
	int tipo;
	union
	{
		ast_sentencia_expresion* expresion;
		ast_sentencia_seleccion* seleccion;
		ast_sentencia_iteracion* iteracion;
		ast_sentencia_retorno*   retorno;
	} sentencia;
} ast_sentencia;

ast_sentencia* ast_sentencia1(ast_sentencia_expresion* expresion);
ast_sentencia* ast_sentencia2(ast_sentencia_seleccion* seleccion);
ast_sentencia* ast_sentencia3(ast_sentencia_iteracion* iteracion);
ast_sentencia* ast_sentencia4(ast_sentencia_retorno* retorno);

void ast_sentencia_free(ast_sentencia* sentencia);

#ifdef __cplusplus
} // extern "C"
#endif
