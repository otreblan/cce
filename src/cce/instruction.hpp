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

#include <string>
#include <string_view>

#include <fmt/format.h>

namespace cce
{

using label_t = int;

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
		JGE,

		// Extensions
		LABEL,
		GOTO_LABEL,
		GOTO_LABEL_IF_NULL,
		LDC_LABEL,

		COMMENT,
	};

	type opcode;

	int r1;
	int r2;
	union
	{
		int r3;
		int offset;

		// Label name
		label_t name;
	};
	std::string comment = "";


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

	/// Label
	static instruction LABEL(label_t name)
	{
		return {.opcode = type::LABEL, .r1 = 0, .r2 = 0, .name = name};
	}

	/// Go to label
	static instruction GOTO_LABEL(label_t name)
	{
		return {.opcode = type::GOTO_LABEL, .r1 = 0, .r2 = 0, .name = name};
	}

	/// Go to label if the contents of R1 is 0
	static instruction GOTO_LABEL_IF_NULL(label_t name, int r1)
	{
		return {.opcode = type::GOTO_LABEL_IF_NULL, .r1 = r1, .r2 = 0, .name = name};
	}

	/// Save label position into a register
	static instruction LDC_LABEL(label_t name, int r1)
	{
		return {.opcode = type::LDC_LABEL, .r1 = r1, .r2 = 0, .name = name};
	}

	/// Prints a comment
	static instruction COMMENT(std::string_view str)
	{
		return {.opcode = type::COMMENT, .r1 = 0, .r2 = 0, .r3 = 0, .comment = str.data()};
	}
};

};

template<>
struct fmt::formatter<cce::instruction>: fmt::formatter<int>
{
	static const char* type_str(cce::instruction::type t)
	{
		switch(t)
		{
			case cce::instruction::type::IN:
				return "IN";
			case cce::instruction::type::OUT:
				return "OUT";
			case cce::instruction::type::ADD:
				return "ADD";
			case cce::instruction::type::SUB:
				return "SUB";
			case cce::instruction::type::MUL:
				return "MUL";
			case cce::instruction::type::DIV:
				return "DIV";
			case cce::instruction::type::HALT:
				return "HALT";
			case cce::instruction::type::LDC:
				return "LDC";
			case cce::instruction::type::LDA:
				return "LDA";
			case cce::instruction::type::LD:
				return "LD";
			case cce::instruction::type::ST:
				return "ST";
			case cce::instruction::type::JEQ:
				return "JEQ";
			case cce::instruction::type::JNE:
				return "JNE";
			case cce::instruction::type::JLT:
				return "JLT";
			case cce::instruction::type::JLE:
				return "JLE";
			case cce::instruction::type::JGT:
				return "JGT";
			case cce::instruction::type::JGE:
				return "JGE";
			default:
				return "";
		}
	}

	template <typename FormatContext>
	auto format(const cce::instruction& i, FormatContext& ctx)
	{
		switch(i.opcode)
		{
			case cce::instruction::type::IN:
			case cce::instruction::type::OUT:
			case cce::instruction::type::ADD:
			case cce::instruction::type::SUB:
			case cce::instruction::type::MUL:
			case cce::instruction::type::DIV:
			case cce::instruction::type::HALT:
				return format_to(ctx.out(),
					"{}  {},{},{}",
					type_str(i.opcode),
					i.r1,
					i.r2,
					i.r3
				);

			case cce::instruction::type::LDC:
			case cce::instruction::type::LDA:
			case cce::instruction::type::LD:
			case cce::instruction::type::ST:
			case cce::instruction::type::JEQ:
			case cce::instruction::type::JNE:
			case cce::instruction::type::JLT:
			case cce::instruction::type::JLE:
			case cce::instruction::type::JGT:
			case cce::instruction::type::JGE:
				return format_to(ctx.out(),
					"{}  {},{}({})",
					type_str(i.opcode),
					i.r1,
					i.offset,
					i.r2
				);

			case cce::instruction::type::COMMENT:
				return format_to(ctx.out(),
					"* {}",
					i.comment
				);

			default:
				break;
		}
		return format_to(ctx.out(), "");
	}
};
