#pragma once
#include <utility>
#include "IImage.h"
#include "../../Utils/FileUtils.h"

class CImage final : public IImage
{
public:
    CImage(
        std::string path,
        const unsigned width,
        const unsigned height
    ): m_path(std::move(path)),
       m_width(width),
       m_height(height)
    {}

    [[nodiscard]] std::string GetPath() const override
    {
        return m_path;
    }

    [[nodiscard]] unsigned GetWidth() const override
    {
        return m_width;
    }

    [[nodiscard]] unsigned GetHeight() const override
    {
        return m_height;
    }

    void Resize(const unsigned width, const unsigned height) override
    {
        m_width = width;
        m_height = height;
    }

    void Remove() override
    {
        FileUtils::DeleteFileIfExists(m_path);

        m_path = "";

        m_width = 0;
        m_height = 0;
    }

private:
    std::string m_path;
    unsigned m_width;
    unsigned m_height;
};
