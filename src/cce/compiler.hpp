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

#include <bitset>
#include <cstdio>
#include <string>
#include <string_view>
#include <vector>

#include "ast.h"
#include "instruction.hpp"

namespace cce
{

struct instruction;

class compiler
{
	/// Program counter
	static constexpr int PC = 7;

	/// Stack pointer
	static constexpr int SP = 6;

	/// Link register
	static constexpr int LR = 5;

	/// Registers saved when calling a function
	static constexpr std::bitset<8> saved_registers = 0b00111110;

	[[noreturn]]
	void usage(int exit_code) const;

	bool print_graph = false;

	std::string infile_path;
	std::string outfile_path;

	std::string_view         current_function;
	std::vector<instruction> code;

	/// Number of temporal variables in the stack.
	int stack_temp_n = 0;

	int compile(ast_programa* programa, int yynerrs);
	int write_to_outfile() const;

	label_t next_label = 0;

	/// Allocate a new label.
	label_t label_alloc();

	void expand_extensions();

	// Code generation
	void args_gen                (ast_args& args);
	void call_gen                (ast_call& call);
	void declaracion_gen         (ast_declaracion& declaracion);
	void declaracion_local_gen   (ast_declaracion_local& declaracion_local);
	void expresion_gen           (ast_expresion& expresion);
	void fun_declaracion_gen     (ast_fun_declaracion& fun_declaracion);
	void programa_gen            (ast_programa& programa);
	void sent_compuesta_gen      (ast_sent_compuesta& sent_compuesta);
	void sentencia_expresion_gen (ast_sentencia_expresion& sentencia_expresion);
	void sentencia_gen           (ast_sentencia& sentencia);
	void sentencia_iteracion_gen (ast_sentencia_iteracion& sentencia_iteracion);
	void sentencia_retorno_gen   (ast_sentencia_retorno& sentencia_retorno);
	void sentencia_seleccion_gen (ast_sentencia_seleccion& sentencia_seleccion);
	void var_declaracion_gen     (ast_var_declaracion& var_declaracion);
	void var_gen                 (ast_var& var);


	// Helper functions

	/// Read an integer from stdin and place result in r1; ignore operands r2 and r3.
	void IN(int r1)
	{
		code.push_back(instruction::IN(r1));
	}

	/// Write contents of r1 to stdout; ignore operands r2 and r3.
	void OUT(int r1)
	{
		code.push_back(instruction::OUT(r1));
	}

	/// Add contents of r2 and r3 and place result in r1.
	void ADD(int r1, int r2, int r3)
	{
		code.push_back(instruction::ADD(r1, r2, r3));
	}

	/// Subtract contents of r3 from contents of r2 and place result in r1.
	void SUB(int r1, int r2, int r3)
	{
		code.push_back(instruction::SUB(r1, r2, r3));
	}

	/// Multiply contents of r2 and contents of r3 and place result in r1.
	void MUL(int r1, int r2, int r3)
	{
		code.push_back(instruction::MUL(r1, r2, r3));
	}

	/// Divide contents of r2 by contents of r3 and place result in r1.
	void DIV(int r1, int r2, int r3)
	{
		code.push_back(instruction::DIV(r1, r2, r3));
	}

	/// Ignore operands and terminate the machine.
	void HALT()
	{
		code.push_back(instruction::HALT());
	}

	/// Place the constant offset in r1; ignore r2.
	void LDC(int r1, int offset)
	{
		code.push_back(instruction::LDC(r1, offset));
	}

	/// Place the address address in r1.
	void LDA(int r1, int offset, int r2)
	{
		code.push_back(instruction::LDA(r1, offset, r2));
	}

	/// Place the contents of data memory location address in r1.
	void LD(int r1, int offset, int r2)
	{
		code.push_back(instruction::LD(r1, offset, r2));
	}

	/// Place the contents of r1 to data memory location address
	void ST(int r1, int offset, int r2)
	{
		code.push_back(instruction::ST(r1, offset, r2));
	}

	/// Branch to address if r1 is equal to 0.
	void JEQ(int r1, int offset, int r2)
	{
		code.push_back(instruction::JEQ(r1, offset, r2));
	}

	/// Branch to address if r1 is not equal to 0.
	void JNE(int r1, int offset, int r2)
	{
		code.push_back(instruction::JNE(r1, offset, r2));
	}

	/// Branch to address if r1 is less than 0.
	void JLT(int r1, int offset, int r2)
	{
		code.push_back(instruction::JLT(r1, offset, r2));
	}

	/// Branch to address if r1 is less than or equal to 0.
	void JLE(int r1, int offset, int r2)
	{
		code.push_back(instruction::JLE(r1, offset, r2));
	}

	/// Branch to address if r1 is greater than 0.
	void JGT(int r1, int offset, int r2)
	{
		code.push_back(instruction::JGT(r1, offset, r2));
	}

	/// Branch to address if r1 is greater than or equal to 0.
	void JGE(int r1, int offset, int r2)
	{
		code.push_back(instruction::JGE(r1, offset, r2));
	}

	/// Label
	void LABEL(label_t name)
	{
		code.push_back(instruction::LABEL(name));
	}

	/// Go to label
	void GOTO_LABEL(label_t name)
	{
		code.push_back(instruction::GOTO_LABEL(name));
	}

	/// Go to label if the contents of R1 is 0
	void GOTO_LABEL_IF_NULL(label_t name, int r1)
	{
		code.push_back(instruction::GOTO_LABEL_IF_NULL(name, r1));
	}


	/// Calls a function, the arguments must be pushed to the stack before.
	void call(std::string_view function);

	/// Pops the arguments and sets PC to the contents of the link register.
	void return_function();

	/// Saves the contents of a register into the stack.
	void save_register(int r);

	/// Restores the register from the content of the top of the stack.
	void restore_register(int r);
public:
	compiler();
	compiler(int argc, char* argv[]);

	/// Parse command line arguments.
	void parse(int argc, char* argv[]);

	/// Run the compiler and return an exit code for main().
	int run();
};

};
