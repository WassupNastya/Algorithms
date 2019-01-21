#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <queue>
using namespace std;

struct element {
	int step;
	int bomb;
};
struct coordinate {
	int x;
	int y;
};

void analyzeDesk(int** desk, int x1, int y1, int bomb, int a, int b, element** desks) {
	queue <coordinate> way;
	coordinate start;
	start.x = x1;
	start.y = y1;

	desks[start.x][start.y].step = 1;

	way.push(start);

	while (!way.empty()) {
		if ((way.front().x + 1 >= 0) && (way.front().y >= 0) && (way.front().x + 1 < a) && (way.front().y < b)) {
			start.x = way.front().x + 1;
			start.y = way.front().y;

			if ((desk[start.x][start.y] != 1) && (desks[start.x][start.y].step == 0)) {
				desks[start.x][start.y].step = desks[way.front().x][way.front().y].step + 1;
				desks[start.x][start.y].bomb = desks[way.front().x][way.front().y].bomb;
				way.push(start);
			}
			else if ((desk[start.x][start.y] == 1) && (desks[start.x][start.y].step == 0) && (desks[way.front().x][way.front().y].bomb > 0)) {
				desks[start.x][start.y].step = desks[way.front().x][way.front().y].step + 1;
				desks[start.x][start.y].bomb = desks[way.front().x][way.front().y].bomb - 1;
				way.push(start);
			}
		}
		if ((way.front().x - 1 >= 0) && (way.front().y >= 0) && (way.front().x - 1 < a) && (way.front().y < b)) {
			start.x = way.front().x - 1;
			start.y = way.front().y;
			if ((desk[start.x][start.y] != 1) && (desks[start.x][start.y].step == 0)) {
				desks[start.x][start.y].step = desks[way.front().x][way.front().y].step + 1;
				desks[start.x][start.y].bomb = desks[way.front().x][way.front().y].bomb;
				way.push(start);
			}
			else if ((desk[start.x][start.y] == 1) && (desks[start.x][start.y].step == 0) && (desks[way.front().x][way.front().y].bomb > 0)) {
				desks[start.x][start.y].step = desks[way.front().x][way.front().y].step + 1;
				desks[start.x][start.y].bomb = desks[way.front().x][way.front().y].bomb - 1;
				way.push(start);
			}
		}
		if ((way.front().x >= 0) && (way.front().y + 1 >= 0) && (way.front().x < a) && (way.front().y + 1 < b)) {
			start.x = way.front().x;
			start.y = way.front().y + 1;
			if ((desk[start.x][start.y] != 1) && (desks[start.x][start.y].step == 0)) {
				desks[start.x][start.y].step = desks[way.front().x][way.front().y].step + 1;
				desks[start.x][start.y].bomb = desks[way.front().x][way.front().y].bomb;
				way.push(start);
			}
			else if ((desk[start.x][start.y] == 1) && (desks[start.x][start.y].step == 0) && (desks[way.front().x][way.front().y].bomb > 0)) {
				desks[start.x][start.y].step = desks[way.front().x][way.front().y].step + 1;
				desks[start.x][start.y].bomb = desks[way.front().x][way.front().y].bomb - 1;
				way.push(start);
			}
		}
		if ((way.front().x >= 0) && (way.front().y - 1 >= 0) && (way.front().x < a) && (way.front().y - 1 < b)){
			start.x = way.front().x;
			start.y = way.front().y - 1;
			if ((desk[start.x][start.y] != 1) && (desks[start.x][start.y].step == 0)) {
				desks[start.x][start.y].step = desks[way.front().x][way.front().y].step + 1;
				desks[start.x][start.y].bomb = desks[way.front().x][way.front().y].bomb;
				way.push(start);
			}
			else if ((desk[start.x][start.y] == 1) && (desks[start.x][start.y].step == 0) && (desks[way.front().x][way.front().y].bomb > 0)) {
				desks[start.x][start.y].step = desks[way.front().x][way.front().y].step + 1;
				desks[start.x][start.y].bomb = desks[way.front().x][way.front().y].bomb - 1;
				way.push(start);
			}
		}
		way.pop();
	}
}
int main() {
	setlocale(LC_ALL, "Russian");
	int** desk;
	int a, b, x1, y1, x2, y2, bomb;
	cout << "Введите размеры поля: ";
	cin >> a >> b;
	cout << "Введите координаты старта: ";
	cin >> x1 >> y1;
	cout << "Введите координаты финиша: ";
	cin >> x2 >> y2;
	cout << "Введите количество бомб: ";
	cin >> bomb;
	desk = (int**)malloc(a * sizeof(int));
	for (int i = 0; i < b; i++) {
		desk[i] = (int*)malloc(a * sizeof(int));
	}
	string buffer;
	ifstream file("text.txt");
	for (int i = 0; i < b; i++) {
		string str;
		getline(file, str);
		buffer += str;
	}
	int count = 0;
	for (int i = 0; i < a; i++) {
		for (int j = 0; j < b; j++) {
			desk[i][j] = buffer[count]-'0';
			count++;
		}
	}
	file.close();

	vector <element**> desks;
	for (int k = 0; k <= bomb; k++) {
		element** tmp;
		tmp = (element**)malloc(a * sizeof(element));
		for (int i = 0; i < b; i++) {
			tmp[i] = (element*)malloc(a * sizeof(element));
		}
		for (int i = 0; i < a; i++) {
			for (int j = 0; j < b; j++) {
				tmp[i][j].step = 0;
				tmp[i][j].bomb = k;
			}
		}
		desks.push_back(tmp);
	}
	
	for (vector<element**>::iterator it = desks.begin(); it != desks.end(); ++it)
		analyzeDesk(desk, x1, y1, bomb, a, b, *it);


	cout << endl;
	int minSteps = 10000;
	int minBombs = bomb;
	for (int count = 0; count <= bomb; count++) {
		if ((desks[count][x2][y2].step != 0) && (desks[count][x2][y2].step < minSteps)) {
			minSteps = desks[count][x2][y2].step;
			minBombs = count;
		}
	}
			cout << "Количество бомб: " << minBombs << " - количество шагов: " << minSteps - 1 << endl;

	system("pause");
}