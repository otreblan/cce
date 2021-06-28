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

#include "lista_declaracion.h"
#include "programa.h"

ast_programa* ast_programa1(ast_lista_declaracion* lista_declaraciones)
{
	ast_programa* programa = malloc(sizeof(ast_programa));

	if(programa)
	{
		*programa = (ast_programa)
		{
			.lista_declaraciones = lista_declaraciones
		};
	}

	return programa;
}

void ast_programa_free(ast_programa* programa)
{
	//if(programa)
	//	ast_lista_declaracion_free(programa->lista_declaraciones);
}
