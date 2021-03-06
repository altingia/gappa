#ifndef GAPPA_TOOLS_CLI_OPTION_H_
#define GAPPA_TOOLS_CLI_OPTION_H_

/*
    gappa - Genesis Applications for Phylogenetic Placement Analysis
    Copyright (C) 2017-2019 Lucas Czech and HITS gGmbH

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.

    Contact:
    Lucas Czech <lucas.czech@h-its.org>
    Exelixis Lab, Heidelberg Institute for Theoretical Studies
    Schloss-Wolfsbrunnenweg 35, D-69118 Heidelberg, Germany
*/

#include "CLI/CLI.hpp"

#include <string>

// =================================================================================================
//      CLI11 Option Helper
// =================================================================================================

/**
 * @brief Helper that encapsulates an option for the command line interface,
 * storing its value and the CLI11 object used in the interface to change that value.
 */
template<typename T>
struct CliOption
{
    CliOption() = default;

    CliOption( T const& val )
        : value( val )
    {}

    CliOption& operator =( CLI::Option* opt )
    {
        option = opt;
        return *this;
    }

    T            value  = {};
    CLI::Option* option = nullptr;
};

/**
 * @brief Specialized version that allows construction from char arrays,
 * so that we can easility initialize the class in standard use cases.
 */
template<>
struct CliOption<std::string>
{
    CliOption() = default;

    CliOption( std::string const& val )
        : value( val )
    {}

    CliOption( char const* val )
        : value( val )
    {}

    CliOption& operator =( CLI::Option* opt )
    {
        option = opt;
        return *this;
    }

    // CliOption& operator =( std::string const& val )
    // {
    //     value = val;
    //     return *this;
    // }
    //
    // CliOption& operator =( char const* val )
    // {
    //     value = val;
    //     return *this;
    // }

    std::string  value  = {};
    CLI::Option* option = nullptr;
};

#endif // include guard
