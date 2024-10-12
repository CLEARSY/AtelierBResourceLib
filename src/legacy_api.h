/******************************************************************************
    This file is part of AtelierBResourceLib
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
******************************************************************************/
#ifndef ATELIERB_LEGACY_API_H
#define ATELIERB_LEGACY_API_H

#if defined(__cplusplus)
#include <cstdio>
#define EXTERN extern "C"
#else
#include <stdio.h>
#define EXTERN extern
#endif

/**@brief Creates a resource manager (currently only capable of accessing
 * existing resources in read-only mode).
 *
 * There is currently no function to free the memory allocated to represent the
 * resource manager.
 */
EXTERN void init_resource_manager(void);

/**@brief Fills the resource manager with the contents of a given resource file.
 *
 * If the resource manager was already filled, its contents are freed before the
 * file is read.
 */
EXTERN void load_resources(
    const char *file1 /*!< the path of a resource file to be stored in the
                         resource manager */
    ,
    const char *file2 /*!< not used*/, const char *file3 /*!< not used*/);

/**@brief Returns the value of the resource identified by tool and name as a C
 * string.
 *
 * @param tool_name_acp the tool the resource is associated to
 * @param resource_name_acp the resource name
 */
EXTERN const char *lookup_resource(const char *tool_name_acp,
                                   const char *resource_name_acp);

#endif  // ATELIERB_LEGACY_API_H
