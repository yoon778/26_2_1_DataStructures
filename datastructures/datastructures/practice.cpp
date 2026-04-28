#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

struct champions {
	string name;
	int hp;
	int mp;
	int speed;
	int range;
	string position;
};

champions champion[50] = {};
int cham_count = 0;

string to_down(string str) {
	for (int i = 0; i < str.length(); ++i) {
		str[i] = tolower(str[i]);
	}
	return str;
}


struct pointer_cham {
	string name;
	int hp;
	int mp;
	int speed;
	int range;
	string position;
	pointer_cham* next;
};
pointer_cham* start = NULL;

void change_pointer() {
	pointer_cham* tail = NULL;
	for (int i = 0; i < cham_count; ++i) {
		pointer_cham* new_cham = new pointer_cham;
		new_cham->name = champion[i].name;
		new_cham->hp = champion[i].hp;
		new_cham->mp = champion[i].mp;
		new_cham->speed = champion[i].speed;
		new_cham->range = champion[i].range;
		new_cham->position = champion[i].position;
		new_cham->next = NULL;

		if (i == 0) {
			start = new_cham;
			tail = new_cham;
		}
		else {
			tail->next = new_cham;
			tail = new_cham;
		}
	}
	if (tail != NULL) {
		tail->next = start;
	}
}

void print_cham(pointer_cham*cham) {
	if (cham == NULL) {
		return;
	}
	cout << "이름 : " << cham->name << " hp : " << cham->hp << " mp : " << cham->mp << " speed : " << cham->speed << " range : " << cham->range <<  " position : " << cham->position << endl;
}

void printall_cham() {
	pointer_cham* now_node = start;
	if (start == NULL) {
		cout << "정보가 없습니다" << endl;
		return;
	}
	do {
		print_cham(now_node);
		now_node = now_node->next;
	} while (now_node != start);
}

void search_cham(string name) {
	pointer_cham* now_node = start;
	if (start == NULL) {
		cout << "정보가 없습니다" << endl;
		return;
	}
	do {
		if (to_down(now_node->name) == to_down(name)) {
			print_cham(now_node);
			break;
		}
		now_node = now_node->next;
	} while (now_node != start);
}

void delete_cham(string name) {
	if (start == NULL) {
		cout << "정보가 없습니다" << endl;
		return;
	}
	pointer_cham* pre_node = start;
	int count = 1;
	while (pre_node->next != start) {
		pre_node = pre_node->next;
		count++;
	}

	pointer_cham* now_node = start;
	for (int i = 0; i < count; ++i) {
		pointer_cham* target = now_node;
		if (to_down(now_node->name) == to_down(name)) {
			if (now_node->next == now_node) {
				start = NULL;
				delete(now_node);
				return;
			}
			if (now_node == start) { // 처음이면
				start = start->next;
				pre_node->next = start;
			}
			else {
				pre_node->next = now_node->next;
				
			}
			now_node = now_node-> next;
			delete(target);
			return ;
		}
		else {
			pre_node = pre_node->next;
			now_node = now_node->next;
		}
	}while (now_node != start);
	cout << name << "이라는 챔피언은 없스니다" << endl;
}

void deleteall_cham(string position) {
	if (start == NULL) {
		cout << "정보가 없습니다" << endl;
		return;
	}
	pointer_cham* pre_node = start;
	int count = 1;
	while (pre_node->next != start) {
		pre_node = pre_node->next;
		count++;
	}

	pointer_cham* now_node = start;
	for (int i = 0; i < count; ++i) {
		pointer_cham* target = now_node;
		if (to_down(now_node->position) == to_down(position)) {
			if (now_node->next == now_node) {
				start = NULL;
				delete(now_node);
				return;
			}
			if (now_node == start) { // 처음이면
				start = start->next;
				pre_node->next = start;
			}
			else {
				pre_node->next = now_node->next;
			}
			now_node = now_node->next;
			delete(target);
		}
		else {
			pre_node = pre_node->next;
			now_node = now_node->next;
		}
	}while (now_node != start);
}

int find_hp() {
	if (start == NULL) {
		cout << "정보가 없습니다" << endl;
		return 0;
	}
	pointer_cham* now_node = start;
	int max_hp = 0;
	do {
		if (now_node->hp > max_hp) {
			max_hp = now_node->hp;
		}
		now_node = now_node->next;
	} while (now_node != start);
	return max_hp;
}
void print_max_hp() {
	if (start == NULL) {
		cout << "정보가 없습니다" << endl;
		return;
	}
	pointer_cham* now_node = start;
	int max_hp = find_hp();
	do {
		if (now_node->hp == max_hp) {
			print_cham(now_node);
		}
		now_node = now_node->next;
	} while (now_node != start);
}
void sort_cham() {
	if (start == NULL) {
		cout << "정보가 없습니다" << endl;
		return;
	}
	pointer_cham* temp_node = start;
	int count = 1;
	while (temp_node->next != start) {
		temp_node = temp_node->next;
		count++;
	}

	for (int i = 0; i < count-1; ++i) {
		pointer_cham* pre_node = start;
		while (pre_node->next != start) {
			pre_node = pre_node->next;
		}
		pointer_cham* now_node = start;
		pointer_cham* next_node = start->next;

		for (int j = 0; j < count-1; ++j) {
			if (now_node->hp < next_node->hp) {
				pre_node->next = next_node;
				now_node->next = next_node->next;
				next_node->next = now_node;

				if (now_node == start) {
					start = next_node;
				}
				pre_node = next_node;
				next_node = now_node->next;
			}
			else {
				pre_node = now_node;
				now_node = next_node;
				next_node = next_node->next;
			}
		}
	}
}

void insert_cham(string name, int hp, int mp, int speed, int range, string position) {
	if (start == NULL) {
		cout << "정보가 없습니다" << endl;
		return;
	}
	pointer_cham* new_cham = new pointer_cham;
	new_cham->name = name;
	new_cham->hp = hp;
	new_cham->mp = mp;
	new_cham->speed = speed;
	new_cham->range = range;
	new_cham->position = position;
	new_cham->next = NULL;

	pointer_cham* pre_node = start;
	while (pre_node->next != start) {
		pre_node = pre_node->next;
	}
	pointer_cham* now_node = start;
	do {
		if (now_node->hp < new_cham->hp) {
			if (now_node == start) {
				start = new_cham;
				new_cham->next = now_node;
				pre_node->next = new_cham;
			}
			else {
				pre_node->next = new_cham;
				new_cham->next = now_node;
			}
			break;
		}
		pre_node = now_node;
		now_node = now_node->next;
	} while (now_node != start);
}

int main() {
	ifstream fin("testdata.txt");
	if (!fin.is_open()) {
		cout << "파일이 없습니다" << endl;
		return 0;
	}
	while (getline(fin, champion[cham_count].name, '\t')) {
		fin >> champion[cham_count].hp >> champion[cham_count].mp >> champion[cham_count].speed >> champion[cham_count].range >> champion[cham_count].position;
		fin.ignore(1000,'\n');
		cham_count++;
		if (cham_count >= 50) {
			cout << "50개 까지 저장 가능합니다" << endl;
			break;
		}
	}
	fin.close();

	change_pointer();

	
	while (true) {
		cout << "명령어 입력(소문자도 가능) / search_sl/ insert_sl / delete_sl / deleteall_sl / printall_sl/ findmaxhp_sl/ sortbyhp_sl" << endl;
		string commend;
		getline(cin, commend);
		commend = to_down(commend);

		if (commend == "search_sl") {
			cout << "이름 : ";
			string name;
			getline(cin, name);
			search_cham(name);
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
		
			insert_cham(name, hp, mp, speed, range, position);
		}
		else if (commend == "delete_sl") {
			cout << "이름 : ";
			string name;
			getline(cin, name);
			delete_cham(name);
		}
		else if (commend == "deleteall_sl") {
			cout << "position : ";
			string position;
			getline(cin, position);
			deleteall_cham(position);
		}
		else if (commend == "printall_sl") {
			printall_cham();
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