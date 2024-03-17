#include "Help.h"
#include "App.h"
#include <sstream>

namespace CLI {

    Option createHelpOption() {
        Option option;
        option.name = "help";
        option.aliases = {"h"};
        option.usage = "Show help";
        return option;
    }

    Command createHelpCommand() {
        Command command;
        command.name = "help";
        command.usage = "Show available commands and options";
        command.aliases = {"h"};
        command.action = [](const Context& context) -> void {
            const App& app = *context.app;

            constexpr int keyLeftPadding = 4;
            constexpr int valueLeftPadding = 4;

            if (context.command != nullptr) {
                const Command& command = *context.command;
                {
                    printf("%s\n", "NAME:");
                    int keyWidth = keyLeftPadding + command.name.length();
                    printf("%*s - %s\n", keyWidth, command.name.data(), command.usage.data());
                    printf("\n");
                }
                {
                    printf("%s\n", "USAGE:");
                    int keyWidth = keyLeftPadding + command.name.length();
                    printf("%*s %s\n", keyWidth, command.name.data(), "[command options] [arguments...]");
                    printf("\n");
                }
                {
                    printf("%s\n", "OPTIONS:");
                    const char* longFormPrefix = "--";
                    const char* shortFormPrefix = "-";
                    int longestKeyLength = 0;
                    for (const Option& option: command.options) {
                        std::stringstream ss;
                        ss << longFormPrefix << option.name;
                        for (std::string alias: option.aliases) {
                            ss << ", " << shortFormPrefix << alias;
                        }
                        int optionKeyLength = ss.str().length();
                        if (optionKeyLength > longestKeyLength) {
                            longestKeyLength = optionKeyLength;
                        }
                    }
                    for (const Option& option: command.options) {
                        std::stringstream ss;
                        ss << longFormPrefix << option.name;
                        for (std::string alias: option.aliases) {
                            ss << ", " << shortFormPrefix << alias;
                        }
                        const std::string& key = ss.str();
                        int keyWidth = keyLeftPadding + key.length();
                        printf("%*s", keyWidth, key.c_str());

                        std::string value = option.usage.length() > 0 ? std::string(option.usage) : "";
                        if (option.defaultValue.length() > 0) {
                            std::stringstream ss;
                            ss << value << " (Default: " << option.defaultValue << ")";
                            value = ss.str();
                        }
                        int keyRightPadding = longestKeyLength - key.length();
                        int valueWidth = keyRightPadding + valueLeftPadding + value.length();
                        printf("%*s\n", valueWidth, value.data());
                    }
                }
            } else {
                {
                    printf("%s\n", "NAME:");
                    int keyWidth = keyLeftPadding + app.name.length();
                    printf("%*s - %s\n", keyWidth, app.name.data(), app.usage.data());
                    printf("\n");
                }
                {
                    printf("%s\n", "USAGE:");
                    int keyWidth = keyLeftPadding + app.name.length();
                    printf("%*s %s\n", keyWidth, app.name.data(), "[global options] command [command options] [arguments...]");
                    printf("\n");
                }
                {
                    printf("%s\n", "COMMANDS:");
                    int longestKeyLength = 0;
                    for (const Command& command: app.commands) {
                        std::stringstream ss;
                        ss << command.name;
                        for (std::string alias: command.aliases) {
                            ss << ", " << alias;
                        }
                        int keyLength = ss.str().length();
                        if (keyLength > longestKeyLength) {
                            longestKeyLength = keyLength;
                        }
                    }
                    for (const Command& command: app.commands) {
                        std::stringstream ss;
                        ss << command.name;
                        for (std::string alias: command.aliases) {
                            ss << ", " << alias;
                        }
                        const std::string& key = ss.str();
                        int keyWidth = keyLeftPadding + key.length();
                        printf("%*s", keyWidth, key.c_str());

                        std::string value = command.usage;
                        int keyRightPadding = longestKeyLength - key.length();
                        int valueWidth = keyRightPadding + valueLeftPadding + value.length();
                        printf("%*s\n", valueWidth, value.data());
                    }
                    printf("\n");
                }
                {
                    printf("%s\n", "GLOBAL OPTIONS:");
                    const char* longFormPrefix = "--";
                    const char* shortFormPrefix = "-";
                    int longestKeyLength = 0;
                    for (const Option& option: app.options) {
                        std::stringstream ss;
                        ss << longFormPrefix << option.name;
                        for (std::string alias: option.aliases) {
                            ss << ", " << shortFormPrefix << alias;
                        }
                        int optionKeyLength = ss.str().length();
                        if (optionKeyLength > longestKeyLength) {
                            longestKeyLength = optionKeyLength;
                        }
                    }
                    for (const Option& option: app.options) {
                        std::stringstream ss;
                        ss << longFormPrefix << option.name;
                        for (std::string alias: option.aliases) {
                            ss << ", " << shortFormPrefix << alias;
                        }
                        const std::string& key = ss.str();
                        int keyWidth = keyLeftPadding + key.length();
                        printf("%*s", keyWidth, key.data());

                        std::string value = option.usage.length() > 0 ? std::string(option.usage) : "";
                        if (option.defaultValue.length() > 0) {
                            std::stringstream ss;
                            ss << value << " (Default: " << option.defaultValue << ")";
                            value = ss.str();
                        }
                        int keyRightPadding = longestKeyLength - key.length();
                        int valueWidth = keyRightPadding + valueLeftPadding + value.length();
                        printf("%*s\n", valueWidth, value.data());
                    }
                }
            }
        };
        return command;
    }
}
