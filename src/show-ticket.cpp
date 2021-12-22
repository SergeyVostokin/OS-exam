#include <locale.h>
#include <string>
#include <time.h>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

string const dataPath = "../data/";
int const studentData = 5;

vector<int> findIndexNode(vector<string> arr, string node) {
	vector<int> indexs;
	for (int i = 0; i < arr.size(); i++)
	{
		if(arr[i]._Equal(node)) {
			indexs.push_back(i);
		}
	}
	return indexs;
}

vector<string> readFile(string path) {
	
	vector<string> result;

	ifstream fst;
	fst.open(path);

	if (fst.is_open()) {
		string data;
		while (getline(fst, data)) {
			result.push_back(data);
		}

		fst.close();
	}
	else {
		cout << "Файл c заданным путём: " << path << " не открыт или не существует!" << endl;
	}

	return result;
}

int main()
{
	setlocale(LC_ALL, "Russian");

	string pathTickets = dataPath + "tickets.txt";

	string studentName = "ФИО";

	vector<string> filesRows = readFile(pathTickets);

	if (filesRows.size() > 0) {
		vector<int> indexes = findIndexNode(filesRows, studentName);
		
		if (indexes.size() > 0) {
			for (int i = 0; i < indexes.size(); i++)
			{
				int index = indexes[i];

				for (int j = 0; j < studentData; j++)
				{
					cout << filesRows[index + j] << endl;
				}
			}
		}
		else {
			cout << "Билетов не обнаружено" << endl;
		}
	}


	return 0;
}