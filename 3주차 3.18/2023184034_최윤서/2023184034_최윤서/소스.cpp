#include <iostream>
#include <cctype>
#include <string>
#include <fstream>
using namespace std;


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

void print_cham(champion cham[30], int num) {
	if (!cham[num].name.empty()) {
		cout << num + 1 << "번째 이름 : [" << cham[num].name << "] hp : [" << cham[num].hp << "] mp : [" << cham[num].mp << "] speed : [" << cham[num].speed << "] range : [" << cham[num].range << "] position : [" << cham[num].position << "]" << endl;
	}
}
void search_cham(champion cham[30], string name) {
	int search_count = 0;
	for (int i = 0; i < 30; ++i) {
		if (todown(cham[i].name) == todown(name)) {
			print_cham(cham, i);
			search_count++;
		}
	}
	if (search_count == 0) {
		cout << "찾는 챔피언이 없습니다. " << endl;
	}
	return;
}
void insert_cham(champion(&cham)[30], string name, int hp, int mp, int speed, int range, string position) {
	int num = -1; // 빈곳 자리
	for (int i = 0; i < 30; ++i) {
		if (cham[i].name.empty()) {
			num = i;
			break;
		}
	}
	if (num == -1) {
		cout << "30자리 꽉 찼습니다" << endl;
		return;
	}
	cham[num].name = name;
	cham[num].hp = hp;
	cham[num].mp = mp;
	cham[num].speed = speed;
	cham[num].range = range;
	cham[num].position = position;
	cout << "추가 완료" << endl;
}
void delete_cham(champion(&cham)[30], string name) {
	int delete_check = 0;
	for (int i = 0; i < 30; ++i) {
		if (todown(cham[i].name) == todown(name)) {
			for (int j = i; j < 29; ++j) {
				cham[j] = cham[j + 1];
			}
			--i;
			delete_check++;
			cham[29].name = "";
			cham[29].hp = 0;
			cham[29].mp = 0;
			cham[29].speed = 0;
			cham[29].range = 0;
			cham[29].position = "";
			cout << "삭제 완료" << endl;
		}
	}
	if (delete_check == 0) {
		cout << name << "이라는 챔피언은 없습니다" << endl;
	}
	return;
}
void deleteall_cham(champion(&cham)[30], string position) {
	int deleteall_check = 0;
	for (int i = 0; i < 30; ++i) {
		if (todown(cham[i].position) == todown(position)) {
			for (int j = i; j < 29; ++j) {
				cham[j] = cham[j + 1];
			}
			--i;
			deleteall_check++;
			cham[29].name = "";
			cham[29].hp = 0;
			cham[29].mp = 0;
			cham[29].speed = 0;
			cham[29].range = 0;
			cham[29].position = "";
		}
	}
	if (deleteall_check == 0) {
		cout << position << "이라는 역할군은 없습니다" << endl;
	}
	return;
}
void find_max(champion cham[30]) {
	int max_num = 0;
	for (int i = 0; i < 30; ++i) {
		if (cham[i].hp > max_num) {
			max_num = cham[i].hp;
		}
	}
	if (max_num == 0) {
		cout << "챔피언이 없습니다" <<endl;
	}
	for (int i = 0; i < 30; ++i) {
		if (cham[i].hp == max_num) {
			print_cham(cham, i);
		}
	}
	return;
}
void sort_cham(champion(&cham)[30]) {
	champion temp;
	int a = 0;
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 29-a; ++j) {
			if (cham[j].hp < cham[j + 1].hp) {
				temp = cham[j];
				cham[j] = cham[j + 1];
				cham[j + 1] = temp;
			}
		}
		a++;
	}
	cout << "정렬완료" << endl;
	return;
}


int main() {
	int count = 0;
	champion champions[30] = {};
	ifstream fin("testdata.txt");
	if (!fin.is_open()) {
		cout << "파일을 찾을 수 없습니다" << endl;
		return 0;
	}
	while (getline(fin, champions[count].name, '\t')) {
		
		fin >> champions[count].hp >> champions[count].mp >> champions[count].speed >> champions[count].range >> champions[count].position;
		fin.ignore(1000, '\n');
		count++;
		if (count ==30) {
			cout << "최대 30개 까지 저장 가능합니다" << endl;
			break;
		}
	}
	fin.close();
	while (true) {
		string commend;
		cout << "명령어 : search / insert / delete / deleteall / printall / findmaxhp / sortbyhp " << endl;
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
			cout << "hp :";
			cin >> hp;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력해주세요" << endl;
				continue;
			}
			cout << "mp :";
			cin >> mp;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력해주세요" << endl;
				continue;
			}
			cout << "speed :";
			cin >> speed;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력해주세요" << endl;
				continue;
			}
			cout << "range :";
			cin >> range;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력해주세요" << endl;
				continue;
			}
			cin.ignore(1000, '\n');
			cout << "position :";
			getline(cin, position);
			insert_cham(champions, name, hp, mp, speed, range, position);
		}
		else if (commend == "delete") {
			cout << "이름 :";
			string name;
			getline(cin, name);
			delete_cham(champions, name);
		}
		else if (commend == "deleteall") {
			cout << "position : ";
			string position;
			getline(cin, position);
			deleteall_cham(champions, position);
		}
		else if (commend == "printall") {
			for (int i = 0; i < 30; ++i) {
				print_cham(champions, i);
			}
		}
		else if (commend == "findmaxhp") {
			find_max(champions);
		}
		else if (commend == "sortbyhp") {
			sort_cham(champions);
		}
		else {
			cout << "잘못된 명령어 입니다." << endl;
		}
	}
}