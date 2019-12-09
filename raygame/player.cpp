#include "player.h"




bool customCollision(Vector2 v, Rectangle r) {
	if (v.x > r.x && v.y > r.y && v.y < r.y + r.height && v.x < r.x + r.width) {
		return true;
	}
	return false;
}
void drawGrid() {
	DrawRectangleLines(40, 40, 520, 520, BLACK);
	DrawLine(213, 40, 213, 560, BLACK);
	DrawLine(40, 213, 560, 213, BLACK);
	DrawLine(387, 40, 387, 560, BLACK);
	DrawLine(40, 387, 560, 387, BLACK);
}
void drawShapes(int * board[3], Color p1, Color p2) {
	for (int i = 0; i < 3; i++) {
		for (int x = 0; x < 3; x++) {
			if (board[i][x] == 1) {
				DrawCircleLines((40 + (174 * x)) + (174 / 2), (40 + (174 * i)) + (174 / 2), (174 / 2) - 5, p1);
			}
			else if (board[i][x] == -1) {
				DrawLine((52 + (173 * x)), (52 + (173 * i)), (200 + (173 * x)), (200 + (173 * i)), p2);
				DrawLine((200 + (173 * x)), (52 + (173 * i)), (52 + (173 * x)), (200 + (173 * i)), p2);
			}
		}
	}
}
int winCondition(int * board[3]) {
	if (board[0][0] == 1 && board[0][1] == 1 && board[0][2] == 1) {
		return 1;
	}
	else if (board[1][0] == 1 && board[1][1] == 1 && board[1][2] == 1) {
		return 1;
	}
	else if (board[2][0] == 1 && board[2][1] == 1 && board[2][2] == 1) {
		return 1;
	}
	else if (board[0][0] == 1 && board[1][0] == 1 && board[2][0] == 1) {
		return 1;
	}
	else if (board[0][1] == 1 && board[1][1] == 1 && board[2][1] == 1) {
		return 1;
	}
	else if (board[0][2] == 1 && board[1][2] == 1 && board[2][2] == 1) {
		return 1;
	}
	else if (board[0][0] == 1 && board[1][1] == 1 && board[2][2] == 1) {
		return 1;
	}
	else if (board[0][2] == 1 && board[1][1] == 1 && board[2][0] == 1) {
		return 1;
	}
	if (board[0][0] == -1 && board[0][1] == -1 && board[0][2] == -1) {
		return -1;
	}
	else if (board[1][0] == -1 && board[1][1] == -1 && board[1][2] == -1) {
		return -1;
	}
	else if (board[2][0] == -1 && board[2][1] == -1 && board[2][2] == -1) {
		return -1;
	}
	else if (board[0][0] == -1 && board[1][0] == -1 && board[2][0] == -1) {
		return -1;
	}
	else if (board[0][1] == -1 && board[1][1] == -1 && board[2][1] == -1) {
		return -1;
	}
	else if (board[0][2] == -1 && board[1][2] == -1 && board[2][2] == -1) {
		return -1;
	}
	else if (board[0][0] == -1 && board[1][1] == -1 && board[2][2] == -1) {
		return -1;
	}
	else if (board[0][2] == -1 && board[1][1] == -1 && board[2][0] == -1) {
		return -1;
	}
	return 0;
}
bool noWin(int * board[3]) {
	int zero = 0;
	for (int i = 0; i < 3; i++) {
		for (int x = 0; x < 3; x++) {
			if (board[i][x] == 0) {
				zero++;
			}
		}
	}
	if (zero == 0) {
		if (winCondition(board) == 0) {
			return true;
		}
	}

	return false;
}
bool colorCompare(Color one, Color two) {
	return (one.r == two.r && one.b == two.b && one.g == two.g && one.a == two.a) ? true : false;
}