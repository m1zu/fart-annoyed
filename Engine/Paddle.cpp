#include "Paddle.h"

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

void Paddle::DoCollision(Ball & ball)
{
	bool top, bottom, left, right;
	rect.checkCollision(ball.getRect(), top, bottom, left, right);
	if (top)
		ball.ReboundY(rect.upperLeft.y - 1.0f - ball.halfWidth * 2.0f);
	if (bottom)
		ball.ReboundY(rect.upperLeft.y + rect.height);
	if (left)
		ball.ReboundX(rect.upperLeft.x - 1.0f - ball.halfWidth * 2.0f);
	if (right)
		ball.ReboundX(rect.upperLeft.x + rect.width);
}
