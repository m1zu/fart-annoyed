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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	wallUpperLeft(Vec2(149.0f, 19.0f)),
	wall(wallUpperLeft, wallPadding),
	ball(Vec2(399.0f-Ball::halfWidth, 299.0f), Vec2(1.0f, 1.0f).Normalize()),
	paddle(Vec2(399.0f-Paddle::width/2.0f, 499.0f))
{
	int counter = 0;
	const Vec2 offset(50.0f, 50.0f);
	for (int i=0; i<nRows; ++i)
		for (int j = 0; j < nColumns; ++j)
		{
			brick[counter] = Brick(Vec2(wallUpperLeft.x + offset.x + j * Brick::width, wallUpperLeft.y + offset.y + i * Brick::height), Colors::Cyan);
				counter++;
		}
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = frameTimer.Mark();

	paddle.Update(wnd.kbd.KeyIsPressed(VK_LEFT), wnd.kbd.KeyIsPressed(VK_RIGHT), dt);
	wall.ClampPaddle(paddle);

	ball.Update(dt);
	wall.ClampBall(ball);

	paddle.DoCollision(ball);
	for (Brick& b : brick)
		if (!b.IsDestroyed())
			b.Update(ball);
}

void Game::ComposeFrame()
{
	wall.Draw(gfx);
	ball.Draw(gfx);
	paddle.Draw(gfx);
	for (Brick& b : brick)
		if (!b.IsDestroyed())
			b.Draw(gfx);
}
