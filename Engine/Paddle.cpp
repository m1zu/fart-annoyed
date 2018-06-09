#include "Paddle.h"
#include <math.h>

Paddle::Paddle(const Vec2 & upperLeft)
	:
	rect(upperLeft, width, height, Colors::Blue)
{
}

void Paddle::Draw(Graphics & gfx)
{
	rect.Draw(gfx);
}

void Paddle::Update(bool left, bool right, float dt)
{
	if (left)
		rect.upperLeft.x -= speed * dt;
	if (right)
		rect.upperLeft.x += speed * dt;
}

Rect Paddle::GetRect()
{
	return rect;
}

void Paddle::ClampX(const float x)
{
	rect.upperLeft.x = x;
}

bool Paddle::DoCollision(Ball & ball)
{
	bool top, bottom, left, right;
	const Rect& ballRect = ball.getRect();
	bool collision;
	if (collision = rect.checkCollision(ballRect, top, bottom, left, right))
	{
		if (top)
		{
			const float paddleRange = (rect.width + ballRect.width) / 2.0f;
			const float relativeBallPosition = ballRect.GetCenter().x - rect.GetCenter().x;
			const float PI = 3.1415;
			const float angle = relativeBallPosition / paddleRange * PI / 2.2f;
			Vec2 newDirection(sin(angle), -cos(angle));
			ball.Redirect(rect.upperLeft.y - 1.0f - ball.halfWidth * 2.0f, newDirection);
		}
		if (bottom)
			ball.ReboundY(rect.upperLeft.y + rect.height);
		if (left)
			ball.ReboundX(rect.upperLeft.x - 1.0f - ball.halfWidth * 2.0f);
		if (right)
			ball.ReboundX(rect.upperLeft.x + rect.width);
	}
	return collision;
}
