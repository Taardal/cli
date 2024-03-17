#include "App.h"
#include "Context.h"
#include "Help.h"
#include <sstream>

namespace CLI {

    App::App() : helpCommand(createHelpCommand()), helpOption(createHelpOption()) {
    }

    void App::run(int argc, char* argv[]) {
        initialize();

        Context context;
        context.app = this;

        bool showHelp = false;

        int firstSegmentIndex = 1;
        bool noSegments = argc - firstSegmentIndex == 0;
        if (noSegments) {
            showHelp = true;
        }
        bool previousSegmentWasOption = false;
        for (int i = firstSegmentIndex; i < argc; i++) {
            std::string segment(argv[i]);
            if (!context.arguments.empty()) {
                context.arguments.push_back(segment);
                continue;
            }
            Option option = getOption(segment, context.command);
            if (!option.name.empty()) {
                previousSegmentWasOption = true;
                context.options.push_back(option);
                if (option.name == helpOption.name) {
                    showHelp = true;
                }
            } else if (previousSegmentWasOption) {
                previousSegmentWasOption = false;
                context.options[context.options.size() - 1].value = segment;
            } else {
                previousSegmentWasOption = false;
                const Command* command = findCommand(segment);
                if (command == nullptr) {
                    context.arguments.push_back(segment);
                    continue;
                }
                if (command->name == helpCommand.name) {
                    showHelp = true;
                    continue;
                }
                context.command = command;
            }
        }
        if (showHelp) {
            helpCommand.action(context);
        } else if (context.command != nullptr) {
            context.command->action(context);
        } else {
            action(context);
        }
    }

    const Command* App::getCommand(const std::string& name) const {
        for (const Command& command : commands) {
            if (command.name == name) {
                return &command;
            }
        }
        return nullptr;
    }

    void App::runCommand(const std::string& name, const Context& context) const {
        const Command* command = getCommand(name);
        if (command != nullptr) {
            command->run(context);
        }
    }

    void App::initialize() {
        commands.push_back(helpCommand);
        options.push_back(helpOption);
    }

    Option App::getOption(std::string segment, const Command* command) const {
        constexpr int longFormDashCount = 2;
        constexpr int shortFormDashCount = 1;

        bool longForm = segment.length() > longFormDashCount && segment.substr(0, longFormDashCount) == "--";
        bool shortForm = segment.length() > shortFormDashCount && segment.substr(0, shortFormDashCount) == "-";

        bool isOption = longForm || shortForm;
        if (!isOption) {
            return {};
        }

        Option option;
        int dashCount = longForm ? longFormDashCount : shortFormDashCount;
        int equalSignIndex = (int) segment.find('=');
        if (equalSignIndex != std::string::npos) {
            option.name = segment.substr(dashCount, equalSignIndex - dashCount);
            option.value = segment.substr(equalSignIndex + 1, segment.length());
        } else {
            option.name = segment.substr(dashCount, segment.length());
        }
        const Option* definedOption = findOption(option.name, options);
        if (definedOption == nullptr && command != nullptr) {
            definedOption = findOption(option.name, command->options);
        }
        if (definedOption == nullptr) {
            std::stringstream ss;
            ss << "Option provided but not defined: " << segment;
            throw std::runtime_error(ss.str());
        }
        option.name = definedOption->name;
        option.usage = definedOption->usage;
        option.aliases = definedOption->aliases;
        return option;
    }

    const Option* App::findOption(std::string name, const std::vector<Option>& flags) const {
        for (const Option& option: flags) {
            if (name == option.name) {
                return &option;
            }
            for (std::string alias: option.aliases) {
                if (name == alias) {
                    return &option;
                }
            }
        }
        return nullptr;
    }

    const Command* App::findCommand(std::string segment) const {
        for (const Command& command: commands) {
            if (segment == command.name) {
                return &command;
            }
            for (std::string commandAlias: command.aliases) {
                if (segment == commandAlias) {
                    return &command;
                }
            }
        }
        return nullptr;
    }
}