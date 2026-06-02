#include <cstddef>

#include "quill/LogMacros.h"
#include "quill/Logger.h"
#include <toml++/toml.hpp>

#include "LBMSolver.hpp"

LBMSolver::LBMSolver(const toml::table& configuration, quill::Logger* logger)
    : time_(
          *configuration["start_time"].value<double>(),
          *configuration["time_step"].value<double>(),
          *configuration["number_of_steps"].value<std::size_t>()
      ),
      logger_(logger)
{
}

auto LBMSolver::run() -> void
{
    LOG_INFO(logger_, "Current simulation time: {}", time_.current_time());

    while (time_.advance())
    {
        LOG_INFO(logger_, "Current simulation time: {}", time_.current_time());
    }
}
