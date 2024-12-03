#include <gtest/gtest.h>
#include "../Document/History/History.h"
#include "../Document/Command/SetTitleCommand.h"

std::string title = "Original Title";
std::string newTitle = "New Title";

std::unique_ptr<ICommand> CreateNewCommand()
{
	return std::move(std::make_unique<SetTitleCommand>(title, newTitle));
}

TEST(HistoryTest, InitialState)
{
	History history;
	EXPECT_FALSE(history.CanUndo());
	EXPECT_FALSE(history.CanRedo());
}

TEST(HistoryTest, AddCommandAndUndo)
{
	History history;
	history.AddAndExecute(std::move(CreateNewCommand()));

	EXPECT_TRUE(history.CanUndo());
	EXPECT_FALSE(history.CanRedo());

	history.Undo();
	EXPECT_FALSE(history.CanUndo());
	EXPECT_TRUE(history.CanRedo());
}

TEST(HistoryTest, UndoAndRedo)
{
	History history;
	history.AddAndExecute(CreateNewCommand());

	history.Undo();
	EXPECT_FALSE(history.CanUndo());
	EXPECT_TRUE(history.CanRedo());

	history.Redo();
	EXPECT_TRUE(history.CanUndo());
	EXPECT_FALSE(history.CanRedo());
}

TEST(HistoryTest, OverflowCommands)
{
	History history;
	for (int i = 0; i < 11; ++i)
	{
		history.AddAndExecute(CreateNewCommand());
	}

	EXPECT_FALSE(history.CanRedo());

	for (int i = 0; i < 10; ++i)
	{
		EXPECT_TRUE(history.CanUndo());
		history.Undo();
		EXPECT_TRUE(history.CanRedo());
	}

	EXPECT_FALSE(history.CanUndo());
}
