#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");

	// относительный путь к каталогу txt файлов
	string path = "../data/";

	string pathFreeBlitz = path + "free-blitz.txt";
	string pathFreeQuests = path + "free-quests.txt";
	string pathQuests = path + "quests.txt";

	// хранение вопросов
	vector<string> questions;

	// флаги успешного окончания работы с файлами
	bool successfullyQuests = false;
	bool successfullyFreeBlitz = false;
	bool successfullyFreeQuests = false;

	// считывание вопросов из файла quests.txt
	ifstream fin;
	fin.open(pathQuests);

	if (fin.fail()) {
		cout << "Произошла ошибка при открытии файла с вопросами!" << endl;
	}
	else {
		string question;
		while (getline(fin, question)) {
			questions.push_back(question);
		}
		cout << "Вопросы успешно извлечены из файла!" << endl;
		successfullyQuests = true;
	}
	fin.close();


	// заполняем файл free-quests.txt от 1 по числу вопросов в файле 
	if (successfullyQuests) {
		ofstream fout;
		fout.open(pathFreeQuests);
		if (fout.fail()) {
			cout << "Отсутствует файл free-quests.txt \n Создаётся файл free-quests.txt" << endl;
			ofstream(pathFreeQuests);

			// делаем повторную попытку открытия файла
			fout.open(pathFreeQuests);
		}

		for (int i = 0; i < questions.size(); i++) {
			fout << i + 1 << endl;
		}

		successfullyFreeQuests = true;
		fout.close();
	}
	else {
		cout << "Невозможно работать с файлом free-quests.txt, так как неудачно считаны вопросы из файла quests.txt" << endl;
	}


	// заполняем файл free-blitz.txt всеми парами вида (1..4) (1..16)
	if (successfullyFreeQuests) {
		ofstream fout;
		fout.open(pathFreeBlitz);
		if (fout.fail()) {
			cout << "Отсутствует файл free-blitz.txt \n Создаётся файл free-blitz.txt" << endl;
			ofstream(pathFreeBlitz);

			// делаем повторную попытку открытия файла
			fout.open(pathFreeBlitz);
		}

		int countTickets = 4;
		int countQuestions = 16;
		for (int i = 0; i < countTickets; i++) {
			for (int j = 0; j < countQuestions; j++) {
				fout << (i + 1) + " " + (j + 1) << endl;
			}
		}

		successfullyFreeBlitz
			fout.close();
	}
	else {
		cout << "Невозможно работать с файлом free-blitz.txt, так как неудачно считаны вопросы из файла quests.txt" << endl;
	}
}