#pragma once

#include "command.h"
#include "command_history.h"
#include "../drag_and_drop.h"

class UndoCommand : public Command
{

private:
    DragAndDrop *_dragAndDrop;
    CommandHistory *_commandHistory;

public:
    UndoCommand(DragAndDrop *dragAndDrop, CommandHistory *commandHistory) : _dragAndDrop{dragAndDrop}, _commandHistory{commandHistory} {}

    void execute() override
    {
        if (_commandHistory->getHistory().empty())
            throw std::string("Unable to undo because there are no commands in history.");

        Command *command = _commandHistory->getHistory().top();
        command->undo();
    }

    void undo() override
    {
        // intentionally left blank
    }
};
