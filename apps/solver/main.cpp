#include <cstddef>
#include <filesystem>
#include <iostream>
#include <span>

#include <toml++/toml.hpp>

auto main(int argc, char* argv[]) -> int
{
    const std::span args = std::span(argv, static_cast<std::size_t>(argc));

    toml::table configuration;

    try
    {
        const std::filesystem::path configuration_filepath = args[1];
        configuration = toml::parse_file(configuration_filepath.string());

        std::cout << configuration << "\n";
    }
    catch (const toml::parse_error& err)
    {
        std::cerr << "Parsing the simulation configuration file failed:\n" << err << "\n";
        return 1;
    }

    return 0;
}
