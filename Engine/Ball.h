#pragma once

#include "Rect.h"

class Ball {
public:
	Ball(const Rect& in_rect, const Vec2& in_vel);

private:
	Rect rect;
	Vec2 velocity;
};