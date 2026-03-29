#include <iostream>
#include <windows.h>
using namespace std;
void show_pan(char pan[19][19], int count_a, int count_b) {
	for (int i = 0; i < 19; ++i) {
		for (int j = 0; j < 19; ++j) {
			cout << pan[i][j] << ' ';
		}
		cout << endl;
	}
	cout << "@ : " << count_a << " # : " << count_b << endl;
	return;
}
void put_stone(char(& pan)[19][19],int& turn, int x, int y, int &count_a, int &count_b) {
	if (pan[y][x] != '+') {
		cout << "이미 돌이 놓여 있습니다" << endl;
		Sleep(500);
		return ;
	}
	if (turn == 1) {
		pan[y][x] = '@'; // 흑돌
		turn = 0;
		count_a++;
		return;
	}
	else {
		pan[y][x] = '#'; //백돌
		turn = 1;
		count_b++;
		return;
		
	}
	
}
int main() {
	char pan[19][19]; //기본 판
	for (int i = 0; i < 19; ++i) {//기본 판 + 넣기
		for (int j = 0; j < 19; ++j) {
			pan[i][j] = '+';
		}
	}
	int who_turn = 1; // 시자 1: @    다음  0 :#
	int count_a = 0;
	int count_b = 0;
	int put_x, put_y; // 입력받는 x y 좌표
	while (true) {
		system("cls");
		show_pan(pan, count_a, count_b);
		bool check = true;
		cout << "넣고 싶은 번호를 넣으시오 (1~19) 종료키는 숫자 00" << endl;
		cin >> put_x >> put_y;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "숫자만 가능" << endl;
			Sleep(1000);
			continue;
		}
		if (put_x == 0 && put_y == 0) {
			return 0;
		}
		put_x--; put_y--; // 입력받은 값 좌표로 변환
		
		if (put_x < 0 || put_x >18 || put_y < 0 || put_y>18) {
			cout << "범위는 1~19" << endl;
			Sleep(1000);
			check = false;
			continue;
		}
		if (check) {
			put_stone(pan, who_turn, put_x, put_y, count_a, count_b);
			system("cls");
			show_pan(pan, count_a, count_b);
		}
	}
	return 0;
}