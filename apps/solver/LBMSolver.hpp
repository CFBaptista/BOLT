#pragma once

#include <quill/Logger.h>
#include <toml++/toml.hpp>

#include "core/time/SimulationTime.hpp"

/**
 * @brief Lattice Boltzmann Method (LBM) solver
 *
 * This class encapsulates a LBM solver and manages the simulation.
 */
class LBMSolver
{
public:
    /**
     * @brief Constructs an LBMSolver with the given configuration and logger.
     *
     * @param configuration The TOML table containing the simulation configuration parameters.
     * @param logger A pointer to a quill::Logger for logging simulation progress and information.
     */
    LBMSolver(const toml::table& configuration, quill::Logger* logger);

    /**
     * @brief Runs the LBM simulation.
     *
     * This method advances the simulation in time according to the configured parameters.
     */
    auto run() -> void;

private:
    bolt::core::SimulationTime<double> time_;
    quill::Logger* logger_;
};
