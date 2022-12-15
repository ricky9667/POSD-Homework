#include "../../../../src/graphics/drag_and_drop/drag_and_drop.h"
#include "../../../../src/graphics/drag_and_drop/mouse_position.h"
#include "../../../../src/graphics/drag_and_drop/command/command_history.h"
#include "../../../../src/graphics/drag_and_drop/command/grab_command.h"
#include "../mock_drag_and_drop.h"

class GrabCommandTest : public ::testing::Test
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

TEST_F(GrabCommandTest, GetCoordinatesShouldWorkExpectedly)
{
    mousePosition->setPos(3, 5);
    GrabCommand *command = new GrabCommand(mockDragAndDrop, commandHistory);

    ASSERT_NEAR(mousePosition->getX(), command->getX(), 0.001);
    ASSERT_NEAR(mousePosition->getY(), command->getY(), 0.001);
}

TEST_F(GrabCommandTest, ExecuteShouldWorkExpectedly)
{
    mousePosition->setPos(24.12, 6.47);
    GrabCommand *command = new GrabCommand(mockDragAndDrop, commandHistory);

    ASSERT_NO_THROW(command->execute());
    ASSERT_NEAR(mousePosition->getX(), mockDragAndDrop->getGrabX(), 0.001);
    ASSERT_NEAR(mousePosition->getY(), mockDragAndDrop->getGrabY(), 0.001);
}

TEST_F(GrabCommandTest, UndoShouldWorkExpectedly)
{
    mousePosition->setPos(10, 15);
    GrabCommand *command = new GrabCommand(mockDragAndDrop, commandHistory);

    ASSERT_NO_THROW(command->undo());
    ASSERT_NEAR(mousePosition->getX(), mockDragAndDrop->getMoveX(), 0.001);
    ASSERT_NEAR(mousePosition->getY(), mockDragAndDrop->getMoveY(), 0.001);
    ASSERT_NEAR(mousePosition->getX(), mockDragAndDrop->getDropX(), 0.001);
    ASSERT_NEAR(mousePosition->getY(), mockDragAndDrop->getDropY(), 0.001);
}