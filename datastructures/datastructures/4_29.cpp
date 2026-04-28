#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

struct champion {
	string name;
	int hp;
	int mp;
	int speed;
	int range;
	string position;
};
int cham_pos = 0;
champion champions[50] = {};



struct pointer_champion {
	string name;
	int hp;
	int mp;
	int speed;
	int range;
	string position;
	pointer_champion* next;
};

string todown(string str) {
	for (int i = 0; i < str.length(); ++i) {
		str[i] = tolower(str[i]);
	}
	return str;
}
// 리스트로 바꾸기
pointer_champion* start = NULL;
void move_array_to_list() {
	pointer_champion* tail = NULL;
	for (int i = 0; i < cham_pos; ++i) {
		// 일단 자료 옮기기
		pointer_champion* new_node = new pointer_champion;
		new_node->name = champions[i].name;
		new_node->hp = champions[i].hp;
		new_node->mp = champions[i].mp;
		new_node->speed = champions[i].speed;
		new_node->range = champions[i].range;
		new_node->position = champions[i].position;
		new_node->next = NULL;

		// 처음이면
		if (start == NULL) {
			start = new_node;
			tail = new_node;
		}
		else {
			tail->next = new_node;
			tail = new_node;
		}
	}
	if (tail != NULL) {
		tail->next = start;
	}
}
void print_cham(pointer_champion* cham) {
	cout << "이름 : [" << cham->name << "] hp : [" << cham->hp << "] mp : [" << cham->mp << "] speed : [" << cham->speed << "] range : [" << cham->range << "] position : [" << cham->position << ']' << endl;
}

// 이름 찾기 
void search_name(string name) {
	if (start == NULL) { // ★ 잊지 말고 추가!
		cout << "등록된 챔피언이 없습니다." << endl;
		return;
	}
	pointer_champion* now_node = start;
	do {
		if (todown(now_node->name) == todown(name)) {
			print_cham(now_node);
			return;
		}
		now_node = now_node->next;
	} while (now_node != start);
	cout << name << "이라는 챔피언은 없습니다" << endl;
	return;
}
// max hp 찾기
int find_max_hp() {
	if (start == NULL) return 0;
	pointer_champion* now_node = start;
	int max_hp = start->hp; // 0 대신 첫 노드의 HP로 시작

	do {
		if (now_node->hp > max_hp) {
			max_hp = now_node->hp;
		}
		now_node = now_node->next;
	} while (now_node != start); // next가 아니라 본인 확인
	return max_hp;
}
void print_max_hp() {
	if (start == NULL) return;
	pointer_champion* now_node = start;
	int max_hp = find_max_hp();
	do {
		if (now_node->hp == max_hp) {
			print_cham(now_node);
		}
		now_node = now_node->next;
	} while (now_node != start);
}

// 삭제
void delete_cham(string name) {
	if (start == NULL) {
		return;
	}
	pointer_champion* pre_node = start;
	while (pre_node ->next != start) {
		pre_node = pre_node->next;
	}
	pointer_champion* now_node = start;
	
	do {
		if (todown(now_node->name) == todown(name)) {
			pointer_champion* target = now_node;
			// 1개 남으면
			if (now_node -> next== now_node) {
				start = NULL;
				delete(target);
				return;
			}
			//첫번째면
			if (now_node == start) {
				start = now_node->next;
				pre_node->next = start;
			}
			else {
				pre_node->next = now_node->next;
			}
			now_node = now_node->next;
			delete(target);
		}
		else {
			pre_node = now_node;
			now_node = now_node->next;
		}
	} while (now_node != start);
}

// 삭제 all
void delete_all_cham(string position) {
	if (start == NULL) return;

	int count = 1; 
	pointer_champion* pre_node = start;

	while (pre_node->next != start) {
		count++;                   // 다음 칸으로 갈 때마다 카운트 증가
		pre_node = pre_node->next; // 꼬리를 향해 전진
	}

	pointer_champion* now_node = start;

	// 2. 찾아낸 개수(count)만큼만 안전하게 삭제 순회
	for (int i = 0; i < count; ++i) {
		if (todown(now_node->position) == todown(position)) {
			pointer_champion* target = now_node;

			if (now_node->next == now_node) {
				start = NULL;
				delete target;
				return;
			}

			if (now_node == start) {
				start = now_node->next;
				pre_node->next = start;
			}
			else {
				pre_node->next = now_node->next;
			}

			now_node = now_node->next;
			delete target;
		}
		else {
			pre_node = now_node;
			now_node = now_node->next;
		}
	}
}

void insert_sl(string name, int hp, int mp, int speed, int range, string position) {
	// 1. 새로운 노드 생성 및 데이터 설정
	pointer_champion* new_node = new pointer_champion;
	new_node->name = name;
	new_node->hp = hp;
	new_node->mp = mp;
	new_node->speed = speed;
	new_node->range = range;
	new_node->position = position;

	// 상황 1: 리스트가 완전히 비어있는 경우
	if (start == NULL) {
		start = new_node;
		new_node->next = start; // 자기 자신을 가리켜 환형 유지
		return;
	}

	// 꼬리(tail) 찾기 (맨 앞 삽입 시 필요)
	pointer_champion* pre_node = start;
	while (pre_node->next != start) {
		pre_node = pre_node->next;
	}

	// 상황 2: 새 노드가 현재 머리(start)보다 HP가 커서 맨 앞에 와야 하는 경우
	if (new_node->hp > start->hp) {
		new_node->next = start;
		start = new_node;
		pre_node->next = start; // 꼬리가 새로운 머리를 가리키게 함
		return;
	}

	// 상황 3: 중간 또는 끝에 삽입되는 경우
	pointer_champion* now_node = start;
	pointer_champion* prev = pre_node; // 탐색을 위한 이전 노드 추적

	// HP가 나보다 작은 놈을 찾을 때까지 전진
	do {
		if (new_node->hp > now_node->hp) {
			break; // 끼어들 자리 발견
		}
		prev = now_node;
		now_node = now_node->next;
	} while (now_node != start);

	// 노드 연결 (다리 잇기)
	prev->next = new_node;
	new_node->next = now_node;
}

//sort
void sort_cham() {
	if (start == NULL || start->next == start) return;

	int count = 1;
	pointer_champion* temp = start;
	while (temp->next != start) {
		count++;
		temp = temp->next;
	}

	for (int i = 0; i < count - 1; ++i) {

		// 매 회전이 시작될 때마다 꼬리(tail)를 다시 찾습니다.
		pointer_champion* tail = start;
		while (tail->next != start) {
			tail = tail->next;
		}

		// 3개의 포인터 나란히 세팅 (앞, 중간, 뒤)
		pointer_champion* pre_node = tail;         
		pointer_champion* now_node = start;       
		pointer_champion* next_node = start->next; 

		// 가장 큰 값이 맨 뒤로 밀려나므로, 최적화를 위해 -i 만큼 뺍니다.
		for (int j = 0; j < count - 1 - i; ++j) {

			// 오름차순 (앞의 HP가 뒤의 HP보다 크면 자리를 바꿈!)
			if (now_node->hp < next_node->hp) {

				// ★ 노드 스왑 3단계 공식 (다리 끊고 다시 잇기)
				pre_node->next = next_node;        // 1. 앞칸을 뒷칸에 연결
				now_node->next = next_node->next;  // 2. 현재칸을 다다음칸에 연결
				next_node->next = now_node;        // 3. 뒷칸을 현재칸에 연결

				// ★ 만약 자리를 바꾼 애가 머리(start)였다면, 머리 푯말도 옮겨줍니다.
				if (now_node == start) {
					start = next_node;
				}

				// 스왑이 끝난 후 포인터 전진:
				// 위치가 물리적으로 (pre -> next -> now) 순서가 되었으므로, 
				// now_node는 가만히 두고 나머지만 재설정합니다.
				pre_node = next_node;
				next_node = now_node->next;
			}
			else {
				// 자리를 안 바꿨을 때는 셋 다 나란히 한 칸씩 전진
				pre_node = now_node;
				now_node = next_node;
				next_node = next_node->next;
			}
		}
	}
}


void print_all_cham() {
	if (start == NULL) { // ★ 예외 처리 추가
		cout << "현재 등록된 챔피언이 없습니다." << endl;
		return;
	}
	pointer_champion* now_node = start;
	do {
		print_cham(now_node);
		now_node = now_node->next;
	} while (now_node != start);
}

int main() {
	
	ifstream fin("testdata.txt");
	if (!fin.is_open()) {
		cout << "파일이 없습니다" << endl;
		return 0;
	}
	while (getline(fin, champions[cham_pos].name, '\t')) {
		fin >> champions[cham_pos].hp >> champions[cham_pos].mp >> champions[cham_pos].speed >> champions[cham_pos].range >> champions[cham_pos].position;
		fin.ignore(1000, '\n');
		cham_pos++;
		if (cham_pos >= 50) {
			cout << "챔피언은 50개 까지 가능합니다" << endl;
			break;
		}
	}
	fin.close();

	move_array_to_list(); // 리스트로 만들기

	if (start == NULL) {
		cout << "정보가 없습니다 insert를 해주세요" << endl;
	}
	while (true) {
		cout << "명령어를 입력해주세요 / Search_SL / Insert_SL / Delete_SL / Deleteall_SL / PrintAll_SL / FindMaxHp_SL / SortByHp_SL" << endl;
		string commend;
		getline(cin, commend);
		commend = todown(commend);
		if (commend == "search_sl") {
			cout << "이름 : ";
			string name;
			getline(cin, name);
			search_name(name);
		}
		else if (commend == "insert_sl") {
			string name;
			int hp;
			int mp;
			int speed;
			int range;
			string position;
			cout << "이름";
			getline(cin, name);
			cout << "hp ";
			cin >> hp;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력해주세요" << endl;
				continue;
			}
			cout << "mp ";
			cin >> mp;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력해주세요" << endl;
				continue;
			}
			cout << "speed ";
			cin >> speed;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력해주세요" << endl;
				continue;
			}
			cout << "range";
			cin >> range;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력해주세요" << endl;
				continue;
			}
			cin.ignore(1000, '\n');
			cout << "position";
			getline(cin, position);
			insert_sl(name, hp, mp, speed, range, position);
		}
		else if (commend == "delete_sl") {
			cout << "name : ";
			string name;
			getline(cin, name);
			delete_cham(name);
		}
		else if (commend == "deleteall_sl") {
			cout << "position : ";
			string position;
			getline(cin, position);
			delete_all_cham(position);
		}
		else if (commend == "printall_sl") {
			print_all_cham();
		}
		else if (commend == "findmaxhp_sl") {
			print_max_hp();
		}
		else if (commend == "sortbyhp_sl") {
			sort_cham();
		}
		else {
			cout << "잘못된 명령어 입니다" << endl;
		}
	}

	return 0;
}