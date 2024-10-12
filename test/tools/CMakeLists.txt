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
project(TEST_TOOLS)

include_directories(${ATELIERB_RESOURCE_LIB_SOURCE_DIR})

add_executable(printResourceFile printResourceFile.cpp)
target_link_libraries(printResourceFile ATELIERB_RESOURCE_LIB)

add_executable(printResourceFileLegacy printResourceFileLegacy.c)
target_link_libraries(printResourceFileLegacy ATELIERB_RESOURCE_LIB)
