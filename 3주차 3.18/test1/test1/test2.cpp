#include <iostream>
#include <cctype> 
#include <string>
#include <fstream>

using namespace std;

struct champion { // 구조체
	string name;
	int hp;
	int mp;
	int speed;
	int range;
	string position;
};
string str_down(string str) { // 소문자 변경
	for (int i = 0; i < str.length(); ++i) {
		str[i] = tolower(str[i]);
	}
	return str;
}
void print_cham(champion cham[40], int num) {
	cout << num + 1 << "번째 이름 : [" << cham[num].name << "] hp : [" << cham[num].hp << "] mp : [" << cham[num].mp << " ] speed : [" << cham[num].speed << "] range : [" << cham[num].range << "] position : [" << cham[num].position  << "]" << endl;
	return;
}

void search_cham(champion cham[40], string name) {
	int check = 0; // 없는지 체크
	for (int i = 0; i < 40; ++i) {
		if (str_down(cham[i].name) == str_down(name)) {
			print_cham(cham, i);
			check++;
		 }
	}
	if (check == 0) {
		cout << "그런 챔피언은 없습니다" << endl;
	}
	return;
}
void insert_cham(champion(&cham)[40], string name, int hp, int mp, int speed, int range, string position) {
	int check = 0; // 빈곳 방 넘버
	for (int i = 0; i < 40; ++i) {
		if (cham[i].name.empty()) {
			check++;
			cham[i].name = name;
			cham[i].hp = hp;
			cham[i].mp = mp;
			cham[i].speed = speed;
			cham[i].range = range;
			cham[i].position = position;
			cout << i + 1 << "번째에 입력 완료" << endl;
			break;
		}
	}
	if (check == 0) {
		cout << "빈곳이 없습니다 " << endl;
		return;
	}
}
void delete_cham(champion(&cham)[40], string name) {
	int delete_check = 0;
	for (int i = 0; i < 40; ++i) {
		if (str_down(cham[i].name) == str_down(name)) {
			for (int j = i; j < 39; ++j) {
				cham[j] = cham[j + 1];
			}
			delete_check++;
			--i;
		}
	}
	if (delete_check == 0) {
		cout << "그런 챔피언은 없습니다" << endl;
		return;
	}
	cham[39].name = "";
	cham[39].hp = 0;
	cham[39].mp = 0;
	cham[39].speed = 0;
	cham[39].range = 0;
	cham[39].position = "";
	if (delete_check == 1) {
		cout << "삭제 완료" << endl;
	}
	else {
		cout << "중복된 챔피언 모두 삭제 완료" << endl;
	}
	return;
}

void deleteall_cham(champion(&cham)[40], string position) {
	int delete_check = 0;
	for (int i = 0; i < 40; ++i) {
		if (str_down(cham[i].position) == str_down(position)) {
			for (int j = i; j < 39; ++j) {
				cham[j] = cham[j + 1];
			}
			delete_check++;
			--i;
		}
	}
	if (delete_check == 0) {
		cout << "그런 역할은 없습니다" << endl;
		return;
	}
	cham[39].name = "";
	cham[39].hp = 0;
	cham[39].mp = 0;
	cham[39].speed = 0;
	cham[39].range = 0;
	cham[39].position = "";
	cout << "삭제 완료" << endl;
	return;
}
void find_max_hp_cham(champion cham[40]) {
	int max_hp = 0;
	for (int i = 0; i < 40; ++i) {
		if (cham[i].hp > max_hp) {
			max_hp = cham[i].hp;
		}
	}
	for (int i = 0; i < 40; ++i) {
		if (cham[i].hp == max_hp) {
			print_cham(cham, i);
		}
	}
	return;
}
void sort_cham(champion(&cham)[40]) {
	int a = 0;
	champion temp;
	for (int i = 0; i < 39; ++i) {
		for (int j = 0; j < 39 - a; ++j) {
			if (cham[j].hp < cham[j + 1].hp) {
				temp = cham[j];
				cham[j] = cham[j + 1];
				cham[j + 1] = temp;
			}
		}
		a++;
	}
	cout << "내림차순 정렬 완료" << endl;
	return;
}

int main() {
	champion champions[40] = {};
	int fin_count = 0; //파일 입출력 받아오는 카운트
	string commend;


	ifstream fin("testdata.txt");
	if (!fin.is_open()) {
		cout << "파일이 없습니다" << endl;
		return 0;
	}

	while (getline(fin, champions[fin_count].name, '\t')) {
		fin >> champions[fin_count].hp >> champions[fin_count].mp >> champions[fin_count].speed >> champions[fin_count].range >> champions[fin_count].position;
		fin.ignore(1000, '\n');
		fin_count++;
		if (fin_count >= 40) {
			cout << "챔피언은 총 40개 까지만 가능합니다" << endl;
			return 0;
		}
	}
	fin.close();
	
	while (true) {
		cout << "명령어 : Search / Insert / Delete / DeleteAll / PrintAll / FindMaxHp / SortbyHp" << endl;
		cin >> commend;
		cin.ignore(1000, '\n');
		commend = str_down(commend);
		
		if (commend == "search") {
			cout << "찾을 챔피언의 이름 : ";
			string name;
			getline(cin, name);
			search_cham(champions, name);
		}
		else if (commend == "insert") {
			string in_name;
			int in_hp;
			int in_mp;
			int in_speed;
			int in_range;
			string in_position;
			cout << "이름 : ";
			getline(cin, in_name);
			cout << "hp : ";
			cin >> in_hp;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력해주세요" << endl;
				continue;
			}
			cout << "mp : ";
			cin >> in_mp;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력해주세요" << endl;
				continue;
			}
			cout << "speed : ";
			cin >> in_speed;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력해주세요" << endl;
				continue;
			}
			cout << "range : ";
			cin >> in_range;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력해주세요" << endl;
				continue;
			}
			cout << "position : ";
			cin >> in_position;
			cin.ignore(1000, '\n');
			insert_cham(champions, in_name, in_hp, in_mp, in_speed, in_range, in_position);
		}
		else if (commend == "delete") {
			string name;
			cout << "삭제할 챔피언 : ";
			getline(cin, name);
			delete_cham(champions, name);
		}
		else if (commend == "deleteall") {
			string position;
			cout << "삭제할 역할 : ";
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
			find_max_hp_cham(champions);
		}
		else if (commend == "sortbyhp") {
			sort_cham(champions);
		}
		else {
			cout << "그런 명령어는 없습니다" << endl;
		}
	}
	return 0;
}