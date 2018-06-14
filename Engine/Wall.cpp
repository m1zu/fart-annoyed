#include "Wall.h"
#include "Colors.h"
#include <assert.h>

Wall::Wall(const Vec2& in_innerTopLeft, const int in_thickness) 
	:
	innerTopLeft(in_innerTopLeft),
	innerRect(in_innerTopLeft, float(Graphics::ScreenWidth) - in_innerTopLeft.x, float(Graphics::ScreenHeight) - in_innerTopLeft.y, Colors::Yellow),
	thickness(in_thickness)
{
}

void Wall::Draw(Graphics & gfx) const
{
	assert(thickness >= 0);
	if (thickness > 0)
		gfx.DrawFrameRect(innerTopLeft, thickness, Colors::Gray);
}

bool Wall::ClampBall(Ball & ball) const
{
	const Rect& ballRect = ball.getRect();
	bool left, right, top, bottom;
	
	if (!innerRect.isCoating(ballRect, top, bottom, left, right))
	{
		if (left)
			ball.ReboundX(innerTopLeft.x);
		else if (right)
			ball.ReboundX(float(Graphics::ScreenWidth) - innerTopLeft.x - ballRect.width);
		if (top)
			ball.ReboundY(innerTopLeft.y);
		else if (bottom)
			ball.ReboundY(float(Graphics::ScreenHeight) - innerTopLeft.y - ballRect.height);

		ball.ResetCooldown();
		return true;
	}
	else return false;
}

void Wall::ClampPaddle(Paddle & paddle) const
{
	bool left, right, temp;

	if (!innerRect.isCoating(paddle.GetRect(), temp, temp, left, right))
	{
		if (left)
			paddle.ClampX(innerTopLeft.x);
		if (right)
			paddle.ClampX(float(Graphics::ScreenWidth) - innerTopLeft.x - Paddle::width);
	}
}
