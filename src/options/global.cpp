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

#include "options/global.hpp"

#include "tools/version.hpp"

#include "genesis/utils/core/logging.hpp"
#include "genesis/utils/core/options.hpp"

#include <thread>

// =================================================================================================
//      Setup Functions
// =================================================================================================

void GlobalOptions::initialize( int const argc, char const* const* argv )
{
    // By default, use the hardware threads.
    threads_.value = std::thread::hardware_concurrency();

    // If hardware value is not available, just use 1 thread.
    // This is executed if the call to hardware_concurrency fails.
    if( threads_.value == 0 ) {
        threads_.value = 1;
    }

    // Set number of threads for genesis.
    genesis::utils::Options::get().number_of_threads( threads_.value );

    // Set verbosity to max, just in case.
    genesis::utils::Logging::max_level( genesis::utils::Logging::LoggingLevel::kDebug4 );

    // Store all arguments in the array.
    command_line_.clear();
    for (int i = 0; i < argc; i++) {
        command_line_.push_back(argv[i]);
    }
}

void GlobalOptions::add_to_module( CLI::App& module )
{
    for( auto subcomm : module.get_subcommands({}) ) {
        add_to_subcommand( *subcomm );
    }
}

void GlobalOptions::add_to_subcommand( CLI::App& subcommand )
{
    // Threads
    threads_ = subcommand.add_option(
        "--threads",
        threads_.value,
        "Number of threads to use for calculations."
    );
    threads_.option->group( "Global Options" );

    // Log File
    log_file_ = subcommand.add_option(
        "--log-file",
        log_file_.value,
        "Write all output to a log file, in addition to standard output to the terminal."
    );
    log_file_.option->group( "Global Options" );

    // Verbosity
    verbose_ = subcommand.add_flag(
        "--verbose",
        verbose_.value,
        "Produce more verbose output."
    );
    verbose_.option->group( "Global Options" );

    // TODO add random seed option
    // TODO add global file overwrite option.

    // TODO in order to run callbacks for certain options, use ther full functional form!
    // for example, the allow overwrite option (yet to do), or threads or the like can use this.
    // then, init is no longer needed
}

// =================================================================================================
//      Run Functions
// =================================================================================================

void GlobalOptions::run_global()
{
    // If user did not provide number, use hardware value.
    if( threads_.value == 0 ) {
        threads_.value = std::thread::hardware_concurrency();
    }

    // If hardware value is not available, just use 1 thread.
    // This is executed if the call to hardware_concurrency fails.
    if( threads_.value == 0 ) {
        threads_.value = 1;
    }

    // Set number of threads for genesis.
    genesis::utils::Options::get().number_of_threads( threads_.value );

    // Set log file.
    if( ! log_file_.value.empty() ) {
        genesis::utils::Logging::log_to_file( log_file_.value );
    }

    // Set verbosity level for logging output.
    if( verbose_.value ) {
        genesis::utils::Logging::max_level( genesis::utils::Logging::LoggingLevel::kMessage2 );
    } else {
        genesis::utils::Logging::max_level( genesis::utils::Logging::LoggingLevel::kMessage1 );
    }
}

// =================================================================================================
//      Getters
// =================================================================================================

std::string GlobalOptions::command_line() const
{
    std::string ret = "";
    for (size_t i = 0; i < command_line_.size(); ++i) {
        ret += ( i==0 ? "" : " " ) + command_line_[i];
    }
    return ret;
}

bool GlobalOptions::verbose() const
{
    return verbose_.value;
}

size_t GlobalOptions::threads() const
{
    return threads_.value;
}

// =================================================================================================
//      Global Instance
// =================================================================================================

/**
 * @brief Instanciation of the global options object. This is alive during the whole program run.
 */
GlobalOptions global_options;
