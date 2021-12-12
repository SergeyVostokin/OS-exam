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

	
	// флаги успешного окончания работы с файлами
	bool successfullyQuests = false;
	bool successfullyFreeBlitz = false;
	bool successfullyFreeQuests = false;

	ifstream fin; // для чтения файлов
	ofstream fout; // для записи в файлы

	// хранение вопросов из quests.txt
	vector<string> questions;
	// считывание вопросов из файла quests.txt
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


	// хранение свободных вопросов 
	vector<int> freeQuests;

	if (successfullyQuests) {

		fin.open(pathFreeQuests);
		// обрабатываем случай, если файл не существует
		if (fin.fail()) {

			fin.close();
			cout << "Отсутствует файл free-quests.txt \n Создаётся файл free-quests.txt" << endl;
			ofstream(pathFreeQuests);

			// открываем файл для записи
			fout.open(pathFreeQuests);

			// заполняем файл free-quests.txt от 1 по числу вопросов в файле 
			for (int i = 0; i < questions.size(); i++) {
				fout << i + 1 << endl;
			}

			fout.close();

			// открываем повторно для чтения
			fin.open(pathFreeQuests);
		}

		while (getline(fin, numberQuestion)) {
			freeQuests.push_back(numberQuestion);
		}

		successfullyFreeQuests = true;

		fin.close();
	}
	else {
		cout << "Невозможно работать с файлом free-quests.txt, так как неудачно считаны вопросы из файла quests.txt" << endl;
	}

	// хранение свободных вопросов для блиц опроса
	vector<string> freeBlitz;
	
	if (successfullyFreeQuests) {
		
		fin.open(pathFreeBlitz);
		// обрабатываем случай, если файл не существует
		if (fin.fail()) {

			fin.close();
			cout << "Отсутствует файл free-blitz.txt \n Создаётся файл free-blitz.txt" << endl;
			ofstream(pathFreeBlitz);

			// открываем файл для записи
			fout.open(pathFreeBlitz);

			// заполняем файл free-blitz.txt всеми парами вида (1..4) (1..16)
			int countTickets = 4;
			int countQuestions = 16;
			for (int i = 0; i < countTickets; i++) {
				for (int j = 0; j < countQuestions; j++) {
					fout << (i + 1) + " " + (j + 1) << endl;
				}
			}

			fout.close();

			// открываем повторно для чтения
			fin.open(pathFreeBlitz);
		}


		while (getline(fin, numberTicketsAndQuestion)) {
			freeBlitz.push_back(numberTicketsAndQuestion);
		}

		successfullyFreeBlitz = true;

		fin.close();
	}
	else {
		cout << "Невозможно работать с файлом free-blitz.txt, так как неудачно считаны вопросы из файла quests.txt" << endl;
	}
}