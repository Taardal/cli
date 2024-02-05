#pragma once

#include <string>
#include <vector>

namespace CLI
{

    struct App;
    struct Command;
    struct Option;

    struct Context
    {
        const App* App;
        const Command* Command = nullptr;
        std::vector<Option> Options;
        std::vector<std::string_view> Arguments;

        bool hasOption(std::string_view name) const;

        const Option* getOption(std::string_view name) const;
    };
}