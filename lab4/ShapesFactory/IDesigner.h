#pragma once
#include "CPictureDraft.h"

class IDesigner
{
public:
    virtual CPictureDraft CreateDraft(std::istream& inputData) = 0;

    virtual ~IDesigner() = default;
};