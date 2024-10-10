#pragma once
#include "IDesigner.h"
#include "IShapeFactory.h"
#include "CPictureDraft.h"

class CDesigner : public IDesigner
{
public:
    explicit CDesigner(IShapeFactory& factory)
        : m_factory(factory)
    {}

    CPictureDraft CreateDraft(std::istream& inputData) override
    {
        CPictureDraft draft;

        std::string line;

        while (getline(inputData, line))
        {
            try
            {
                draft.AddShape(std::move(m_factory.CreateShape(line)));
                std::cout << "Shape added!\n";
            }
            catch (const std::exception& err)
            {
                std::cout << err.what() << std::endl;
            }
        }

        return draft;
    }

private:
    IShapeFactory& m_factory;
};