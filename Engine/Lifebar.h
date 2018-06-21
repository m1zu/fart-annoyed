#pragma once

#include "Graphics.h"
#include "Ball.h"

class Lifebar {
public:
	Lifebar(int nLifes, const Vec2& lifesDrawLocation, const Vec2& wallUpperLeft);

	Lifebar& operator--();

	int GetLifes() const;
	void Draw(Graphics& gfx);
	bool updateBallDeath(const Ball& ball);


private:
	int nLifes;
	Vec2 lifesDrawLocation;

	static constexpr float deathFielHeightRatio = 0.05f;
	Rect deathField;
};