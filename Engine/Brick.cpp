#include "Brick.h"
#include <assert.h>

Brick::Brick(const Vec2 & upperLeft, Color c)
	:
	rect(upperLeft, width, height, c)
{
	assert(!initialized);
	initialized = true;
}

void Brick::Draw(Graphics & gfx)
{
	assert(initialized);
	if (!isDestroyed)
		rect.Draw(gfx, 1);
}

bool Brick::CheckBallCollision(const Ball & ball) const
{
	assert(initialized);
	if (!isDestroyed)
	{
		bool temp;
		return rect.checkCollision(ball.getRect(), temp, temp, temp, temp);
	}
	else return false;
}

void Brick::ExecuteBallCollision(Ball & ball)
{
	assert(initialized);
	assert(!isDestroyed);
	bool top, bottom, left, right;
	const Rect& ballRect = ball.getRect();
	const float vx = ball.GetVelocity().x;
	const float vy = ball.GetVelocity().y;
	if (isDestroyed = rect.checkCollision(ballRect, top, bottom, left, right))
	{
		if (top && vy>0)
			ball.ReboundY(rect.upperLeft.y - 1.0f - ball.halfWidth * 2.0f);
		if (bottom && vy<0)
			ball.ReboundY(rect.upperLeft.y + rect.height);
		if (left && vx>0)
			ball.ReboundX(rect.upperLeft.x - 1.0f - ball.halfWidth * 2.0f);
		if (right && vx<0)
			ball.ReboundX(rect.upperLeft.x + rect.width);
		ball.ResetCooldown();
	}
}

bool Brick::IsDestroyed() const
{
	return isDestroyed;
}

Vec2 Brick::GetCenter() const
{
	return rect.GetCenter();
}
