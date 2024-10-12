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
#ifndef ATELIERB_RESOURCE_FILE_READER_H
#define ATELIERB_RESOURCE_FILE_READER_H

#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

/**
 * Atelier B resources are parameters for the different components of Atelier B
 * (type checker, PO generator...) Atelier B resource files are text files with
 * the following formatting convention.
 *
 * - Comments may be started with a ! and extends up to the end of the line.
 * - Each resource is described on a line as follows:
 * `ATB*<tool>*<name>:<value>` This creates a resource for the component
 * identified by `<tool>`, with the given `<name>` and `<value>`. So, the
 * identifier for the resource is the pair
 *   `"<tool>, <name>"`.
 *
 */
namespace AtelierB {

/**@brief Representation of a resource with its value */
struct Resource {
    std::string m_tool; /*!< The identifier for the component of the resource */
    std::string m_name; /*!< The name for the resource */
    std::string m_value; /*!< The value for the resource */

    friend std::ostream &operator<<(std::ostream &, const Resource &);
};

/**@brief A class to access resource files in read-only mode */
class ResourceFileReader {
   public:
    ResourceFileReader();
    ~ResourceFileReader();
    /**@brief Reads all the resources from the given file and stores them
     * internally.
     *
     * If there is an error, the internal error status is set.
     */
    void loadFile(const std::filesystem::path &file);
    /**@brief Return the internal error status. */
    bool error() const;
    /**@brief Returns the value of the resource identified by tool and name. */
    const std::string &lookupResource(const std::string &tool,
                                      const std::string &name);
    /**@brief Returns the value of the resource identified by tool and name as a
     * C string. */
    const char *lookupResourceCStr(const std::string &tool,
                                   const std::string &resource);

   private:
    std::vector<Resource> m_resources;
    bool m_error;

    friend std::ostream &operator<<(std::ostream &, const ResourceFileReader &);
};

/**@brief library version string */
extern const std::string ResourceLibVersion;
/**@brief library source SHA1 string */
extern const std::string ResourceLibSHA1;
/**@brief library copyright information */
extern const std::string ResourceLibCopyright;
/**@brief library license information */
extern const std::string ResourceLibLicense;

};  // namespace AtelierB

#endif  // ATELIERB_RESOURCE_FILE_READER_H
