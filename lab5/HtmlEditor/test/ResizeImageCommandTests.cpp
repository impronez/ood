#include <gtest/gtest.h>
#include "../Document/Command/InsertParagraphCommand.h"
#include "../Document/Command/ReplaceTextCommand.h"
#include "../Document/Command/InsertImageCommand.h"
#include "../Document/CDocument.h"

const std::string IMAGE_PATH = "dog1.jpg";

TEST(ResizeImageCommandTests, ExecuteResizesImageSuccess)
{
	std::vector<CDocumentItem> items;
	auto image = std::make_shared<CImage>(IMAGE_PATH, 100, 200);
	items.emplace_back(image);

	ResizeImageCommand command(0, 150, 300, items);

	EXPECT_NO_THROW(command.DoExecute());

	ASSERT_EQ(image->GetHeight(), 300);
	ASSERT_EQ(image->GetWidth(), 150);
}

TEST(ResizeImageCommandTests, ExecuteThrowsOnInvalidPositionError)
{
	std::vector<CDocumentItem> items;
	auto image = std::make_shared<CImage>(IMAGE_PATH, 100, 200);
	items.emplace_back(image);

	ResizeImageCommand command(1, 300, 150, items);

	EXPECT_THROW(command.DoExecute(), std::invalid_argument);
}

TEST(ResizeImageCommandTests, ExecuteThrowsWhenNoImageAtPositionError)
{
	std::vector<CDocumentItem> items;

	ResizeImageCommand command(0, 150, 300, items);

	EXPECT_THROW(command.DoExecute(), std::invalid_argument);
}

TEST(ResizeImageCommandTests, UnexecuteResizesBackToOriginalSizeSuccess)
{
	std::vector<CDocumentItem> items;
	auto image = std::make_shared<CImage>(IMAGE_PATH, 100, 200);
	items.emplace_back(image);

	ResizeImageCommand command(0, 150, 300, items);

	command.DoExecute();
	ASSERT_EQ(image->GetWidth(), 150);
	ASSERT_EQ(image->GetHeight(), 300);

	command.DoUnexecute();

	ASSERT_EQ(image->GetWidth(), 100);
	ASSERT_EQ(image->GetHeight(), 200);
}

TEST(ResizeImageCommandTests, UnexecuteThrowsOnInvalidPositionError)
{
	std::vector<CDocumentItem> items;
	auto image = std::make_shared<CImage>(IMAGE_PATH, 100, 200);
	items.emplace_back(image);

	ResizeImageCommand command(1, 150, 300, items);

	EXPECT_THROW(command.DoUnexecute(), std::invalid_argument);
}
