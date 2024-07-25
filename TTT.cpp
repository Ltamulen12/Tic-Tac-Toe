//Evaluate AI, explain how it works
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

struct tic_tac_toe {
	char board[3][3];
	char player;
	char cpu;
};

/*Creates the board for the first time and fills empty spaces with periods*/
void initalize_board(char board[3][3]) {

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			board[i][j] = '.';
		}
	}
}

/*Every time this function is called the board is printed*/
void print_board(char board[3][3]) {

	for (int i = 0; i < 3; i++) {
		cout << endl;
		for (int j = 0; j < 3; j++) {
			cout << "  ";
			cout << board[i][j];
		}
	}
	cout << endl << endl;
}


char check_win(char board[3][3]) {

	if (board[0][0] != '.' && (board[0][0] == board[0][1] && board[0][0] == board[0][2] ||
		board[0][0] == board[1][0] && board[0][0] == board[2][0] ||
		board[0][0] == board[1][1] && board[0][0] == board[2][2]))

		return board[0][0];

	if (board[1][1] != '.' && (board[1][1] == board[1][0] && board[1][1] == board[1][2] ||
		board[1][1] == board[0][1] && board[1][1] == board[2][1] ||
		board[1][1] == board[2][0] && board[1][1] == board[0][2]))

		return board[1][1];

	if (board[2][2] != '.' && (board[2][2] == board[0][2] && board[2][2] == board[1][2] ||
		board[2][2] == board[2][0] && board[2][2] == board[2][1]))

		return board[2][2];

	return 0;
}

int negamax(char board[3][3], char player, char cpu);

/*Checks the current board for the best possible move*/
int pick_best_move(char board[3][3], char player, char cpu) {

	int best_move_score = -9999;
	int best_move_row = -9999;
	int best_move_col = -9999;
	int score_for_this_move = 0;

	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (board[r][c] == '.') {
				board[r][c] = player; //Try a test move
				score_for_this_move = -(negamax(board, cpu, player));
				board[r][c] = '.'; //Put back test move
				if (score_for_this_move >= best_move_score) {
					best_move_score = score_for_this_move;
					best_move_row = r;
					best_move_col = c;
				}
			}
		}
	}
	return (10 * best_move_row + best_move_col);
}

/*Negamax calls itself and tries every possible move*/
int negamax(char board[3][3], char player, char cpu) {

	int best_move_score = -9999;
	int score_for_this_move = 0;

	//If player 1 wins, then the score is high (good for player1)
	if (check_win(board) == player)
		return 1000;

	//If player 2 loses, then the score is low (bad for player1)
	else if (check_win(board) == cpu)
		return -1000;

	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (board[r][c] == '.') {
				board[r][c] = player; //Try test move.
				score_for_this_move = -(negamax(board, cpu, player));
				board[r][c] = '.'; //Put back test move.
				if (score_for_this_move >= best_move_score) {
					best_move_score = score_for_this_move;
				}
			}
		}
	}

	if (best_move_score == -9999 || best_move_score == 0)
		return 0;

	else if (best_move_score < 0)
		return best_move_score + 1;

	else if (best_move_score > 0)
		return best_move_score - 1;
	

}

/*Allows the player to choose a space to progress the board*/
void player_move(char board[3][3], char player) {

	while (1) {
		string string_row;
		string string_col;
		int row = 0, col = 0;
		while (1) {
			cout << "Where would you like to play? " << endl;
			cout << "Enter the row: ";
			cin >> string_row;
			row = atoi(string_row.c_str());

			if (row >= 1 && row <= 3)
				break;
			cout << "You need to enter a row on the board between 1 and 3" << endl;
		}

		while (1) {
			cout << "Enter the column: ";
			cin >> string_col;
			col = atoi(string_col.c_str());

			if (col >= 1 && col <= 3)
				break;
			cout << "You need to enter a column on the board between 1 and 3" << endl;
		}
		if (board[row - 1][col - 1] == '.') {
			board[row - 1][col - 1] = player;
			break;
		}
		else
			cout << "That space is already taken" << endl << endl;
	}
}

/*Function keeps track of game progression*/
void play_game(char board[3][3], char player, char cpu) {

	int moves = 0;
	while (moves < 9) {
		player_move(board, player);
		moves++;
		print_board(board);
		if (check_win(board)) {
			cout << "You win!" << endl;
			exit(1);
		}
		if (moves == 9)
			break;
		int next_move = pick_best_move(board, cpu, player);
		int row = next_move / 10;
		int col = next_move % 10;
		board[row][col] = cpu;
		moves++;
		print_board(board);
		if (check_win(board)) {
			cout << "You lose!" << endl;
			exit(2);
		}
	}
	cout << "It's a tie!" << endl;
}
/*Main function calls all others to setup game*/
int main() {

	tic_tac_toe game;
	initalize_board(game.board);
	char choice;

	cout << "Hello! Would you like to be X's or O's? ";
	cin >> game.player;
	cout << endl;

	if (game.player == 'x' || game.player == 'X') {
		game.cpu = 'O';
	}
	if (game.player == 'o' || game.player == 'O') {
		game.cpu = 'X';
	}

	print_board(game.board);
	play_game(game.board, game.player, game.cpu);
	print_board(game.board);
	return 0;
}

