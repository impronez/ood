#pragma once

#include <iomanip>
#include <set>

#include "CMenu.h"
#include "Canvas/ICanvas.h"
#include "Slide/ISlide.h"
#include "Factory/IShapeFactory.h"
#include "Group/CShapeGroup.h"

class CommandHandler
{
public:
    CommandHandler(std::unique_ptr<ISlide> slide, std::unique_ptr<ICanvas> canvas,
                   std::unique_ptr<IShapeFactory> factory)
        : m_slide(std::move(slide)), m_canvas(std::move(canvas)), m_factory(std::move(factory))
    {
        m_menu.AddItem("InsertShape", "Usage: InsertShape <type> <left> <top> <width> <height> <outlineRGBAColor> <fillRGBAColor>. Adds a shape.",
            [&](std::istringstream &params) { InsertShape(params); });
        m_menu.AddItem("GroupShapes", "Usage: GroupShapes <index1> <index2> ... Groups selected shapes.",
            [&](std::istringstream &params) { GroupShapes(params); });
        m_menu.AddItem("RemoveShape", "Usage: RemoveShape <index>. Removes a shape by index.",
            [&](std::istringstream &params) { RemoveShape(params); });
        m_menu.AddItem("List", "List all shapes on the slide.",
            [&](std::istringstream &params) { GetShapes(); });
        m_menu.AddItem("GetShapeGroupIndexes", "List all shape groups on the slide.",
            [&](std::istringstream &params) { GetShapeGroupIndexes(); });
        m_menu.AddItem("SetLineStyle",
            "Usage: SetLineStyle <index> <color> <enable|disable>. Sets outline style for a shape.",
            [&](std::istringstream &params) { SetLineStyle(params); });
        m_menu.AddItem("SetStrokeWidth", "Usage: SetStrokeWidth <stroke-width>. Sets stroke width of line",
            [&](std::istringstream &params) { SetStrokeWidth(params); });
        m_menu.AddItem("SetFillStyle", "Usage: SetFillStyle <index> <color> <enable|disable>. Sets fill style for a shape.",
            [&](std::istringstream &params) { SetFillStyle(params); });
        m_menu.AddItem("TransformShape", "Usage: TransformShape <index> <left> <top> <width> <height>. Transforms a shape.",
            [&](std::istringstream &params) { TransformShape(params); });
        m_menu.AddItem("Draw", "Draws the slide on the canvas.", [&](std::istringstream &params) { Draw(); });
        m_menu.AddItem("Help", "Shows command list.", [&](std::istringstream &params) { Help(); });
        m_menu.AddItem("Export", "Usage: Export <outputFilename>. Exports the slide on the canvas.",
            [&](std::istringstream &params) { Export(params); });
        m_menu.AddItem("Exit", "Exits the program.", [&](std::istringstream &params) { Exit(); });
    }

    void Run()
    {
        m_menu.Run();
    }

private:
    void InsertShape(std::istringstream& params) const
    {
        try
        {
            auto shape = m_factory->CreateShape(params);
            m_slide->InsertShape(std::move(shape), m_slide->GetShapesCount());

            std::cout << "Shape added!\n";
        }
        catch (const std::exception &e)
        {
            std::cerr << "Error inserting shape: " << e.what() << std::endl;
        }
    }

    void RemoveShape(std::istringstream& params) const
    {
        size_t index;
        params >> index;
        if (index < m_slide->GetShapesCount())
        {
            m_slide->RemoveShapeAtIndex(index);

            std::cout << "Shape removed!\n";
        }
        else
        {
            std::cerr << "Invalid shape index." << std::endl;
        }
    }

    void GetShapeGroupIndexes() const
    {
        for (size_t i = 0; i < m_slide->GetShapesCount(); ++i)
        {
            const auto shape = m_slide->GetShapeAtIndex(i);

            if (shape->GetType() == CShapeGroup::TYPE)
            {
                std::cout << i << std::endl;
            }
        }
    }

    void GetShapes() const
    {
        for (size_t i = 0; i < m_slide->GetShapesCount(); ++i)
        {
            const auto shape = m_slide->GetShapeAtIndex(i);
            std:: cout << i << ":\n"
                << "  Type: " << shape->GetType() << std::endl;

            auto frame = shape->GetFrame();
            PrintFrameInfo(frame);

            auto lineStyle = shape->GetLineStyle();
            PrintStyleInfo("lineStyle", lineStyle);

            auto fillStyle = shape->GetFillStyle();
            PrintStyleInfo("fillStyle", fillStyle);
        }
    }

    void SetLineStyle(std::istringstream& params) const
    {
        size_t index;

        params >> index;
        if (index < m_slide->GetShapesCount())
        {
            RGBAColor newColor = GetRGBA(params);
            bool isEnabled = GetStyleState(params);

            auto shape = m_slide->GetShapeAtIndex(index);
            shape->SetLineStyle(newColor, isEnabled);

            std::cout << "Line style installed!\n";
        }
        else
        {
            throw std::invalid_argument("Invalid shape index.");
        }
    }

    void SetStrokeWidth(std::istringstream& params) const
    {
        size_t index;
        if (!(params >> index))
        {
            throw std::invalid_argument("Invalid value of stroke width.");
        }

        m_canvas->SetStrokeWidth(index);

        std::cout << "Stroke width installed!\n";
    }

    void SetFillStyle(std::istringstream& params) const
    {
        size_t index;

        params >> index;
        if (index < m_slide->GetShapesCount())
        {
            RGBAColor newColor = GetRGBA(params);
            bool isEnabled = GetStyleState(params);

            auto shape = m_slide->GetShapeAtIndex(index);
            shape->SetFillStyle(newColor, isEnabled);

            std::cout << "Fill style installed!\n";
        }
        else
        {
            throw std::invalid_argument("Invalid shape index.");
        }
    }

    void TransformShape(std::istringstream& params) const
    {
        size_t index;
        params >> index;

        if (index < m_slide->GetShapesCount())
        {
            double left, top, width, height;
            if (!(params >> left >> top >> width >> height))
            {
                throw std::invalid_argument("Invalid transform values.");
            }

            auto shape = m_slide->GetShapeAtIndex(index);
            shape->SetFrame(left, top, width, height);

            std::cout << "Transformed!\n";
        }
        else
        {
            throw std::invalid_argument("Invalid shape index.");
        }
    }

    void GroupShapes(std::istringstream& params) const
    {
        std::set<size_t> indexes;
        size_t index;

        while(params >> index)
        {
            if (index < m_slide->GetShapesCount())
            {
                indexes.insert(index);
            }
            else
            {
                std::cerr << "Invalid shape index." << std::endl;
                return;
            }
        }

        if (indexes.size() > 1)
        {
            m_slide->InsertShapeGroup(indexes);

            std::cout << "Shapes grouped!\n";
        }
    }

    void Draw() const
    {
        if (m_slide->GetShapesCount() > 0)
        {
            m_slide->Draw(*m_canvas.get());

            std::cout << "Drawed!\n";
        }
    }

    void Help() const
    {
        m_menu.ShowInstructions();
    }

    void Export(std::istringstream& params) const
    {
        std::string outputFilename;
        params >> outputFilename;

        std::ofstream output(outputFilename);
        if (!output.is_open())
        {
            throw std::ios::failure("Failed to open output file.");
        }

        m_canvas->Export(output);

        std::cout << "Exported!\n";
    }

    void Exit()
    {
        m_menu.Exit();
    }

    static std::string GetColorStringFromRGBA(std::optional<RGBAColor> color)
    {
        if (!color.has_value())
        {
            return "none";
        }

        std::stringstream ss;
        ss << "0x" << std::setw(8) << std::setfill('0') << std::hex << color.value();
        return ss.str();
    }

    static RGBAColor GetRGBA(std::istringstream& params)
    {
        RGBAColor color;
        if (!(params >> std::hex >> color))
        {
            throw std::invalid_argument("Invalid color.");
        }

        return color;
    }

    static bool GetStyleState(std::istringstream& params)
    {
        std::string state;
        params >> state;

        if (state == "enable")
        {
            return true;
        }
        if (state == "disable")
        {
            return false;
        }

        throw std::invalid_argument("Invalid style state.");
    }

    static void PrintFrameInfo(std::optional<RectD>& frame)
    {
        if (!frame.has_value())
        {
            std::cout << "  Frame: none\n";
        }
        else
        {
            std::cout << "  Frame (left, top, width, height): " << frame.value().left<< " "<< frame.value().top
                << " " << frame.value().width << " " << frame.value().height << std::endl;
        }
    }

    static void PrintStyleInfo(const std::string& styleType, const std::shared_ptr<IStyle>& style)
    {
        if (style != nullptr)
        {
            std::string state = style->IsEnabled() ? "enabled" : "disabled";
            std::string color = GetColorStringFromRGBA(style->GetColor());
            std::cout << "  " << styleType << ": " << color << ", " << state << std::endl;
        } else
        {
            std::cout << "  " << styleType << ": none, none" << std::endl;
        }
    }

    CMenu m_menu;
    std::unique_ptr<ISlide> m_slide;
    std::unique_ptr<ICanvas> m_canvas;
    std::unique_ptr<IShapeFactory> m_factory;
};
