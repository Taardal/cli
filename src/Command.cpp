#include "Command.h"

namespace CLI {

    bool Command::hasOption(std::string_view name) const {
        for (const Option& option: Options) {
            if (option.Name == name) {
                return true;
            }
        }
        return false;
    }

    const Option* Command::getOption(std::string_view name) const {
        for (const Option& option: Options) {
            if (option.Name == name) {
                return &option;
            }
        }
        return nullptr;
    }

    std::string_view Command::getOptionValue(std::string_view name) const {
        const Option* targetOption = nullptr;
        for (const Option& option: Options) {
            if (option.Name == name) {
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