#include "raylib.h"
#include <string>

int main()
{
	int screenHeight = 680;
	int screenWidth = 920;

	float rectangleWidth = 20.0f;
	float rectangleHeight = 100.0f;

	float playerPosX = 80.0f;
	float playerPosY = screenHeight / 2.0f - rectangleHeight / 2.0f;

	float enemyPosX = screenWidth - playerPosX - rectangleWidth;
	float enemyPosY = screenHeight / 2.0f - rectangleHeight / 2.0f;

	float characterSpeed = 300.0f;

	Rectangle player = {
		playerPosX,
		playerPosY,
		rectangleWidth,
		rectangleHeight
	};

	Rectangle enemy = {
		enemyPosX,
		enemyPosY,
		rectangleWidth,
		rectangleHeight
	};

	float ballSize = 15.0f;

	Vector2 ballSpeed = { 150.0f, 250.0f };
	Vector2 ball = {
		(float)screenWidth / 2.0f,
		(float)screenHeight / 2.0f
	};

	int playerPoints = 0;
	int enemyPoints = 0;

	InitWindow(screenWidth, screenHeight, "Ping Pong");
	SetTargetFPS(60);

	while (!WindowShouldClose())
	{
		float dt = GetFrameTime();

		BeginDrawing();

		ClearBackground(BLACK);

		DrawText(
			TextFormat("%d | %d", playerPoints, enemyPoints),
			screenWidth / 2 - 37,
			80,
			40,
			WHITE
		);

		DrawRectangleRec(player, WHITE);
		DrawRectangleRec(enemy, WHITE);
		DrawCircleV(ball, ballSize, WHITE);

		//Ball Movement
		ball.y += ballSpeed.y * dt;
		ball.x += ballSpeed.x * dt;

		if (ball.y - ballSize <= 0)
		{
			ballSpeed.y *= -1;
		}

		if (ball.y >= screenHeight - ballSize)
		{
			ballSpeed.y *= -1;
		}

		if (ball.x - ballSize <= 0)
		{
			enemyPoints++;
			ball.x = (float)screenWidth / 2.0f;
			ball.y = (float)screenHeight / 2.0f;
		}

		if (ball.x >= screenWidth - ballSize)
		{
			playerPoints++;
			ball.x = (float)screenWidth / 2.0f;
			ball.y = (float)screenHeight / 2.0f;
		}

		//Player Movement
		if (IsKeyDown(KEY_W) && player.y >= 0)
		{
			player.y -= characterSpeed * dt;
		}

		if (IsKeyDown(KEY_S) &&
			player.y <= screenHeight - rectangleHeight)
		{
			player.y += characterSpeed * dt;
		}

		//Enemy Movement
		if (IsKeyDown(KEY_UP) && enemy.y >= 0)
		{
			enemy.y -= characterSpeed * dt;
		}

		if (IsKeyDown(KEY_DOWN) &&
			enemy.y <= screenHeight - rectangleHeight)
		{
			enemy.y += characterSpeed * dt;
		}

		//Collision Ball and Characters
		if (CheckCollisionCircleRec(ball, ballSize, player))
		{
			ballSpeed.x *= -1;
		}

		if (CheckCollisionCircleRec(ball, ballSize, enemy))
		{
			ballSpeed.x *= -1;
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
