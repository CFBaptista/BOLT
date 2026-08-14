#include <format>
#include <stdexcept>
#include <string_view>

#include "toml_parser.hpp" //NOLINT(misc-header-include-cycle)

namespace bolt::config
{

template <typename T>
auto get_toml_value(const toml::table& table, std::string_view key) -> T
{
    if (!table.contains(key))
    {
        throw std::invalid_argument(std::format("Key '{}' not found in TOML table", key));
    }

    if (auto value = table[key].value<T>(); value)
    {
        return *value;
    }

    throw std::invalid_argument(
        std::format("Value for key '{}' in TOML table is not convertible to the expected type", key)
    );
}

} // namespace bolt::config
