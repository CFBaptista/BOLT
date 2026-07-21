#include "utilities.hpp"

#include <chrono>
#include <format>
#include <string>

namespace bolt::app
{

auto get_timestamp() -> std::string
{
    const auto now = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());
    const auto timestamp = std::format("{:%Y%m%dT%H%M%SZ}", now);

    return timestamp;
}

} // namespace bolt::app
