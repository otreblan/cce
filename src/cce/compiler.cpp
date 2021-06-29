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
	// TODO
	fmt::print("Outfile: {}\n", outfile_path);
	return EXIT_FAILURE;
}
