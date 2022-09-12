#include "Option.h"

namespace Clipp {

    std::string_view Option::getValueOrDefault() const {
        return Value.length() > 0 ? Value : DefaultValue.length() > 0 ? DefaultValue : "";
    }
}