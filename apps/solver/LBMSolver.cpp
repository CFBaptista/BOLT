#include <quill/LogMacros.h>
#include <quill/Logger.h>
#include <toml++/toml.hpp>

#include "LBMSolver.hpp"
#include "configuration.hpp"

LBMSolver::LBMSolver(const ApplicationConfiguration& configuration, quill::Logger* logger)
    : time_(
          configuration.time.start_time,
          configuration.time.time_step,
          configuration.time.number_of_steps
      ),
      logger_(logger)
{
}

auto LBMSolver::initial_log_messages() -> void
{
    LOG_INFO(logger_, "Starting simulation");
    LOG_INFO(logger_, "Start time: {}", time_.start_time());
    LOG_INFO(logger_, "Time step size: {}", time_.time_step());
    LOG_INFO(logger_, "Number of time steps: {}", time_.number_of_steps());
    LOG_INFO(logger_, "Starting time loop");
    LOG_INFO(
        logger_, "Time step: {}/{} | Simulation time: {}", 0, time_.number_of_steps(),
        time_.start_time()
    );
}

auto LBMSolver::final_log_messages() -> void
{
    LOG_INFO(logger_, "Finished time loop");
    LOG_INFO(logger_, "Finished simulation");
}

auto LBMSolver::run() -> void
{
    initial_log_messages();

    while (time_.advance())
    {
        LOG_INFO(
            logger_, "Time step: {}/{} | Simulation time: {}", time_.current_step(),
            time_.number_of_steps(), time_.current_time()
        );
    }

    final_log_messages();
}
