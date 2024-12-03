#include <gtest/gtest.h>
#include "../Document/Command/InsertImageCommand.h"

const std::string IMAGE_PATH = "output.jpg";

bool AssertDirectoryIsNotEmpty(const std::string &path)
{
	std::filesystem::path dirPath(path);
	if (!exists(dirPath) || !is_directory(dirPath))
	{
		return false;
	}

	return std::any_of(std::filesystem::directory_iterator(dirPath), std::filesystem::directory_iterator{},
	                   [](const std::filesystem::directory_entry &) {
		                   return true;
	                   });
}

std::string GetFirstFileOnDirectory(const std::string &path)
{
	std::filesystem::path dirPath(path);
	if (!exists(dirPath) || !is_directory(dirPath))
	{
		return "";
	}

	for (const auto &entry: std::filesystem::directory_iterator(dirPath))
	{
		if (is_regular_file(entry.status()))
		{
			return entry.path().filename().string();
		}
	}

	return "";
}

bool AssertFilesAreEqual(const std::string &path1, const std::string &path2)
{
	std::ifstream file1(path1, std::ios::binary);
	std::ifstream file2(path2, std::ios::binary);

	if (!file1.is_open() || !file2.is_open())
	{
		return false;
	}

	file1.seekg(0, std::ios::end);
	file2.seekg(0, std::ios::end);

	if (file1.tellg() != file2.tellg())
	{
		return false;
	}

	file1.seekg(0);
	file2.seekg(0);

	return std::equal(std::istreambuf_iterator(file1),
	                  std::istreambuf_iterator<char>(),
	                  std::istreambuf_iterator(file2));
}

TEST(InsertImageCommandTests, ExecuteInsertsImageAtEndSuccess)
{
	std::vector<CDocumentItem> items;
	std::string imagePath = IMAGE_PATH;
	int width = 100;
	int height = 200;

	InsertImageCommand command(imagePath, width, height, std::nullopt, items);

	EXPECT_NO_THROW(command.DoExecute());

	ASSERT_EQ(items.size(), 1);
	EXPECT_TRUE(AssertDirectoryIsNotEmpty("images"));
	EXPECT_TRUE(AssertFilesAreEqual(IMAGE_PATH, "images/" + GetFirstFileOnDirectory("images")));
}

TEST(InsertImageCommandTests, ExecuteInsertsImageAtPositionSuccess)
{
	std::vector<CDocumentItem> items;
	std::string imagePath = IMAGE_PATH;
	int width = 100;
	int height = 200;

	InsertImageCommand command(imagePath, width, height, 0, items);

	EXPECT_NO_THROW(command.DoExecute());

	ASSERT_EQ(items.size(), 1);
	EXPECT_TRUE(AssertDirectoryIsNotEmpty("images"));
	EXPECT_TRUE(AssertFilesAreEqual(IMAGE_PATH, "images/" + GetFirstFileOnDirectory("images")));
}

TEST(InsertImageCommandTests, ExecuteThrowsOnInvalidPositionError)
{
	std::vector<CDocumentItem> items;
	std::string imagePath = IMAGE_PATH;
	int width = 100;
	int height = 200;

	InsertImageCommand command(imagePath, width, height, 2, items);

	EXPECT_THROW(command.DoExecute(), std::invalid_argument);
}

TEST(InsertImageCommandTests, UnexecuteRemovesLastInsertedSuccess)
{
	std::vector<CDocumentItem> items;
	std::string imagePath = IMAGE_PATH;
	int width = 100;
	int height = 200;

	InsertImageCommand command(imagePath, width, height, std::nullopt, items);

	command.DoExecute();
	ASSERT_EQ(items.size(), 1);
	EXPECT_TRUE(AssertDirectoryIsNotEmpty("images"));
	EXPECT_TRUE(AssertFilesAreEqual(IMAGE_PATH, "images/" + GetFirstFileOnDirectory("images")));

	command.DoUnexecute();
	ASSERT_EQ(items.size(), 0);
	EXPECT_TRUE(AssertDirectoryIsNotEmpty("images"));
	EXPECT_TRUE(AssertFilesAreEqual(IMAGE_PATH, "images/" + GetFirstFileOnDirectory("images")));
}

TEST(InsertImageCommandTests, UnexecuteRemovesInsertedAtPosition)
{
	std::vector<CDocumentItem> items;
	std::string imagePath = IMAGE_PATH;
	int width = 100;
	int height = 200;

	InsertImageCommand command(imagePath, width, height, 0, items);

	command.DoExecute();
	ASSERT_EQ(items.size(), 1);
	EXPECT_TRUE(AssertDirectoryIsNotEmpty("images"));
	EXPECT_TRUE(AssertFilesAreEqual(IMAGE_PATH, "images/" + GetFirstFileOnDirectory("images")));

	command.DoUnexecute();
	ASSERT_EQ(items.size(), 0);
	EXPECT_TRUE(AssertDirectoryIsNotEmpty("images"));
	EXPECT_TRUE(AssertFilesAreEqual(IMAGE_PATH, "images/" + GetFirstFileOnDirectory("images")));
}
