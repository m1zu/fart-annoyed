#include "Lifebar.h"
#include "SpriteCodex.h"
#include "Ball.h"

Lifebar::Lifebar(int in_nLifes, const Vec2& in_lifesDrawLocation, const Vec2& wallUpperLeft)
	:
	nLifes(in_nLifes),
	lifesDrawLocation(in_lifesDrawLocation),
	deathField(Vec2(wallUpperLeft.x, wallUpperLeft.y + (float(Graphics::ScreenHeight) - 2.0f*wallUpperLeft.y)*(1.0f-deathFielHeightRatio))
		, Vec2(float(Graphics::ScreenWidth) - wallUpperLeft.x, float(Graphics::ScreenHeight) - wallUpperLeft.y)
		, Colors::Red)
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
	for (int i = 0; i < nSpares; ++i)
		SpriteCodex::DrawBall(Vec2(lifesDrawLocation.x, lifesDrawLocation.y - Ball::halfWidth * 3 * i), gfx);
	deathField.Draw(gfx);
}

bool Lifebar::updateBallDeath(const Ball & ball)
{
	if (deathField.checkCollision(ball.getRect()))
	{
		if(nLifes >= 0)
			nLifes--;
		return true;
	}
	else return false;
}
