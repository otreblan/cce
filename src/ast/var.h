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

typedef struct _ast_var
{
	char* ID;
	ast_expresion* expresion;
} ast_var;

ast_var* ast_var1(char* ID);
ast_var* ast_var2(char* ID, ast_expresion* expresion);

void ast_var_free(ast_var* var);

#ifdef __cplusplus
} // extern "C"
#endif
