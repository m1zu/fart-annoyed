#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball(const Vec2 & center, const Vec2 & in_vel)
	:
	rect(center, halfWidth, Colors::Gray),
	velocity(in_vel)
{
}

void Ball::Draw(Graphics & gfx)
{
	SpriteCodex::DrawBall(rect.GetCenter(), gfx);
}

void Ball::Update(float dt)
{
	rect.upperLeft += velocity * dt;
}

void Ball::ReboundX(float repositionX)
{
	velocity.x *= (-1);
	rect.upperLeft.x = repositionX;
}

void Ball::ReboundY(float repositionY)
{
	velocity.y *= (-1);
	rect.upperLeft.y = repositionY;
}

Rect Ball::getRect() const
{
	return rect;
}
