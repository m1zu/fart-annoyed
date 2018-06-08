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

public:
	static constexpr float halfWidth = 7.0f;

private:
	Rect rect;
	const float speed = 300.0f;
	Vec2 velocity;
};