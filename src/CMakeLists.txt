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
project(ATELIERB_RESOURCE_LIB)

add_custom_target(ATELIERB_RESOURCE_LIB_VERSION
  ${CMAKE_COMMAND}
    -D SRC=${CMAKE_CURRENT_SOURCE_DIR}/version.h.in
    -D DST=${CMAKE_CURRENT_SOURCE_DIR}/version.h
    -D GIT_EXECUTABLE=${GIT_EXECUTABLE}
    -D PROJECT_NAME=${PROJECT_NAME}
    -P ${CMAKE_SOURCE_DIR}/cmake/macros/GenerateVersionHeader.cmake
  DEPENDS
    ${CMAKE_CURRENT_SOURCE_DIR}/version.h.in
  BYPRODUCTS
    ${CMAKE_CURRENT_SOURCE_DIR}/version.h
    )

set(ATELIERB_RESOURCE_LIB_SOURCES
    ResourceLibReader.cpp
    legacy_api.cpp
    version.cpp
  )

set(ATELIERB_RESOURCE_LIB_HEADERS
    AtelierBResourceLib.h
    legacy_api.h
    version.h
  )

add_library(ATELIERB_RESOURCE_LIB STATIC ${ATELIERB_RESOURCE_LIB_SOURCES} ${ATELIERB_RESOURCE_LIB_HEADERS})
