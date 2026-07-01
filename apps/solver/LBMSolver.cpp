#include <cstddef>

#include <quill/LogMacros.h>
#include <quill/Logger.h>
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
    LOG_INFO(logger_, "Starting time loop");
    LOG_INFO(logger_, "Time step size: {}", time_.time_step());
    LOG_INFO(
        logger_, "Time step: {}/{} | Simulation time: {}", 0, time_.number_of_steps(),
        time_.starting_time()
    );

    while (time_.advance())
    {
        LOG_INFO(
            logger_, "Time step: {}/{} | Simulation time: {}", time_.current_step(),
            time_.number_of_steps(), time_.current_time()
        );
    }

    LOG_INFO(logger_, "Finished time loop");
}
