#pragma once
#include <iostream>

namespace graphics_lib
{
    using namespace std;
    // ����� ��� ���������
    class ICanvas
    {
    public:
        // ������ "����" � ����� x, y
        virtual void MoveTo(int x, int y) = 0;
        // ������ ����� � ������� �������, ���������� ���� � ����� x,y
        virtual void LineTo(int x, int y) = 0;
        virtual ~ICanvas() = default;
    };

    // ���������� ������ ��� ���������
    class CCanvas : public ICanvas
    {
    public:
        void MoveTo(int x, int y) override
        {
            cout << "MoveTo (" << x << ", " << y << ")" << endl;
        }
        void LineTo(int x, int y) override
        {
            cout << "LineTo (" << x << ", " << y << ")" << endl;
        }
    };
}