#include <iostream>
#include <string>
#include <fstream>
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
string todown(string str) {
	for (int i = 0; i < str.length(); ++i) {
		str[i] = tolower(str[i]);
	}
	return str;
}

void print_cham(champion cham[50], int num) {
	if (!cham[num].name.empty()) {
		cout << num + 1 << "번째  이름: [" << cham[num].name << "] hp: [" << cham[num].hp << "] mp: [" << cham[num].mp << "] speed: [" << cham[num].speed << "] range: [" << cham[num].range << "] position: [" << cham[num].position << "]" << endl;
	}
	
}
void search_cham(champion cham[50], string name) {
	int search_check = 0;
	for (int i = 0; i < 30; ++i) {
		if (todown(cham[i].name) == todown(name)) {
			print_cham(cham, i);
			search_check++;
		}
	}
	if (search_check == 0) {
		cout << name << "라는 챔피언은 없습니다" << endl;
		return;
	}
	return;
}

void inseart_cham(champion(&cham)[50], string name, int hp, int mp, int speed, int range, string position) {
	int num = -1; //  빈곳 번호
	for(int i = 0 ; i < 30 ; ++i){
		if (cham[i].name.empty()) {
			num = i;
			break;
		}
	}
	if (num == -1) {
		cout << "챔피언을 저장할 수 있는 30개가 다 찼습니다" << endl;
		return;
	}
	cham[num].name = name;
	cham[num].hp = hp;
	cham[num].mp = mp;
	cham[num].speed = speed;
	cham[num].range = range;
	cham[num].position = position;
	cout << "저장 완료" << endl;
	return;
}
void delete_cham(champion(&cham)[50], string name) {
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
		}
	}
	if (delete_check == 0) {
		cout << name << "이란 챔피언이 없습니다" << endl;
	}

	
		cout << "삭제 완료" << endl;
	
	return;
}
void deleteall_cham(champion(&cham)[50], string position) {
	int deleteall_check = 0;
	for (int i = 0; i < 30; ++i) {
		if (todown(cham[i].position) == todown(position)) {
			for (int j = i; j < 29; ++j) {
				cham[j] = cham[j + 1];
			}
			--i;
			deleteall_check++;
		}
	}
	if (deleteall_check == 0) {
		cout << position << "이란 챔피언이 없습니다" << endl;
	}
	else {
		cham[29].name = "";
		cham[29].hp = 0;
		cham[29].mp = 0;
		cham[29].speed = 0;
		cham[29].range = 0;
		cham[29].position = "";
		cout << "삭제 완료" << endl;
	}
	return;
}
void find_max_hp_cham(champion cham[50]) {
	int max_hp = 0;
	for (int i = 0; i < 30; ++i) {
		if (cham[i].hp > max_hp) {
			max_hp = cham[i].hp;
		}
	}
	if (max_hp <= 0) {
		cout << "챔피언이 없습니다" << endl;
	}
	else {
		for (int i = 0; i < 30; ++i) {
			if (cham[i].hp == max_hp) {
				print_cham(cham, i);
			}
		}
	}
	return;
}

void sort_hp_cham(champion(&cham)[50]) {
	int a = 0;
	champion temp;
	for (int i = 0; i < 30; ++i) {
		for (int j = 0; j < 29; j++) {
			if (cham[j].hp < cham[j + 1].hp) {
				temp = cham[j];
				cham[j] = cham[j + 1];
				cham[j + 1] = temp;
			}
		}
	}
	cout << "정렬 완료" <<endl;
}





int main() {
	int file_check = 0;
	champion champions[50] = {};
	ifstream fin("testdata.txt");
	if (!fin.is_open()) {
		cout << "파일을 찾을 수 없습니다" << endl;
		return 0;
	}
	while (getline(fin, champions[file_check].name, '\t')) {
		fin >> champions[file_check].hp >> champions[file_check].mp >> champions[file_check].speed >> champions[file_check].range >> champions[file_check].position;
		fin.ignore(1000, '\n');
		file_check++;
		if (file_check >= 30) {
			cout << "최대 30개 챔피언 까지 저장 가능 합니다." << endl;
			return 0;
		}
	}
	fin.close();

	while (true) {
		string commend;
		cout << "명령어를 입력해주세요" << endl;
		cout << "Search / Insert / Delete / DeleteAll / PrintAll / FindMaxHp / SortByHp" << endl;
		getline(cin, commend);
		commend = todown(commend);
		if (commend == "search") {
			string name;
			cout << "찾을 챔피언 이름 : ";
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
			cout << "position:";
			getline(cin, position);
			inseart_cham(champions, name, hp, mp, speed, range, position);
		}
		else if (commend == "delete") {
			string name;
			cout << "삭제할 챔피언의 이름 : ";
			getline(cin, name);
			delete_cham(champions, name);
		}
		else if (commend == "deleteall") {
			string position;
			cout << "삭제할 역할군 : ";
			getline(cin, position);
			deleteall_cham(champions, position);
		}
		else if (commend == "printall") {
			for (int i = 0; i < 30; i++) {
				print_cham(champions ,i);
			}
		}
		else if (commend == "findmaxhp") {
			find_max_hp_cham(champions);
		}
		else if (commend == "sortbyhp") {
			sort_hp_cham(champions);

		}
		else {
			cout << "잘못된 명령어 입니다" << endl;
		}
	}

	return 0;

}