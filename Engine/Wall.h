#pragma once

#include "Vec2.h"
#include "Graphics.h"

class Wall{
public:
	Wall(const Vec2& in_innerTopLeft, const int in_thickness);

	void Draw(Graphics& gfx) const;

private:
	Vec2 innerTopLeft;
	const int thickness;
};