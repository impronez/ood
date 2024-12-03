#include <gtest/gtest.h>
#include "../Document/Command/InsertParagraphCommand.h"

TEST(InsertParagraphCommandTest, InsertAtEndSuccess)
{
	std::vector<CDocumentItem> items;
	std::string text = "New paragraph text";

	InsertParagraphCommand command(text, std::nullopt, items);

	command.DoExecute();

	ASSERT_EQ(items.size(), 1);

	auto paragraph = std::dynamic_pointer_cast<CParagraph>(items[0].GetParagraph());
	ASSERT_NE(paragraph, nullptr);
	EXPECT_EQ(paragraph->GetText(), text);

	command.DoUnexecute();

	EXPECT_TRUE(items.empty());
}

TEST(InsertParagraphCommandTest, InsertAtPositionSuccess)
{
	std::string text = "Existing paragraph";
	auto paragraph = std::make_shared<CParagraph>(text);
	CDocumentItem item(paragraph);
	std::vector<CDocumentItem> items = {item};

	std::string textInserted = "Inserted paragraph";
	size_t position = 0;

	InsertParagraphCommand command(textInserted, position, items);

	command.DoExecute();

	ASSERT_EQ(items.size(), 2);

	auto paragraph1 = std::dynamic_pointer_cast<CParagraph>(items[position].GetParagraph());
	ASSERT_NE(paragraph1, nullptr);
	EXPECT_EQ(paragraph1->GetText(), textInserted);

	command.DoUnexecute();

	ASSERT_EQ(items.size(), 1);
	EXPECT_EQ(items[0].GetParagraph()->GetText(), "Existing paragraph");
}

TEST(InsertParagraphCommandTest, InsertAtInvalidPositionError)
{
	std::vector<CDocumentItem> items;
	std::string text = "Text for invalid position";
	size_t invalidPosition = 10;

	InsertParagraphCommand command(text, invalidPosition, items);

	EXPECT_THROW(command.DoExecute(), std::invalid_argument);
	EXPECT_TRUE(items.empty());
}
