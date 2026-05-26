#pragma once

#include <concepts>
#include <cstddef>

namespace bolt
{

namespace core
{

template <std::floating_point Real>
class SimulationTime
{
public:
    using value_type = Real;

    SimulationTime(
        const Real& starting_time,
        const Real& time_step,
        const std::size_t& number_of_steps
    );
    ~SimulationTime() = default;
    SimulationTime(const SimulationTime&) = delete;
    auto operator=(const SimulationTime&) -> SimulationTime& = delete;
    SimulationTime(SimulationTime&&) noexcept = delete;
    auto operator=(SimulationTime&&) noexcept -> SimulationTime& = delete;

    auto current_time() const -> Real;
    auto end_time() const -> Real;
    auto advance() -> void;

private:
    Real starting_time_;
    Real time_step_;
    std::size_t number_of_steps_;
    std::size_t current_step_;
};

} // namespace core

} // namespace bolt

#include "core/time/SimulationTime.tpp"
