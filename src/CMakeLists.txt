# Compilador
# Copyright © 2021 otreblan
#
# cce is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# cce is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with cce.  If not, see <http://www.gnu.org/licenses/>.


BISON_TARGET(parser
	parser.y
	${CMAKE_CURRENT_BINARY_DIR}/parser.c
	DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.h
)

FLEX_TARGET(scanner
	lexer.l
	${CMAKE_CURRENT_BINARY_DIR}/lexer.c
)

ADD_FLEX_BISON_DEPENDENCY(scanner parser)

# The program itself
add_executable(${PROJECT_NAME})

target_sources(${PROJECT_NAME}
	PRIVATE
		# Generated
		${BISON_parser_OUTPUTS}
		${FLEX_scanner_OUTPUTS}

		# C++
		main.cpp
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		${FLEX_LIBRARIES}
)

target_include_directories(${PROJECT_NAME}
	PRIVATE
		${CMAKE_CURRENT_BINARY_DIR}
		${CMAKE_CURRENT_SOURCE_DIR}
)
