#[[ This file is part of AtelierBResourceLib
    Copyright (C) 2024 CLEARSY (contact@clearsy.com)

    AtelierBResourceLib is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; GNU General Public License version 3
    of the License

    AtelierBResourceLib is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with AtelierBResourceLib; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
]]
project(ATELIERB_RESOURCE_LIB_TEST)

add_subdirectory(tools)

# Search for a suitable shell program, so that the tests can be run under windows
# if a unix-like shell is available
find_program(TEST_SHELL
	NAMES bash sh
	PATHS env PATH)

macro(add_resource_file_reader_test id)
   add_test(ResourceFileReader.${id} ${TEST_SHELL} ${CMAKE_CURRENT_SOURCE_DIR}/do_ctest
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${TEST_TOOLS_BINARY_DIR}
    ${id})
   set_tests_properties(ResourceFileReader.${id} PROPERTIES FAIL_REGULAR_EXPRESSION "!!.*")
   set_tests_properties(ResourceFileReader.${id} PROPERTIES PASS_REGULAR_EXPRESSION "OK")
   set_tests_properties(ResourceFileReader.${id} PROPERTIES TIMEOUT 14400)
   set_tests_properties(ResourceFileReader.${id} PROPERTIES LABELS NGOP)
endmacro(add_resource_file_reader_test)

if(TEST_SHELL)
add_resource_file_reader_test(test01)
add_resource_file_reader_test(test02)
add_resource_file_reader_test(test03)
add_resource_file_reader_test(test04)
endif(TEST_SHELL)