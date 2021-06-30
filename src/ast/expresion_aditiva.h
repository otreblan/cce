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

typedef struct _ast_addop             ast_addop;
typedef struct _ast_term              ast_term;
typedef struct _ast_expresion_aditiva ast_expresion_aditiva;

typedef struct _ast_expresion_aditiva
{
	ast_expresion_aditiva* expresion_aditiva;
	ast_addop*             addop;
	ast_term*              term;
} ast_expresion_aditiva;

ast_expresion_aditiva* ast_expresion_aditiva1(
	ast_expresion_aditiva* expresion_aditiva,
	ast_addop*             addop,
	ast_term*              term
);

ast_expresion_aditiva* ast_expresion_aditiva2(ast_term* term);

void ast_expresion_aditiva_free(ast_expresion_aditiva* expresion_aditiva);

#ifdef __cplusplus
} // extern "C"
#endif
