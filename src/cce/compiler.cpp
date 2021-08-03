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
#include <fmt/core.h>
#include <getopt.h>
#include <iostream>
#include <unordered_map>

#include "compiler.hpp"
#include "graph.hpp"
#include "semantic.hpp"
#include "instruction.hpp"
#include "parser.h"

const int cce::compiler::PC = 7;
const int cce::compiler::SP = 6;

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
		exit_code |= compile(programa, errors);
		exit_code |= write_to_outfile();
	}

	ast_programa_free(programa);

	return exit_code;
}

// setea un atributo a los nodos del arbol




int cce::compiler::compile(ast_programa* programa, int yynerrs)
{
	if(!programa)
		return EXIT_FAILURE;

	if(yynerrs > 0)
		return EXIT_FAILURE;

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

	programa_gen(*programa);

	// TODO
	// ¿Optimización?

	return EXIT_SUCCESS;
}

int cce::compiler::write_to_outfile() const
{
	if(FILE* outfile = fopen(outfile_path.empty()? "a.tm": outfile_path.c_str(), "w"))
	{
		for(size_t i = 0; i < code.size(); i++)
			fmt::print(outfile, "{}:    {}\n", i, code[i]);

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

void cce::compiler::expand_extensions()
{
	std::vector<cce::instruction> r;

	std::unordered_map<int, size_t> label_pos;
	int i = 0;

	for(const auto& inst: code)
	{
		if(inst.opcode == instruction::type::LABEL)
		{
			label_pos[inst.name] = i+1;
		}
		else
		{
			i++;
		}
	}

	for(const auto& inst: code)
	{
		switch(inst.opcode)
		{
			case instruction::type::GOTO_LABEL:
				r.push_back(instruction::LDC(PC, label_pos[inst.name]));
				break;

			case instruction::type::LABEL:
				break;

			default:
				r.push_back(inst);
				break;
		}
	}

	code = r;
}

void cce::compiler::programa_gen(ast_programa& programa)
{
	// Setup stack
	LD(SP, 0, 0);

	// TODO
	HALT();
}

void cce::compiler::args_gen(ast_args& args)
{
	// TODO
}

void cce::compiler::call_gen(ast_call& call)
{
	// TODO
}

void cce::compiler::declaracion_gen(ast_declaracion& declaracion)
{
	// TODO
}

void cce::compiler::declaracion_local_gen(ast_declaracion_local& declaracion_local)
{
	// TODO
}

void cce::compiler::expresion_gen(ast_expresion& expresion)
{
	// TODO
}

void cce::compiler::fun_declaracion_gen(ast_fun_declaracion& fun_declaracion)
{
	// TODO
}

void cce::compiler::lista_arg_gen(ast_lista_arg& lista_arg)
{
	// TODO
}

void cce::compiler::lista_declaracion_gen(ast_lista_declaracion& lista_declaracion)
{
	// TODO
}

void cce::compiler::lista_params_gen(ast_lista_params& lista_params)
{
	// TODO
}

void cce::compiler::lista_sentencias_gen(ast_lista_sentencias& lista_sentencias)
{
	// TODO
}

void cce::compiler::op_gen(ast_op& relop)
{
	// TODO
}

void cce::compiler::param_gen(ast_param& param)
{
	// TODO
}

void cce::compiler::params_gen(ast_params& params)
{
	// TODO
}

void cce::compiler::sent_compuesta_gen(ast_sent_compuesta& sent_compuesta)
{
	// TODO
}

void cce::compiler::sentencia_expresion_gen(ast_sentencia_expresion& sentencia_expresion)
{
	// TODO
}

void cce::compiler::sentencia_gen(ast_sentencia& sentencia)
{
	// TODO
}

void cce::compiler::sentencia_iteracion_gen(ast_sentencia_iteracion& sentencia_iteracion)
{
	// TODO
}

void cce::compiler::sentencia_retorno_gen(ast_sentencia_retorno& sentencia_retorno)
{
	// TODO
}

void cce::compiler::sentencia_seleccion_gen(ast_sentencia_seleccion& sentencia_seleccion)
{
	// TODO
}

void cce::compiler::tipo_gen(ast_tipo& tipo)
{
	// TODO
}

void cce::compiler::var_declaracion_gen(ast_var_declaracion& var_declaracion)
{
	// TODO
}

void cce::compiler::var_gen(ast_var& var)
{
	// TODO
}

