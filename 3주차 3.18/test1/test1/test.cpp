#include <iostream>
#include <string>
#include <cctype>
#include <fstream>
using namespace std;

struct lolchampion { // 구조체
	string name;
	int hp;
	int mp;
	int speed;
	int range;
	string position;
};

string todown(string cham) {  // 소문자로 바꾸기
	for (int i = 0; i < cham.length(); ++i) {
		cham[i] = tolower(cham[i]);
	}
	return cham;
}
void print_cham(lolchampion cham[30] , int a) { // 챔피언 정보 출력
	if(!cham[a].name.empty()){
			cout << a + 1 << "번째 이름: [" << cham[a].name << "] hp : [" << cham[a].hp << "] mp : [" << cham[a].mp << "] speed : [" << cham[a].speed << "] range : [" << cham[a].range << "] position : [" << cham[a].position << ']' << endl;
	}
	return;
}

void search_name(lolchampion cham[30], string name) { // 이름 찾아서 출력
	int check = 0; // 있는지 없는지 체크
	for (int i = 0; i < 30; ++i) {
		if (todown(cham[i].name) == todown(name)) {
			print_cham(cham, i);
			check ++;
		}
	}
	if (check == 0) {
		cout << "그런 이름의 챔피언이 없습니다. " << endl;
	}
	return;
}

void insert_cham(lolchampion(&cham)[30], string name, int hp, int mp, int speed , int range, string position) { // 챔피언 추가
	int empty_space = -1;
	for (int i = 0; i < 30; ++i) {
		if (cham[i].name.empty()) {
			empty_space = i;
			break;
		}
	}
	if (empty_space == -1) {
		cout << "공백이없습ㄴ디ㅏ" << endl;
		return;
	}
	cham[empty_space].name = name;
	cham[empty_space].hp = hp;
	cham[empty_space].mp = mp;
	cham[empty_space].speed = speed;
	cham[empty_space].range = range;
	cham[empty_space].position = position;
	cout << "추가 완료" << endl;
}

void delete_cham(lolchampion(&cham)[30], string name) {
	int check = 0; // 있는지 없는지 체크
	for (int i = 0; i < 30; ++i) {
		if (todown(cham[i].name) == todown(name)) {
			for (int j = i; j < 29; ++j) {
				cham[j] = cham[j + 1];
			}
			cham[29].name = "";
			cham[29].hp = 0;
			cham[29].mp = 0;
			cham[29].speed = 0;
			cham[29].range = 0;
			cham[29].position = "";
			--i;
			check++;

		}
	}
	if (check == 0) {
		cout << "그런 이름의 챔피언이 없습니다. " << endl;
		return;
	}
	cout << "삭제완료" << endl;;
	return;
}

void deleteall_cham(lolchampion(&cham)[30], string position) {
	int count = 0;
	for (int i = 0; i < 29; ++i) {
		if (todown(cham[i].position) == todown(position)) {
			for (int j = i; j < 29; ++j) {
				cham[j] = cham[j + 1];
			}
			--i;
			cham[29].name = "";
			cham[29].hp = 0;
			cham[29].mp = 0;
			cham[29].speed = 0;
			cham[29].range = 0;
			cham[29].position = "";
			count++;
		}
	}
	if (count == 0) {
		cout << "맞는 position이 없습니다" << endl;
		return;
	}
	cout << "삭제 완료" << endl;
	return;
}

void find_max_cham(lolchampion cham[30]) {
	int location; // 가장 큰 수 위치
	int num = -1; // 가장 작은 수
	for (int i = 0; i < 30; ++i) {
		if (!cham[i].name.empty() && cham[i].hp > num) {
			num = cham[i].hp;
			location = i;
		}
	}
	if (num == -1) {
		cout << "정보가 없음" << endl;
		return;
	}
	for (int i = 0; i < 30; ++i) {
		if (cham[location].hp == cham[i].hp) {
			print_cham(cham, i);
		}
	}
	return;
}

void sort_cham(lolchampion(&cham)[30]) {
	lolchampion temp;
	int a = 0;
	for (int i = 0; i < 29; ++i) {
		for (int j = 0; j < 29 - a; ++j) {
			if (cham[j].hp < cham[j + 1].hp) {
				temp = cham[j];
				cham[j] = cham[j + 1];
				cham[j + 1] = temp;
			}
		}
		a++;
	}
	cout << "정렬 완료" << endl;
	return;
}

int main() {
	lolchampion champions[30] = {};
	ifstream fin("testdata.txt");
	if (!fin.is_open()) {
		cout << "파일을 찾을 수 없습니다" << endl;
		return 0;
	}
	int count = 0;

	while (getline(fin, champions[count].name, '\t')) {
		fin >> champions[count].hp >> champions[count].mp >> champions[count].speed >> champions[count].range >> champions[count].position;
		fin.ignore(1000, '\n');
		count++;
		if (count >= 30) {
			cout << "저장할 곳이 꽉 찼습니다" << endl;
			break;
		}
	}
	fin.close();

	while (true) {
		cout << "커맨드 : search /insert /delete /deleteall /printall /findmaxhp /sortbyhp" << endl;
		string commend;
		getline(cin, commend);
		commend = todown(commend);
		if (commend == "search") {
			string name;
			cout << " 챔피언 이름 : ";
			getline(cin, name);
			search_name(champions, name);
		}
		else if (commend == "insert") {
			string name;
			int hp;
			int mp;
			int speed;
			int range;
			string position;
			cout << "넣을 챔피언의 정보를 입력해주세요" << endl;
			cout << "이름 :";
			getline(cin, name);
			cout << "hp : ";
			cin >> hp;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력해주세요" << endl;
				continue;
			}
			cout << "mp : ";
			cin >> mp;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력해주세요" << endl;
				continue;
			}
			cout << "speed : ";
			cin >> speed;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력해주세요" << endl;
				continue;
			}
			cout << "range : ";
			cin >> range;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력해주세요" << endl;
				continue;
			}
			cout << "position : ";
			cin >> position;
			cout << endl;
			insert_cham(champions, name, hp, mp, speed, range, position);
			cin.ignore(1000, '\n');
		}
		else if (commend == "delete") {
			string name;
			cout << "삭제할 챔피언의 이름 : ";
			getline(cin, name);
			delete_cham(champions, name);
		}
		else if (commend == "deleteall") {
			string position;
			cout << "삭제할 포지션 : ";
			cin >> position;
			cout << endl;
			cin.ignore(1000, '\n');
			deleteall_cham(champions, position);
		}
		else if (commend == "printall") {
			cout << "모든 챔피언 출력" << endl;
			for (int i = 0; i < 30; ++i) {
				print_cham(champions, i);
			}
			cout << endl;
		}
		else if (commend == "findmaxhp") {
			find_max_cham(champions);
		}
		else if (commend == "sortbyhp") {
			sort_cham(champions);
		}
		else {
			cout << "가능한 명령어가 아닙니다" << endl;
		}
	}
	return 0;
}