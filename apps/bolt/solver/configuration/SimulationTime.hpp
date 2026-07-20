#pragma once

#include <concepts>
#include <cstddef>

namespace bolt
{

namespace core
{

/// @brief A class template representing the time for a numerical simulation.
///
/// This class manages the state of simulation time and provides methods to obtain the current time
/// and to advance time by a time step.
///
/// @tparam Real The floating-point type to be used for representing time.
template <std::floating_point Real>
class SimulationTime
{
public:
    /// @brief The floating-point type value type.
    using value_type = Real;

    /// @brief Constructor to initialize the simulation time.
    ///
    /// @param start_time The initial time of the simulation.
    /// @param time_step The time step to advance the simulation at each step.
    /// @param number_of_steps The total number of steps in the simulation.
    SimulationTime(
        const Real& start_time,
        const Real& time_step,
        const std::size_t& number_of_steps
    );
    /// @brief Destructor.
    ~SimulationTime() = default;
    SimulationTime(const SimulationTime&) = delete;
    auto operator=(const SimulationTime&) -> SimulationTime& = delete;
    SimulationTime(SimulationTime&&) noexcept = delete;
    auto operator=(SimulationTime&&) noexcept -> SimulationTime& = delete;

    /// @brief Get the starting time of the simulation.
    ///
    /// @return The starting time of the simulation.
    auto start_time() const -> Real;

    /// @brief Get the time step of the simulation.
    ///
    /// @return The time step of the simulation.
    auto time_step() const -> Real;

    /// @brief Get the total number of steps in the simulation.
    ///
    /// @return The total number of steps in the simulation.
    auto number_of_steps() const -> std::size_t;

    /// @brief Get the current step of the simulation.
    ///
    /// @return The current step of the simulation.
    auto current_step() const -> std::size_t;

    /// @brief Get the current time of the simulation.
    ///
    /// @return The current time of the simulation.
    auto current_time() const -> Real;
    /// @brief Get the end time of the simulation.
    ///
    /// @return The end time of the simulation.
    auto end_time() const -> Real;
    /// @brief Advance the simulation time by one time step.
    ///
    /// @return False if the simulation has reached the end time, true otherwise.
    auto advance() -> bool;

private:
    Real start_time_;
    Real time_step_;
    std::size_t number_of_steps_;
    std::size_t current_step_;
};

} // namespace core

} // namespace bolt

#include "SimulationTime.tpp"
