#include "Command.h"

namespace CLI {
    void Command::run(const Context& context) const {
        action(context);
    }

    bool Command::hasOption(const std::string& name) const {
        for (const Option& option: options) {
            if (option.name == name) {
                return true;
            }
        }
        return false;
    }

    const Option* Command::getOption(const std::string& name) const {
        for (const Option& option: options) {
            if (option.name == name) {
                return &option;
            }
        }
        return nullptr;
    }

    std::string Command::getOptionValue(const std::string& name) const {
        const Option* targetOption = nullptr;
        for (const Option& option: options) {
            if (option.name == name) {
                targetOption = &option;
                break;
            }
        }
        if (targetOption == nullptr) {
            return "";
        }
        return targetOption->getValueOrDefault();
    }
}