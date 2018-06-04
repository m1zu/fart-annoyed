#include "Rect.h"
#include <assert.h>

Rect::Rect(const Vec2 & upperLeft, const float width, const float height, Color c)
	:
	width(width),
	height(height),
	upperLeft(upperLeft),
	c(c)
{
}

Rect::Rect(const Vec2 & upperLeft, const Vec2 & lowerRight, Color c)
	:
	Rect(upperLeft, lowerRight.x - upperLeft.x + 1, lowerRight.y - upperLeft.y + 1, c)
{
	assert(lowerRight.x > upperLeft.x && lowerRight.y > upperLeft.y);
}

Rect::Rect(const Vec2 & middle, const float squareHalfWidth, Color c)
	:
	Rect(Vec2(middle.x - squareHalfWidth, middle.y - squareHalfWidth), squareHalfWidth * 2, squareHalfWidth * 2, c)
{
}

void Rect::Draw(Graphics & gfx, int padding)
{
	assert(padding < int(width / 2.0f) - 1);
	Vec2 paddingVec = upperLeft;
	paddingVec += Vec2(float(padding), float(padding));
	gfx.DrawRectDim(paddingVec, int(width - 2*padding), int(height - 2*padding), c);
}
