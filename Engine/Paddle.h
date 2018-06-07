#pragma once

#include "Vec2.h"
#include "Rect.h"
#include "Graphics.h"
#include "Ball.h"

class Paddle {
public:
	Paddle(const Vec2& in_position);

	void Draw(Graphics& gfx);
	void Update(bool left, bool right, float dt);
	Rect GetRect();
	void ClampX(const float x);
	void DoCollision(Ball& ball);

public:
	static constexpr float width = 70.0f;
	static constexpr float height = 10.0f;

private:
	const float speed = 300.0f;
	Rect rect;
		
};