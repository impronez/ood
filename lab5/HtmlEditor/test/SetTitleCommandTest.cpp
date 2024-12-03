#include <gtest/gtest.h>
#include "../Document/Command/SetTitleCommand.h"

TEST(SetTitleCommandTest, DoExecuteSetsNewTitleSuccess)
{
	std::string title = "Original Title";
	std::string newTitle = "New Title";

	SetTitleCommand command(title, newTitle);

	command.DoExecute();

	EXPECT_EQ(title, "New Title");

	command.DoUnexecute();

	EXPECT_EQ(title, "Original Title");
}

TEST(SetTitleCommandTest, DoUnexecuteRevertsToOldTitleSuccess)
{
	std::string title = "Initial Title";
	std::string newTitle = "Updated Title";

	SetTitleCommand command(title, newTitle);

	command.DoExecute();

	EXPECT_EQ(title, "Updated Title");

	command.DoUnexecute();

	EXPECT_EQ(title, "Initial Title");
}

TEST(SetTitleCommandTest, RepeatedExecuteAndUnexecuteSuccess)
{
	std::string title = "Start Title";
	std::string newTitle = "Changed Title";

	SetTitleCommand command(title, newTitle);

	command.DoExecute();
	EXPECT_EQ(title, "Changed Title");

	command.DoUnexecute();
	EXPECT_EQ(title, "Start Title");

	command.DoExecute();
	EXPECT_EQ(title, "Changed Title");

	command.DoUnexecute();
	EXPECT_EQ(title, "Start Title");
}

TEST(SetTitleCommandTest, DoExecuteWithSameTitleSuccess)
{
	std::string title = "Same Title";

	SetTitleCommand command(title, title);

	command.DoExecute();

	EXPECT_EQ(title, "Same Title");

	command.DoUnexecute();

	EXPECT_EQ(title, "Same Title");
}
