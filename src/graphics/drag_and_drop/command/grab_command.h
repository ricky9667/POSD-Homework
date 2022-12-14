#pragma once

#include "command.h"
#include "command_history.h"
#include "../drag_and_drop.h"
#include "../mouse_position.h"

class GrabCommand : public Command
{
private:
    DragAndDrop *_dragAndDrop;
    CommandHistory *_commandHistory;
    double _x, _y;

public:
    GrabCommand(DragAndDrop *dragAndDrop, CommandHistory *commandHistory) {}
    GrabCommand(const GrabCommand &grabCommand) {} // copy constructor

    void execute() override {}

    void undo() override {}

    double getX() const {}

    double getY() const {}
};
