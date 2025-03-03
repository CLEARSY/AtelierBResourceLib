/******************************* CLEARSY **************************************
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
#include <fstream>
#include <regex>
#include <cstring>

#include "AtelierBResourceLib.h"

using fspath = std::filesystem::path;
using std::string;
using std::vector;

std::ostream& AtelierB::operator<<(std::ostream& os,
                                   const AtelierB::Resource& r) {
    os << "ATB*" << r.m_tool << "*" << r.m_name << ":" << r.m_value;
    return os;
}

std::ostream& AtelierB::operator<<(std::ostream& os,
                                   const AtelierB::ResourceFileReader& r) {
    if (r.m_error) {
        os << "<error>" << std::endl;
    } else {
        for (size_t i = 0; i < r.m_resources.size(); ++i) {
            os << r.m_resources.at(i) << std::endl;
        }
    }
    return os;
}

AtelierB::ResourceFileReader::ResourceFileReader()
    : m_resources(), m_error(false) {}

AtelierB::ResourceFileReader::~ResourceFileReader() {}

void AtelierB::ResourceFileReader::loadFile(const fspath& path) {
    using std::getline;
    using std::ifstream;

    ifstream file(path);

    if (!file.is_open()) {
        m_error = true;
        return;
    }

    string line;
    int lineNumber = 1;
    const std::regex variableRegex(R"((?:^|[^\$]+)(\$(?:[A-Za-z0-9._-]+|\{[A-Za-z0-9._-]+\})))");
    std::regex resourceRegex(R"(ATB\*(\w+)\*(\w+):\s*(.*))");  // Regex pattern

    while (std::getline(file, line)) {
        // Remove comments
        auto commentPos = line.find('!');
        if (commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
        }

        // Trim whitespace
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        // Replace variables
        {
            std::smatch matches;
            std::string::const_iterator searchStart(line.cbegin());
            while (std::regex_search(searchStart, line.cend(), matches, variableRegex)) {
                const std::string envvar = matches[1];
                std::string varname = envvar;
                varname.erase(std::remove_if(varname.begin(), varname.end(),
                                             [](const char &c){ return c == '$' || c == '{' || c == '}'; }),
                              varname.end());
                char *replacement = std::getenv(varname.c_str());
                if (replacement == NULL) {
                    fprintf(stderr,
                            "%s:%d: Resource file error: unknown environment variable %s\n",
                            path,
                            lineNumber,
                            envvar.c_str()) ;
                    searchStart = matches[1].first + envvar.length();
                } else {
                    const size_t offset = matches[1].first - line.cbegin();
                    line.replace(matches[1].first, matches[1].second, replacement);
                    searchStart = line.cbegin()+ offset + strlen(replacement);
                }
            }

            const std::string target = "$$";
            const std::string replacement = "$";
            size_t pos = 0;

            while ((pos = line.find(target, pos)) != std::string::npos) {
                line.replace(pos, target.length(), replacement);
                pos += replacement.length();
            }
        }

        // Match resource declaration
        std::smatch matches;
        if (std::regex_match(line, matches, resourceRegex)) {
            Resource resource;
            resource.m_tool = matches[1].str();
            resource.m_name = matches[2].str();
            resource.m_value = matches[3].str();

            m_resources.push_back(resource);
        }

        lineNumber++;
    }
    file.close();
}

const string& AtelierB::ResourceFileReader::lookupResource(const string& tool,
                                                           const string& name) {
    static const string none{};
    for (size_t i = 0; i < m_resources.size(); ++i) {
        if (m_resources.at(i).m_tool == tool &&
            m_resources.at(i).m_name == name) {
            return m_resources.at(i).m_value;
        }
    }
    m_error = true;
    return none;
}

const char* AtelierB::ResourceFileReader::lookupResourceCStr(
    const string& tool, const string& name) {
    for (size_t i = 0; i < m_resources.size(); ++i) {
        if (m_resources.at(i).m_tool == tool &&
            m_resources.at(i).m_name == name) {
            return m_resources.at(i).m_value.c_str();
        }
    }
    m_error = true;
    return nullptr;
}
