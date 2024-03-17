#pragma once

#include "Command.h"
#include "Option.h"
#include <string>
#include <vector>
#include <functional>

namespace CLI {

    struct App {
    public:
        std::string name;
        std::string usage;
        std::vector<Command> commands;
        std::vector<Option> options;
        std::function<void(const Context& context)> action;

    private:
        Command helpCommand;
        Option helpOption;

    public:
        App();

        void run(int argc, char* argv[]);

        const Command* getCommand(const std::string& name) const;

        void runCommand(const std::string& name, const Context& context) const;

    private:
        void initialize();

        Option getOption(std::string segment, const Command* command) const;

        const Option* findOption(std::string name, const std::vector<Option>& flags) const;

        const Command* findCommand(std::string segment) const;
    };
}