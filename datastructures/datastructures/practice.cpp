#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
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

void to_pointer() {
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
string to_down(string str) {
	for (int i = 0; i < str.length(); ++i) {
		str[i] = tolower(str[i]);
	}
	return str;
}

void print_cham(pointer_cham* cham) {
	cout << "이름 : " << cham->name << " hp : " << cham->hp <<  " mp : " << cham->mp << " speed : " << cham->speed << " range : " << cham->range << " position : " << cham->position << endl; 
}

void printall_cham() {
	pointer_cham* now_node = start;

	if (start == NULL) {
		cout << "자료가 없다" << endl;
		return;
	}
	do {
		print_cham(now_node);
		now_node = now_node->next;
	}while(now_node != start);

}
void search_cham(string name) {
	if (start == NULL) {
		cout << "자료가 없다" << endl;
		return;
	}
	int count = 0;
	pointer_cham* now_node = start;
	do {
		if (to_down(now_node->name) == to_down(name)) {
			print_cham(now_node);
			count++;
		}
		now_node = now_node->next;
	} while (now_node != start);
	if (count == 0) {
		cout << name << "이라는 챔피언은 없습니다" << endl;
	}
}
void delete_cham(string name) {
	if (start == NULL) {
		cout << "자료가 없다" << endl;
		return;
	}
	pointer_cham* pre_node = start;
	int count = 1;
	bool check = true;
	while (pre_node->next != start) {
		pre_node = pre_node->next;
		count++;
	}
	pointer_cham* now_node = start;
	for (int i = 0; i < count; ++i) {
		if (to_down(now_node->name) == to_down(name)) {
			if (now_node->next == now_node) {
				start = NULL;
				delete now_node;
				return;
			}
			if (now_node == start) {
				start = now_node->next;
				pre_node->next = start;
			}
			else {
				pre_node->next = now_node->next;
			}
			check = false;
			delete(now_node);
			break;
		}
		pre_node = now_node;
		now_node = now_node->next;
	}
	if (check) {
		cout << name << "이라는 챔피언은 없습니다" << endl;
	}
}
void delete_all_cham(string position) {
	if (start == NULL) {
		cout << "자료가 없다" << endl;
		return;
	}
	pointer_cham* pre_node = start;
	int count = 1;
	bool check = true;
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
				delete now_node;
				return;
			}
			if (now_node == start) {
				start = now_node->next;
				pre_node->next = start;
			}
			else {
				pre_node->next = now_node->next;
			}
			check = false;
			now_node = now_node->next;
			delete(target);
		}
		else {
			pre_node = now_node;
			now_node = now_node->next;
		}
	}
	if (check) {
		cout << position << "이라는 position은 없습니다" << endl;
	}
}
int find_hp() {
	if (start == NULL) {
		cout << "재료가 없댜ㅏ" << endl;
		return 0;
	}
	pointer_cham* now_node = start;
	int max_hp = 0;
	do {
		if (max_hp < now_node->hp) {
			max_hp = now_node->hp;
		}
		now_node = now_node->next;
	} while (now_node != start);
	return max_hp;
}
void print_max() {
	if (start == NULL) {
		cout << "재료가 없댜ㅏ" << endl;
		return;
	}
	pointer_cham* now_node = start;
	int max_hp = find_hp();
	do {
		if (max_hp == now_node->hp) {
			print_cham(now_node);
		}
		now_node = now_node->next;
	} while (now_node != start);
	
}

void sort_cham() {
	if (start == NULL) {
		cout << "재료가 없댜ㅏ" << endl;
		return;
	}
	int count = 1;
	pointer_cham* temp = start;
	while (temp->next != start) {
		temp = temp->next;
		count++;
	}
	for (int i = 0; i < count-1; ++i) {
		pointer_cham* pre_node = start;
		while (pre_node->next != start) {
			pre_node = pre_node->next;
		}
		pointer_cham* now_node = start;
		pointer_cham* next_node = now_node->next;
		for (int j = 0; j < count - 1; ++j) {
			if (now_node->hp < next_node->hp) {
				if (now_node == start) {
					start = next_node;
					pre_node->next = next_node;
					now_node->next = next_node->next;
					next_node->next = now_node;
				}
				else {
					pre_node->next = next_node;
					now_node->next = next_node->next;
					next_node->next = now_node;
				}
				pre_node = next_node;
				next_node = now_node ->next;
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
		cout << "재료가 없댜ㅏ" << endl;
		return;
	}
	pointer_cham* new_node = new pointer_cham;
	new_node->name = name;
	new_node->hp = hp;
	new_node->mp = mp;
	new_node->speed = speed;
	new_node->range = range;
	new_node->position = position;
	new_node->next = NULL;

	pointer_cham* now_node = start;
	pointer_cham* pre_node = start;
	int count = 1;
	while (pre_node->next != start) {
		count++;
		pre_node = pre_node->next;
	}
	bool check = true;
	for (int i = 0; i < count;++i) {
		if (now_node->hp < new_node->hp) {
			if (now_node == start) {
				start = new_node;
				pre_node->next = start;
				new_node->next = now_node;
				check = false;
				break;
			}
			else {
				pre_node->next = new_node;
				new_node->next = now_node;
				check = false;
				break;
			}
		}
		else {
			pre_node = now_node;
			now_node = now_node->next;
		}
	}
	if (check) {
		pre_node->next = new_node;
		new_node->next = start;
	}
}

int main() {
	ifstream fin("testdata.txt");
	if (!fin.is_open()) {
		cout << "파일을 찾지 못했습니다" << endl;
		return 0;
	}
	while (getline(fin, champion[cham_count].name, '\t')) {
		fin >> champion[cham_count].hp >> champion[cham_count].mp >> champion[cham_count].speed >> champion[cham_count].range >> champion[cham_count].position;
		fin.ignore(1000 , '\n');
		cham_count++;
		if (cham_count >= 50) {
			cout << "챔피언은 50개 까지 입력 가능합니다" << endl;
			break;
		}
	}
	fin.close();
	to_pointer();

	while (true) {
		string commend;
		cout << "명령어(소문자 가능) / search_sl / insert_sl / delete_sl / deleteall_sl/ printall_sl / findmaxhp_sl / sortbyhp_sl" << endl;
		getline(cin, commend);
		commend = to_down(commend);

		if (commend == "search_sl") {
			string name;
			cout << "이름 : ";
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
			cout << "이름 :";
			getline(cin, name);
			cout << "hp :";
			cin >> hp;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력하세요ㅕ" << endl;
			}
			cout << "mp :";
			cin >> mp;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력하세요ㅕ" << endl;
			}
			cout << "speed :";
			cin >> speed;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력하세요ㅕ" << endl;
			}
			cout << "range :";
			cin >> range;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력하세요ㅕ" << endl;
			}
			cin.ignore(1000, '\n');
			cout << "position :";
			getline(cin, position);
			insert_cham(name, hp, mp, speed, range, position);
		}
		else if (commend == "delete_sl") {
			string name;
			cout << "이름 : ";
			getline(cin, name);
			delete_cham(name);
			
		}
		else if (commend == "deleteall_sl") {
			string position;
			cout << "position : ";
			getline(cin, position);
			delete_all_cham(position);
		}
		else if (commend == "printall_sl") {
			printall_cham();
		}
		else if (commend == "findmaxhp_sl") {
			print_max();
		}
		else if (commend == "sortbyhp_sl") {
			sort_cham();

		}
		else {
			cout << "잘못된 명령어 입니다" << endl;
		}
	}


}