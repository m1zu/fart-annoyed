/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	wallUpperLeft(Vec2(149.0f, 19.0f)),
	wall(wallUpperLeft, wallPadding),
	ball(Vec2(399.0f - Ball::halfWidth, 299.0f), Vec2(0.0f, 1.0f).Normalize()),
	paddle(Vec2(399.0f - Paddle::width / 2.0f, 499.0f)),
	lifebar(3, Vec2(120.0f, Graphics::ScreenHeight - 20.0f)),
	s_bounce(L"Sounds\\arkpad.wav"),
	s_brick(L"Sounds\\arkbrick.wav")
{
	SoundSystem::SetMasterVolume(0.05f);
	Color colorString[nRows] = { Colors::Blue, Colors::Cyan, Colors::Green, Colors::Magenta, Colors::Red, Colors::White, Colors::Yellow };
	int counter = 0;
	const Vec2 offset(30.0f, 50.0f);
	for (int i = 0; i < nRows; ++i)
		for (int j = 0; j < nColumns; ++j)
		{
			brick[counter] = Brick(Vec2(wallUpperLeft.x + offset.x + j * Brick::width, wallUpperLeft.y + offset.y + i * Brick::height), colorString[i]);
			counter++;
		}
}

void Game::Go()
{
	gfx.BeginFrame();

	float elapsedTime = frameTimer.Mark();
	while (elapsedTime > 0) {
		const float dt = std::min(0.0025f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= 0.0025f;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(const float dt)
{
	if (gameIsStarted && !gameOver) {
		paddle.Update(wnd.kbd.KeyIsPressed(VK_LEFT), wnd.kbd.KeyIsPressed(VK_RIGHT), dt);
		wall.ClampPaddle(paddle);

		ball.Update(dt);
		if (wall.ClampBall(ball))
			s_bounce.Play();

		if (paddle.DoBallCollision(ball))
			s_bounce.Play();

		bool collisionHappened = false;
		int currentCollisionIndex;
		float currentCollisionDistanceSq;
		int counter = 0;
		for (int i = 0; i < nRows; ++i)
			for (int j = 0; j < nColumns; ++j)
			{
				if (!brick[counter].IsDestroyed())
					if (brick[counter].CheckBallCollision(ball))
						if (collisionHappened)
						{
							float newCollisionDistanceSq = (brick[counter].GetCenter() - ball.getRect().GetCenter()).GetLengthSq();
							if (newCollisionDistanceSq < currentCollisionDistanceSq)
							{
								currentCollisionDistanceSq = newCollisionDistanceSq;
								currentCollisionIndex = counter;
							}
						}
						else
						{
							collisionHappened = true;
							currentCollisionDistanceSq = (brick[counter].GetCenter() - ball.getRect().GetCenter()).GetLengthSq();
							currentCollisionIndex = counter;
						}
				counter++;
			}
		if (collisionHappened) {
			brick[currentCollisionIndex].ExecuteBallCollision(ball);
			s_brick.Play();
		}
	}
	else if (wnd.kbd.KeyIsPressed(VK_RETURN))
		gameIsStarted = true;
}

void Game::ComposeFrame()
{
	wall.Draw(gfx);
	ball.Draw(gfx);
	paddle.Draw(gfx);
	for (Brick& b : brick)
		if (!b.IsDestroyed())
			b.Draw(gfx);
	lifebar.Draw(gfx);
}
