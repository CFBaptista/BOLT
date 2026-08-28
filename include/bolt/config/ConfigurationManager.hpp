#pragma once

#include <memory>
#include <span>
#include <string>
#include <string_view>

namespace bolt::config
{

/// @brief A class to parse command-line arguments and manage settings from input files.
class ConfigurationManager
{
public:
    ConfigurationManager() = delete;

    /// @brief Initialize the class with command-line arguments.
    ///
    /// @param args A span of string views representing the command-line arguments.
    explicit ConfigurationManager(std::span<const std::string_view> args);

    ConfigurationManager(const ConfigurationManager&) = delete;

    /// @brief Move constructor.
    ///
    /// @param other The other ConfigurationManager instance to move from.
    ConfigurationManager(ConfigurationManager&& other) = default;

    auto operator=(const ConfigurationManager&) -> ConfigurationManager& = delete;

    /// @brief Move assignment operator.
    ///
    /// @param other The other ConfigurationManager instance to move from.
    ///
    /// @return Reference to the current ConfigurationManager instance.
    auto operator=(ConfigurationManager&& other) -> ConfigurationManager& = default;

    /// @brief Destructor.
    ~ConfigurationManager();

    /// @brief Adds a command-line option to the parser.
    ///
    /// @tparam T The type of the value associated with the option.
    ///
    /// @param option The command-line option string (e.g., "-c,--config").
    /// @param value Reference to the variable that will hold the option's value.
    /// @param description Description of the option for help messages.
    template <typename T>
    auto add_cli_option(const std::string& option, T& value, const std::string& description)
        -> void;

    /// @brief Retrieves a configuration value from a parsed configuration file.
    ///
    /// @tparam T The type of the configuration value.
    ///
    /// @param key The key corresponding to the configuration value.
    /// @return The value associated with the specified key.
    template <typename T>
    auto get_config_value(const std::string& key) const -> T;

    /// @brief Parse the command-line arguments.
    auto parse() -> void;

private:
    struct Impl;
    std::unique_ptr<Impl> pimpl_;

    std::span<const std::string_view> args_;
};

} // namespace bolt::config
