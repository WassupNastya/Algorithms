#include <iostream>
#include <queue>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

const int n = 3;

struct list {
	string s;
	list* parent = nullptr;
	list* next = nullptr;
};
struct element
{
	int f;
	string str;
	int Sx, Sy;
	int step = 0;
	list* ptr;
};

void GoUp(list* ptr) {
	if (ptr == nullptr) return;
	GoUp(ptr->parent);
	int a = 0;
	cout << "Следующий шаг: " << endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << ptr->s[a];
			a++;
		}
		cout << endl;
	}
	cout << endl;
}
list* AddElement(string s, list* ptr) {
	list * element = new list;
	element->s = s;
	element->parent = ptr;
	return element;
}
int FindG(char (&array)[3][3]) {
	string s = { "диапазон " };
	int a = 0;
	int count = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (s[a] != array[i][j]) count++;
			a++;
		}
	}
	return count;
}
bool CheckBorder(int x, int y)
{
	if ((x < 0) || (x > 2) || (y < 0) || (y > 2)) return 0;
	else return 1;
}
bool CheckStepBack(int x1, int y1, int bx, int by)
{
	if ((x1 == bx) && (y1 == by)) return 1;
	else return 0;

}
bool CompareString(string s)
{
	if (s == "диапазон ") return 1;
	else return 0;
}
int main() {
	setlocale(LC_ALL, "Russian");
	ifstream fin("text.txt");
	char str[3 * n + 1];
	int error_flag = 0;
	if (!fin.is_open())
		cout << "Ошибка, файл не открыт!\n";
	else
	{
		fin.getline(str, 3 * n + 1);
		cout << "Считанная строка: " << str << endl;
	}

	list* root = AddElement(str, nullptr);

	char matrix[n][n];
	int a = 0;
	int Sx, Sy;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			matrix[i][j] = str[a];
			if (str[a] == ' ') {
				Sx = i;
				Sy = j;
			}
			a++;
		}
	}

	int xarray[4] = { -1, 0, 1, 0 };
	int yarray[4] = { 0, 1, 0, -1 };

	element array[4];
	for (int i = 0; i < 4; i++)
	{
		string s;
		char tcurr[n][n];
		if ((CheckBorder(Sx + xarray[i], Sy + yarray[i]) == 1) && (CheckStepBack(Sx + xarray[i], Sy + yarray[i], Sx, Sy) == 0))
		{
			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					tcurr[j][k] = matrix[j][k];
				}
			}
			swap(tcurr[Sx + xarray[i]][Sy + yarray[i]], tcurr[Sx][Sy]);

			for (int j = 0; j < n; j++) {
				for (int k = 0; k < n; k++) {
					s += tcurr[j][k];
				}
			}
			array[i].str = s;
			array[i].f = FindG(tcurr) + 1;
		}
		else array[i].f = 0;
	}

	queue <int> q;
	for (int i = 0; i < 4; i++) { 
		if (array[i].f != 0) q.push(i);
	}


	auto cmp = [](element a, element b) {return a.f > b.f; };
	priority_queue <element, deque <element>, decltype(cmp)> pq(cmp);

	
	
	while (!q.empty()) {
		element e;
		e.str = array[q.front()].str;
		e.step = 1;
		e.f = array[q.front()].f + e.step;
		e.Sx = Sx;
		e.Sy = Sy;
		e.ptr = AddElement(e.str, root);
		pq.push(e);
		q.pop();
	}
	
	while (true)
	{
		string tmp = pq.top().str;
		list* ptr = pq.top().ptr;
		if (CompareString(tmp))
		{
			cout << "Нашли!" << endl;
			cout << endl;
			cout << endl;
			cout << "Время выполнения: " << clock() / 1000.0 << endl;
			cout << "Количество перестановок: " << pq.top().step << endl;
			cout << "Путь: " << endl;
			GoUp(ptr);
			break;
		}
		int xc, yc;
		int a = 0;
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < n; k++) {
				if (tmp[a] == ' ') {
					xc = j;
					yc = k;
				}
				a++;
			}
		}
		
		for (int i = 0; i < 4; i++)
		{
			int xcurr, ycurr;
			a = 0;
			string s;
			char tcurr[n][n];
			if (CheckBorder(xc + xarray[i], yc + yarray[i]) == 1)
			{
				for (int j = 0; j < n; j++) {
					for (int k = 0; k < n; k++) {
						tcurr[j][k] = tmp[a];
						a++;
					}
				}
				swap(tcurr[xc + xarray[i]][yc + yarray[i]], tcurr[xc][yc]);

				if (CheckStepBack(pq.top().Sx, pq.top().Sy, xc + xarray[i], yc + yarray[i])==0) {
					a = 0;
					for (int j = 0; j < n; j++) {
						for (int k = 0; k < n; k++) {
							s += tcurr[j][k];
							if (s[a] == ' ') {
								xcurr = j;
								ycurr = k;
							}
						}
					}
					array[i].str = s;
					array[i].f = FindG(tcurr) + pq.top().step + 1;
				}
				else {
					array[i].f = 0;
					array[i].str = "-";
				}
			}
			else {
				array[i].f = 0;
				array[i].str = "-";
			}
		}
		
			queue <int> qtmp;
			for (int i = 0; i < 4; i++) { 
				if (array[i].f != 0) qtmp.push(i);
			}
			int tmp_step = pq.top().step;
			pq.pop();
			while (!qtmp.empty()) {
				element etmp;
				etmp.str = array[qtmp.front()].str;
				etmp.ptr = AddElement(etmp.str, ptr);
				etmp.Sx = xc;
				etmp.Sy = yc;
				etmp.step = tmp_step + 1;
				etmp.f = array[qtmp.front()].f;
				pq.push(etmp);
				qtmp.pop();
			}

	}
	system("pause");
}