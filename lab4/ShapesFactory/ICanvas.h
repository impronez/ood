#pragma once
#include "Color.h"
#include "Point.h"

class ICanvas
{
public:
	virtual void SetColor(const CColor color) = 0;

	virtual void DrawLine(double fromX, double fromY, double toX, double toY) = 0;

	virtual void DrawEllipse(double cx, double cy, double rx, double ry) = 0;

	// В каком случае следует сделать деструктор виртуальным, какие альтернативы у виртуального деструктора
	// Виртуальный деструктор в том случае, если класс является интерфейсом/базовым для других
	// Это позволяет правильно освобождать ресурсы производных классов при удалении объектов через указатели на базовый класс
	// Т.е если не указать деструктор виртуальным, то при удалении указателя на подкласс, вызовется деструктор только интерфейса (память выделенная подклассом не высвободится)
	virtual ~ICanvas() {};
};