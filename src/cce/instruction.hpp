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

namespace cce
{

struct instruction
{
	enum class type
	{
		IN,
		OUT,
		ADD,
		SUB,
		MUL,
		DIV,
		HALT,
		LDC,
		LDA,
		LD,
		ST,
		JEQ,
		JNE,
		JLT,
		JLE,
		JGT,
		JGE
	};

	type opcode;
	int r1;
	int r2;
	union
	{
		int r3;
		int offset;
	};

	/// Read an integer from stdin and place result in r1; ignore operands r2 and r3.
	static instruction IN(int r1)
	{
		return {.opcode = type::IN, .r1 = r1, .r2 = 0, .r3 = 0};
	}

	/// Write contents of r1 to stdout; ignore operands r2 and r3.
	static instruction OUT(int r1)
	{
		return {.opcode = type::OUT, .r1 = r1, .r2 = 0, .r3 = 0};
	}

	/// Add contents of r2 and r3 and place result in r1.
	static instruction ADD(int r1, int r2, int r3)
	{
		return {.opcode = type::ADD, .r1 = r1, .r2 = r2, .r3 = r3};
	}

	/// Subtract contents of r3 from contents of r2 and place result in r1.
	static instruction SUB(int r1, int r2, int r3)
	{
		return {.opcode = type::SUB, .r1 = r1, .r2 = r2, .r3 = r3};
	}

	/// Multiply contents of r2 and contents of r3 and place result in r1.
	static instruction MUL(int r1, int r2, int r3)
	{
		return {.opcode = type::MUL, .r1 = r1, .r2 = r2, .r3 = r3};
	}

	/// Divide contents of r2 by contents of r3 and place result in r1.
	static instruction DIV(int r1, int r2, int r3)
	{
		return {.opcode = type::DIV, .r1 = r1, .r2 = r2, .r3 = r3};
	}

	/// Ignore operands and terminate the machine.
	static instruction HALT()
	{
		return {.opcode = type::HALT, .r1 = 0, .r2 = 0, .r3 = 0};
	}

	/// Place the constant offset in r1; ignore r2.
	static instruction LDC(int r1, int offset)
	{
		return {.opcode = type::LDC, .r1 = r1, .r2 = 0, .offset = offset};
	}

	/// Place the address address in r1.
	static instruction LDA(int r1, int offset, int r2)
	{
		return {.opcode = type::LDA, .r1 = r1, .r2 = r2, .offset = offset};
	}

	/// Place the contents of data memory location address in r1.
	static instruction LD(int r1, int offset, int r2)
	{
		return {.opcode = type::LD, .r1 = r1, .r2 = r2, .offset = offset};
	}

	/// Place the contents of r1 to data memory location address
	static instruction ST(int r1, int offset, int r2)
	{
		return {.opcode = type::ST, .r1 = r1, .r2 = r2, .offset = offset};
	}

	/// Branch to address if r1 is equal to 0.
	static instruction JEQ(int r1, int offset, int r2)
	{
		return {.opcode = type::JEQ, .r1 = r1, .r2 = r2, .offset = offset};
	}

	/// Branch to address if r1 is not equal to 0.
	static instruction JNE(int r1, int offset, int r2)
	{
		return {.opcode = type::JNE, .r1 = r1, .r2 = r2, .offset = offset};
	}

	/// Branch to address if r1 is less than 0.
	static instruction JLT(int r1, int offset, int r2)
	{
		return {.opcode = type::JLT, .r1 = r1, .r2 = r2, .offset = offset};
	}

	/// Branch to address if r1 is less than or equal to 0.
	static instruction JLE(int r1, int offset, int r2)
	{
		return {.opcode = type::JLE, .r1 = r1, .r2 = r2, .offset = offset};
	}

	/// Branch to address if r1 is greater than 0.
	static instruction JGT(int r1, int offset, int r2)
	{
		return {.opcode = type::JGT, .r1 = r1, .r2 = r2, .offset = offset};
	}

	/// Branch to address if r1 is greater than or equal to 0.
	static instruction JGE(int r1, int offset, int r2)
	{
		return {.opcode = type::JGE, .r1 = r1, .r2 = r2, .offset = offset};
	}

};

};
