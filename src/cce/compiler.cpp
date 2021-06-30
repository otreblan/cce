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

#include <cstdlib>
#include <getopt.h>

#include <fmt/core.h>

#include "compiler.hpp"
#include "parser.h"
#include "instruction.hpp"

void cce::compiler::usage(int exit_code) const
{
	fmt::print(
		"Usage: cce [options] infile\n"
		"\t-h, --help           Show this help.\n"
		"\t-o, --output=outfile Set output file.\n"
	);

	exit(exit_code);
}

cce::compiler::compiler(){}

cce::compiler::compiler(int argc, char* argv[])
{
	parse(argc, argv);
}

void cce::compiler::parse(int argc, char* argv[])
{
	if(argc < 2)
		usage(EXIT_FAILURE);

	int c;
	static const char shortopts[] = "ho:";
	static const option options[] =
	{
		{"help",   no_argument,       nullptr, 'h'},
		{"output", required_argument, nullptr, 'o'},
	};

	while((c = getopt_long(argc, argv, shortopts, options, nullptr)) != -1)
	{
		switch (c) {
			case 'h':
				usage(EXIT_SUCCESS);
				break;

			case 'o':
				outfile_path = optarg;
				break;

			default:
				exit(EXIT_FAILURE);
		}
	}

	for(int i = optind; i < argc; i++)
		infile_path = argv[i];
}

int cce::compiler::run()
{
	FILE* infile = fopen(infile_path.c_str(), "r");
	FILE* outfile = fopen(outfile_path.c_str(), "w");

	if(!infile)
	{
		perror(infile_path.c_str());
		fclose(outfile);
		return EXIT_FAILURE;
	}

	if(!outfile)
	{
		perror(outfile_path.c_str());
		return EXIT_FAILURE;
	}

	int exit_code = EXIT_SUCCESS;
	int errors = 0;

	ast_programa* programa = parse_file(infile, &errors);
	compile(programa, errors, exit_code);
	ast_programa_free(programa);

	fclose(infile);
	fclose(outfile);

	return exit_code;
}

std::vector<cce::instruction> cce::compiler::compile(ast_programa* programa, int yynerrs, int& exit_code)
{
	std::vector<cce::instruction> v;

	if(!programa)
	{
		exit_code = EXIT_FAILURE;
		return v;
	}

	if(yynerrs > 0)
	{
		exit_code = EXIT_FAILURE;
		return v;
	}

	// TODO
	exit_code = EXIT_SUCCESS;
	return v;
}
