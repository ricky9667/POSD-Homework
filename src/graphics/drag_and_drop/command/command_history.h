#pragma once

#include <stack>
#include "command.h"
#include "macro_command.h"

class CommandHistory
{
private:
    bool inMacro = false;
    std::stack<Command *> _history;
    std::stack<Command *> _undoCommands;

public:
    CommandHistory() {}
    ~CommandHistory() {}

    void beginMacroCommand() {}

    void addCommand(Command *command) {}

    void endMacroCommand() {}

    void undo() {}

    std::stack<Command *> getHistory() {}
};
