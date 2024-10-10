#pragma once
#include "ICanvas.h"
#include "IDesigner.h"
#include "CPainter.h"

class CClient
{
public:
    explicit CClient(IDesigner& designer)
        : m_designer(designer)
    {}

    void HandleCommand(std::istream& inputData, ICanvas& canvas, CPainter& painter)
    {
        CPictureDraft pictureDraft = m_designer.CreateDraft(inputData);

        painter.DrawPicture(pictureDraft, canvas);
    }

private:
    IDesigner& m_designer;
};