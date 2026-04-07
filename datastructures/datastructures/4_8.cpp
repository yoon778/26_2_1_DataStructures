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

string todown(string str) {
	for (int i = 0; i < str.length(); ++i) {
		str[i] = tolower(str[i]);
	}
	return str;
}
void print_cham(champion cham[50], int n) {
	cout << "이름 : [" << cham[n].name << "] hp : [" << cham[n].hp << "] mp : [" << cham[n].mp << "] speed : [" << cham[n].speed << "] range : [" << cham[n].range << "] position : [" << cham[n].position << ']' << endl;
}
void printall_cham(champion cham[50], int n) {
	if (n == 50) {
		return;
	}
	if (!cham[n].name.empty()) {
		print_cham(cham, n);
	}
	printall_cham(cham, n + 1);
}

void search_cham(champion cham[50], string name, int count) {
	if (count == 50) {
		cout << name << "이란 챔피언은 없습니다" << endl;
		return ;
	}
	if (!cham[count].name.empty() && todown(cham[count].name) == todown(name)) {
		print_cham(cham, count);
		return;
	}
	search_cham(cham, name, count + 1);
}
void inseart_cham(champion (&cham)[50] , string name, int hp, int mp, int speed, int range, string position, int count) {
	if (count == 50) {
		cout << "빈자리가 없습니다" << endl;
		return;
	}
	if (cham[count].name.empty()) {
		cham[count].name = name;
		cham[count].hp = hp;
		cham[count].mp = mp;
		cham[count].speed = speed;
		cham[count].range = range;
		cham[count].position = position;
		cout << "추가 완" << endl;
		return;
	}
	inseart_cham(cham, name, hp, mp, speed, range, position, count + 1);
}

void delete_cham(champion(&cham)[50], string name, int count) {
	if (count == 50) {
		cout << name << "이라는 챔피언은 없습니다" << endl;
		return;
	}
	if (!cham[count].name.empty() && todown(cham[count].name) == todown(name)) {
		cham[count].name = "";
		cham[count].hp = 0;
		cham[count].mp = 0;
		cham[count].speed = 0;
		cham[count].range = 0;
		cham[count].position = "";
		cout << "삭제 완" << endl;
		return;
	}
	delete_cham(cham, name, count + 1);
}
int  deleteall_cham(champion(&cham)[50], string position, int count) {
	
	if (count == 50) {
		return 0;
	}
	int delete_count = 0;
	if (!cham[count].position.empty() && todown(cham[count].position) == todown(position)) {
		cham[count].name = "";
		cham[count].hp = 0;
		cham[count].mp = 0;
		cham[count].speed = 0;
		cham[count].range = 0;
		cham[count].position = "";
		delete_count = 1;

	}
	return delete_count + deleteall_cham(cham, position, count + 1);
}

int findmaxhp_cham(champion cham[50] , int count) {
	if (count == 49) {
		return cham[49].hp;
	}
	int max_hp = findmaxhp_cham(cham, count + 1);
	if (cham[count].hp < max_hp) {
		return max_hp;
	}
	else {
		return cham[count].hp;
	}
}
void find_print_cham(champion cham[50], int target_hp , int count) {
	if (count == 50) {
		return;
	}
	if (!cham[count].name.empty() && cham[count].hp == target_hp) {
		print_cham(cham, count);
	}
	find_print_cham(cham, target_hp, count + 1);
}

int findmaxhp_index_cham(champion cham[50], int count) {
	if (count == 50) {
		return 49;
	}
	int max_hp_index = findmaxhp_index_cham(cham, count + 1);
	if (cham[count].hp < cham[max_hp_index].hp) {
		return max_hp_index;
	}
	else {
		return count;
	}
}

void sort_cham(champion(&cham)[50], int count) {
	if (count == 49) {
		return;
	}

	int max_hp_index = findmaxhp_index_cham(cham, count);
	if (cham[count].hp != cham[max_hp_index].hp) {
		champion temp = cham[count];
		cham[count] = cham[max_hp_index];
		cham[max_hp_index] = temp;
	}
	sort_cham(cham, count + 1);
}


int main() {
	champion champions[50] = {};
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
	string commend;

	while (true) {
		cout << "명령어를 입력해주세요" << endl;
		getline(cin, commend);
		commend = todown(commend);

		if (commend == "search_r") {
			string name;
			cout << "이름";
			getline(cin, name);
			search_cham(champions, name, 0);
		}
		else if (commend == "insert_r") {
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

			inseart_cham(champions, name, hp, mp, speed, range, position, 0);
		}
		else if (commend == "delete_r") {
			cout << "이름 ";
			string name;
			getline(cin, name);
			delete_cham(champions, name, 0);

		}
		else if (commend == "deleteall_r") {
			string position;
			cout << "포지션 ";
			getline(cin, position );
			int delete_count = deleteall_cham(champions, position, 0);
			if (delete_count == 0) {
				cout << position << "이라는 역할은 없습니다" << endl;
			}
			else {
				cout << "삭제 완" << endl;
			}
		}
		else if (commend == "printall_r") {
			printall_cham(champions, 0);
		}
		else if (commend == "findmaxhp_r") {
			find_print_cham(champions, findmaxhp_cham(champions, 0), 0);
		}
		else if (commend == "sortbyhp_r") {
			sort_cham(champions, 0);
		}
		else {
			cout << "잘못된 커맨드 입니다" << endl;
		}
	}

	return 0;
}