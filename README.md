# AtelierBResourceLib

[![CMake on multiple platforms](https://github.com/CLEARSY/AtelierBResourceLib/actions/workflows/cmake-multi-platform.yml/badge.svg)](https://github.com/CLEARSY/AtelierBResourceLib/actions/workflows/cmake-multi-platform.yml)

The ultimate goal of this project is to provide a modern C++ API to access Atelier B resource files.

Currently the feature set is limited to load a resource file and obtain resource values
(for a full feature set, use instead the legacy RESOURCES library).

## Motivation

The RESOURCES library sits currently in the BCOMPILER project. This creates an artificial dependency
on the BCOMPILER for any code base needing to access resource files. One solution to break this dependency
would be to create a standalone RESOURCES project.

The RESOURCES library was developed when the C++ standard library was very limited and does not take advantage
of the modern support for strings, containers and file system access. We estimate that using the full capabilities
of the C++ standard library would greatly simplify the code base and possibly make it more robust.

The purpose of developing AtelierBResourceLib is to develop a modern C++ implementation of the feature set
offered by the RESOURCES library, together with a C API.

## Licensing

This code is distributed under the license: "GNU GENERAL PUBLIC LICENSE, Version 3".
See the LICENSE file in this repository.
