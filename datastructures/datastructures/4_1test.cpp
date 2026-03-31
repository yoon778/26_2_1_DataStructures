#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;

int cham_pos = 0;

struct champion {
	string name;
	int hp;
	int mp;
	int speed;
	int range;
	string position;
};
string todown(string str) {
	for (int i = 0; i < str.length(); ++i) {
		str[i] = tolower(str[i]);
	}
	return str;
}
void print_cham(champion cham[40], int n) {
	cout << n+1 << "번째 이름 : [" << cham[n].name << "] hp : [" << cham[n].hp << "] mp : [" << cham[n].mp << "] speed : [" << cham[n].speed << "] range : [" << cham[n].range << "] position : [" << cham[n].position << ']' << endl;
}
void search_cham(champion cham[40], string name) {
	bool check = true;
	for (int i = 0; i < 40; ++i) {
		if (!cham[i].name.empty() && todown(cham[i].name) == todown(name)) {
			print_cham(cham, i);
			check = false;
		}
	}
	if (check) {
		cout << "챔피언이 없습니다" << endl;
	}
	return;
}
void insert_cham(champion(&cham)[40], string name, int hp, int mp, int speed, int range, string position) {
	if (cham_pos >= 40) {
		cout << "가득 차있습니다" << endl;
		return;
	}
	cham[cham_pos].name = name;
	cham[cham_pos].hp = hp;
	cham[cham_pos].mp = mp;
	cham[cham_pos].speed = speed;
	cham[cham_pos].range = range;
	cham[cham_pos].position = position;
	cham_pos++;
}
void delete_cham(champion(&cham)[40], string name) {
	bool check = true;
	for (int i = 0; i < 40; ++i) {
		if (!cham[i].name.empty() && todown(cham[i].name) == todown(name)) {
			for (int j = i; j < 39; ++j) {
				cham[j] = cham[j + 1];
				check = false;
			}
			--cham_pos;
			--i;
		}
	}
	cham[39].name = "";
	cham[39].hp = 0;
	cham[39].mp = 0;
	cham[39].speed = 0;
	cham[39].range = 0;
	cham[39].position = "";
	
	if (check) {
		cout << name << "이란 챔피언이 없습니다" << endl;
		return;
	}
	cout << "삭제 완료" << endl;
	return;
}

void deleteall_cham(champion(&cham)[40], string position) {
	bool check = true;
	for (int i = 0; i < 40; ++i) {
		if (!cham[i].position.empty() && todown(cham[i].position) == todown(position)) {
			for (int j = i; j < 39; ++j) {
				cham[j] = cham[j + 1];
				check = false;
			}
			--i;
			--cham_pos;
		}
	}
	cham[39].name = "";
	cham[39].hp = 0;
	cham[39].mp = 0;
	cham[39].speed = 0;
	cham[39].range = 0;
	cham[39].position = "";

	if (check) {
		cout << position << "이란 역할이 없습니다" << endl;
		return;
	}
	cout << "삭제 완료" << endl;
	return;
}
void findmax_cham(champion cham[40]) {
	int max_int = 0;
	for (int i = 0; i < 40; ++i) {
		if (max_int < cham[i].hp) {
			max_int = cham[i].hp;
		}
	}
	for (int i = 0; i < 40; ++i) {
		if (cham[i].hp == max_int) {
			print_cham(cham, i);
		}
	}
}
void sort_cham(champion(&cham)[40]) {
	champion temp;
	for (int i = 0; i < 40; ++i) {
		for (int j = 0; j < 39; ++j) {
			if (cham[j].hp < cham[j + 1].hp) {
				temp = cham[j];
				cham[j] = cham[j + 1];
				cham[j + 1] = temp;
			}
		}
	}
}



int main() {
	champion champions[40] = {};
	ifstream fin("testdata.txt");
	if (!fin.is_open()) {
		cout << "파일을 찾을 수 없습니다" << endl;
		return 0;
	}
	while (getline(fin, champions[cham_pos].name, '\t')) {
		fin >> champions[cham_pos].hp >> champions[cham_pos].mp >> champions[cham_pos].speed >> champions[cham_pos].range >> champions[cham_pos].position;
		cham_pos++;
		fin.ignore(1000, '\n');
		if (cham_pos >= 40) {
			cout << "챔피언은 40개 까지 저장 가능합니다" << endl;
			break;
		}
	}
	fin.close();

	while (true) {
		string commend;
		cout << "명령어를 입력하시오  / search / inssert / delete / deleteall / printall / findmaxhp / sortbyhp" << endl;
		getline(cin, commend);
		commend = todown(commend);

		if (commend == "search") {
			cout << "이름 : ";
			string name;
			getline(cin, name);
			search_cham(champions, name);
		}
		else if (commend == "insert") {
			string name;
			int hp;
			int mp;
			int speed;
			int range;
			string position;
			cout << "이름 : ";
			getline(cin, name);
			cout << "hp : ";
			cin >> hp;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 가능합니다" << endl;
				continue;
			}
			cout << "mp : ";
			cin >> mp;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 가능합니다" << endl;
				continue;
			}
			cout << "speed : ";
			cin >> speed;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 가능합니다" << endl;
				continue;
			}
			cout << "range : ";
			cin >> range;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 가능합니다" << endl;
				continue;
			}
			cin.ignore(1000, '\n');
			cout << "position : ";
			getline(cin, position);
			insert_cham(champions, name, hp, mp, speed, range, position);
		}
		else if (commend == "delete") {
			cout << "이름: ";
			string name;
			getline(cin, name);
			delete_cham(champions, name);
		}
		else if (commend == "deleteall") {
			cout << "역할 : ";
			string position;
			getline(cin, position);
			deleteall_cham(champions, position);
		}
		else if (commend == "printall") {
			for (int i = 0; i < 40; ++i) {
				if (!champions[i].name.empty()) {
					print_cham(champions, i);
				}
			}
		}
		else if (commend == "findmaxhp") {
			findmax_cham(champions);
		}
		else if (commend == "sortbyhp") {
			sort_cham(champions);
		}
		else {
			cout << "잘못된 명령어 입니다" << endl;
		}
	}
	return 0;
}