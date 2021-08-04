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

#include <cassert>
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
		expand_extensions();
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

	int semantic_errors = 0;

	table_id = ast_semantic(stdout, programa, semantic_errors, next_label);

	for (const auto &item: table_id){
		auto elem = item.second;
		//std::cout <<"ID: " << item.first << " , TIPO: " << item.second.tipo;


		if (elem.simb_tipo == simbolo_tipo::FUNCION){
			std::cout <<"Func id: " << item.first << " , TIPO: " << item.second.tipo;

			std::cout << "\n   args: ";
			for (auto arg: elem.args){
				std::cout << arg.id << " ";

			}
			std::cout << "\tlabel: " << elem.label;

			std::cout << "\n   local_vars: ";
			for (auto arg: elem.local_vars){
				std::cout << arg.id << " ";

			}
		}
		std::cout << "\n";
	}

	programa_gen(*programa);

	// TODO
	// ¿Optimización?

	return EXIT_SUCCESS;
}

int cce::compiler::write_to_outfile() const
{
	if(FILE* outfile = fopen(outfile_path.empty()? "a.tm": outfile_path.c_str(), "w"))
	{
		int i = 0;
		for(const auto& instr: code)
		{
			if(instr.opcode == instruction::type::COMMENT)
			{
				fmt::print(outfile, "{}\n", instr);
			}
			else
			{
				fmt::print(outfile, "{}:    {}\n", i, instr);
				i++;
			}
		}

		fclose(outfile);
		return EXIT_SUCCESS;
	}

	perror(outfile_path.c_str());
	return EXIT_FAILURE;
}

cce::label_t cce::compiler::label_alloc()
{
	return next_label++;
}

void cce::compiler::expand_extensions()
{
	std::vector<cce::instruction> r;

	std::unordered_map<label_t, size_t> label_pos;
	size_t i = 0;

	for(const auto& inst: code)
	{
		switch(inst.opcode)
		{
			case instruction::type::LABEL:
				label_pos[inst.name] = i;
				break;

			case instruction::type::COMMENT:
				break;

			default:
				i++;
				break;
		}
	}

	for(const auto& inst: code)
	{
		switch(inst.opcode)
		{
			case instruction::type::GOTO_LABEL:
				r.push_back(instruction::COMMENT(fmt::format("GOTO_LABEL L{}", inst.name)));
				r.push_back(instruction::LDC(PC, label_pos.at(inst.name)));
				break;

			case instruction::type::GOTO_LABEL_IF_NULL:
				r.push_back(instruction::COMMENT(fmt::format("GOTO_LABEL_IF_NULL L{}", inst.name)));
				r.push_back(instruction::JEQ(inst.r1, label_pos.at(inst.name), inst.r1));
				break;

			case instruction::type::LDC_LABEL:
				r.push_back(instruction::COMMENT(fmt::format("LDC_LABEL L{}", inst.name)));
				r.push_back(instruction::LDC(inst.r1, label_pos.at(inst.name)));
				break;

			case instruction::type::LABEL:
				r.push_back(instruction::COMMENT(fmt::format("L{}:", inst.name)));
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

	// Call main
	call("main");

	HALT();

	// Setup global variables
	for(auto* list = programa.lista_declaraciones; list; list = list->next)
	{
		if(auto* declaracion = list->declaracion)
		{
			if(declaracion->tipo == AST_VAR_DECLARACION)
			{
				if(auto* var = declaracion->var)
				{
					var_declaracion_gen(*var);
				}
			}
		}
	}

	// Functions
	for(auto* list = programa.lista_declaraciones; list; list = list->next)
	{
		if(auto* declaracion = list->declaracion)
		{
			if(declaracion->tipo == AST_FUN_DECLARACION)
			{
				if(auto* fun = declaracion->fun)
				{
					fun_declaracion_gen(*fun);
				}
			}
		}
	}
}

void cce::compiler::args_gen(ast_args& args)
{
	for(auto* list = args.lista_arg; list; list = list->next)
	{
		if(auto* expresion = list->expresion)
		{
			expresion_gen(*expresion);

			// Push arguments.
			save_register(0);
		}
	}
}

void cce::compiler::call_gen(ast_call& call)
{
	if(auto* args = call.args)
	{
		args_gen(*args);
	}

	compiler::call(call.ID);
}

void cce::compiler::expresion_gen(ast_expresion& expresion)
{
	switch(expresion.tipo)
	{
		case AST_ASIGNACION:
			if(auto* var = expresion.asignacion.var)
			{
				int offset = var_pos(var->ID);

				// TODO arrays
				//if(auto* expresion1 = var->expresion)
				//{
				//	assert(false);
				//}

				if(auto* expresion2 = expresion.asignacion.expresion)
				{
					expresion_gen(*expresion2);
				}

				// Store the contents of R0 in SP[offset].
				ST(0, offset, SP);
			}

			break;

		case AST_EXPRESION_SIMPLE:
			if(auto* expresion1 = expresion.expresion1)
			{
				if(auto* expresion2 = expresion.expresion2)
				{
#ifndef NDEBUG
					int current_temp_n = stack_temp_n;
#endif
					expresion_gen(*expresion1);
					push_temporal(0); // Push expresion result

					expresion_gen(*expresion2);
					pop_temporal(1);

					assert(current_temp_n == stack_temp_n);
					operation(0, 1, expresion.op, 0);
				}
			}
			break;

		case AST_VAR:
			if(auto* var = expresion.var)
			{
				int offset = var_pos(var->ID);

				// TODO arrays
				//if(auto* expresion = var->expresion)
				//{
				//	assert(false);
				//}

				// Load the contents of SP[offset] into R0.
				LD(0, offset, SP);
			}
			break;

		case AST_CALL:
			if(auto* call = expresion.call)
			{
				call_gen(*call);
			}
			break;

		case AST_NUM:
			LDC(0, expresion.NUM);
			break;
	}
}

void cce::compiler::fun_declaracion_gen(ast_fun_declaracion& fun_declaracion)
{
	assert(stack_temp_n == 0);

	current_function = fun_declaracion.ID;

	COMMENT(current_function);
	LABEL(table_id.at(current_function).label);

	if(auto* sent_compuesta = fun_declaracion.sent_compuesta)
	{
		sent_compuesta_gen(*sent_compuesta);
	}

	// Default return
	return_function();

	current_function = {};
}

void cce::compiler::sent_compuesta_gen(ast_sent_compuesta& sent_compuesta)
{
	for(auto* list = sent_compuesta.declaracion_local; list; list = list->next)
	{
		if(auto* var_declaracion = list->var_declaracion)
		{
			var_declaracion_gen(*var_declaracion);
		}
	}

	for(auto* list = sent_compuesta.lista_sentencias; list; list = list->next)
	{
		if(auto* sentencia = list->sentencia)
		{
			sentencia_gen(*sentencia);
		}
	}
}

void cce::compiler::sentencia_expresion_gen(ast_sentencia_expresion& sentencia_expresion)
{
	if(auto* expresion = sentencia_expresion.expresion)
	{
		expresion_gen(*expresion);
	}
}

void cce::compiler::sentencia_gen(ast_sentencia& sentencia)
{
	switch(sentencia.tipo)
	{
		case AST_SENTENCIA_EXPRESION:
			if(auto* expresion = sentencia.expresion)
			{
				sentencia_expresion_gen(*expresion);
			}
			break;

		case AST_SENTENCIA_SELECCION:
			if(auto* seleccion = sentencia.seleccion)
			{
				sentencia_seleccion_gen(*seleccion);
			}
			break;

		case AST_SENTENCIA_ITERACION:
			if(auto* iteracion = sentencia.iteracion)
			{
				sentencia_iteracion_gen(*iteracion);
			}
			break;

		case AST_SENTENCIA_RETORNO:
			if(auto* retorno = sentencia.retorno)
			{
				sentencia_retorno_gen(*retorno);
			}
			break;
	}
}

void cce::compiler::sentencia_iteracion_gen(ast_sentencia_iteracion& sentencia_iteracion)
{
	label_t start = label_alloc();
	label_t end = label_alloc();

	LABEL(start);

	if(auto* expresion = sentencia_iteracion.expresion)
	{
		expresion_gen(*expresion);
	}

	// Go label end if R0 is 0
	GOTO_LABEL_IF_NULL(end, 0);

	for(auto* list = sentencia_iteracion.lista_sentencias; list; list = list->next)
	{
		if(auto* sentencia = list->sentencia)
		{
			sentencia_gen(*sentencia);
		}
	}

	GOTO_LABEL(start);
	LABEL(end);
}

void cce::compiler::sentencia_retorno_gen(ast_sentencia_retorno& sentencia_retorno)
{
	if(auto* expresion = sentencia_retorno.expresion)
	{
		expresion_gen(*expresion);
	}

	// Returns whatever is in R0.
	return_function();
}

void cce::compiler::sentencia_seleccion_gen(ast_sentencia_seleccion& sentencia_seleccion)
{
	if(auto* expresion = sentencia_seleccion.expresion)
	{
		expresion_gen(*expresion);
	}

	int after_false = label_alloc();
	int after_else = -1;

	GOTO_LABEL_IF_NULL(after_false, 0);

	if(auto* sentencia = sentencia_seleccion.sentencia1)
	{
		sentencia_gen(*sentencia);
	}

	if(sentencia_seleccion.sentencia2)
	{
		GOTO_LABEL(after_else = label_alloc());
	}

	LABEL(after_false);

	// Else
	if(auto* sentencia = sentencia_seleccion.sentencia2)
	{
		sentencia_gen(*sentencia);
		LABEL(after_else);
	}
}

void cce::compiler::var_declaracion_gen(ast_var_declaracion& var_declaracion)
{
	if(current_function.empty()) // Global declaration
	{
		// TODO
	}
	else // Local declaration
	{
		// Grow the stack by size.
		int size = 1;

		if(var_declaracion.es_arreglo)
			size = var_declaracion.num;

		LDA(SP, -size, SP);
	}
}

void cce::compiler::call(std::string_view function)
{
	if(function == "entrada")
	{
		IN(0);
		return;
	}
	else if(function == "salida")
	{
		restore_register(0);
		OUT(0);
		return;
	}

	// Save registers
	for(size_t i = 0; i < saved_registers.size(); i++)
	{
		if(saved_registers[i])
		{
			save_register(i);
		}
	}

	// Get function and return labels
	label_t fun_label    = table_id.at(function).label;
	label_t return_label = label_alloc();

	// Save label address to the link register.
	LDC_LABEL(return_label, LR);
	GOTO_LABEL(fun_label);

	LABEL(return_label);

	// Restore registers
	for(size_t _i = 0; _i < saved_registers.size(); _i++)
	{
		size_t i = saved_registers.size() - _i - 1;

		if(saved_registers[i])
		{
			restore_register(i);
		}
	}

	// Pop arguments
	const auto& fun_elem = table_id.at(function);
	if(!fun_elem.args.empty())
	{
		LDA(SP, fun_elem.args.size(), SP);
	}
}

void cce::compiler::return_function()
{
	// Pop local declarations of the current function.
	const auto& fun_elem = table_id.at(current_function);
	if(!fun_elem.local_vars.empty())
	{
		size_t size = 0;

		for(const auto& local: fun_elem.local_vars)
		{
			size += local.size;
		}

		LDA(SP, size, SP);
	}

	// Set PC
	LDA(PC, 0, LR);
}

void cce::compiler::save_register(int r)
{
	// Grow the stack by 1.
	LDA(SP, -1, SP);

	// Store the register
	ST(r, 0, SP);
}

void cce::compiler::restore_register(int r)
{
	// Load the register
	LD(r, 0, SP);

	// Shrink the stack by 1
	LDA(SP, 1, SP);
}

void cce::compiler::push_temporal(int r)
{
	save_register(r);
	stack_temp_n++;
}

void cce::compiler::pop_temporal(int r)
{
	assert(stack_temp_n > 0);

	restore_register(r);
	stack_temp_n--;
}

int cce::compiler::var_pos(std::string_view variable)
{
	auto var_index = [](std::string_view variable, const std::vector<arg_elem>& v)
	{
		ssize_t i = 0;
		for(const auto& arg: v)
		{
			if(variable == arg.id)
				return i;

			i++;
		}
		return -1L;
	};

	ssize_t i = -1;
	int pos = stack_temp_n;
	const table_elem& var_elem = table_id.at(current_function);

	if((i = var_index(variable, var_elem.local_vars)) != -1) // Local
	{
		pos += var_elem.local_vars.size() - 1 - i;
	}
	else if((i = var_index(variable, var_elem.args)) != -1) // Arguments
	{
		pos += saved_registers.count();
		pos += var_elem.local_vars.size();
		pos += var_elem.args.size() - 1 - i;
	}
	else
	{
		assert(false);
	}

	return pos;
}

void cce::compiler::operation(int result, int left, ast_op op, int right)
{
	switch(op)
	{
		case AST_SUMA:
			ADD(result, left, right);
			break;

		case AST_RESTA:
			SUB(result, left, right);
			break;

		case AST_MULTIPLICACION:
			MUL(result, left, right);
			break;

		case AST_DIVISION:
			DIV(result, left, right);
			break;

		case AST_EQ:
		case AST_GE:
		case AST_GQ:
		case AST_LE:
		case AST_LQ:
		case AST_NE:
			rel_operation(result, left, op, right);
			break;
	}
}

void cce::compiler::rel_operation(int result, int left, ast_op op, int right)
{
	SUB(result, right, left);

	// Jump 3 instructions forward if left op right is true.
	switch(op)
	{
		case AST_LE:
			JLT(result, 3, PC);
			break;

		case AST_LQ:
			JLE(result, 3, PC);
			break;

		case AST_GE:
			JGT(result, 3, PC);
			break;

		case AST_GQ:
			JGE(result, 3, PC);
			break;

		case AST_EQ:
			JEQ(result, 3, PC);
			break;

		case AST_NE:
			JNE(result, 3, PC);
			break;

		default:
			assert(false);
			break;
	}

	// Set result to false.
	LDC(result, 0);

	// Jump 2 instructions forward
	JEQ(result, 2, PC);

	// Set result to true.
	LDC(result, 1);
}
