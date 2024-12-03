#include <gtest/gtest.h>
#include "../Document/Command/ReplaceTextCommand.h"
#include "../Document/Paragraph/CParagraph.h"

TEST(ReplaceTextCommandTest, DoExecuteReplaceTextAtPositionSuccess)
{
	std::vector<CDocumentItem> items;
	std::string oldText = "Original text";
	items.emplace_back(std::make_shared<CParagraph>(oldText));

	std::string newText = "Replaced text";
	size_t position = 0;

	ReplaceTextCommand command(newText, position, items);

	command.DoExecute();

	auto paragraph = std::dynamic_pointer_cast<CParagraph>(items[position].GetParagraph());
	ASSERT_NE(paragraph, nullptr);
	EXPECT_EQ(paragraph->GetText(), newText);

	command.DoUnexecute();

	EXPECT_EQ(paragraph->GetText(), "Original text");
}

TEST(ReplaceTextCommandTest, DoExecuteReplaceTextWithInvalidPositionError)
{
	std::vector<CDocumentItem> items;
	std::string newText = "Text for invalid position";
	size_t invalidPosition = 10;

	ReplaceTextCommand command(newText, invalidPosition, items);

	EXPECT_THROW(command.DoExecute(), std::invalid_argument);
}

TEST(ReplaceTextCommandTest, DoUnexecuteRestoreOriginalTextSuccess)
{
	std::vector<CDocumentItem> documentItems;
	std::string oldText = "Initial text";
	documentItems.emplace_back(std::make_shared<CParagraph>(oldText));

	std::string newText = "New text";
	size_t position = 0;

	ReplaceTextCommand command(newText, position, documentItems);

	command.DoExecute();

	auto paragraph = std::dynamic_pointer_cast<CParagraph>(documentItems[position].GetParagraph());
	ASSERT_NE(paragraph, nullptr);
	EXPECT_EQ(paragraph->GetText(), newText);

	command.DoUnexecute();

	EXPECT_EQ(paragraph->GetText(), "Initial text");
}
