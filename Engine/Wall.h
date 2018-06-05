#pragma once

#include "Rect.h"

class Wall{
	Wall(const Rect& in_innerRect, const int in_thickness);

	void Draw(Graphics& gfx) const;

private:
	Rect innerRect;
	const int thickness;
};