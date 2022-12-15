#include "../../../../src/graphics/drag_and_drop/drag_and_drop.h"
#include "../../../../src/graphics/drag_and_drop/mouse_position.h"
#include "../../../../src/graphics/drag_and_drop/command/command_history.h"
#include "../../../../src/graphics/drag_and_drop/command/macro_command.h"
#include "../mock_drag_and_drop.h"
#include "mock_command.h"

class CommandHistoryTest : public ::testing::Test
{
protected:
    CommandHistory *commandHistory;
    MousePosition *mousePosition;

    void SetUp() override
    {
        commandHistory = new CommandHistory();
        mousePosition = MousePosition::getInstance();
    }

    void TearDown() override
    {
        delete commandHistory;
    }
};

TEST_F(CommandHistoryTest, AddCommandShouldWorkExpectedly)
{
    MockCommand *command1 = new MockCommand();
    MockCommand *command2 = new MockCommand();

    commandHistory->addCommand(command1);
    commandHistory->addCommand(command2);

    std::stack<Command *> commands = commandHistory->getHistory();

    ASSERT_EQ(2, commands.size());
    ASSERT_EQ(command2, commands.top());
    commands.pop();
    ASSERT_EQ(command1, commands.top());
}

TEST_F(CommandHistoryTest, AddCommandShouldAndCommandToMacroCommand)
{
    MockCommand *command1 = new MockCommand();
    MockCommand *command2 = new MockCommand();

    commandHistory->beginMacroCommand();
    commandHistory->addCommand(command1);
    commandHistory->addCommand(command2);
    commandHistory->endMacroCommand();

    std::stack<Command *> commands = commandHistory->getHistory();

    ASSERT_EQ(1, commands.size());
    ASSERT_EQ(command1, commands.top()->getCommands().at(0));
    ASSERT_EQ(command2, commands.top()->getCommands().at(1));
}

TEST_F(CommandHistoryTest, UndoShouldWorkExpectedly)
{
    MockCommand *command = new MockCommand();

    commandHistory->addCommand(command);
    ASSERT_FALSE(command->isUndoCalled());

    commandHistory->undo();
    ASSERT_TRUE(command->isUndoCalled());
}