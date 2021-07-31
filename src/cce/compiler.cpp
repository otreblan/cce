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
#include <iostream>
#include <fmt/core.h>

#include "compiler.hpp"
#include "graph.hpp"
#include "semantic.hpp"
#include "instruction.hpp"
#include "parser.h"

void cce::compiler::usage(int exit_code) const
{
	fmt::print(
		"Usage: cce [options] infile\n"
		"\t-h, --help           Show this help.\n"
		"\t-o, --output=outfile Set output file.\n"
		"\t-g, --graph          Print an ast graph.\n"
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
	static const char shortopts[] = "ho:g";
	static const option options[] =
	{
		{"help",   no_argument,       nullptr, 'h'},
		{"output", required_argument, nullptr, 'o'},
		{"graph",  no_argument,       nullptr, 'g'},
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

			case 'g':
				print_graph = true;
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

	if(!infile)
	{
		perror(infile_path.c_str());
		return EXIT_FAILURE;
	}

	int exit_code = EXIT_SUCCESS;
	int errors = 0;

	ast_programa* programa = parse_file(infile, &errors);
	fclose(infile);

	if(print_graph) // CEs -> graph
	{
		ast_graph(stdout, programa);
	}
	else // CEs -> tm
	{
		std::vector<instruction> code = compile(programa, errors, exit_code);
		exit_code |= write_to_outfile(code);
	}

	ast_programa_free(programa);

	return exit_code;
}

// setea un atributo a los nodos del arbol




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
	// Análisis semántico

	int semantic_errors = 0;
	std::vector<table_elem> table_id = ast_semantic(stdout, programa, semantic_errors);

	for (auto elem: table_id){
		std::cout <<"ID: " << elem.id_name << " , TIPO: " << elem.tipo;

		if (elem.simb_tipo == simbolo_tipo::FUNCION){
			std::cout << "\n   args: ";
			for (auto arg: elem.args){
				std::cout << arg.id << " ";
			}
			std::cout << "\n";

		}

		std::cout << "\n";
	}



	// TODO
	// Generación de código

	// TODO
	// ¿Optimización?

	exit_code = EXIT_SUCCESS;
	return v;
}

int cce::compiler::write_to_outfile(const std::vector<instruction>& v) const
{
	if(FILE* outfile = fopen(outfile_path.empty()? "a.tm": outfile_path.c_str(), "w"))
	{
		for(size_t i = 0; i < v.size(); i++)
			fmt::print(outfile, "{}:    {}\n", i, v[i]);

		fclose(outfile);
		return EXIT_SUCCESS;
	}

	perror(outfile_path.c_str());
	return EXIT_FAILURE;
}

int cce::compiler::label_alloc()
{
	return next_label++;
}
