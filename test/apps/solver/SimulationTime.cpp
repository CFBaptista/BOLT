#include <cstddef>
#include <stdexcept>

#include <catch2/catch_test_macros.hpp>

#include "bolt/solver/configuration/SimulationTime.hpp"

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("Verify properties and state of simulation time")
{
    GIVEN("A valid set of parameters")
    {
        const double start_time = 0.0;
        const double time_step = 0.1;
        const std::size_t number_of_steps = 10;

        bolt::core::SimulationTime<double> time(start_time, time_step, number_of_steps);

        THEN("The current time is equal to the starting time")
        {
            REQUIRE(time.current_time() == start_time);
        }

        THEN("The end time is correctly calculated")
        {

            REQUIRE(time.end_time() == start_time + (time_step * number_of_steps));
        }

        THEN("Advancing the simulation time updates the current time correctly")
        {
            for (std::size_t step = 0; step < number_of_steps; ++step)
            {
                REQUIRE(time.current_time() == start_time + (time_step * step));
                time.advance();
            }

            REQUIRE(time.current_time() == time.end_time());
        }
    }
}

// NOLINTNEXTLINE(readability-function-cognitive-complexity)
SCENARIO("Invalid parameters for simulation time throw exceptions")
{
    THEN("Non-positive time step throws an exception")
    {
        // NOLINTNEXTLINE(readability-magic-numbers, cppcoreguidelines-avoid-magic-numbers)
        REQUIRE_THROWS_AS(bolt::core::SimulationTime<double>(0.0, -0.1, 10), std::invalid_argument);
        REQUIRE_THROWS_AS(bolt::core::SimulationTime<double>(0.0, 0.0, 10), std::invalid_argument);
    }

    THEN("Zero number of steps throws an exception")
    {
        // NOLINTNEXTLINE(readability-magic-numbers, cppcoreguidelines-avoid-magic-numbers)
        REQUIRE_THROWS_AS(bolt::core::SimulationTime<double>(0.0, 0.1, 0), std::invalid_argument);
    }
}
