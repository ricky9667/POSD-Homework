#pragma once

#include "command.h"
#include <vector>

class MacroCommand : public Command
{
private:
    std::vector<Command *> _commands;

public:
    MacroCommand() {}
    ~MacroCommand() {}

    void execute() override {}

    void addCommand(Command *command) override {}

    void undo() override {}

    std::vector<Command *> getCommands() override {}
};
