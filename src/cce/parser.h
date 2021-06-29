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

#include <stdio.h>

#include "ast.h"

#ifdef __cplusplus
extern "C" {
#endif

#if __GNUC__ >= 11
__attribute__ ((malloc (ast_programa_free, 1)))
#endif
ast_programa* parse_file(FILE* infile);

void __parse_file_init(FILE* infile);
void __parse_file_free(void);

#ifdef __cplusplus
} // extern "C"
#endif
