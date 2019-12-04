/*******************************************************************************************
*
*   raylib [core] example - basic window
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2013-2016 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <iostream>
#include "raylib.h"
#include "player.h"

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 600;
	int screenHeight = 600;

	int board[3][3] = { {0,0,0}, {0,0,0}, {0,0,0}};
	Rectangle checkers[3][3];
	for (int i = 0; i < 3; i++) {
		for(int x = 0; x < 3; x++){
			checkers[i][x].x = 40 + (173 * i);
			checkers[i][x].y = 40 + (173 * x);
			checkers[i][x].height = 213 + (173 * i);
			checkers[i][x].width = 213 + (173 * x);
		}
	}

	InitWindow(screenWidth, screenHeight, "Basic Tic Tac Toe");
	Color p1 = BLACK;
	Color p2;
	bool start = false;
	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------
		if (IsKeyPressed(KEY_R)) {
			for (int i = 0; i < 3; i++) {
				for (int x = 0; x < 3; x++) {
					board[i][x] = 0;
				}
			}
		}
		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawRectangleLines(40, 40, 520, 520, BLACK);
		DrawLine(213, 40, 213, 560, BLACK);
		DrawLine(40, 213, 560, 213, BLACK);
		DrawLine(387, 40, 387, 560, BLACK);
		DrawLine(40, 387, 560, 387, BLACK);
		DrawText("Player 1: ", 0, 0, 20, BLACK);
		DrawText("Player 2: ", 450, 0, 20, BLACK);

		Rectangle first;
		first.x = 40;
		first.y = 40;
		first.width = 173;
		first.height = 173;
		
		for (int i = 0; i < 3; i++) {
			for (int x = 0; x < 3; x++) {
				if (board[i][x] == 1) {
					DrawCircleLines((40+(174*i)) + (174 / 2), (40 + (174 * x)) + (174 / 2), (174 / 2) - 5, p1);
				}
				else if (board[i][x] == -1) {
					DrawLine((52 + (173*i)), (52 + (173 * i)), (200 + (173*x)), (200 + (173 * x)), p1);
					DrawLine((52 + (173 * i)), (200 + (173 * x)), (200 + (173 * x)), (52 + (173 * i)), p1);
				}
			}
		}
		if (customCollision(GetMousePosition(),first)) {
			if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
				if(board[0][0] == 0){
					board[0][0] = 1;
				}
			}
			if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
				if (board[0][0] == 0) {
					board[0][0] = -1;
				}
			}
		}
		if (start) {
			DrawRectangle(149,49,300,450,BLACK);
			DrawRectangle(150, 50, 298, 448,RAYWHITE);
			DrawText("How many players:", 200, 75, 20, BLACK);
			DrawRectangle(200,145,100,40,GRAY);
			DrawText("1 Player", 210, 155, 20, BLACK);
			DrawRectangle(200,175,130,40,GRAY);
			DrawText("2 Players", 210, 185, 20, BLACK);
		}

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}