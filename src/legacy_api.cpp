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
#include "legacy_api.h"

#include "AtelierBResourceLib.h"

static AtelierB::ResourceFileReader *resource_manager{nullptr};

void init_resource_manager(void) {
    if (resource_manager != nullptr) {
        delete resource_manager;
    }
    resource_manager = new AtelierB::ResourceFileReader();
}

void load_resources(const char *system_file_name_acp, const char *,
                    const char *) {
    if (resource_manager == nullptr) return;
    resource_manager->loadFile(system_file_name_acp);
}

const char *lookup_resource(const char *tool, const char *name) {
    if (resource_manager == nullptr) return nullptr;
    return resource_manager->lookupResourceCStr(tool, name);
}
