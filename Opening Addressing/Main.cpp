#include <iostream>
#include <string>
#include <list>
#include <fstream>
using namespace std;

const int SIZE = 10000,
CHOICE = 37;

string hashTable[SIZE];
int col = 0;
int h = 0;
int number = 100;

void newHashTable() {
	for (int i = 0; i < SIZE; i++) {
		hashTable[i] = "\0";
	}
}
void print() {
	for (int i = 0; i < SIZE; i++) {
		if (hashTable[i] != "\0") cout << "Key: " << i << " - value: " << hashTable[i] << endl;
		}
	cout << "Number of collisions: " << col << endl;
}
void addElement(string str) {
	int hash = 0;
	for (int i = 0; i < str.length(); i++)
		hash += CHOICE * h + (int)str[i];
	if (hashTable[hash] != "\0") {
		col++;
		int flag = 0;
		for (int i = 0; i <= SIZE - hash; i++) {
			if (hashTable[hash + i] == "\0") {
				hashTable[hash + i] = str;
				flag = 1;
				break;
			}
		}
		if (flag == 0) {
			for (int i = 0; i <= SIZE - hash; i++) {
				if (hashTable[hash + i] == "\0") {
					hashTable[hash + i] = str;
					break;
				}
			}
		}
	}
	else hashTable[hash] = str;
	h = h % number;
	return;
}
void writeToFile(int n) {
	const char* array[] = { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l",
							"m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z" };
	ofstream out;
	out.open("text.txt");
	if (out.is_open())
	{
		for (int j = 0; j < n; j++) {
			string s = "";
			for (int i = 0; i < 10; i++) {
				s += array[rand() % (sizeof array / sizeof(char*))];
			}
			out << s << endl;
		}
	}
	out.close();
}
int main() {
	setlocale(LC_ALL, "Russian");
	newHashTable();
	writeToFile(100);
	string line;
	ifstream in("text.txt");
	if (in.is_open())
	{
		while (getline(in, line))
		{
			addElement(line);
		}
	}
	in.close();
	print();
	system("pause");
}
