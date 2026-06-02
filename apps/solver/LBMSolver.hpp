#pragma once

#include "quill/Logger.h"
#include <toml++/toml.hpp>

#include "core/time/SimulationTime.hpp"
#include "quill/Logger.h"

class LBMSolver
{
public:
    LBMSolver(const toml::table& configuration, quill::Logger* logger);

    auto run() -> void;

private:
    bolt::core::SimulationTime<double> time_;
    quill::Logger* logger_;
};
