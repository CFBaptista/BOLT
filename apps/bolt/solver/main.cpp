#include <string_view>
#include <vector>

#include <quill/LogMacros.h>
#include <quill/Logger.h>

#include "LBMSolver.hpp"
#include "bolt/core/logger.hpp"
#include "configuration.hpp"

auto main(int argc, char* argv[]) -> int
{
    const std::vector<std::string_view> args{
        argv, argv + argc // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    };

    const bolt::app::ApplicationConfiguration configuration{bolt::app::parse_configuration(args)};

    quill::Logger* logger{
        bolt::core::configure_logger(configuration.io.output_directory, configuration.io.log_level)
    };

    bolt::app::LBMSolver solver(configuration, logger);
    solver.run();

    return 0;
}
