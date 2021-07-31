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

#include <cstdio>
#include <string>
#include <vector>

typedef struct _ast_programa ast_programa;

namespace cce
{

struct instruction;

class compiler
{
	[[noreturn]]
	void usage(int exit_code) const;

	bool print_graph = false;

	std::string infile_path;
	std::string outfile_path;

	std::vector<instruction> compile(ast_programa* programa, int yynerrs, int& exit_code);
	int write_to_outfile(const std::vector<instruction>& v) const;

	int next_label = 0;

	/// Allocate a new label.
	int label_alloc();
public:
	compiler();
	compiler(int argc, char* argv[]);

	/// Parse command line arguments.
	void parse(int argc, char* argv[]);

	/// Run the compiler and return an exit code for main().
	int run();
};

};
