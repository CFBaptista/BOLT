#include <chrono>
#include <format>
#include <string>

#include "timestamp.hpp"

namespace bolt::core
{

auto get_timestamp() -> std::string
{
    const auto now = std::chrono::floor<std::chrono::seconds>(std::chrono::system_clock::now());
    const auto timestamp = std::format("{:%Y%m%dT%H%M%SZ}", now);

    return timestamp;
}

} // namespace bolt::core
