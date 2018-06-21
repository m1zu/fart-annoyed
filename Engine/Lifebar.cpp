#include "Lifebar.h"
#include "SpriteCodex.h"
#include "Ball.h"

Lifebar::Lifebar(int in_nLifes, const Vec2& in_drawLocation)
	:
	nLifes(in_nLifes),
	drawLocation(in_drawLocation)
{
}

Lifebar & Lifebar::operator--()
{
	nLifes--;
	return *this;
}

int Lifebar::GetLifes() const
{
	return nLifes;
}

void Lifebar::Draw(Graphics & gfx)
{
	int nSpares = nLifes - 1;
	for (int i=0; i<nSpares; ++i)
	SpriteCodex::DrawBall(Vec2(drawLocation.x, drawLocation.y - Ball::halfWidth*3*i), gfx);
}
