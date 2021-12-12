#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;


// метод проверки на существование файла
bool fileExists(string path) {

	fstream fst;
	bool result = false;

	fst.open(path);

	if (!fst.fail()) {
		result = true;
		fst.close();
	}

	return result;
}

// метод для построчного заполнения файла 
void writeFile(string path, vector<string> data) {

	fstream fst;
	fst.open(path);

	if (fst.is_open()) {
		for (int i = 0; i < data.size(); i++) {
			fst << data[i] << endl;
		}

		fst.close();
	}
	else {
		cout << "Файл c заданным путём: " << path << " не открыт или не существует!" << endl;
	}
}

// метод для построчного считывания файла
vector<string> readFile(string path) {

	vector<string> result;

	fstream fst;
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

	// относительный путь к каталогу txt файлов
	string path = "../data/";

	string pathFreeBlitz = path + "free-blitz.txt";
	string pathFreeQuests = path + "free-quests.txt";
	string pathQuests = path + "quests.txt";

	
	// _____Начало блока подготовки файлов к работе и считывание вопросов из quests.txt_____
	
	// флаги успешной создания(при необходимости) и заполнения файлов
	bool successfullyQuests = false;
	bool successfullyFreeBlitz = false;
	bool successfullyFreeQuests = false;

	
	vector<string> questions; // хранение вопросов из quests.txt

	// считывание вопросов из файла quests.txt
	if (fileExists(pathQuests)) {
		questions = readFile(pathQuests);
		successfullyQuests = true;
	}
	else {
		cout << "Произошла ошибка при открытии файла с вопросами!" << endl;
	}
	
	
	// подготовка данных для заполнения файлов
	// для free-quests.txt
	vector<string> freeQuests;
	for (int i = 0; i < questions.size(); i++) {
		freeQuests.push_back(to_string(i + 1);
	}

	// для free-blitz.txt
	int countTickets = 4;
	int countBlitzQuests = 16;
	vector<string> freeBlitz;
	for (int i = 0; i < countTickets; i++) {
		for (int j = 0; j < countBlitzQuests) {
			freeBlitz.push_back(to_string(i) + to_string(j));
		}
	}

	// проверка на существование файла free-quests.txt и его заполнения
	if (successfullyQuests) {

		// обрабатываем случай, если файл не существует
		if (!fileExists(pathFreeQuests)) {
			cout << "Отсутствует файл free-quests.txt \n Создаётся файл free-quests.txt" << endl;
			ofstream(pathFreeQuests);
		}
		
		writeFile(pathFreeQuests, freeQuests);
		successfullyFreeQuests = true;
	}
	else {
		cout << "Невозможно работать с файлом free-quests.txt, так как неудачно считаны вопросы из файла quests.txt" << endl;
	}

	

	// проверка на существование файла free-blitz.txt и его заполнения
	if (successfullyFreeQuests) {

		// обрабатываем случай, если файл не существует
		if (!fileExists(pathFreeQuests)) {
			cout << "Отсутствует файл free-blitz.txt \n Создаётся файл free-blitz.txt" << endl;
			ofstream(pathFreeBlitz);
		}
		
		
		writeFile(pathFreeBlitz, freeBlitz);
		successfullyFreeBlitz = true;
	}
	else {
		cout << "Невозможно работать с файлом free-blitz.txt, так как неудачно считаны вопросы из файла quests.txt" << endl;
	}

	// _____Конец блока подготовки файлов к работе и считывание вопросов из quests.txt_____

}