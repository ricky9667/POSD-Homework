#include "../../../../src/graphics/drag_and_drop/drag_and_drop.h"
#include "../../../../src/graphics/drag_and_drop/mouse_position.h"
#include "../../../../src/graphics/drag_and_drop/command/command_history.h"
#include "../../../../src/graphics/drag_and_drop/command/move_command.h"
#include "../mock_drag_and_drop.h"

class MoveCommandTest : public ::testing::Test
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

TEST_F(MoveCommandTest, GetCoordinatedShouldWorkExpectedly)
{
    mousePosition->setPos(3, 5);
    MoveCommand *command = new MoveCommand(mockDragAndDrop, commandHistory);

    ASSERT_NEAR(mousePosition->getX(), command->getX(), 0.001);
    ASSERT_NEAR(mousePosition->getY(), command->getY(), 0.001);

    delete command;
}

TEST_F(MoveCommandTest, ExecuteShouldWorkExpectedly)
{
    mousePosition->setPos(24.12, 6.47);
    MoveCommand *command = new MoveCommand(mockDragAndDrop, commandHistory);

    ASSERT_NO_THROW(command->execute());
    ASSERT_NEAR(mousePosition->getX(), mockDragAndDrop->getMoveX(), 0.001);
    ASSERT_NEAR(mousePosition->getY(), mockDragAndDrop->getMoveY(), 0.001);

    delete command;
}

TEST_F(MoveCommandTest, UndoShouldWorkExpectedly)
{
    mousePosition->setPos(10, 15);
    MoveCommand *command = new MoveCommand(mockDragAndDrop, commandHistory);

    ASSERT_NO_THROW(command->undo());
    ASSERT_NEAR(mousePosition->getX(), mockDragAndDrop->getMoveX(), 0.001);
    ASSERT_NEAR(mousePosition->getY(), mockDragAndDrop->getMoveY(), 0.001);

    delete command;
}
