# Compilador
# Copyright © 2021 otreblan
#
# cce is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# cce is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with cce.  If not, see <http://www.gnu.org/licenses/>.

target_sources(${PROJECT_NAME}
	PRIVATE
		# C
		args.c
		call.c
		declaracion.c
		declaracion_local.c
		expresion.c
		fun_declaracion.c
		lista_arg.c
		lista_declaracion.c
		lista_params.c
		lista_sentencias.c
		param.c
		params.c
		programa.c
		sent_compuesta.c
		sentencia.c
		sentencia_expresion.c
		sentencia_iteracion.c
		sentencia_retorno.c
		sentencia_seleccion.c
		tipo.c
		var.c
		var_declaracion.c
)
