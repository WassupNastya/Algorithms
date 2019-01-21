#include "stdafx.h"
#include <iostream>
#include <algorithm> 
#include <queue> 
#include <fstream>
#include "cstdlib"

using namespace std;

struct COORDINATE {
	int x, y;
};
void PrintDesk(int x, int y, int** desk) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			cout << desk[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}
bool OutOfTheDesk(int x, int y, int hb, int vb) {
	if ((x >= hb) || (x < 0)) {
		return false;
	}
	else if ((y >= vb) || (y < 0)) {
		return false;
	}
	else return true;
}
bool IsItHorse(int x, int y, int bx, int by) {
	if ((x == bx) && (y == by)) {
		return true;
	}
	else return false;
}
bool NoStepBack(int ** desk, int i, int j) {
	if (desk[i][j] == 0) {
		return true;
	}
	return false;
}
bool Condition(int ** desk, int a, int b, int c, int d) {
		if (OutOfTheDesk(a, b, c, d) && NoStepBack(desk, a, b)) {
		return true;
	}
	else return false;
}
void Space() {
	cout << endl;
}
int UseSwap(int** desk, int* array1, int* array2, int x, int y) {
	int count = 0;
	for (int a = 0; a < 8; a++) {
		if (OutOfTheDesk(x + array1[a], y + array2[a], sizeof(desk), sizeof(desk))) {
			count++;
		}
	}
	return count;
}

void main()
{
	int hb, vb, x1, y1, x2, y2;
	int** desk;
	int MovesX[] = { 1,2,2,1,-1,-2,-2,-1 };
	int MovesY[] = { 2,1,-1,-2,-2,-1,1,2 };
	COORDINATE data;

	ifstream fin("text.txt");
	if (!fin.is_open())
		cout << "Error!\n";
	else
	{
		fin >> hb >> vb >> x1 >> y1 >> x2 >> y2;
		cout << hb << ' ' << vb << endl << x1 << ' ' << y1 << endl << x2 << ' ' << y2 << endl;
		Space();
		fin.close();
	}

	desk = (int**)malloc(hb * sizeof(int));
	for (int i = 0; i < hb; i++) {
		desk[i] = (int*)malloc(vb * sizeof(int));
	}

	if (UseSwap(desk, MovesX, MovesY, x1, y1) >= UseSwap(desk, MovesX, MovesY, x2, y2)) {
		swap(x1, x2);
		swap(y1, y2);
	}

	data.x = x1;
	data.y = y1;
	desk[x1][y1] = 1;

	queue <COORDINATE> c;

	c.push(data);
	for (int i = 0; i < hb; i++) {
		for (int j = 0; j < vb; j++) {
			desk[i][j] = 0;
			cout << desk[i][j] << ' ';
		}
		Space();
	}
	Space();

	
	while (!c.empty()) {
		for (int a = 0; a < 8; a++) {
			int &MoveX = MovesX[a];
			int &MoveY = MovesY[a];
			if (Condition(desk, c.front().x + MoveX, c.front().y + MoveY, hb, vb))
			{
				data.x = c.front().x + MoveX;
				data.y = c.front().y + MoveY;
				c.push(data);
				desk[data.x][data.y] = desk[c.front().x][c.front().y] + 1;
				if (IsItHorse(c.back().x, c.back().y, x2, y2)) {
					cout << "Result: " << desk[c.back().x][c.back().y] << endl;
					Space();
					PrintDesk(hb, vb, desk);
					Space();
					system("pause");
				}
			}
		}
		c.pop();
	}
}
