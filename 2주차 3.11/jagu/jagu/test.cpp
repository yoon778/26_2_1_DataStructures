#include <iostream>
#include <string>
using namespace std;

int main() {
	string pan[19][19]; // 기본 판 만들기
	for (int i = 0; i < 19; ++i) {
		for (int j = 0; j < 19; ++j) {
			pan[i][j] = "+";
		}
	}
	
	int x; //입력할 x위치
	int y; //입력할 y위치
	int w_b_check = 0; // 백 검 돌 두기 체크/  기본 흑
	int w_num = 0;
	int b_num = 0;


	while (true) {
		

		int check_wrong = 0; // 잘못 입력 체크
		cout << " 아아 please put the number (x, y) if you want finish, you press alpha " << endl;
		cin >> x >> y;
		x -= 1;
		y -= 1;
		if (x < 0 || x >19 || y < 0 || y>19) { // 잘못 입력된다면
			cout << "wrong number you should 0~19" << endl;
			check_wrong = 1;
		}
		if (check_wrong != 1) {
			if (w_b_check == 0) {
				if (pan[y][x] == "+") {
					pan[y][x] = "@";
					w_b_check = 1; //백 1로 변경
					b_num++;
				}
				else {
					cout << "allready ston here" << endl;
					check_wrong = 1;
				}
			}
			else if (w_b_check == 1) {
				if (pan[y][x] == "+") {
					pan[y][x] = "O";
					w_b_check = 0; //흑 0로 변경
					w_num++;
				}
				else {
					cout << "allready ston here" << endl;
					check_wrong = 1;
				}
			}
		}
		if (check_wrong != 1) {
			for (int i = 0; i < 19; ++i) {
				for (int j = 0; j < 19; ++j) {
					cout << pan[i][j] << " ";
				}
				cout << endl;
			}
			cout << "Black : " << b_num << " White : " << w_num <<endl;
		}

	}

	return 0;
}