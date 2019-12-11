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
	int screen = 0;
	std::cout << "Please enter a size of the  screen(Recomended 600)\n";
	std::cin >> screen;

	if (screen < 500) {
		std::cout << "Size to small... Auto update will incur\n";
		screen = 500;
	}
	else if (screen > 1000) {
		std::cout << "Size to large... Auto update will incur\n";
		screen = 1000;
	}
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

	Color stlmteColor = randColor();

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

	InitWindow(screen, screen, "Basic Tic-Tac-Toe");
	//Sets the rectangles of the board
	for (int i = 0; i < 3; i++) {
		for(int x = 0; x < 3; x++){
			checkers[i][x].x = (float)(GetScreenWidth() / 8) + ((GetScreenWidth() * 3 / 4) / 3 * x);
			checkers[i][x].y = (float)(GetScreenHeight() / 8) + ((GetScreenHeight() * 3 / 4) / 3 * i);
			checkers[i][x].height = (float)(GetScreenWidth() * 3 / 4) / 3;
			checkers[i][x].width = (float)(GetScreenHeight() * 3 / 4) / 3;
		}
	}
	SetTargetFPS(60);
	//--------------------------------------------------------------------------------------
	
	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		stlmteColor = randColor();
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------
		//Resets current game
		if (IsKeyPressed(KEY_R)&&win) {
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
		//Resets Game
		if (IsKeyPressed(KEY_GRAVE)) {
			start = true;
			playerChose = false;
			for (int i = 0; i < 3; i++) {
				for (int x = 0; x < 3; x++) {
					board[i][x] = 0;
				}
			}
			one->color = RAYWHITE;
			two->color = RAYWHITE;
			stalemate = 0;
			one->score = 0;
			two->score = 0;
			ai->score = 0;
			ai2->score = 0;
			ai->turnReset();
			ai2->turnReset();
			clicked = false;
			randDone = false;
			first = false;
			playerOne = true;
			win = false;
			startPhase = 0;
		}
		//Changes the text of the turn of the player
		if (!win) {
			
			if (playerOne) {
				if (!noPlayer) {
					DrawText("Turn: Player One", (GetScreenHeight() / 2) - 100, 0, 20, BLACK);
				}
				else {
					DrawText("Turn: AI.2", (GetScreenHeight() / 2) - 100, 0, 20, BLACK);
				}
				currPlayer = 1;
			}
			else {
				if (!onePlayer) {
					DrawText("Turn: Player Two", (GetScreenHeight() / 2) - 100, 0, 20, BLACK);
				}
				else {
					DrawText("Turn: AI", (GetScreenHeight() / 2) - 100, 0, 20, BLACK);
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
		drawGrid(checkers);
		
		//Initial Startup for color pick and player check
		if (start) {
			Rectangle Blue;
			Blue.x =(float) (GetScreenWidth() / 2) - 70;
			Blue.y = (float)(GetScreenHeight() / 2) - 40;
			Blue.width = 70;
			Blue.height = 70;
			Rectangle Red;
			Red.x = (float)(GetScreenWidth() / 2) + 20;
			Red.y = (float)(GetScreenHeight() / 2) - 40;
			Red.width = 70;
			Red.height = 70;
			Rectangle Black;
			Black.x = (float)(GetScreenWidth() / 2) - 70;
			Black.y = (float)(GetScreenHeight() / 2) + 50;
			Black.width = 70;
			Black.height = 70;
			Rectangle Green;
			Green.x = (float)(GetScreenWidth() / 2) + 20;
			Green.y = (float)(GetScreenHeight() / 2) + 50;
			Green.width = 70;
			Green.height = 70;
			DrawRectangle((GetScreenWidth() / 2) - 140, (GetScreenHeight() / 2) - 170, 300, 350, LIGHTGRAY);
			//First Choice the player is given
			if (!playerChose) {
				Color b1;
				Color b2;
				Color b3;
				Rectangle p1;
				p1.x = (float)(GetScreenWidth() / 2) - 60;
				p1.y = (float)(GetScreenHeight() / 2) - 100;
				p1.width = 135;
				p1.height = 40;
				Rectangle p2;
				p2.x = (float)(GetScreenWidth() / 2) - 65;
				p2.y = (float)(GetScreenHeight() / 2) - 50;
				p2.width = 150;
				p2.height = 40;
				Rectangle p3;
				p3.x = (float)(GetScreenWidth() / 2) - 70;
				p3.y = (float)(GetScreenHeight() / 2);
				p3.width = 160;
				p3.height = 40;
				//One Player
				if (customCollision(GetMousePosition(),p1)) {
					b1 = DARKGRAY;
					b2 = GRAY;
					b3 = GRAY;
					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
						onePlayer = true;
						playerChose = true;
						noPlayer = false;
					}
				}
				//Two Player
				else if (customCollision(GetMousePosition(), p2)) {
					b2 = DARKGRAY;
					b1 = GRAY;
					b3 = GRAY;
					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
						onePlayer = false;
						playerChose = true;
						noPlayer = false;
					}
				}
				//No Player
				else if (customCollision(GetMousePosition(), p3)) {
					b3 = DARKGRAY;
					b2 = GRAY;
					b1 = GRAY;
					if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
						onePlayer = true;
						playerChose = true;
						noPlayer = true;
						start = false;
					}
				}
				else {
					b1 = GRAY;
					b2 = GRAY;
					b3 = GRAY;
				}
				DrawRectangleRec(p1,b1);
				DrawRectangleRec(p2,b2);
				DrawRectangleRec(p3,b3);
				DrawText("How many Players:", (GetScreenHeight() / 2) - 90, (GetScreenHeight() / 2) - 150, 20, BLACK);
				DrawText("One Player.", (GetScreenHeight() / 2) - 50, (GetScreenHeight() / 2) - 90, 20, BLACK);
				DrawText("Two Players.", (GetScreenHeight() / 2) - 55, (GetScreenHeight() / 2) - 40, 20, BLACK);
				DrawText("Zero Players.", (GetScreenHeight() / 2) - 60, (GetScreenHeight() / 2) + 10, 20, BLACK);
			}
			//Player picks color
			else if (onePlayer && playerChose && !noPlayer) {
				if (startPhase == 0) {
					DrawText("Player 1", (GetScreenWidth() / 2) - 40, (GetScreenHeight() / 2) - 150, 20, BLACK);
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
			//Players pick colors
			else if(!onePlayer && playerChose && !noPlayer) {
				//Player one color pick
				if (startPhase == 0) {
					DrawText("Player 1", (GetScreenHeight() / 2) - 40, (GetScreenHeight() / 2) - 150, 20, BLACK);
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
				//Player one color pick
				else if (startPhase == 1) {
					DrawText("Player 2", (GetScreenWidth() / 2) - 40, (GetScreenHeight() / 2) - 150, 20, BLACK);
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
				DrawText("Choose Color:", (GetScreenWidth() / 2) - 70, (GetScreenHeight() / 2) - 90, 20, BLACK);

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
		}
		//PvP
		else if (!onePlayer && !noPlayer) {
			//Randomly selects first player
			if (zeroedBoard(board) && !clicked) {
				DrawRectangle((GetScreenWidth() / 2) - 140, (GetScreenHeight() / 2) - 170, 300, 350, LIGHTGRAY);
				DrawText("Who goes First:", (GetScreenWidth() / 2) - 70, (GetScreenHeight() / 2) - 130, 20, BLACK);
				if (!randDone) {
					ran = rand() % 2;
				}
				int temp = ran;
				if (temp == 0) {
					DrawText("Player 2", (GetScreenWidth() / 2) - 50, (GetScreenHeight() / 2) - 40, 30, BLACK);
					playerOne = false;
					randDone = true;
				}
				else if (temp == 1) {
					DrawText("Player 1", (GetScreenWidth() / 2) - 50, (GetScreenHeight() / 2) - 40, 30, BLACK);
					playerOne = true;
					randDone = true;
				}
				DrawText("Press E to continue", (GetScreenWidth() / 2) - 90, (GetScreenHeight() / 2) + 40, 20, BLACK);
				if (IsKeyPressed(KEY_E)) {
					clicked = true;
				}
			}
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
				DrawRectangle((GetScreenWidth() / 2) - 140, (GetScreenHeight() / 2) - 170, 300, 350, LIGHTGRAY);
				DrawText("Player One Wins!", (GetScreenWidth() / 2) - 90, (GetScreenWidth() / 2) - 90, 20, BLACK);
				DrawText("Press R to reset game", (GetScreenWidth() / 2) - 120, (GetScreenWidth() / 2) - 20, 20, BLACK);
				if (!win) {
					one->score++;
					win = true;
				}
			}
			//Checks board to see if Player 2 won
			else if (winCondition(board) == -1) {
				DrawRectangle((GetScreenWidth() / 2) - 140, (GetScreenHeight() / 2) - 170, 300, 350, LIGHTGRAY);
				DrawText("Player Two Wins!", (GetScreenWidth() / 2) - 90, (GetScreenWidth() / 2) - 90, 20, BLACK);
				DrawText("Press R to reset game", (GetScreenWidth() / 2) - 120, (GetScreenWidth() / 2) - 20, 20, BLACK);
				if (!win) {
					two->score++;
					win = true;
				}
			}
			//Checks board to see if no one won
			else if (noWin(board)) {
				DrawRectangle((GetScreenWidth() / 2) - 140, (GetScreenHeight() / 2) - 170, 300, 350, LIGHTGRAY);
				DrawText("Looks like a stalemate.", (GetScreenWidth() / 2) - 115, (GetScreenWidth() / 2) - 90, 20, BLACK);
				DrawText("Press R to reset game", (GetScreenWidth() / 2) - 120, (GetScreenWidth() / 2) - 20, 20, BLACK);
				win = true;
			}
		}
		//PvC
		else if (onePlayer && !noPlayer) {
			//Randomly selects first player
			if (zeroedBoard(board) && !clicked) {
				DrawRectangle((GetScreenWidth() / 2) - 140, (GetScreenHeight() / 2) - 170, 300, 350, LIGHTGRAY);
				DrawText("Who goes First:", (GetScreenWidth() / 2) - 70, (GetScreenHeight() / 2) - 130, 20, BLACK);
				if (!randDone) {
					ran = rand() % 2;
				}
				int temp=ran;
				if (temp == 0) {
					DrawText("AI", (GetScreenWidth() / 2) - 10, (GetScreenHeight() / 2) - 40,30,BLACK);
					playerOne = false;
					randDone = true;
				}
				else if (temp == 1) {
					DrawText("Player", (GetScreenWidth() / 2) - 40, (GetScreenHeight() / 2) - 40, 30, BLACK);
					playerOne = true;
					randDone = true;
				}
				DrawText("Press E to continue", (GetScreenWidth() / 2) - 90, (GetScreenHeight() / 2) + 40,20,BLACK);
				if (IsKeyPressed(KEY_E)) {
					clicked = true;
				}
			}
			//Player Move
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
			//AI plays
			else if (!playerOne && !win) {
				ai->checkMove(board);
				playerOne = !playerOne;
			}
			//Checks board to see if Player 1 won
			if (winCondition(board) == 1) {
				DrawRectangle((GetScreenWidth() / 2) - 140, (GetScreenHeight() / 2) - 170, 300, 350, LIGHTGRAY);
				DrawText("Player One Wins!", (GetScreenWidth() / 2) - 90, (GetScreenHeight() / 2) - 90, 20, BLACK);
				DrawText("Press R to reset game", (GetScreenWidth() / 2) - 120, (GetScreenHeight() / 2) - 20, 20, BLACK);
				if (!win) {
					one->score++;
					win = true;
				}
			}
			//Checks board to see if AI won
			else if (winCondition(board) == -1) {
				DrawRectangle((GetScreenWidth() / 2) - 140, (GetScreenHeight() / 2) - 170, 300, 350, LIGHTGRAY);
				DrawText("AI Wins!", (GetScreenWidth() / 2) - 70, (GetScreenWidth() / 2) - 90, 20, BLACK);
				DrawText("Press R for new game", (GetScreenWidth() / 2) - 110, (GetScreenWidth() / 2) - 20, 20, BLACK);
				if (!win) {
					ai->score++;
					win = true;
				}
			}
			//Checks board to see if no one won
			else if (noWin(board)) {
				DrawRectangle((GetScreenWidth() / 2) - 140, (GetScreenHeight() / 2) - 170, 300, 350, LIGHTGRAY);
				DrawText("Looks like a stalemate.", (GetScreenWidth() / 2) - 115, (GetScreenWidth() / 2) - 90, 20, BLACK);
				DrawText("Press R to reset game", (GetScreenWidth() / 2) - 120, (GetScreenWidth() / 2) - 20, 20, BLACK);
				win = true;
			}
		}
		//AI Tic-Tac-Toe
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
		//Draws the scores of the players **
		if (!noPlayer) {
			DrawText(FormatText("Player 1: %01i", one->score), 20, 0, 20, one->color);
		}
		else {
			DrawText(FormatText("AI 2: %01i", ai2->score), 20, 0, 20, ai2->color);
		}
		if (!onePlayer) {
			DrawText(FormatText("Player 2: %01i", two->score), (GetScreenWidth()) - 150, 0, 20, two->color);
		}
		else {
			DrawText(FormatText("AI: %01i", ai->score), (GetScreenWidth()) - 100, 0, 20, ai->color);
		}
		//End drawing scores			  **
		DrawText(FormatText("Stalemate %01i", stalemate), (GetScreenWidth()/2) - 80, (GetScreenWidth()) - 40, 30, stlmteColor);
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