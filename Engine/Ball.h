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

public:
	static constexpr float halfWidth = 7.0f;

private:
	Rect rect;
	Vec2 velocity;
};