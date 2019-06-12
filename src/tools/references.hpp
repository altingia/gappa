#ifndef GAPPA_TOOLS_CITE_H_
#define GAPPA_TOOLS_CITE_H_

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
#include <vector>

// =================================================================================================
//      Citations
// =================================================================================================

void check_all_citations();
void check_citations( std::vector<std::string> const& keys );
void check_citation( std::string const& key );

std::vector<std::string> get_all_citation_keys();

std::string cite_bibtex( std::string const& key );
std::string cite_bibtex( std::vector<std::string> const& keys );

std::string cite_markdown( std::string const& key, bool with_quote_block = true );
std::string cite_markdown( std::vector<std::string> const& keys, bool with_quote_block = true );

#endif // include guard
