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

#include "player.h"

int main()
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 600;
	int screenHeight = 600;
	srand(time(NULL));
	bool noPlayer = false;
	bool playerChose = false;
	bool clicked = false;
	bool randDone = false;
	bool first = true;
	bool onePlayer = false;
	bool playerOne = true;
	bool win = false;
	bool start = true;
	int stalemate = 0;
	int startPhase = 0;
	int currPlayer;
	int ran;

	Player * one = new Player();
	Player * two = new Player();
	AI * ai = new AI();
	AI * ai2 = new AI();
	one->score = 0;
	two->score = 0;
	ai->score = 0;
	ai2->score = 0;

	ai->color = ORANGE;
	ai2->color = BLUE;
	one->color = RAYWHITE;
	two->color = RAYWHITE;

	ai->move = -1;
	ai2->move = 1;

	int ** board = new int*[3];
	for (int i = 0; i < 3; i++) {
			board[i] = new int[3];
	}
	for (int i = 0; i < 3; i++) {
		for (int x = 0; x < 3; x++) {
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
			ai->turnReset();
			ai2->turnReset();
			clicked = false;
			randDone = false;
			first = false;
			playerOne = true;
			win = false;
		}
		//Prints current board state
		if (IsKeyPressed(KEY_H)){
			for (int i = 0; i < 3; i++) {
				for (int x = 0; x < 3; x++) {
					std::cout << board[i][x];
				}
				std::cout << std::endl;
			}
		}
		//Changes the turn of the player
		if (!win) {
			
			if (playerOne) {
				if (!noPlayer) {
					DrawText("Turn: Player One", 200, 0, 20, BLACK);
				}
				else {
					DrawText("Turn: AI.2", 200, 0, 20, BLACK);
				}
				currPlayer = 1;
			}
			else {
				if (!onePlayer) {
					DrawText("Turn: Player Two", 200, 0, 20, BLACK);
				}
				else {
					DrawText("Turn: AI", 200, 0, 20, BLACK);
				}
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
		
		//Initial Startup for color pick and player check
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
			if (!playerChose) {
				Rectangle p1;
				p1.x = 240;
				p1.y = 200;
				p1.width = 135;
				p1.height = 40;
				Rectangle p2;
				p2.x = 235;
				p2.y = 250;
				p2.width = 150;
				p2.height = 40;
				Rectangle p3;
				p3.x = 230;
				p3.y = 300;
				p3.width = 160;
				p3.height = 40;
				DrawRectangleRec(p1,GRAY);
				DrawRectangleRec(p2,GRAY);
				DrawRectangleRec(p3,GRAY);
				DrawText("How many Players:", 210, 150, 20, BLACK);
				DrawText("One Player.", 250, 210, 20, BLACK);
				DrawText("Two Players.", 245, 260, 20, BLACK);
				DrawText("Zero Players.", 240, 310, 20, BLACK);
				if (customCollision(GetMousePosition(),p1)) {
					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
						onePlayer = true;
						playerChose = true;
					}
				}
				else if (customCollision(GetMousePosition(), p2)) {
					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
						onePlayer = false;
						playerChose = true;
					}
				}
				else if (customCollision(GetMousePosition(), p3)) {
					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
						onePlayer = true;
						playerChose = true;
						noPlayer = true;
						start = false;
					}
				}
			}
			else if (onePlayer && playerChose && !noPlayer) {
				if (startPhase == 0) {
					DrawText("Player 1", 260, 150, 20, BLACK);
					if (customCollision(GetMousePosition(), Blue)) {
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
				else {
					start = false;
				}
				if (!colorCompare(one->color, BLUE)) {
					DrawRectangleRec(Blue, BLUE);
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
			else if(!onePlayer && playerChose && !noPlayer) {
				if (startPhase == 0) {
					DrawText("Player 1", 260, 150, 20, BLACK);
					if (customCollision(GetMousePosition(), Blue)) {
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

				if (!colorCompare(one->color, BLUE)) {
					DrawRectangleRec(Blue, BLUE);
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
			two->score = 0;

		}
		//Main loop for game
		else if(!onePlayer && !noPlayer) {
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
				DrawText("Press R for new game", 190, 280, 20, BLACK);
				if (!win) {
					one->score++;
					win = true;
				}
			}
			//Checks board to see if Player 2 won
			else if (winCondition(board) == -1) {
				DrawRectangle(150, 150, 300, 300, LIGHTGRAY);
				DrawText("Player Two Wins!", 210, 210, 20, BLACK);
				DrawText("Press R for new game", 190, 280, 20, BLACK);
				if (!win) {
					two->score++;
					win = true;
				}
			}
			//Checks board to see if no one won
			else if (noWin(board)) {
				DrawRectangle(150, 150, 300, 300, LIGHTGRAY);
				if (!first) {
					DrawText("Looks like a stalemate.", 185, 210, 20, BLACK);
				}
				DrawText("Press R for new game", 190, 280, 20, BLACK);
				stalemate++;
			}
		}
		else if (onePlayer && !noPlayer) {
			//Randomly selects first player
			if (zeroedBoard(board) && !clicked) {
				DrawRectangle(150, 130, 300, 350, LIGHTGRAY);
				DrawText("Who goes First:", 210, 150, 20, BLACK);
				if (!randDone) {
					ran = rand() % 2;
				}
				int temp=ran;
				if (temp == 0) {
					DrawText("AI",280,260,30,BLACK);
					playerOne = false;
					randDone = true;
				}
				else if (temp == 1) {
					DrawText("Player", 250, 260, 30, BLACK);
					playerOne = true;
					randDone = true;
				}
				DrawText("Press E to continue",190,340,20,BLACK);
				if (IsKeyPressed(KEY_E)) {
					clicked = true;
				}
			}
			else if (playerOne && !win) {
				for (int i = 0; i < 3; i++) {
					for (int x = 0; x < 3; x++) {
						if (customCollision(GetMousePosition(), checkers[i][x])) {
							if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
								if (board[i][x] == 0) {
									board[i][x] = 1;
									playerOne = !playerOne;
									ai->turnIncrease();
								}
							}
						}
					}
				}
				
			}
			else if (!playerOne && !win) {
				ai->checkMove(board);
				playerOne = !playerOne;
			}
			//Checks board to see if Player 1 won
			if (winCondition(board) == 1) {
				DrawRectangle(150, 150, 300, 300, LIGHTGRAY);
				DrawText("Player One Wins!", 210, 210, 20, BLACK);
				DrawText("Press R for new game", 190, 280, 20, BLACK);
				if (!win) {
					one->score++;
					win = true;
				}
			}
			//Checks board to see if AI won
			else if (winCondition(board) == -1) {
				DrawRectangle(150, 150, 300, 300, LIGHTGRAY);
				DrawText("AI Wins!", 230, 210, 20, BLACK);
				DrawText("Press R for new game", 190, 280, 20, BLACK);
				if (!win) {
					ai->score++;
					win = true;
				}
			}
			else if (noWin(board)) {
				DrawRectangle(150, 150, 300, 300, LIGHTGRAY);
				if (!first) {
					DrawText("Looks like a stalemate.", 185, 210, 20, BLACK);
				}
				win = true;
				DrawText("Press R for new game", 190, 280, 20, BLACK);
				stalemate++;
			}
		}
		else if (noPlayer) {
			if (zeroedBoard(board) && !clicked) {
				if (!randDone) {
					ran = rand() % 2;
				}
				int temp = ran;
				if (temp == 0) {
					playerOne = false;
					randDone = true;
				}
				else if (temp == 1) {
					playerOne = true;
					randDone = true;
				}
				clicked = true;
			}
			else if (playerOne && !win) {
				ai2->checkMove(board);
				playerOne = !playerOne;
				ai->turnIncrease();
			}
			else if (!playerOne && !win) {
				ai->checkMove(board);
				playerOne = !playerOne;
				ai2->turnIncrease();
			}
			if (winCondition(board) == 1) {
				if (!win) {
					ai2->score++;
					win = true;
				}
				for (int i = 0; i < 3; i++) {
					for (int x = 0; x < 3; x++) {
						board[i][x] = 0;
					}
				}
				ai->turnReset();
				ai2->turnReset();
				clicked = false;
				randDone = false;
				first = false;
				playerOne = true;
				win = false;
			}
			else if (winCondition(board) == -1) {
				if (!win) {
					ai->score++;
					win = true;
				}
				for (int i = 0; i < 3; i++) {
					for (int x = 0; x < 3; x++) {
						board[i][x] = 0;
					}
				}
				ai->turnReset();
				ai2->turnReset();
				clicked = false;
				randDone = false;
				first = false;
				playerOne = true;
				win = false;
			}
			else if (noWin(board)) {
				if (!first) {
				}
				win = true;
				for (int i = 0; i < 3; i++) {
					for (int x = 0; x < 3; x++) {
						board[i][x] = 0;
					}
				}
				ai->turnReset();
				ai2->turnReset();
				clicked = false;
				randDone = false;
				first = false;
				playerOne = true;
				win = false;
				stalemate++;
			}
		}
		//Draws the shapes
		drawShapes(board,(!noPlayer)?one->color:ai2->color,(onePlayer)?ai->color:two->color);
		//Draws the scores of the players
		if (!noPlayer) {
			DrawText(FormatText("Player 1: %01i", one->score), 0, 0, 20, one->color);
		}
		else {
			DrawText(FormatText("AI 2: %01i", ai2->score), 0, 0, 20, ai2->color);
		}
		if (!onePlayer) {
			DrawText(FormatText("Player 2: %01i", two->score), 450, 0, 20, two->color);
		}
		else {
			DrawText(FormatText("AI: %01i", ai->score), 520, 0, 20, ai->color);
		}
		DrawText(FormatText("Stalemate %01i", stalemate), 220, 560, 30, BLACK);
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