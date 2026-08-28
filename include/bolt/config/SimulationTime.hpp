#pragma once

#include <concepts>
#include <cstddef>

namespace bolt::config
{

/// @brief Represents and manages the discrete time for a numerical simulation.
///
/// @tparam Real Floating-point type to be used for real numbers.
template <std::floating_point Real>
class SimulationTime
{
public:
    /// @brief Floating-point value type.
    using value_type = Real;

    /// @brief Constructs and initializes the simulation time.
    ///
    /// @param start_time Initial time of the simulation (seconds).
    /// @param time_step Time increment when advancing the simulation by one step (seconds).
    /// @param number_of_steps Total number of steps in the simulation.
    SimulationTime(
        const Real& start_time,
        const Real& time_step,
        const std::size_t& number_of_steps
    );

    SimulationTime(const SimulationTime&) = delete;
    SimulationTime(SimulationTime&&) noexcept = delete;
    auto operator=(const SimulationTime&) -> SimulationTime& = delete;
    auto operator=(SimulationTime&&) noexcept -> SimulationTime& = delete;

    /// @brief Default destructor.
    ~SimulationTime() = default;

    /// @brief Gets the initial time of the simulation.
    ///
    /// @return Initial time (seconds).
    auto start_time() const -> Real;

    /// @brief Gets the time increment for advancing the simulation by one step.
    ///
    /// @return Time increment (seconds).
    auto time_step() const -> Real;

    /// @brief Gets the total number of steps in the simulation.
    ///
    /// @return Number of steps.
    auto number_of_steps() const -> std::size_t;

    /// @brief Gets the current step of the simulation.
    ///
    /// @return Current step.
    auto current_step() const -> std::size_t;

    /// @brief Gets the current time of the simulation.
    ///
    /// @return Current time (seconds).
    auto current_time() const -> Real;

    /// @brief Gets the end time of the simulation.
    ///
    /// @return End time (seconds).
    auto end_time() const -> Real;

    /// @brief Advances the simulation in time by one time step.
    ///
    /// @return `false` if the simulation has reached the end time, `true` otherwise.
    auto advance() -> bool;

private:
    Real start_time_;
    Real time_step_;
    std::size_t number_of_steps_;
    std::size_t current_step_;
};

} // namespace bolt::config

#include "SimulationTime.tpp"
