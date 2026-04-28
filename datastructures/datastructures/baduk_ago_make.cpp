#include <iostream>
#include <windows.h>

using namespace std;

void show_pan(int pan[19][19], int countw, int countb) {
	for (int i = 0; i < 19; ++i) {
		for (int j = 0; j < 19; ++j) {
			if (pan[i][j] == 0) cout << "+ ";
			else if (pan[i][j] == 1) cout << "# "; // 흑
			else if (pan[i][j] == 2) cout << "@ "; // 백
		}
		cout << endl;
	}
	cout << "@(백) : " << countw << "  #(흑) : " << countb << endl;
}

bool check_stone(int pan[19][19], int x, int y) {
	if (pan[y][x] != 0) {
		cout << "이미 돌이 있습니다" << endl;
		Sleep(800);
		return false;
	}
	else {
		return true;
	}
}

void put_stone(int pan[19][19], int x, int y, int& turn, int& countw, int& countb) {
	if (turn == 0) { // 흑
		pan[y][x] = 1;
		turn = 1;
		countb++;
	}
	else { // 백
		pan[y][x] = 2;
		turn = 0;
		countw++;
	}
}

int main() {
	int pan[19][19] = { 0 };

	int stone_turn = 0;
	int put_x, put_y;
	int countw = 0;
	int countb = 0;

	while (true) {
		system("cls");
		show_pan(pan, countw, countb);

		cout << "돌을 놓을 좌표를 입력하시오 좌표는 (0,0) 부터 (18,18) 까지 있습니다." << endl;
		cin >> put_x >> put_y;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "숫자만 입력해주세요" << endl;
			Sleep(800);
			continue;
		}

		if (put_x < 0 || put_x > 18 || put_y < 0 || put_y > 18) {
			cout << "숫자는 (0, 0) 부터 (18, 18) 까지 있습니다" << endl;
			Sleep(800);
			continue;
		}

		if (check_stone(pan, put_x, put_y)) {
			put_stone(pan, put_x, put_y, stone_turn, countw, countb);
		}
		else {
			continue;
		}
	}

	return 0;
}