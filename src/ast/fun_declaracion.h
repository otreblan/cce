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

typedef struct _ast_tipo           ast_tipo;
typedef struct _ast_params         ast_params;
typedef struct _ast_sent_compuesta ast_sent_compuesta;

typedef struct _ast_fun_declaracion
{
	ast_tipo*           tipo;
	char*               id;
	ast_params*         params;
	ast_sent_compuesta* sent_compuesta;
} ast_fun_declaracion;

ast_fun_declaracion* ast_fun_declaracion1(
	ast_tipo*           tipo,
	char*               id,
	ast_params*         params,
	ast_sent_compuesta* sent_compuesta
);

void ast_fun_declaracion_free(ast_fun_declaracion* fun_declaracion);

#ifdef __cplusplus
} // extern "C"
#endif
