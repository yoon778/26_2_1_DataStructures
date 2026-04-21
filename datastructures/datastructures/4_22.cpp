#include <iostream>
#include <windows.h>

using namespace std;

// =====================================================================
// 1. 상태 저장용 구조체 (AI 데이터 확장 포함)
// =====================================================================
struct LineInfo {
	// [현재 시험 과제용 변수]
	int black_total; // 흑돌 총 개수
	int white_total; // 백돌 총 개수
	int max_count;   // 최대 연속 개수
	int max_color;   // 최대 연속된 돌의 색 (1: 흑, 2: 백)
	int max_start_x; // 최대 연속이 시작된 x좌표
	int max_start_y; // 최대 연속이 시작된 y좌표

	// ==========================================================
	// 🤖 [미래 AI 탑재 공간 1: 패턴 카운터]
	// 다음 주에 이곳에 열린 3목, 닫힌 3목, 4목 등의 개수를 누적할 
	// 변수들을 선언하게 됩니다. (예: int black_open_3 = 0;)
	// ==========================================================
};

// =====================================================================
// 2. 가로, 세로, 대각선 스캔 함수들
// =====================================================================

// [가로 스캔]
LineInfo scan_width_line(int pan[19][19], int y) {
	LineInfo info = { 0, 0, 0, 0, -1, -1 }; // 나중에 AI 변수들도 0으로 초기화 추가
	int state = 0;         // 이전 돌 상태
	int current_count = 0; // 현재 연속 개수

	for (int x = 0; x <= 19; ++x) { // 🚨 19까지 순회하게 하여 마지막 벽을 만나게 함 (AI 처리용 트릭)
		int stone = (x < 19) ? pan[y][x] : -1; // 19번째 인덱스는 가상의 벽(-1)으로 처리

		// 1. 전체 개수 세기 (시험 요구사항)
		if (stone == 1) info.black_total++;
		else if (stone == 2) info.white_total++;

		// 2. 상태 전이 및 AI 패턴 분석
		if (stone == state) {
			// 같은 돌이 계속 이어질 때
			if (state != 0) current_count++;
		}
		else {
			// 돌의 색이 바뀌거나 끊겼을 때 (이 순간이 방금 센 돌들을 결산할 타이밍입니다!)
			if (state != 0 && current_count > 0) {
				// ----------------------------------------------------------
				// 🤖 [미래 AI 탑재 공간 2: 열린/닫힌 공간 판정]
				// 이곳에서 방금까지 세었던 current_count가 3인지 4인지 확인하고,
				// 시작점 바로 앞 (x - current_count - 1)과 
				// 현재 막힌 위치 (x)의 값이 빈칸(0)인지 벽(-1)인지 검사하여 
				// info 구조체의 패턴 카운터를 증가시킵니다.
				// ----------------------------------------------------------

				// [현재 시험 과제용 로직] 최대값 갱신
				if (current_count > info.max_count) {
					info.max_count = current_count;
					info.max_color = state;
					info.max_start_x = x - current_count;
					info.max_start_y = y;
				}
			}
			// 새로운 돌로 상태 갱신
			state = stone;
			current_count = (stone != 0 && stone != -1) ? 1 : 0;
		}
	}
	return info;
}

// [세로 스캔]
LineInfo scan_height_line(int pan[19][19], int x) {
	LineInfo info = { 0, 0, 0, 0, -1, -1 };
	int state = 0;
	int current_count = 0;

	for (int y = 0; y <= 19; ++y) {
		int stone = (y < 19) ? pan[y][x] : -1;

		if (stone == 1) info.black_total++;
		else if (stone == 2) info.white_total++;

		if (stone == state) {
			if (state != 0) current_count++;
		}
		else {
			if (state != 0 && current_count > 0) {
				// ----------------------------------------------------------
				// 🤖 [미래 AI 탑재 공간 2: 열린/닫힌 공간 판정]
				// 세로 방향의 연속 돌(current_count) 가치 평가
				// ----------------------------------------------------------
				if (current_count > info.max_count) {
					info.max_count = current_count;
					info.max_color = state;
					info.max_start_x = x;
					info.max_start_y = y - current_count;
				}
			}
			state = stone;
			current_count = (stone != 0 && stone != -1) ? 1 : 0;
		}
	}
	return info;
}

// [우하향(↘) 대각선 스캔]
LineInfo scan_diagonal_down_right(int pan[19][19], int start_x, int start_y) {
	LineInfo info = { 0, 0, 0, 0, -1, -1 };
	int state = 0;
	int current_count = 0;

	int x = start_x, y = start_y;

	while (true) {
		int stone = (x < 19 && y < 19) ? pan[y][x] : -1;

		if (stone == 1) info.black_total++;
		else if (stone == 2) info.white_total++;

		if (stone == state) {
			if (state != 0) current_count++;
		}
		else {
			if (state != 0 && current_count > 0) {
				// ----------------------------------------------------------
				// 🤖 [미래 AI 탑재 공간 2: 열린/닫힌 공간 판정]
				// 우하향 대각선 방향의 연속 돌 가치 평가
				// ----------------------------------------------------------
				if (current_count > info.max_count) {
					info.max_count = current_count;
					info.max_color = state;
					info.max_start_x = x - current_count;
					info.max_start_y = y - current_count;
				}
			}
			state = stone;
			current_count = (stone != 0 && stone != -1) ? 1 : 0;
		}

		if (x >= 19 || y >= 19) break; // 가상의 벽까지 처리 후 루프 종료
		x++; y++;
	}
	return info;
}

// [좌하향(↙) 대각선 스캔]
LineInfo scan_diagonal_down_left(int pan[19][19], int start_x, int start_y) {
	LineInfo info = { 0, 0, 0, 0, -1, -1 };
	int state = 0;
	int current_count = 0;

	int x = start_x, y = start_y;

	while (true) {
		int stone = (x >= 0 && y < 19) ? pan[y][x] : -1;

		if (stone == 1) info.black_total++;
		else if (stone == 2) info.white_total++;

		if (stone == state) {
			if (state != 0) current_count++;
		}
		else {
			if (state != 0 && current_count > 0) {
				// ----------------------------------------------------------
				// 🤖 [미래 AI 탑재 공간 2: 열린/닫힌 공간 판정]
				// 좌하향 대각선 방향의 연속 돌 가치 평가
				// ----------------------------------------------------------
				if (current_count > info.max_count) {
					info.max_count = current_count;
					info.max_color = state;
					info.max_start_x = x + current_count;
					info.max_start_y = y - current_count;
				}
			}
			state = stone;
			current_count = (stone != 0 && stone != -1) ? 1 : 0;
		}

		if (x < 0 || y >= 19) break;
		x--; y++;
	}
	return info;
}

// =====================================================================
// 3. 게임 진행 기본 함수들
// =====================================================================
void show_pan(int pan[19][19], int countw, int countb) {
	for (int i = 0; i < 19; ++i) {
		for (int j = 0; j < 19; ++j) {
			if (pan[i][j] == 0) cout << "+ ";
			else if (pan[i][j] == 1) cout << "# ";
			else if (pan[i][j] == 2) cout << "@ ";
		}
		cout << endl;
	}
	cout << "@(백) : " << countw << "  #(흑) : " << countb << endl;
}

bool check_stone(int pan[19][19], int x, int y) {
	if (pan[y][x] != 0) {
		cout << "이미 돌이 놓여 있습니다" << endl;
		Sleep(800);
		return false;
	}
	else return true;
}

void put_stone(int pan[19][19], int x, int y, int& turn, int& countw, int& countb) {
	if (turn == 0) { pan[y][x] = 1; turn = 1; countb++; }
	else { pan[y][x] = 2; turn = 0; countw++; }
}

// =====================================================================
// 4. 메인 로직
// =====================================================================
int main() {
	int pan[19][19] = { 0 };
	int stone_turn = 0;
	int put_x, put_y;
	int countw = 0, countb = 0;

	while (true) {
		system("cls");
		show_pan(pan, countw, countb);

		cout << "\n[데이터 분석 보고서] (콘솔 가독성을 위해 연속 돌이 2개 이상인 곳만 출력)" << endl;

		// 1. 가로줄 분석
		for (int y = 0; y < 19; ++y) {
			LineInfo res = scan_width_line(pan, y);
			if (res.max_count >= 2) {
				cout << "[가로 " << y << "줄] -> 흑: " << res.black_total << "개, 백: " << res.white_total << "개";
				cout << " | 최대 연속: " << (res.max_color == 1 ? "흑" : "백") << "돌 " << res.max_count << "개 (★돌 시작 좌표: " << res.max_start_x << ", " << res.max_start_y << ")\n";
			}
		}

		// 2. 세로줄 분석
		for (int x = 0; x < 19; ++x) {
			LineInfo res = scan_height_line(pan, x);
			if (res.max_count >= 2) {
				cout << "[세로 " << x << "줄] -> 흑: " << res.black_total << "개, 백: " << res.white_total << "개";
				cout << " | 최대 연속: " << (res.max_color == 1 ? "흑" : "백") << "돌 " << res.max_count << "개 (★돌 시작 좌표: " << res.max_start_x << ", " << res.max_start_y << ")\n";
			}
		}

		// 3. 우하향(↘) 대각선 분석
		for (int i = 0; i < 19; ++i) {
			LineInfo res1 = scan_diagonal_down_right(pan, i, 0); // 윗변
			if (res1.max_count >= 2) {
				cout << "[우하향(↘) 궤도: " << i << ", 0] -> 최대 연속: " << (res1.max_color == 1 ? "흑" : "백") << "돌 " << res1.max_count << "개 (★돌 시작 좌표: " << res1.max_start_x << ", " << res1.max_start_y << ")\n";
			}

			if (i > 0) {
				LineInfo res2 = scan_diagonal_down_right(pan, 0, i); // 왼쪽 변
				if (res2.max_count >= 2) {
					cout << "[우하향(↘) 궤도: 0, " << i << "] -> 최대 연속: " << (res2.max_color == 1 ? "흑" : "백") << "돌 " << res2.max_count << "개 (★돌 시작 좌표: " << res2.max_start_x << ", " << res2.max_start_y << ")\n";
				}
			}
		}

		// 4. 좌하향(↙) 대각선 분석
		for (int i = 0; i < 19; ++i) {
			LineInfo res1 = scan_diagonal_down_left(pan, i, 0); // 윗변
			if (res1.max_count >= 2) {
				cout << "[좌하향(↙) 궤도: " << i << ", 0] -> 최대 연속: " << (res1.max_color == 1 ? "흑" : "백") << "돌 " << res1.max_count << "개 (★돌 시작 좌표: " << res1.max_start_x << ", " << res1.max_start_y << ")\n";
			}

			if (i > 0) {
				LineInfo res2 = scan_diagonal_down_left(pan, 18, i); // 오른쪽 변
				if (res2.max_count >= 2) {
					cout << "[좌하향(↙) 궤도: 18, " << i << "] -> 최대 연속: " << (res2.max_color == 1 ? "흑" : "백") << "돌 " << res2.max_count << "개 (★돌 시작 좌표: " << res2.max_start_x << ", " << res2.max_start_y << ")\n";
				}
			}
		}
		cout << "-----------------------------------------------------\n" << endl;

		// 5. 플레이어 입력
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
	}
	return 0;
}