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
    GrabCommand(DragAndDrop *dragAndDrop, CommandHistory *commandHistory) : _dragAndDrop{dragAndDrop}, _commandHistory{commandHistory}
    {
        MousePosition *mousePosition = MousePosition::getInstance();
        _x = mousePosition->getX();
        _y = mousePosition->getY();
    }

    GrabCommand(const GrabCommand &command)
    {
        _dragAndDrop = command._dragAndDrop;
        _commandHistory = command._commandHistory;
        _x = command._x;
        _y = command._y;
    }

    void execute() override
    {
        _dragAndDrop->grab(_x, _y);
        _commandHistory->beginMacroCommand();
        _commandHistory->addCommand(new GrabCommand(*this));
    }

    void undo() override
    {
        _dragAndDrop->move(_x, _y);
        _dragAndDrop->drop(_x, _y);
    }

    double getX() const
    {
        return _x;
    }

    double getY() const
    {
        return _y;
    }
};
