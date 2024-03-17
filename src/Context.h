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
        const App* app;
        const Command* command = nullptr;
        std::vector<Option> options;
        std::vector<std::string> arguments;

        bool hasOption(const std::string& name) const;

        const Option* getOption(const std::string& name) const;
    };
}