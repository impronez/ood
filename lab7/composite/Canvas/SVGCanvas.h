#pragma once
#include <format>
#include <sstream>
#include <vector>

#include "ICanvas.h"

class SVGCanvas final : public ICanvas
{
public:
    SVGCanvas(double width, double height)
        : m_startPoint({0, 0}),
        m_width(width),
        m_height(height)
    {
        Start();
    }

    void SetStrokeWidth(unsigned strokeWidth) override
    {
        m_strokeWidth = strokeWidth;
    }

    void SetLineColor(RGBAColor color) override
    {
        m_outlineColor = color;
    }

    void BeginFill(RGBAColor color) override
    {
        if (IsColorHasValue(color))
        {
            m_fillColor = color;
            m_fillPos = m_strm.tellp();
        }
    }

    void EndFill() override
    {
        if (IsColorHasValue(m_fillColor))
        {
            FillVertexesArea();
            m_fillAreaVertexes = {};
            m_fillColor = 0;
        }
    }

    void MoveTo(double x, double y) override
    {
        m_startPoint = { x, y };
    }

    void LineTo(double x, double y) override
    {
        m_strm << std::format(R"(    <line x1="{}" y1="{}" x2="{}" y2="{}" )", m_startPoint.x, m_startPoint.y, x, y);
        AddOutlineColor();
        m_strm << "/>" << std::endl;

        if (IsColorHasValue(m_fillColor))
        {
            m_fillAreaVertexes.push_back(m_startPoint);
            m_fillAreaVertexes.push_back({ x, y });
        }
    }

    void DrawEllipse(double left, double top, double width, double height) override
    {
        double rx = width / 2;
        double ry = height / 2;
        double cx = left + rx;
        double cy = top + ry;

        m_strm << std::format(R"(    <ellipse cx="{}" cy="{}" rx="{}" ry="{}" )", cx, cy, rx, ry);

        FillFigure();
        AddOutlineColor();

        m_strm << "/>" << std::endl;
    }

    void Save()
    {
        m_strm << "</svg>" << std::endl;

        m_isSaved = true;
    }

    void Export(std::ostream& output) override
    {
        if (!m_isSaved)
        {
            Save();
        }

        output << m_strm.str();
    }

private:
    void Start()
    {
        m_strm.str("");
        m_strm << std::format(R"(<svg xmlns="http://www.w3.org/2000/svg" version="1.1" width="{}" height="{}">)",
            m_width, m_height) << std::endl;
    }

    void AddOutlineColor()
    {
        if (IsColorHasValue(m_outlineColor))
        {
            m_strm << std::format(R"( stroke="{}" stroke-width="{}")", GetColorString(m_outlineColor), m_strokeWidth);
        }
    }

    void FillFigure()
    {
        if (IsColorHasValue(m_fillColor))
        {
            m_strm << std::format(R"(fill="{}")", GetColorString(m_fillColor));
        }
        else
        {
            m_strm << "fill=\"transparent\"";
        }
    }

    void FillVertexesArea()
    {
        if (m_fillAreaVertexes.empty() || !IsColorHasValue(m_fillColor))
        {
            return;
        }

        std::string lines = m_strm.str().substr(static_cast<unsigned>(m_fillPos));

        m_strm.seekp(m_fillPos, std::ios::beg);

        m_strm << std::format(R"(    <path d="M {} {})", m_fillAreaVertexes[0].x, m_fillAreaVertexes[0].y);

        for (size_t i = 1; i < m_fillAreaVertexes.size(); ++i)
        {
            m_strm << std::format(R"( L {} {})", m_fillAreaVertexes[i].x, m_fillAreaVertexes[i].y);
        }

        m_strm << " Z\"";
        m_strm << format(R"( fill="{}")", GetColorString(m_fillColor));
        m_strm << "/>" << std::endl;
        m_strm << lines;
    }

    static std::string GetColorString(const RGBAColor color)
    {
        double alpha = (color >> 24 & 255) / 255.0;
        auto red = color >> 16 & 255;
        auto green = color >> 8 & 255;
        auto blue = color >> 0 & 255;

        return std::format(R"(rgb{}{}, {}, {}, {}{})", '(', red, green, blue, alpha, ')');
    }

    static bool IsColorHasValue(const RGBAColor color)
    {
        return color > 0;
    }

    double m_width;
    double m_height;

    unsigned m_strokeWidth = 1;

    PointD m_startPoint;
    std::stringstream m_strm {};
    std::streampos m_fillPos;

    RGBAColor m_outlineColor {};
    RGBAColor m_fillColor {};

    std::vector<PointD> m_fillAreaVertexes;

    bool m_isSaved = false;
};