#pragma once

#include <quill/Logger.h>
#include <toml++/toml.hpp>

#include "configuration/configuration_datatypes.hpp"
#include "core/time/SimulationTime.hpp"

/// @brief Lattice Boltzmann Method (LBM) solver.
///
/// This class encapsulates a LBM solver and manages the simulation.
class LBMSolver
{
public:
    /// @brief Constructs an LBMSolver with the given configuration.
    ///
    /// @param configuration The application configuration.
    /// @param logger The logger handle.
    explicit LBMSolver(const ApplicationConfiguration& configuration, quill::Logger* logger);

    /// @brief Logs initial messages before starting the simulation.
    ///
    /// This method logs the starting time, time step size, and number of time steps.
    auto initial_log_messages() -> void;

    /// @brief Logs final messages after completing the simulation.
    ///
    /// This method logs the completion of the time loop and the end of the simulation.
    auto final_log_messages() -> void;

    /// @brief Runs the LBM simulation.
    ///
    /// This method advances the simulation in time according to the configured parameters.
    auto run() -> void;

private:
    bolt::core::SimulationTime<double> time_;
    quill::Logger* logger_;
};
