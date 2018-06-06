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
