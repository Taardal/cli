#include "Option.h"

namespace CLI {

    std::string Option::getValueOrDefault() const {
        return value.length() > 0 ? value : defaultValue.length() > 0 ? defaultValue : "";
    }
}