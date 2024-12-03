#pragma once

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <filesystem>
#include <format>

class FileUtils
{
public:
	static constexpr size_t FILENAME_LENGTH = 15;

	static std::string GetFileName(const std::string &path)
	{
		std::cout << path << std::endl;
		size_t slashPosition = path.find_last_of('/');

		if (slashPosition != std::string::npos && slashPosition != 0)
		{
			return path.substr(slashPosition + 1);
		}

		return "";
	}

	static std::string GetFileExtension(const std::string &path)
	{
		size_t dotPosition = path.find_last_of('.');

		if (dotPosition != std::string::npos && dotPosition != 0)
		{
			return path.substr(dotPosition + 1);
		}

		return "";
	}

	static std::string GenerateRandomFileName(const std::string& extension)
	{
		const std::string characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
		std::string randomString;

		srand(static_cast<unsigned int>(time(0)));

		for (size_t i = 0; i < FILENAME_LENGTH; ++i)
		{
			randomString += characters[rand() % characters.size()];
		}
		return randomString + '.' + extension;
	}

	static bool CopyFile(const std::string &inputFilePath, const std::string &outputFilePath)
	{
		const std::filesystem::path from(inputFilePath);
		const std::filesystem::path to(outputFilePath);

		std::filesystem::path outputDir = to.parent_path();
		if (!outputDir.empty() && !exists(outputDir))
		{
			create_directories(outputDir);
		}

		copy(from, to, std::filesystem::copy_options::overwrite_existing);

		return true;
	}

	static void DeleteFileIfExists(const std::string &filePath)
	{
		if (FileExists(filePath))
		{
			std::filesystem::remove(filePath);
		}
	}

	static bool FileExists(const std::string &filePath)
	{
		return std::filesystem::exists(filePath);
	}
};
