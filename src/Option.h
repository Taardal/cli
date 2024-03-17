#pragma once

#include <string>
#include <vector>

namespace CLI {

    struct Option {
        std::string name;
        std::string usage;
        std::string value;
        std::string defaultValue;
        std::vector<std::string> aliases;

        std::string getValueOrDefault() const;
    };
}
