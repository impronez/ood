#pragma once
#include <fstream>
#include <vector>
#include "FileUtils.h"
#include "../Document/CConstDocumentItem.h"

class HtmlUtils
{
public:
    static void CreateHtmlFile(
        const std::string &title,
        const std::vector<CConstDocumentItem> &items,
        const std::string &filePath
    )
    {
        std::ofstream output(filePath);
        if (!output.is_open())
        {
            throw std::runtime_error("Unable to open output file");
        }

        output << "<!DOCTYPE html>\n<html lang=\"en\">\n<head>\n";
        output << "<title>" << HtmlEncode(title) << "</title>\n";
        output << "</head>\n<body>\n";

        for (const auto &item: items)
        {
            auto paragraph = item.GetParagraph();
            auto image = item.GetImage();

            if (paragraph != nullptr)
            {
                output << "<p>" << HtmlEncode(paragraph->GetText()) << "</p>\n";
            }

            if (image != nullptr)
            {
                const auto imageName = FileUtils::GetFileName(image->GetPath());
                const auto imagePath = std::format("images/{}", imageName);

                output << "<img src=\"" << HtmlEncode(imagePath) << "\" "
                        << "width=" << image->GetWidth() << " "
                        << "height=" << image->GetHeight()
                        << " />" << std::endl;
            }
        }

        output << "</body>\n</html>";

        output.close();
    }

private:
    static std::string HtmlEncode(const std::string &text)
    {
        std::string encoded;
        for (const auto ch: text)
        {
            switch (ch)
            {
                case '<': encoded += "&lt;";
                break;
                case '>': encoded += "&gt;";
                break;
                case '"': encoded += "&quot;";
                break;
                case '\'': encoded += "&apos;";
                break;
                case '&': encoded += "&amp;";
                break;
                default: encoded += ch;
                break;
            }
        }
        return encoded;
    }
};