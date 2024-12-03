#include <gtest/gtest.h>
#include "../Document/CDocument.h"

const std::string IMAGE_PATH = "output.jpg";

TEST(DocumentTest, InsertParagraph)
{
	CDocument document;
	EXPECT_EQ(document.GetItemsCount(), 0);

	document.InsertParagraph("First paragraph", std::nullopt);
	EXPECT_EQ(document.GetItemsCount(), 1);
	EXPECT_EQ(document.GetItem(0).GetParagraph()->GetText(), "First paragraph");

	document.InsertParagraph("Second paragraph", std::nullopt);
	EXPECT_EQ(document.GetItemsCount(), 2);
	EXPECT_EQ(document.GetItem(1).GetParagraph()->GetText(), "Second paragraph");
}

TEST(DocumentTest, ReplaceText)
{
	CDocument document;
	document.InsertParagraph("Old text", std::nullopt);
	EXPECT_EQ(document.GetItem(0).GetParagraph()->GetText(), "Old text");

	document.ReplaceText("New text", 0);
	EXPECT_EQ(document.GetItem(0).GetParagraph()->GetText(), "New text");
}

TEST(DocumentTest, InsertImage)
{
	CDocument document;
	EXPECT_EQ(document.GetItemsCount(), 0);

	document.InsertImage(IMAGE_PATH, 800, 600, std::nullopt);

	EXPECT_EQ(document.GetItemsCount(), 1);
	EXPECT_EQ(document.GetItem(0).GetImage()->GetWidth(), 800);
	EXPECT_EQ(document.GetItem(0).GetImage()->GetHeight(), 600);
}

TEST(DocumentTest, ResizeImage)
{
	CDocument document;
	document.InsertImage(IMAGE_PATH, 800, 600, std::nullopt);

	EXPECT_EQ(document.GetItem(0).GetImage()->GetWidth(), 800);
	EXPECT_EQ(document.GetItem(0).GetImage()->GetHeight(), 600);

	document.ResizeImage(0, 1024, 768);
	EXPECT_EQ(document.GetItem(0).GetImage()->GetWidth(), 1024);
	EXPECT_EQ(document.GetItem(0).GetImage()->GetHeight(), 768);
}

TEST(DocumentTest, DeleteItem)
{
	CDocument document;
	document.InsertParagraph("Paragraph 1", std::nullopt);
	document.InsertParagraph("Paragraph 2", std::nullopt);

	EXPECT_EQ(document.GetItemsCount(), 2);
	document.DeleteItem(0);
	EXPECT_EQ(document.GetItemsCount(), 1);
	EXPECT_EQ(document.GetItem(0).GetParagraph()->GetText(), "Paragraph 2");
}

TEST(DocumentTest, SetTitle)
{
	CDocument document;
	EXPECT_EQ(document.GetTitle(), "");

	document.SetTitle("New Title");
	EXPECT_EQ(document.GetTitle(), "New Title");

	document.SetTitle("Updated Title");
	EXPECT_EQ(document.GetTitle(), "Updated Title");
}

TEST(DocumentTest, UndoRedo)
{
	CDocument document;
	document.InsertParagraph("First paragraph", std::nullopt);
	document.InsertParagraph("Second paragraph", std::nullopt);

	EXPECT_TRUE(document.CanUndo());
	document.Undo();
	EXPECT_EQ(document.GetItemsCount(), 1);
	EXPECT_EQ(document.GetItem(0).GetParagraph()->GetText(), "First paragraph");

	EXPECT_TRUE(document.CanRedo());
	document.Redo();
	EXPECT_EQ(document.GetItemsCount(), 2);
	EXPECT_EQ(document.GetItem(1).GetParagraph()->GetText(), "Second paragraph");
}
