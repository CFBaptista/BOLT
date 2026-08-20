#pragma once

#include <quill/Logger.h>

#include "bolt/config/SimulationTime.hpp"

#include "configuration.hpp"

namespace bolt::app
{

/// @brief Represents a Lattice Boltzmann Method (LBM) solver.
class LBMSolver
{
public:
    /// @brief Constructs and configures a LBMSolver.
    ///
    /// @param configuration The application configuration.
    /// @param logger The logger handle.
    explicit LBMSolver(const ApplicationConfiguration& configuration, quill::Logger* logger);

    /// @brief Advances the LBM simulation in time.
    auto run() -> void;

private:
    bolt::config::SimulationTime<double> time_;
    [[maybe_unused]] quill::Logger* logger_;

    /// @brief Logs initial messages before starting the simulation.
    auto initial_log_messages() const -> void;

    /// @brief Logs final messages after completing the simulation.
    auto final_log_messages() const -> void;
};

} // namespace bolt::app
