#include "../../../../src/graphics/drag_and_drop/drag_and_drop.h"
#include "../../../../src/graphics/drag_and_drop/mouse_position.h"
#include "../../../../src/graphics/drag_and_drop/command/command_history.h"
#include "../../../../src/graphics/drag_and_drop/command/grab_command.h"
#include "../../../../src/graphics/drag_and_drop/command/move_command.h"
#include "../../../../src/graphics/drag_and_drop/command/drop_command.h"
#include "../../../../src/graphics/drag_and_drop/command/macro_command.h"
#include "../mock_drag_and_drop.h"
#include "mock_command.h"

class MacroCommandTest : public ::testing::Test
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

TEST_F(MacroCommandTest, AddCommandShouldWorkExpectedly)
{
    MacroCommand *macroCommand = new MacroCommand();

    mousePosition->setPos(3, 2);
    GrabCommand *grabCommand = new GrabCommand(mockDragAndDrop, commandHistory);
    mousePosition->setPos(6, 4);
    DropCommand *dropCommand = new DropCommand(mockDragAndDrop, commandHistory);

    macroCommand->addCommand(grabCommand);
    macroCommand->addCommand(dropCommand);

    std::vector<Command *> commands = macroCommand->getCommands();
    ASSERT_EQ(2, commands.size());
    ASSERT_EQ(grabCommand, commands.at(0));
    ASSERT_EQ(dropCommand, commands.at(1));

    delete macroCommand;
}

TEST_F(MacroCommandTest, ExecuteShouldWorkExpectedly)
{
    MacroCommand *macroCommand = new MacroCommand();
    MockCommand *command1 = new MockCommand();
    MockCommand *command2 = new MockCommand();
    MockCommand *command3 = new MockCommand();

    macroCommand->addCommand(command1);
    macroCommand->addCommand(command2);
    macroCommand->addCommand(command3);

    ASSERT_FALSE(command1->isExecuteCalled());
    ASSERT_FALSE(command2->isExecuteCalled());
    ASSERT_FALSE(command3->isExecuteCalled());

    macroCommand->execute();

    ASSERT_TRUE(command1->isExecuteCalled());
    ASSERT_TRUE(command2->isExecuteCalled());
    ASSERT_TRUE(command3->isExecuteCalled());

    delete macroCommand;
}

TEST_F(MacroCommandTest, UndoShouldWorkExpectedly)
{
    MacroCommand *macroCommand = new MacroCommand();
    MockCommand *command1 = new MockCommand();
    MockCommand *command2 = new MockCommand();
    MockCommand *command3 = new MockCommand();

    macroCommand->addCommand(command1);
    macroCommand->addCommand(command2);
    macroCommand->addCommand(command3);

    ASSERT_FALSE(command1->isUndoCalled());
    ASSERT_FALSE(command2->isUndoCalled());
    ASSERT_FALSE(command3->isUndoCalled());

    macroCommand->undo();

    ASSERT_TRUE(command1->isUndoCalled());
    ASSERT_TRUE(command2->isUndoCalled());
    ASSERT_TRUE(command3->isUndoCalled());

    delete macroCommand;
}