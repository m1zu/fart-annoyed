#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball(const Vec2 & center, const Vec2 & in_vel)
	:
	rect(center, halfWidth, Colors::Gray),
	inital_rect(rect),
	velocity(in_vel),
	intial_velocity(velocity)
{
}

void Ball::Draw(Graphics & gfx)
{
	SpriteCodex::DrawBall(rect.GetCenter(), gfx);
}

void Ball::Update(float dt)
{
	rect.upperLeft += velocity * speed * dt;
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

void Ball::Redirect(const float repositionY, const Vec2 & direction)
{
	rect.upperLeft.y = repositionY;
	velocity = direction.GetNormalized();
}

void Ball::ResetCooldown()
{
	cooldown = false;
}

void Ball::ActivateCooldown()
{
	cooldown = true;
}

bool Ball::Cooldown() const
{
	return cooldown;
}

Vec2 Ball::GetVelocity() const
{
	return velocity;
}

void Ball::Reset()
{
	velocity = intial_velocity;
	rect = inital_rect;
}
