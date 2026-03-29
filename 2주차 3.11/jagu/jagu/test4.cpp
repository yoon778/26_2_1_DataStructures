#include <iostream>
#include <windows.h>

using namespace std;


void show_pan(char pan[19][19], int wcount, int bcount) {  //판 출력
	for (int i = 0; i < 19; ++i) {
		for (int j = 0; j < 19; ++j) {
			cout << pan[i][j] << ' ';
		}
		cout << endl;
	}
	cout << "@(백돌) : " << wcount << "개  #(흑돌) : " << bcount << endl;
}

bool stone_check(char pan[19][19], int x, int y) { // 판에 놓을 곳이 비었는지
	if (pan[y][x] != '+') {
		cout << "이미 돌이 놓여 있습니다" << endl;
		Sleep(700);
		return false;
	}
}

void put_pan(char (& pan)[19][19], int x, int y, int& turn , int &wcoun, int &bcoun) {
	if (turn == 0) {
		pan[y][x] = '@';
		turn = 1;
		wcoun++;
	}
	else {
		pan[y][x] = '#';
		turn = 0;
		bcoun++;
	}
}

int main() {
	int stone_turn = 0; // 돌 순서 0 @  / 1 #
	
	char pan[19][19]; // 기본적인 판
	for (int i = 0; i < 19; ++i) { //판에 + 넣기
		for (int j = 0; j < 19; ++j) {
			pan[i][j] = '+';
		}
	}

	int w_count = 0;
	int b_count = 0;
	while (true) {
		int check = 0; //0은 문제점 미발생 1은 문제 발생


		system("cls");
		show_pan(pan, w_count, b_count);


		int put_x, put_y;  // 돌 놓을 위치

		cout << "돌을 놓을 자리 (1,1) 부터 (19,19) 까지 중에 입력해주새요(백돌 @, 흑돌 #)  / 종료는 숫자 0 0 을 눌러주세요" << endl;
		cin >> put_x >> put_y;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "숫자만 입력해주세요" << endl;
			Sleep(700);
			continue;
		}
		if (put_x == 0 && put_y == 0) {
			cout << "종료됩니다" << endl;
			Sleep(700);
			return 0;
		}
		if (put_x < 1 || put_x >19 || put_y < 1 || put_y >19) {
			cout << "1부터 19중까지 중에 입력해수세요." << endl;
			check = 1;
			Sleep(700);
		}

		--put_x; --put_y; //x랑 y 좌표값으로 만들기
		if (check == 0) {
			if (stone_check(pan, put_x, put_y)) {
				put_pan(pan, put_x, put_y, stone_turn, w_count, b_count);
			}
		}

	}

	return 0;
}