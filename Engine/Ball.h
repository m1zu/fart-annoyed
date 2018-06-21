#pragma once

#include "Rect.h"

class Ball {
public:
	Ball(const Vec2 & center, const Vec2& in_vel);

	void Draw(Graphics& gfx);

	void Update(float dt);
	void ReboundX(float repositionX);
	void ReboundY(float repositionY);
	Rect getRect() const;
	void Redirect(const float repositionY, const Vec2& direction);
	void ResetCooldown();
	void ActivateCooldown();
	bool Cooldown() const;
	Vec2 GetVelocity() const;
	void Reset();

public:
	static constexpr float halfWidth = 7.0f;

private:
	Rect rect;
	Rect inital_rect;
	const float speed = 350.0f;
	Vec2 velocity;
	Vec2 intial_velocity;
	bool cooldown = false;
};