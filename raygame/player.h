#pragma once
#include <stdlib.h> 
#include <iostream>
#include <time.h>
#include "raylib.h"
struct Player {
public:
	Color color;
	int score;
};
class AI :public Player {
public:
	void checkMove(int * board[3]);
	void turnIncrease();
	int getTurn();
	void turnReset();
	int move;
private:
	int turn = 0;
};
Color randColor();
bool customCollision(Vector2, Rectangle);
bool zeroedBoard(int * board[3]);
int winCondition(int * board[3]);
bool noWin(int * board[3]);
void drawGrid(Rectangle rec[3][3]);
void drawShapes(int * board[3], Color p1, Color p2);
bool colorCompare(Color one, Color two);