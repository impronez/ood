#include <iostream>
#include <string>
#include <format>

#include "graphics_lib.h"
#include "modern_graphics_lib.h"
#include "shape_drawing_lib.h"

#include "ModernGraphicsAdapter.h"

using namespace std;

namespace app
{
	void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
	{
		using namespace shape_drawing_lib;

		const CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
		const CRectangle rectangle({ 30, 40 }, 18, 24);

		painter.Draw(triangle);
		painter.Draw(rectangle);
	}

	void PaintPictureOnCanvas()
	{
		graphics_lib::CCanvas simpleCanvas;
		shape_drawing_lib::CCanvasPainter painter(simpleCanvas);

		PaintPicture(painter);
	}

	void PaintPictureOnModernGraphicsRenderer()
	{
		modern_graphics_lib::CModernGraphicsRenderer renderer(cout);
		ModernGraphicsAdapter adaptedModernRenderer(renderer);
		shape_drawing_lib::CCanvasPainter painter(adaptedModernRenderer);

		renderer.BeginDraw();

		PaintPicture(painter);

		renderer.EndDraw();
	}
}


int main()
{
	cout << "Should we use new API (y)?";

	string userInput;

	if (getline(cin, userInput) && (userInput == "y" || userInput == "Y"))
	{
		app::PaintPictureOnModernGraphicsRenderer();
	}
	else
	{
		app::PaintPictureOnCanvas();
	}

	return 0;
}