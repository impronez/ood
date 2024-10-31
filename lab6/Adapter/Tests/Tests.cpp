#define CATCH_CONFIG_MAIN
#include "../../../../catch/catch.hpp"

#include <sstream>
#include <vector>

#include "../graphics_lib.h"
#include "../modern_graphics_lib.h"
#include "../ModernGraphicsAdapter.h"
#include "../ModernGraphicsClassAdapter.h"

namespace mgl = modern_graphics_lib;
namespace gl = graphics_lib;

mgl::CRGBAColor ConvertToColor(const uint32_t colorValue)
{
	constexpr float colorScale = 1.0f / 255.0f;

	// blue - (0-7), green(7-15), red (16-23), alpha (23-31)
	const auto red = static_cast<float>((colorValue >> 16) & 0xFF) * colorScale;
	const auto green = static_cast<float>((colorValue >> 8) & 0xFF) * colorScale;
	const auto blue = static_cast<float>(colorValue & 0xFF) * colorScale;
	const auto alpha = static_cast<float>((colorValue >> 24) & 0xFF) * colorScale;	

	return { red, green, blue, alpha };
}

std::string DrawWithoutAdapter(const std::vector<Point>& points, const uint32_t color)
{
	std::stringstream strm;
	mgl::CModernGraphicsRenderer renderer(strm);
	const auto rgbaColor = ConvertToColor(color);

	const auto first = points.begin();
	renderer.BeginDraw();

	for (auto it = first; it != points.end(); ++it)
	{
		if (it + 1 != points.end())
		{
			renderer.DrawLine(*it, *(it + 1), rgbaColor);
		}
		else
		{
			renderer.DrawLine(*it, *first, rgbaColor);
		}
	}

	renderer.EndDraw();

	return strm.str();
}

void DrawWithAdapter(mgl::CModernGraphicsRenderer& renderer, graphics_lib::ICanvas& adapter,
	const std::vector<Point>& points, const uint32_t color)
{
	adapter.SetColor(color);
	renderer.BeginDraw();

	const auto first = points.begin();
	adapter.MoveTo(first->x, first->y);

	for (auto it = first + 1; it != points.end(); ++it)
	{
		adapter.LineTo(it->x, it->y);
	}

	adapter.LineTo(first->x, first->y);
	renderer.EndDraw();
}

std::string DrawWithObjectAdapter(const std::vector<Point>& points, const uint32_t color)
{
	std::stringstream strm;
	mgl::CModernGraphicsRenderer renderer(strm);
	ModernGraphicsAdapter adapter(renderer);

	DrawWithAdapter(renderer, adapter, points, color);

	return strm.str();
}

std::string DrawShapeWithClassAdapter(const std::vector<Point>& points, const uint32_t color)
{
	std::stringstream strm;
	ModernGraphicsClassAdapter adapter(strm);

	DrawWithAdapter(adapter, adapter, points, color);

	return strm.str();
}

TEST_CASE("check object adapter interface implementation")
{
	std::stringstream strm;
	mgl::CModernGraphicsRenderer renderer(strm);
	ModernGraphicsAdapter adapter(renderer);

	static_cast<graphics_lib::ICanvas*>(&adapter);
}

TEST_CASE("draw triangle with object adapter")
{
	auto triangle =
	{
		Point(10, 15),
		Point(100, 200),
		Point(150, 250),
	};

	constexpr uint32_t color = 0xFFFFFFFF;

	const auto originalShape = DrawWithoutAdapter(triangle, color);
	const auto withAdapterShape = DrawWithObjectAdapter(triangle, color);

	REQUIRE(originalShape == withAdapterShape);
}

TEST_CASE("check class adapter interface implementation")
{
	std::stringstream strm;
	ModernGraphicsClassAdapter adapter(strm);

	static_cast<graphics_lib::ICanvas*>(&adapter);
	static_cast<mgl::CModernGraphicsRenderer*>(&adapter);
}

TEST_CASE("draw triangle with class adapter")
{
	auto triangle =
	{
		Point(10, 15),
		Point(100, 200),
		Point(150, 250),
	};

	constexpr uint32_t color = 0xFFAAAAFF;

	const auto originalShape = DrawWithoutAdapter(triangle, color);
	const auto withAdapterShape = DrawShapeWithClassAdapter(triangle, color);

	REQUIRE(originalShape == withAdapterShape);
}