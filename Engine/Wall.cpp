#include "Wall.h"
#include "Colors.h"
#include <assert.h>

Wall::Wall(const Vec2& in_innerTopLeft, const int in_thickness) 
	:
	innerTopLeft(in_innerTopLeft),
	thickness(in_thickness)
{
}

void Wall::Draw(Graphics & gfx) const
{
	assert(thickness >= 0);
	if (thickness > 0)
		gfx.DrawFrameRect(innerTopLeft, thickness, Colors::Gray);
}

void Wall::DoCollsion(Ball & ball)
{
	const Rect& ballRect = ball.getRect();
	const float ballLeft = ballRect.upperLeft.x;
	const float ballRight = ballRect.upperLeft.x + ballRect.width - 1.0f;
	const float ballTop = ballRect.upperLeft.y;
	const float ballBottom = ballRect.upperLeft.y + ballRect.height - 1.0f;

	if (ballLeft < innerTopLeft.x)
		ball.ReboundX(innerTopLeft.x);
	else if (ballRight > float(Graphics::ScreenWidth) - innerTopLeft.x)
		ball.ReboundX(float(Graphics::ScreenWidth) - innerTopLeft.x - ballRect.width);
	if (ballTop < innerTopLeft.y)
		ball.ReboundY(innerTopLeft.y);
	else if (ballBottom > float(Graphics::ScreenHeight) - innerTopLeft.y)
		ball.ReboundY(float(Graphics::ScreenHeight) - innerTopLeft.y - ballRect.height);
}
