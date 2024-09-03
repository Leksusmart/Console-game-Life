#include <iostream>
#include <thread>
using namespace std;

bool World[10][118];
bool LastWorld[10][118];
const bool dead = false;
const bool alive = true;
int Gcounter = 0;
bool survive = true;
int matchCounter = 0;
int matchCounter2 = 0;


void PrintWorld() {
	cout << "Поколение " << Gcounter<<endl;
	cout << " ";
	for (int i = 0; i < 117; i++) {
		cout << "-";
	}
	cout << " " << endl;
	for (int i = 0; i < 10; i++) {
		cout << "|";
		for (int j = 0; j < 118; j++) {
			char h = 'O';
			if (World[i][j] == alive) cout << h;
			else cout << " ";
		}
		cout <<"|" << endl;
	}
	cout << " ";
	for (int i = 0; i < 117; i++) {
		cout << "-";
	}
	cout << " " << endl << endl;
	Gcounter++;
}
void check() {
	bool BufWorld[10][118];
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 118; j++) {
			BufWorld[i][j] = dead;
		}
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 118; j++) {
			int aliveCounter = 0;
			if ((i - 1) >= 0 && (j - 1) >=0 && World[i - 1][j - 1] == alive)aliveCounter++;
			if ((i - 1) >= 0 && World[i - 1][j] == alive)aliveCounter++;
			if ((i - 1) >= 0 && (j + 1) <= 118 && World[i - 1][j + 1] == alive)aliveCounter++;

			if ((j - 1) >= 0 && World[i][j - 1] == alive)aliveCounter++;
			if ((j + 1) <= 118 && World[i][j + 1] == alive)aliveCounter++;

			if ((i + 1) <= 10 && (j - 1) >= 0 && World[i + 1][j - 1] == alive)aliveCounter++;
			if ((i + 1) <= 10 && World[i + 1][j] == alive)aliveCounter++;
			if ((i + 1) <= 10 && (j + 1) <= 118 && World[i + 1][j + 1] == alive)aliveCounter++;

			if (World[i][j] == dead) {
				if (aliveCounter == 3)BufWorld[i][j] = alive;
			}
			else {
				if (aliveCounter == 2 || aliveCounter == 3)
					BufWorld[i][j] = alive;
				else BufWorld[i][j] = dead;
			}
		}
	}
	matchCounter = 0;
	matchCounter2 = 0;
	survive = false;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 118; j++) {
			if (World[i][j] == BufWorld[i][j])matchCounter++;
			if (LastWorld[i][j] == BufWorld[i][j])matchCounter2++;
			LastWorld[i][j] = World[i][j];
			World[i][j] = BufWorld[i][j];
			if (World[i][j] == alive)survive = true;
		}
	}
}
void start(int x, int y) {
	//? ? ?
	//? ? ?
	//? ? ?

	if ((y - 1) >= 0 && (x - 1) >= 0) if (rand() % 2)World[y - 1][x - 1] = alive;
	if ((y - 1) >= 0)if (rand() % 2)World[y - 1][x] = alive;
	if ((y - 1) >= 0 && (x + 1) <= 118)if (rand() % 2)World[y - 1][x + 1] = alive;

	if ((x - 1) >= 0)if (rand() % 2)World[y][x - 1] = alive;
	if (rand() % 2)World[y][x] = alive;
	if ((y + 1) <= 118)if (rand() % 2)World[y][x + 1] = alive;

	if ((y + 1) <= 10 && (x - 1) >= 0)if (rand() % 2)World[y + 1][x - 1] = alive;
	if ((y + 1) <= 10)if (rand() % 2)World[y + 1][x] = alive;
	if ((y + 1) <= 10 && (x + 1) <= 118)if (rand() % 2)World[y + 1][x + 1] = alive;
}
int main() {
	setlocale(LC_ALL, "ru");
	srand(time(NULL));
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 118; j++) {
			World[i][j] = dead;
		}
	}
	cout << "Добро пожаловать в Игру в \"Жизнь\"!\n" << "Чтобы начать введите координаты начала колонии y-[0;10] x-[0;118]\nCтартовое поколение будет выбрано рандомно" << endl;
	int x, y;
	cin >> y >> x;
startGameLink:
	Gcounter = 0;
	survive = true;
	matchCounter = 0;
	matchCounter2 = 0;
	if(x>= 0 && x <=118 && y >=0 &&y<=10)start(x, y);
	else {
		cout << "Данные координаты лежат за пределами области игры,\nпоэтому будут выбраны базовые координаты\n";
		this_thread::sleep_for(chrono::seconds(3));
		start(59, 5);
	}
	PrintWorld();
	bool k = false;
	while (survive) {
		check();
		PrintWorld();
		if ((matchCounter == 1180 || matchCounter2 == 1180) && k) {
			cout << "\t\t\t\t\tВаша колония застряла в бесконечном цикле..\a"<<endl;
			cout << "Хотите начать заново?\n";
			system("pause");
			goto startGameLink;
		}
		else if (matchCounter == 1180 || matchCounter2 == 1180) k = true;
		this_thread::sleep_for(chrono::seconds(1));
	}
	cout << "\t\t\t\t\t\tКолония вымерла\a"<<endl;
	cout << "Хотите начать заново?\n";
	system("pause");
	goto startGameLink;
}