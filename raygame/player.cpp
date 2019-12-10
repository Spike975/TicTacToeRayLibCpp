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
bool zeroedBoard(int * board[3]) {
	int zero = 0;
	for (int i = 0; i < 3; i++) {
		for (int x = 0; x < 3; x++) {
			if (board[i][x] == 0) {
				zero++;
			}
		}
	}
	if (zero == 9) {
		return true;
	}
	return false;
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


//AI CODE:
void AI::checkMove(int * board[3]) {
	int oposite = 0;
	if (move == 1) {
		oposite = -1;
	}
	else {
		oposite = 1;
	}
	if (turn == 0) {
		int temp1 = rand() % 3;
		int temp2 = rand() % 3;
		do {
			if (board[temp1][temp2] != 0) {
				temp1 = rand() % 3;
				temp2 = rand() % 3;
			}
		} while (board[temp1][temp2] != 0);
		board[temp1][temp2] = move;
	}
	else if (turn == 1) {
		if (board[1][1] == oposite) {
			board[0][0] = move;
		}
		else {
			int temp1 = rand() % 3;
			int temp2 = rand() % 3;
			do {
				if (board[temp1][temp2] != 0) {
					temp1 = rand() % 3;
					temp2 = rand() % 3;
				}
			} while (board[temp1][temp2] != 0);
			board[temp1][temp2] = move;
		}
	}
	else {
		//Start offense
		if (board[0][0] == move && board[0][1] == move && board[0][2] == 0) {
			board[0][2] = move;
		}
		else if (board[0][0] == move && board[0][1] == 0 && board[0][2] == move) {
			board[0][1] = move;
		}
		else if (board[0][0] == 0 && board[0][1] == move && board[0][2] == move) {
			board[0][0] = move;
		}
		else if (board[1][0] == move && board[1][1] == move && board[1][2] == 0) {
			board[1][2] = move;
		}
		else if (board[1][0] == move && board[1][1] == 0 && board[1][2] == move) {
			board[1][1] = move;
		}
		else if (board[1][0] == 0 && board[1][1] == move && board[1][2] == move) {
			board[1][0] = move;
		}
		else if (board[2][0] == move && board[2][1] == move && board[2][2] == 0) {
			board[2][2] = move;
		}
		else if (board[2][0] == move && board[2][1] == 0 && board[2][2] == move) {
			board[2][1] = move;
		}
		else if (board[2][0] == 0 && board[2][1] == move && board[2][2] == move) {
			board[2][0] = move;
		}

		else if (board[0][0] == move && board[1][0] == move && board[2][0] == 0) {
			board[2][0] = move;
		}
		else if (board[0][0] == move && board[1][0] == 0 && board[2][0] == move) {
			board[1][0] = move;
		}
		else if (board[0][0] == 0 && board[1][0] == move && board[2][0] == move) {
			board[0][0] = move;
		}
		else if (board[0][1] == move && board[1][1] == move && board[2][1] == 0) {
			board[2][1] = move;
		}
		else if (board[0][1] == move && board[1][1] == 0 && board[2][1] == move) {
			board[1][1] = move;
		}
		else if (board[0][1] == 0 && board[1][1] == move && board[2][1] == move) {
			board[0][1] = move;
		}
		else if (board[0][2] == move && board[1][2] == move && board[2][2] == 0) {
			board[2][2] = move;
		}
		else if (board[0][2] == move && board[1][2] == 0 && board[2][2] == move) {
			board[1][2] = move;
		}
		else if (board[0][2] == 0 && board[1][2] == move && board[2][2] == move) {
			board[0][2] = move;
		}

		else if(board[0][0] == 0 && board[1][1] == move && board[2][2] == move){
			board[0][0] = move;
		}
		else if (board[0][0] == move && board[1][1] == 0 && board[2][2] == move) {
			board[1][1] = move;
		}
		else if (board[0][0] == move && board[1][1] == move && board[2][2] == 0) {
			board[2][2] = move;
		}
		else if (board[0][2] == 0 && board[1][1] == move && board[2][0] == move) {
			board[0][2] = move;
		}
		else if (board[0][2] == move && board[1][1] == 0 && board[2][0] == move) {
			board[1][1] = move;
		}
		else if (board[0][2] == move && board[1][1] == move && board[2][0] == 0) {
			board[2][0] = move;
		}
		//Start defense
		else if (board[0][0] ==move && board[0][1] == oposite && board[0][2]==0) {
			board[0][2] = move;
		}
		else if (board[0][0] == oposite && board[0][1] == 0 && board[0][2] == oposite) {
			board[0][1] = move;
		}
		else if (board[0][0] == 0 && board[0][1] == oposite && board[0][2] == oposite) {
			board[0][0] = move;
		}
		else if (board[1][0] == oposite && board[1][1] == oposite && board[1][2] == 0) {
			board[1][2] = move;
		}
		else if (board[1][0] == oposite && board[1][1] == 0 && board[1][2] == oposite) {
			board[1][1] = move;
		}
		else if (board[1][0] == 0 && board[1][1] == oposite && board[1][2] == oposite) {
			board[1][0] = move;
		}
		else if (board[2][0] == oposite && board[2][1] == oposite && board[2][2] == 0) {
			board[2][2] = move;
		}
		else if (board[2][0] == oposite && board[2][1] == 0 && board[2][2] == oposite) {
			board[2][1] = move;
		}
		else if (board[2][0] == 0 && board[2][1] == oposite && board[2][2] == oposite) {
			board[2][0] = move;
		}

		else if (board[0][0] == oposite && board[1][0] == oposite && board[2][0] == 0) {
			board[2][0] = move;
		}
		else if (board[0][0] == oposite && board[1][0] == 0 && board[2][0] == oposite) {
			board[1][0] = move;
		}
		else if (board[0][0] == 0 && board[1][0] == oposite && board[2][0] == oposite) {
			board[0][0] = move;
		}
		else if (board[0][1] == oposite && board[1][1] == oposite && board[2][1] == 0) {
			board[2][1] = move;
		}
		else if (board[0][1] == oposite && board[1][1] == 0 && board[2][1] == oposite) {
			board[1][1] = move;
		}
		else if (board[0][1] == 0 && board[1][1] == oposite && board[2][1] == oposite) {
			board[0][1] = move;
		}
		else if (board[0][2] == oposite && board[1][2] == oposite && board[2][2] == 0) {
			board[2][2] = move;
		}
		else if (board[0][2] == oposite && board[1][2] == 0 && board[2][2] == oposite) {
			board[1][2] = move;
		}
		else if (board[0][2] == 0 && board[1][2] == oposite && board[2][2] == oposite) {
			board[0][2] = move;
		}

		else if (board[0][0] == 0 && board[1][1] == oposite && board[2][2] == oposite) {
		board[0][0] = move;
		}
		else if (board[0][0] == oposite && board[1][1] == 0 && board[2][2] == oposite) {
		board[1][1] = move;
		}
		else if (board[0][0] == oposite && board[1][1] == oposite && board[2][2] == 0) {
		board[2][2] = move;
		}
		else if (board[0][2] == 0 && board[1][1] == oposite && board[2][0] == oposite) {
		board[0][2] = move;
		}
		else if (board[0][2] == oposite && board[1][1] == 0 && board[2][0] == oposite) {
		board[1][1] = move;
		}
		else if (board[0][2] == oposite && board[1][1] == oposite && board[2][0] == 0) {
		board[2][0] = move;
		}

		else {
			int temp1 = rand() % 3;
			int temp2 = rand() % 3;
			do {
				if (board[temp1][temp2] != 0) {
					temp1 = rand() % 3;
					temp2 = rand() % 3;
				}
			} while (board[temp1][temp2] != 0);
			board[temp1][temp2] = move;
		}
	}
	turnIncrease();
}
int AI::getTurn() {
	return turn;
}
void AI::turnReset() {
	turn = 0;
}
void AI::turnIncrease() {
	turn++;
}