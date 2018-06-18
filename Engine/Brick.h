#pragma once

#include "Rect.h"
#include "Graphics.h"
#include "Ball.h"

class Brick {
public:
	Brick() = default;
	Brick(const Vec2& upperLeft, Color c);

	void Draw(Graphics& gfx);
	bool CheckBallCollision(const Ball& ball) const;
	void ExecuteBallCollision(Ball& ball);
	bool IsDestroyed() const;
	Vec2 GetCenter() const;

public:
	static constexpr float width = 40.0f;
	static constexpr float height = 20.0f;

private:
	bool isDestroyed = false;
	bool initialized = false;
	Rect rect;
};