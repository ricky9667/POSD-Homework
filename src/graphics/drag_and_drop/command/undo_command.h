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
    UndoCommand(DragAndDrop *dragAndDrop, CommandHistory *commandHistory) {}

    void execute() override {}

    void undo() override {}
};
