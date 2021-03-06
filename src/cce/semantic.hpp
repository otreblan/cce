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

#include <vector>
#include <map>
#include "instruction.hpp"

typedef struct _IO_FILE FILE;
typedef struct _ast_programa ast_programa;
enum class simbolo_tipo{
    FUNCION,
    VARIABLE
};

struct arg_elem{
    char*        id;
    int          tipo;
    simbolo_tipo simb_tipo;
    bool         isArray;
    size_t       size;
};

struct table_elem{
    char*        id_name;
    int          tipo;
    simbolo_tipo simb_tipo;
    bool         isArray;

    // si es función
    std::vector<arg_elem> args; 
    std::vector<arg_elem> local_vars;
    cce::label_t label; 
};




namespace cce
{

/// Semantic analisis
// ID -> Table elem
std::map<std::string_view , table_elem>  ast_semantic(FILE* file, const ast_programa* programa, int & errors, cce::label_t &mext_label);

};
