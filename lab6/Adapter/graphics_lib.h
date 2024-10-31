#pragma once
#include <iostream>
#include <iomanip>
#include <cstdint>

namespace graphics_lib
{
    using namespace std;
    // ����� ��� ���������
	class ICanvas
	{
	public:
		// ������������� ���� "����"
		virtual void SetColor(uint32_t rgbColor) = 0;

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
		void SetColor(const uint32_t rgbColor) override
		{
			std::cout << "SetColor on #" << std::hex << std::setfill('0') << rgbColor << std::dec << std::endl;
		}

		void MoveTo(const int x, const int y) override
		{
			std::cout << "MoveTo (" << x << ", " << y << ")" << std::endl;
		}

		void LineTo(const int x, const int y) override
		{
			std::cout << "LineTo (" << x << ", " << y << ")" << std::endl;
		}
	};
}