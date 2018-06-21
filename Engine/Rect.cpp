#include "Rect.h"
#include <assert.h>

Rect::Rect(const Vec2 & upperLeft, const float width, const float height, Color c)
	:
	width(width),
	height(height),
	upperLeft(upperLeft),
	c(c)
{
}

Rect::Rect(const Vec2 & upperLeft, const Vec2 & lowerRight, Color c)
	:
	Rect(upperLeft, lowerRight.x - upperLeft.x + 1, lowerRight.y - upperLeft.y + 1, c)
{
	assert(lowerRight.x > upperLeft.x && lowerRight.y > upperLeft.y);
}

Rect::Rect(const Vec2 & middle, const float squareHalfWidth, Color c)
	:
	Rect(Vec2(middle.x - squareHalfWidth, middle.y - squareHalfWidth), squareHalfWidth * 2, squareHalfWidth * 2, c)
{
}

void Rect::Draw(Graphics & gfx, int padding)
{
	assert(padding < int(width / 2.0f) - 1);
	Vec2 paddingVec = upperLeft;
	paddingVec += Vec2(float(padding), float(padding));
	gfx.DrawRectDim(paddingVec, int(width - 2*padding), int(height - 2*padding), c);
}

Vec2 Rect::GetCenter() const
{
	return Vec2(upperLeft.x + width/2.0f, upperLeft.y + height/2.0f);
}

bool Rect::checkCollision(const Rect & in_rect, bool & collision_top, bool & collision_bottom, bool & collision_left, bool & collision_right) const
{
	collision_top = false;
	collision_bottom = false;
	collision_left = false;
	collision_right = false;

	const float in_left = in_rect.upperLeft.x;
	const float in_right = in_rect.upperLeft.x + in_rect.width - 1.0f;
	const float in_top = in_rect.upperLeft.y;
	const float in_bottom = in_rect.upperLeft.y + in_rect.height - 1.0f;

	const float left = upperLeft.x;
	const float right = upperLeft.x + width - 1.0f;
	const float top = upperLeft.y;
	const float bottom = upperLeft.y + height - 1.0f;

	if (in_bottom > top
		&& in_top < bottom
		&& in_right > left
		&& in_left < right)
	{
		Vec2 in_center = in_rect.GetCenter();
		Vec2 center = GetCenter();

		// centered collisions
		if (in_center.x > left && in_center.x < right) {
			if (in_center.y < center.y) {
				collision_top = true;
				return true;
			}
			else {
				collision_bottom = true;
				return true;
			}
		}
		if (in_center.y > top && in_center.y < bottom) {
			if (in_center.x < center.x) {
				collision_left = true;
				return true;
			}
			else {
				collision_right = true;
				return true;
			}

		}
		//edge collisions
		const Vec2 normCenterVec = (in_center - center).GetNormalized();
		const Vec2 in_upperleft = in_rect.upperLeft;
		const float y = normCenterVec.y;
		const float x = normCenterVec.x;
		if (y < 0 && x < 0)
		{
			Vec2 normCornerVec(in_upperleft.x - upperLeft.x, in_upperleft.y - upperLeft.y);
			normCornerVec.Normalize();
			if (std::abs(normCornerVec.y) < std::abs(normCornerVec.x)) {
				collision_left = true;
				return true;
			}
			else {
				collision_top = true;
				return true;
			}
		}
		if (y < 0 && x > 0)
		{
			Vec2 normCornerVec(in_upperleft.x - (upperLeft.x + width -1.0f), in_upperleft.y - upperLeft.y);
			normCornerVec.Normalize();
			if (std::abs(normCornerVec.y) < std::abs(normCornerVec.x)) {
				collision_right = true;
				return true;
			}
			else {
				collision_top = true;
				return true;
			}
		}
		if (y > 0 && x < 0)
		{
			Vec2 normCornerVec(in_upperleft.x - upperLeft.x, in_upperleft.y - (upperLeft.y + height - 1.0f));
			normCornerVec.Normalize();
			if (std::abs(normCornerVec.y) < std::abs(normCornerVec.x)) {
				collision_left = true;
				return true;
			}
			else {
				collision_bottom = true;
				return true;
			}
		}
		if (y > 0 && x > 0)
		{
			Vec2 normCornerVec(in_upperleft.x - (upperLeft.x + width - 1.0f), in_upperleft.y - (upperLeft.y + height - 1.0f));
			normCornerVec.Normalize();
			if (std::abs(normCornerVec.y) < std::abs(normCornerVec.x)) {
				collision_right = true;
				return true;
			}
			else {
				collision_bottom = true;
				return true;
			}
		}
	}

	return false;
}

bool Rect::checkCollision(const Rect & in_rect) const
{
	bool temp;
	return checkCollision(in_rect, temp, temp, temp, temp);
}

bool Rect::isCoating(const Rect & innerRect, bool & collision_top, bool & collision_bottom, bool & collision_left, bool & collision_right) const
{
	collision_top = false;
	collision_bottom = false;
	collision_left = false;
	collision_right = false;

	const float in_left = innerRect.upperLeft.x;
	const float in_right = innerRect.upperLeft.x + innerRect.width - 1.0f;
	const float in_top = innerRect.upperLeft.y;
	const float in_bottom = innerRect.upperLeft.y + innerRect.height - 1.0f;

	if (in_left < upperLeft.x)
		collision_left = true;
	else if (in_right > float(Graphics::ScreenWidth) - upperLeft.x)
		collision_right = true;
	if (in_top < upperLeft.y)
		collision_top = true;
	else if (in_bottom > float(Graphics::ScreenHeight) - upperLeft.y)
		collision_bottom = true;

		return !(collision_top || collision_bottom || collision_left || collision_right);
}

bool Rect::isCoating(const Rect & innerRect) const
{
	bool temp;
	return isCoating(innerRect, temp, temp, temp, temp);
}
