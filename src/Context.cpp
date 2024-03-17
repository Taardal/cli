#include "Command.h"
#include "Context.h"
#include "Option.h"

namespace CLI {

    bool Context::hasOption(const std::string& name) const {
        for (const Option& option: options) {
            if (option.name == name) {
                return true;
            }
        }
        return false;
    }

    const Option* Context::getOption(const std::string& name) const {
        for (const Option& option: options) {
            if (option.name == name) {
                return &option;
            }
        }
        return nullptr;
    }
}