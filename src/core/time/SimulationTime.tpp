#pragma once

#include <concepts>
#include <cstddef>
#include <stdexcept>

#include "core/time/SimulationTime.hpp"

namespace bolt
{

namespace core
{

template <std::floating_point Real>

SimulationTime<Real>::SimulationTime(
    const Real& starting_time, // NOLINT(bugprone-easily-swappable-parameters)
    const Real& time_step,     // NOLINT(bugprone-easily-swappable-parameters)
    const std::size_t& number_of_steps
)
    : starting_time_(starting_time), time_step_(time_step), number_of_steps_(number_of_steps),
      current_step_(0)
{
    if (time_step_ <= static_cast<Real>(0))
    {
        throw std::invalid_argument("Time step must be positive.");
    }

    if (number_of_steps_ == 0)
    {
        throw std::invalid_argument("Number of time steps must be greater than zero.");
    }
}

template <std::floating_point Real>
auto SimulationTime<Real>::starting_time() const -> Real
{
    return starting_time_;
}

template <std::floating_point Real>
auto SimulationTime<Real>::time_step() const -> Real
{
    return time_step_;
}

template <std::floating_point Real>
auto SimulationTime<Real>::number_of_steps() const -> std::size_t
{
    return number_of_steps_;
}

template <std::floating_point Real>
auto SimulationTime<Real>::current_step() const -> std::size_t
{
    return current_step_;
}

template <std::floating_point Real>
auto SimulationTime<Real>::current_time() const -> Real
{
    return starting_time_ + (time_step_ * static_cast<Real>(current_step_));
}

template <std::floating_point Real>
auto SimulationTime<Real>::end_time() const -> Real
{
    return starting_time_ + (time_step_ * static_cast<Real>(number_of_steps_));
}

template <std::floating_point Real>
auto SimulationTime<Real>::advance() -> bool
{
    if (current_step_ < number_of_steps_)
    {
        ++current_step_;
        return true;
    }

    return false;
}

} // namespace core

} // namespace bolt
