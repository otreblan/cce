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

#include <stdlib.h>

#include "tipo.h"

static ast_tipo* ast_tipo_alloc();

static ast_tipo* ast_tipo_alloc()
{
	ast_tipo* tipo = malloc(sizeof(ast_tipo));

	return tipo;
}

ast_tipo* ast_tipo_entero()
{
	ast_tipo* tipo = ast_tipo_alloc();

	if(tipo)
		tipo->tipo = AST_ENTERO;

	return tipo;
}
ast_tipo* ast_tipo_sin_tipo()
{
	ast_tipo* tipo = ast_tipo_alloc();

	if(tipo)
		tipo->tipo = AST_SIN_TIPO;

	return tipo;
}

void ast_tipo_free(ast_tipo* tipo)
{
	free(tipo);
}
