#pragma once

#include "Vec2.h"
#include "Graphics.h"

class Rect {
public:
	Rect() = default;
	Rect(const Vec2& upperLeft, const float width, const float height, Color c);
	Rect(const Vec2& upperLeft, const Vec2& lowerRight, Color c);
	Rect(const Vec2& middle, const float squareHalfWidth, Color c);

	void Draw(Graphics& gfx, int padding = 0);
	Vec2 GetCenter() const;
	bool checkCollision(const Rect& in_rect, bool& top, bool& bottom, bool& left, bool& right) const;
	bool isCoating(const Rect & innerRect, bool & collision_top, bool & collision_bottom, bool & collision_left, bool & collision_right) const;

public:
	const float width;
	const float height;
	Vec2 upperLeft;
	Color c;
};