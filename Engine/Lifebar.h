#pragma once

#include "Graphics.h"

class Lifebar {
public:
	Lifebar(int nLifes, const Vec2& drawLocation);

	Lifebar& operator--();

	int GetLifes() const;
	void Draw(Graphics& gfx);

private:
	int nLifes;
	Vec2 drawLocation;
};