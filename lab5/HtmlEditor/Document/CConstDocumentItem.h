#pragma once

#include <memory>

#include "Image/IImage.h"
#include "Paragraph/IParagraph.h"

/*
Неизменяемый элемент документа
*/
class CConstDocumentItem
{
public:
    explicit CConstDocumentItem(std::shared_ptr<const IImage> image)
        : m_image(std::move(image))
    {}

    explicit CConstDocumentItem(std::shared_ptr<const IParagraph> paragraph)
        : m_paragraph(std::move(paragraph))
    {}

    std::shared_ptr<const IImage> GetImage() const
    {
        return m_image;
    }

    std::shared_ptr<const IParagraph> GetParagraph() const
    {
        return m_paragraph;
    }
    virtual ~CConstDocumentItem() = default;
private:
    std::shared_ptr<const IImage> m_image = nullptr;
    std::shared_ptr<const IParagraph> m_paragraph = nullptr;
};