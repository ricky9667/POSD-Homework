#include "../../../../src/graphics/drag_and_drop/drag_and_drop.h"
#include "../../../../src/graphics/drag_and_drop/mouse_position.h"
#include "../../../../src/graphics/drag_and_drop/command/command_history.h"
#include "../../../../src/graphics/drag_and_drop/command/drop_command.h"
#include "../mock_drag_and_drop.h"

class DropCommandTest : public ::testing::Test
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

TEST_F(DropCommandTest, GetCoordinatesShouldWorkExpectedly)
{
    mousePosition->setPos(3, 5);
    DropCommand *command = new DropCommand(mockDragAndDrop, commandHistory);

    ASSERT_NEAR(mousePosition->getX(), command->getX(), 0.001);
    ASSERT_NEAR(mousePosition->getY(), command->getY(), 0.001);

    delete command;
}

TEST_F(DropCommandTest, ExecuteShouldWorkExpectedly)
{
    mousePosition->setPos(24.12, 6.47);
    DropCommand *command = new DropCommand(mockDragAndDrop, commandHistory);

    ASSERT_NO_THROW(command->execute());
    ASSERT_NEAR(mousePosition->getX(), mockDragAndDrop->getDropX(), 0.001);
    ASSERT_NEAR(mousePosition->getY(), mockDragAndDrop->getDropY(), 0.001);

    delete command;
}

TEST_F(DropCommandTest, UndoShouldWorkExpectedly)
{
    mousePosition->setPos(10, 15);
    DropCommand *command = new DropCommand(mockDragAndDrop, commandHistory);

    ASSERT_NO_THROW(command->undo());
    ASSERT_NEAR(mousePosition->getX(), mockDragAndDrop->getGrabX(), 0.001);
    ASSERT_NEAR(mousePosition->getY(), mockDragAndDrop->getGrabY(), 0.001);

    delete command;
}