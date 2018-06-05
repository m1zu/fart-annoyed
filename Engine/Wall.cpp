#include "Wall.h"
#include "Colors.h"
#include <assert.h>

Wall::Wall(const Vec2& in_innerTopLeft, const int in_thickness) 
	:
	innerTopLeft(in_innerTopLeft),
	thickness(in_thickness)
{
}

void Wall::Draw(Graphics & gfx) const
{
	assert(thickness >= 0);
	if (thickness > 0)
		gfx.DrawFrameRect(innerTopLeft, thickness, Colors::Gray);
}
