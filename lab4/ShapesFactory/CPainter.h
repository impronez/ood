#pragma once
#include "CPictureDraft.h"
#include "ICanvas.h"

class CPainter
{
public:
    void DrawPicture(const CPictureDraft& draft, ICanvas& canvas)
    {
        for (const auto& shape : draft)
        {
            shape->Draw(canvas);
        }
    }
};