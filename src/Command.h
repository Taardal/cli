#pragma once

#include "Context.h"
#include "Option.h"
#include <string>
#include <vector>
#include <functional>

namespace CLI {

    struct Command {
        std::string name;
        std::string usage;
        std::vector<std::string> aliases;
        std::vector<Option> options;
        std::function<void(const Context&)> action;

        void run(const Context& context) const;

        bool hasOption(const std::string& name) const;

        const Option* getOption(const std::string& name) const;

        std::string getOptionValue(const std::string& name) const;
    };
}