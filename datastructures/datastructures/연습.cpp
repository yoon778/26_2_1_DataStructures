#include <iostream>
#include <cctype>
#include <string>
#include<fstream>

using namespace std;

struct champion {
	string name;
	int hp;
	int mp;
	int speed;
	int range;
	string position;
};
int cham_loca = 0;
string todown(string str) {
	for (int i = 0; i < str.length(); ++i) {
		str[i] = tolower(str[i]);
	}
	return str;
}
void print_cham(champion cham[50], int n) {
	if (!cham[n].name.empty()) {
		cout << "이름 : [" << cham[n].name << "] hp : [" << cham[n].hp << "] mp : [" << cham[n].mp << "] speed : [" << cham[n].speed << "] range : [" << cham[n].range << "] position : [" << cham[n].position << ']' << endl;
	}
	return;
}
void printall_cham(champion cham[50], int count) {
	if (count == 50) {
		return;
	}
	print_cham(cham, count);
	printall_cham(cham, count + 1);
	return;
}
void search_cham(champion cham[50], string name, int count) {
	if (count == 50) {
		cout << name << "이라는 챔피언은 없습ㄴ디ㅏ" << endl;
		return;
	}	
	if (!cham[count].name.empty() && todown(cham[count].name) == todown(name)) {
		print_cham(cham, count);
		return;
	}
	search_cham(cham, name, count + 1);
}
void insert_cham(champion(&cham)[50], string name, int hp, int mp, int speed, int range, string position, int count) {
	if (count == 50) {
		cout << "현재 저장 가능한 공간이 없습니다" << endl;
		return;
	}
	if (cham[count].name.empty()) {
		cham[count].name = name;
		cham[count].hp = hp;
		cham[count].mp = mp;
		cham[count].speed = speed;
		cham[count].range = range;
		cham[count].position = position;
		cout << "추가완" << endl;
		return;
	}
	insert_cham(cham, name, hp, mp, speed, range, position, count + 1);
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
		cout << "삭제완" << endl;
		return;
	}
	delete_cham(cham, name, count + 1);
}
 

int deleteall_cham(champion(&cham)[50], string position, int count) {
	if (count == 50) {
		return 0;
	}
	int delete_count = deleteall_cham(cham, position, count + 1);
	if (!cham[count].name.empty() && todown(cham[count].position) == todown(position)) {
		cham[count].name = "";
		cham[count].hp = 0;
		cham[count].mp = 0;
		cham[count].speed = 0;
		cham[count].range = 0;
		cham[count].position = "";
		return  delete_count +1;
	}
	else {
		return delete_count ;
	}
}

int find_max_hp(champion cham[50], int count) {
	if (count == 50) {
		return 0;
	}
	int max_hp = find_max_hp(cham, count + 1);
	if (!cham[count].name.empty() && cham[count].hp > max_hp) {
		return cham[count].hp;
	}
	else {
		return max_hp;
	}
}
void max_hp_print(champion cham[50], int count, int max_hp) {
	if (count == 50) {
		return;
	}
	if (!cham[count].name.empty() && cham[count].hp == max_hp) {
		print_cham(cham, count);
	}
	max_hp_print(cham, count + 1, max_hp);
}
int find_max_hp_index(champion cham[50], int count) {
	if (count == 50) {
		return 49;
	}
	int maxhp_index = find_max_hp_index(cham, count + 1);
	if (!cham[count].name.empty() && cham[count].hp > cham[maxhp_index].hp) {
		return count;
	}
	else {
		return maxhp_index;
	}
}
void sort_maxhp_cham(champion(&cham)[50], int count) {
	if (count == 50) {
		return;
	}
	int max_index = find_max_hp_index(cham, count);
	if (count != max_index) {
		champion temp = cham[count];
		cham[count] = cham[max_index];
		cham[max_index] = temp;
	}
	sort_maxhp_cham(cham, count + 1);
	
}



int main() {
	ifstream fin("testdata.txt");
	champion champions[50] = {};
	while (getline(fin, champions[cham_loca].name, '\t')) {
		fin >> champions[cham_loca].hp >> champions[cham_loca].mp >> champions[cham_loca].speed >> champions[cham_loca].range >> champions[cham_loca].position;
		fin.ignore(1000, '\n');
		cham_loca++;
		if (cham_loca >= 50) {
			cout << "챔피언은 50개 까지 저장 가능합니다" << endl;
			break;
		}
	}	
	fin.close();

	while (true) {
		string commend;
		cout << "명령어를 입력하세요" << endl;
		getline(cin, commend);
		commend = todown(commend);

		if (commend == "search_r") {
			cout << "이름 : ";
			string name;
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

			cout << "이름 :";
			getline(cin, name);
			cout << "hp :";
			cin >> hp;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력" << endl;
				continue;
			}
			cout << "mp :";
			cin >> mp;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력" << endl;
				continue;
			}
			cout << "speed :";
			cin >> speed;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력" << endl;
				continue;
			}
			cout << "range :";
			cin >> range;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(1000, '\n');
				cout << "숫자만 입력" << endl;
				continue;
			}
			cin.ignore(1000, '\n');
			cout << "position :";
			getline(cin, position);

			insert_cham(champions, name, hp, mp, speed, range, position, 0);
		}
		else if (commend == "delete_r") {
			cout << "이름 : ";
			string name;
			getline(cin, name);
			delete_cham(champions, name, 0);

		}
		else if (commend == "deleteall_r") {
			cout << "position : ";
			string position;
			getline(cin, position);
			if (deleteall_cham(champions, position, 0) == 0)
			{
				cout << position << "이라는 역할을 없습니다" << endl;
			}
			else {
				cout << "삭제완" << endl;
			}
		}
		else if (commend == "printall_r") {
			printall_cham(champions, 0);
		}
		else if (commend == "findmaxhp_r") {
			int maxhp = find_max_hp(champions, 0);
			max_hp_print(champions, 0, maxhp);
		}
		else if (commend == "sortbyhp_r") {
			sort_maxhp_cham(champions, 0);
			cout << "정령 완" << endl;
		}
		else {
			cout << "잘못된 명령어입니다" << endl;
		}
	}
	return 0;
}