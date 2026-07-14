#include <cstddef>
#include <span>

#include <quill/LogMacros.h>
#include <quill/Logger.h>

#include "LBMSolver.hpp"
#include "configuration/configuration.hpp"
#include "configuration/configuration_datatypes.hpp"
#include "configuration/logger.hpp"

auto main(int argc, char* argv[]) -> int
{
    const std::span<char*> args{argv, static_cast<std::size_t>(argc)};

    const ApplicationConfiguration configuration{parse_configuration(args)};

    quill::Logger* logger{
        configure_logger(configuration.io.output_directory, configuration.io.log_level)
    };

    LBMSolver solver(configuration, logger);
    solver.run();

    return 0;
}
