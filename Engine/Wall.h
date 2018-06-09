#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Ball.h"
#include "Paddle.h"

class Wall{
public:
	Wall(const Vec2& in_innerTopLeft, const int in_thickness);

	void Draw(Graphics& gfx) const;
	bool ClampBall(Ball& ball) const;
	void ClampPaddle(Paddle& paddle) const;

private:
	Vec2 innerTopLeft;
	Rect innerRect;
	const int thickness;
};