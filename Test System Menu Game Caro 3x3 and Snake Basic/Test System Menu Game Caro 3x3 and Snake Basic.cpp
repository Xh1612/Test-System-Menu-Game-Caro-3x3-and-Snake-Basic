#include <iostream>
#include <conio.h>
#include <iomanip>
using namespace std;

class Snake {
private:
	const int Height = 20;
	const int Width = 20;
	bool gameover;
	int x, y, Foodx, Foody, Score;
	int Tailx[100],Taily[100];
	int ntail;

	//STF

	enum Direce { STOP = 0 , LEFT, RIGHT, UP, DOWN};
	Direce dir;

public:
	void setup();
	bool check() { return gameover; };
	void map();
	void input();
	void logic();
};


void Snake::setup() {
	dir = STOP;
	gameover = false;
	x = 20 / 2;
	y = 20 / 2;
	Foodx = rand() % Height;
	Foody = rand() % Width;
	Score = 0;
	ntail = 0;
}

void Snake::map() {
	system("cls");
	for (int i = 0; i < Width + 2; i++)
		cout << setw(2) << "#";
	cout << endl;

	for (int j = 0; j < Height;j++) {
		for (int i = 0; i < Width; i++) {
			if (i == 0) { cout<< setw(2) << "#"; }
			if (x == i && y == j) { cout << setw(2) << "O"; }
			else if (Foodx == i && Foody == j) { cout<<setw(2) << "F"; }
			else
			{
				bool printail = false;
				for (int k = 0; k < ntail; k++) {
					if (Tailx[k] == i && Taily[k] == j) {
						cout << setw(2) << "o";
						printail = true;
					}
					
				}
				if (!printail) {
					cout << setw(2) << " ";
				}
			}
			if (i==Width - 1)
			{
				cout << setw(2) << "#";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < Width + 2; i++) {
		cout << setw(2) << "#";
	}
	cout << endl;
	cout << "Score :" << Score << endl;
}

void Snake::input() {

	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			dir = LEFT;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 'x':
			gameover = true;
			break;
		}
	}
}




void Snake::logic()
{

	//Input

	

	//Save Tail
	int prex = Tailx[0];
	int prey = Taily[0];
	int prexx, preyy;
	Tailx[0] = x;
	Taily[0] = y;
	for (int i = 1; i < ntail;i++)
	{
		prexx = Tailx[i];
		preyy = Taily[i];
		Tailx[i] = prex;
		Taily[i] = prey;
		prex = prexx;
		prey = preyy;
	}

	switch (dir)
	{
	case Snake::LEFT:
		x--;
		break;
	case Snake::RIGHT:
		x++;
		break;
	case Snake::UP:
		y--;
		break;
	case Snake::DOWN:
		y++;
		break;
	default:
		break;
	}

	// Wall

	if (y > Width - 1) y = 0;else if (y < 0) y = Width;
	if (x > Height - 1) x = 0; else if (x < 0) x = Height;

	//Condifi lose

	for (int i = 0; i < ntail ; i++)
		if (Tailx[i] == x && Taily[i] == y)
		{
			gameover = true;
		}

	//

	if (x == Foodx && y == Foody) {
		++ntail;
		Foodx = rand() % Height;
		Foody = rand() % Width;
		Score += 10;
	}

}


class caro3x3 {
private:
	char Board[3][3] = { { ' ' , ' ' , ' ' },{ ' ', ' ' , ' ' },{ ' ', ' ' , ' ' } };
	bool Check = false;
	char player = 'X';
	int col, wor;
public:
	void DrawBoard();
	
	/*void GetCheckWin(bool CheckWin) { Check = CheckWin; };*/
	bool CheckWin(char player) {
		for (int i = 0; i < 3; i++) {
			if (Board[i][0] == player && Board[i][1] == player && Board[i][2] == player)
				return true;
			if (Board[0][i] == player && Board[1][i] == player && Board[2][i] == player)
				return true;
		}
		if (Board[0][0] == player && Board[1][1] == player && Board[2][2] == player)
			return true;
		if (Board[2][0] == player && Board[1][1] == player && Board[1][2] == player)
			return true;
		return false;
	};
	void input();
	void logic();
	bool checkgame() { return Check; };
};


void caro3x3::DrawBoard() {
	cout << "-------------\n";
	for (int i = 0; i < 3; i++) {
		cout << "| ";
		for (int j = 0; j < 3; j++) {
			cout << Board[i][j] << " | ";
		}
		cout << "\n-------------\n";
	}
}

void caro3x3::input() {
	if (_kbhit())
	{
		switch (_getch()) {
		case 'x':
			Check = false;
			break;
		}
	}
}


void caro3x3::logic() {
	while (true) {


		DrawBoard();
		cin >> col >> wor;
		if (col > 3 || col < 1 || wor > 3 || wor < 1 || Board[col - 1][wor - 1] != ' ')
		{
			cout << "Error";
			continue;
		}

		Board[col - 1][wor - 1] = player;

		if (CheckWin(player))
		{
			cout << "Player " << player << "Win";
			break;
		}

		player = (player == 'X') ? 'O' : 'X';

		//input stop

		
	}

	DrawBoard();
	
}

void playCaro() {
	caro3x3 test;
	while (!test.checkgame()) {
		test.input();
		test.logic();
	}
}



void playSnake() {
    
	Snake test;
	test.setup();
	while (!test.check()) {
		test.map();
		test.input();
		test.logic();
	}

    std::cout << "Game Snake\n";
}





int main() {
    int choice;

    do {
        std::cout << "Menu:\n";
        std::cout << "1. Play Caro 3x3\n";
        std::cout << "2. Play Snake\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice (1-3): ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            playCaro();
            break;
        case 2:
            playSnake();
            break;
        case 3:
            std::cout << "Exit program...\n";
            break;
        default:
            std::cout << "Enter error. Pls enter again.\n";
        }
    } while (choice != 3);

    return 0;
}

