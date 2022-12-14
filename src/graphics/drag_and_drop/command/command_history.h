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

    void beginMacroCommand()
    {
        inMacro = true;
        _history.push(new MacroCommand());
    }

    void addCommand(Command *command)
    {
        if (inMacro)
        {
            MacroCommand *macroCommand = dynamic_cast<MacroCommand *>(_history.top());
            macroCommand->addCommand(command);
        }
        _history.push(command);
    }

    void endMacroCommand()
    {
        inMacro = false;
    }

    void undo()
    {
        if (_history.empty())
            return;

        Command *command = _history.top();
        _history.pop();
        _undoCommands.push(command);
    }

    std::stack<Command *> getHistory()
    {
        return _history;
    }
};
