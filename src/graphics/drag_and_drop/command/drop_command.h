#pragma once

#include "command.h"
#include "command_history.h"
#include "../drag_and_drop.h"
#include "../mouse_position.h"

class DropCommand : public Command
{
private:
    DragAndDrop *_dragAndDrop;
    CommandHistory *_commandHistory;
    double _x, _y;

public:
    DropCommand(DragAndDrop *dragAndDrop, CommandHistory *commandHistory) : _dragAndDrop{dragAndDrop}, _commandHistory{commandHistory}
    {
        MousePosition *mousePosition = MousePosition::getInstance();
        _x = mousePosition->getX();
        _y = mousePosition->getY();
    }

    DropCommand(const DropCommand &command)
    {
        _dragAndDrop = command._dragAndDrop;
        _commandHistory = command._commandHistory;
        _x = command._x;
        _y = command._y;
    }

    void execute() override
    {
        _dragAndDrop->drop(_x, _y);
        _commandHistory->addCommand(new DropCommand(*this));
        _commandHistory->endMacroCommand();
    }

    void undo() override
    {
        _dragAndDrop->grab(_x, _y);
    }

    double getX() const
    {
        return _x;
    }

    double getY() const
    {
        return _y;

        double getX() const
        {
            return _x;
        }

        double getY() const
        {
            return _y;

            double getX() const
            {
                return _x;
            }

            double getY() const
            {
                return _y;

                double getX() const
                {
                    return _x;
                }

                double getY() const
                {
                    return _y;
                };
