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
#include "player.h"

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 600;
	int screenHeight = 600;
	bool playerOne = true;
	bool win = false;
	bool start = true;
	int startPhase = 0;
	int currPlayer;

	Player * one = new Player();
	Player * two = new Player();
	one->score = 0;
	two->score = 0;
	one->color = RAYWHITE;
	two->color = RAYWHITE;

	int ** board = new int*[3];
	for (int i = 0; i < 3; i++) {
			board[i] = new int[3];
	}
	for (int i = 0; i < 3; i++) {
		for (int x = 0; x < 0; x++) {
			board[i][x] = 0;
		}
	}
	//The area for the boxes of the board
	Rectangle checkers[3][3];
	for (int i = 0; i < 3; i++) {
		for(int x = 0; x < 3; x++){
			checkers[i][x].x =(float) 40 + (173 * x);
			checkers[i][x].y = (float)40 + (173 * i);
			checkers[i][x].height = (float)173;
			checkers[i][x].width = (float)173;
		}
	}

	InitWindow(screenWidth, screenHeight, "Basic Tic-Tac-Toe");
	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------
		//Resets game
		if (IsKeyPressed(KEY_R)) {
			for (int i = 0; i < 3; i++) {
				for (int x = 0; x < 3; x++) {
					board[i][x] = 0;
				}
			}
			playerOne = true;
			win = false;
		}
		//Changes the turn of the player
		if (!win) {
			if (playerOne) {
				DrawText("Turn: Player One", 200, 0, 20, BLACK);
				currPlayer = 1;
			}
			else {
				DrawText("Turn: Player Two", 200, 0, 20, BLACK);
				currPlayer = -1;
			}
		}
		//Makes sure the board can't be chaned after someone won
		else {
			currPlayer = 0;
		}

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();
		ClearBackground(RAYWHITE);

		//Draws the board
		drawGrid();
		
		//Draws the scores of the players
		DrawText(FormatText("Player 1: %01i", one->score), 0, 0, 20, one->color);
		DrawText(FormatText("Player 2: %01i", two->score), 450, 0, 20, two->color);

		//Draws the shapes
		drawShapes(board,one->color,two->color);
		//Initial Startup for color pick
		if (start) {
			Rectangle Blue;
			Blue.x = 210;
			Blue.y = 260;
			Blue.width = 70;
			Blue.height = 70;
			Rectangle Red;
			Red.x = 320;
			Red.y = 260;
			Red.width = 70;
			Red.height = 70;
			Rectangle Black;
			Black.x = 210;
			Black.y = 360;
			Black.width = 70;
			Black.height = 70;
			Rectangle Green;
			Green.x = 320;
			Green.y = 360;
			Green.width = 70;
			Green.height = 70;
			DrawRectangle(150, 130, 300, 350, LIGHTGRAY);
			if (startPhase == 0) {
				DrawText("Player 1", 260, 150, 20, BLACK);
				if (customCollision(GetMousePosition(),Blue)) {
					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
						one->color = BLUE;
						startPhase++;
					}
				}
				if (customCollision(GetMousePosition(), Red)) {
					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
						one->color = RED;
						startPhase++;
					}
				}
				if (customCollision(GetMousePosition(), Black)) {
					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
						one->color = BLACK;
						startPhase++;
					}
				}
				if (customCollision(GetMousePosition(), Green)) {
					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
						one->color = DARKGREEN;
						startPhase++;
					}
				}
			}
			else if (startPhase == 1) {
				DrawText("Player 2", 260, 150, 20, BLACK);
				if (!colorCompare(one->color, BLUE)) {
					if (customCollision(GetMousePosition(), Blue)) {
						if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
							two->color = BLUE;
							startPhase++;
						}
					}
				}
				if (!colorCompare(one->color, RED)) {
					if (customCollision(GetMousePosition(), Red)) {
						if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
							two->color = RED;
							startPhase++;
						}
					}
				}
				if (!colorCompare(one->color, BLACK)) {
					if (customCollision(GetMousePosition(), Black)) {
						if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
							two->color = BLACK;
							startPhase++;
						}
					}
				}
				if (!colorCompare(one->color, DARKGREEN)) {
					if (customCollision(GetMousePosition(), Green)) {
						if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
							two->color = DARKGREEN;
							startPhase++;
						}
					}
				}
			}
			else {
				start = false;
			}
			
			DrawText("Choose Color:", 230, 210, 20, BLACK);
			
			if (!colorCompare(one->color,BLUE)) {
				DrawRectangleRec(Blue,BLUE);
			}
			if (!colorCompare(one->color, RED)) {
				DrawRectangleRec(Red, RED);
			}
			if (!colorCompare(one->color, BLACK)) {
				DrawRectangleRec(Black, BLACK);
			}
			if (!colorCompare(one->color, DARKGREEN)) {
				DrawRectangleRec(Green, DARKGREEN);
			}
		}
		//Main loop for game
		else {
			for (int i = 0; i < 3; i++) {
				for (int x = 0; x < 3; x++) {
					if (customCollision(GetMousePosition(), checkers[i][x])) {
						if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
							if (board[i][x] == 0) {
								board[i][x] = currPlayer;
								playerOne = !playerOne;
							}
						}
					}
				}
			}
			//Checks board to see if Player 1 won
			if (winCondition(board) == 1) {
				DrawRectangle(150, 150, 300, 300, LIGHTGRAY);
				DrawText("Player One Wins!", 210, 210, 20, BLACK);
				DrawText("Press R to reset game", 180, 280, 20, BLACK);
				if (!win) {
					one->score++;
					win = true;
				}
			}
			//Checks board to see if Player 2 won
			else if (winCondition(board) == -1) {
				DrawRectangle(150, 150, 300, 300, LIGHTGRAY);
				DrawText("Player Two Wins!", 210, 210, 20, BLACK);
				DrawText("Press R to reset game", 180, 280, 20, BLACK);
				if (!win) {
					two->score++;
					win = true;
				}
			}
			//Checks board to see if no one won
			else if (noWin(board)) {
				DrawRectangle(150, 150, 300, 300, LIGHTGRAY);
				DrawText("Looks like a stalemate.", 185, 210, 20, BLACK);
				DrawText("Press R to reset game", 190, 280, 20, BLACK);
			}
		}
		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------
	//Deleting
	for (int i = 0; i < 3; ++i) {
		delete[] board[i];
	}
	delete[] board;
	delete one;
	delete two;
	return 0;
}