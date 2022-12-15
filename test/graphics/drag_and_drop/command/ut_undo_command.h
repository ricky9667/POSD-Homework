#include "../../../../src/graphics/drag_and_drop/drag_and_drop.h"
#include "../../../../src/graphics/drag_and_drop/mouse_position.h"
#include "../../../../src/graphics/drag_and_drop/command/command_history.h"
#include "../../../../src/graphics/drag_and_drop/command/undo_command.h"
#include "../../../../src/graphics/drag_and_drop/command/macro_command.h"
#include "../mock_drag_and_drop.h"
#include "mock_command.h"

class UndoCommandTest : public ::testing::Test
{
protected:
    MockDragAndDrop *mockDragAndDrop;
    CommandHistory *commandHistory;
    MousePosition *mousePosition;

    void SetUp() override
    {
        mockDragAndDrop = new MockDragAndDrop();
        commandHistory = new CommandHistory();
        mousePosition = MousePosition::getInstance();
    }

    void TearDown() override
    {
        delete mockDragAndDrop;
        delete commandHistory;
    }
};

TEST_F(UndoCommandTest, ExecuteShouldWorkExpectedly)
{
    MockCommand *mockCommand = new MockCommand();
    UndoCommand *undoCommand = new UndoCommand(mockDragAndDrop, commandHistory);

    commandHistory->addCommand(mockCommand);
    undoCommand->execute();
    ASSERT_TRUE(mockCommand->isUndoCalled());

    delete mockCommand;
    delete undoCommand;
}

TEST_F(UndoCommandTest, ExecuteShouldThrowExceptionIfHistoryIsEmpty)
{
    UndoCommand *undoCommand = new UndoCommand(mockDragAndDrop, commandHistory);

    ASSERT_ANY_THROW(undoCommand->execute());

    delete undoCommand;
}
