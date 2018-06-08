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

void Brick::Update(Ball & ball)
{
	assert(initialized);
	if (!isDestroyed)
	{
		bool top, bottom, left, right;
		const Rect& ballRect = ball.getRect();
		isDestroyed = rect.checkCollision(ballRect, top, bottom, left, right);
		if (top)
			ball.ReboundY(rect.upperLeft.y - 1.0f - ball.halfWidth * 2.0f);
		if (bottom)
			ball.ReboundY(rect.upperLeft.y + rect.height);
		if (left)
			ball.ReboundX(rect.upperLeft.x - 1.0f - ball.halfWidth * 2.0f);
		if (right)
			ball.ReboundX(rect.upperLeft.x + rect.width);
	}
}

bool Brick::IsDestroyed() const
{
	return isDestroyed;
}
