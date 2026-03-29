#include <iostream>
#include <windows.h>

using namespace std;

int count_w = 0;
int count_b = 0;

void show_pan(char pan[19][19], int w, int b) {  // 판 출력
	for (int i = 0; i < 19; ++i) {
		for (int j = 0; j < 19; ++j) {
			cout << pan[i][j] <<' ';
		}
		cout << endl;
	}
	cout << "@ : " << b << " # : " << w << endl; // 돌개수 카운트 출력
	return;
}
bool check_stone(char pan[19][19], int x, int y) { // 자리 비어있는지 확인
	if (pan[y][x] != '+') {
		cout << "already stone here" << endl;
		Sleep(1000);
		return false;
	}
	else {
		return true;
	}
}

void put_stone(char(& pan)[19][19], int x, int y, int& turn) {
	if (turn == 0) {
		pan[y][x] = '@';
		turn = 1;
		count_b++;
	}
	else {
		pan[y][x] = '#';
		turn = 0;
		count_w++;
	}
	return;
}

int main() {
	char pan[19][19];
	for (int i = 0; i < 19; i++) { //기본판
		for (int j = 0; j < 19; j++) {
			pan[i][j] = '+';
		}
	}
	show_pan(pan, count_w, count_b);
	int who_turn = 0; // 누구 턴인가 0 = @   1= #
	int putx;  // 돌 놓는 x 좌표
	int puty;// 돌놓은 y 좌표
	
	while (true) {
		bool check = true;
		cout << "where do you put x, y (1~18) end key : 00" << endl;
		cin >> putx >> puty; 
		cout << endl;
		if (cin.fail()) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "number please" <<endl;
		}
		if (putx == 0) {
			cout << "end good bye" << endl;
			break;
		}
		putx--;
		puty--;
		if (putx < 0 || putx>18 || puty < 0||puty>18) {
			cout << "please number only 1~19" << endl;
			check = false;
		}
		if (check) {
			if (check_stone(pan, putx, puty)) {
				put_stone(pan, putx, puty, who_turn);
			}
			system("cls");
			show_pan(pan,count_w, count_b);
			
		}
	}
	
}