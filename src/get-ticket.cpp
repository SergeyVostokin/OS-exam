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

	ofstream fst;
	fst.open(path);

	if (fst.is_open()) {
		for (int i = 0; i < data.size(); i++) {
			fst << data[i] << endl;
		}
	}
	else {
		cout << "Файл c заданным путём: " << path << " не открыт или не существует!" << endl;
	}
	fst.close();
}

// метод для построчного считывания файла
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

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Russian");

	// настройка рандома для уникальности
	srand(time(0));

    // получаем параметры с консоли

	string path = argv[2];
	int length = path.length();

	// дополняем путь при необходимости
	if (path[length - 1] != '/') {
		path += "/";
	}


	string file = argv[1];

	string pathName = path + file;
	string pathFreeBlitz = path + "free-blitz.txt";
	string pathFreeQuests = path + "free-quests.txt";
	string pathQuests = path + "quests.txt";
	string pathTickets = path + "tickets.txt";

	// _____Начало блока подготовки файлов к работе и считывание вопросов из quests.txt_____

	// флаги успешной создания(при необходимости) и заполнения файлов
	bool successfullyQuests = false;
	bool successfullyFreeBlitz = false;
	bool successfullyFreeQuests = false;

	// берём имя из file (результат метода - вектор, берём элемент под 1 индексом)
	string student = readFile(pathName)[0];


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
	vector<string> fixFreeQuests;
	for (int i = 0; i < questions.size(); i++) {
		fixFreeQuests.push_back(to_string(i + 1));
	}

	// для free-blitz.txt
	int countTickets = 4;
	int countBlitzQuests = 16;
	vector<string> fixFreeBlitz;
	for (int i = 0; i < countTickets; i++) {
		for (int j = 0; j < countBlitzQuests; j++) {
			fixFreeBlitz.push_back(to_string(i + 1) + to_string(j + 1));
		}
	}

	// проверка на существование файла free-quests.txt и создание при отсутствии
	if (successfullyQuests) {

		// обрабатываем случай, если файл не существует
		if (!fileExists(pathFreeQuests)) {
			cout << "(!) Отсутствует файл free-quests.txt\nСоздаётся файл free-quests.txt" << endl;
			ofstream fout(pathFreeQuests);
			fout.close();
		}

		successfullyFreeQuests = true;
	}
	else {
		cout << "Невозможно работать с файлом free-quests.txt, так как неудачно считаны вопросы из файла quests.txt" << endl;
	}



	// проверка на существование файла free-blitz.txt и создание при отсутствии
	if (successfullyFreeQuests) {

		// обрабатываем случай, если файл не существует
		if (!fileExists(pathFreeBlitz)) {
			cout << "(!) Отсутствует файл free-blitz.txt\nСоздаётся файл free-blitz.txt" << endl;
			ofstream fout(pathFreeBlitz);
			fout.close();
		}

		successfullyFreeBlitz = true;
	}
	else {
		cout << "Невозможно работать с файлом free-blitz.txt, так как неудачно считаны вопросы из файла quests.txt" << endl;
	}

	// _____Конец блока подготовки файлов к работе и считывание вопросов из quests.txt_____



	vector<string> mainQuests; // хранение основных вопросов
	vector<string> blitzQuests; // хранение дополнительных вопросов с билетами

	int countMainQuests = 2;
	countBlitzQuests = 2;

	if (successfullyQuests && successfullyFreeQuests && successfullyFreeBlitz) {

		// ____Начало блока распределения вопросов_____

		for (int i = 0; i < countMainQuests; i++) {
			vector<string> varFreeQuests = readFile(pathFreeQuests);

			// проверка на наличие свободных номеров
			if (varFreeQuests.empty() || varFreeQuests[0] == "") {
				// если их нет, то заполняем файл заново
				writeFile(pathFreeQuests, fixFreeQuests);
				varFreeQuests = readFile(pathFreeQuests);
			}


			bool isFree = true;

			while (isFree) {
				string randNumberQuest = to_string(1 + rand() % fixFreeQuests.size()); // генерация от 1 до ...

				for (int j = 0; j < varFreeQuests.size(); j++) {

					// ищём совпадение по свободному вопросу
					if (randNumberQuest.compare(varFreeQuests[j]) == 0) {

						// если нашли, то добавляем его
						mainQuests.push_back(questions[stoi(randNumberQuest) - 1]);

						// удаляем элемент из вектора свободных вопросов
						varFreeQuests.erase(varFreeQuests.begin() + j);

						// перезаписываем файл free-quests.txt новым вектором свободных вопросов
						writeFile(pathFreeQuests, varFreeQuests);

						isFree = false;
						break;
					}
				}
			}
		}



		for (int i = 0; i < countBlitzQuests; i++) {
			vector<string> varFreeBlitz = readFile(pathFreeBlitz);

			// проверка на наличие свободных вопросов и билетов
			if (varFreeBlitz.empty() || varFreeBlitz[0] == "") {
				// если их нет, то заполняем файл заново
				writeFile(pathFreeBlitz, fixFreeBlitz);
				varFreeBlitz = readFile(pathFreeBlitz);
			}

			bool isFree = true;

			while (isFree) {
				string randNumberTicket = to_string(1 + rand() % 4); // генерация от 1 до 4
				string randNumberQuest = to_string(1 + rand() % 16); // генерация от 1 до 16
				string randTicketQuest = randNumberTicket + randNumberQuest;

				for (int j = 0; j < varFreeBlitz.size(); j++) {

					// ищём совпадение по свободному вопросу и билету
					if (randTicketQuest.compare(varFreeBlitz[j]) == 0) {

						// если нашли, то добавляем их
						blitzQuests.push_back(randTicketQuest);

						// удаляем элемент из вектора свободных вопросов и билетов
						varFreeBlitz.erase(varFreeBlitz.begin() + j);

						// перезаписываем файл free-blitz.txt новым вектором свободных вопросов и билетов
						writeFile(pathFreeBlitz, varFreeBlitz);

						isFree = false;
						break;
					}
				}
			}
		}

		// ____Конец блока распределения вопросов_____


		// ____Начало блока заполнения файла информацией о студенте и его вопросах

		// обрабатываем случай, если файл не существует
		if (!fileExists(pathTickets)) {
			cout << "(!) Отсутствует файл tickets.txt\nСоздаётся файл  tickets.txt" << endl;
			ofstream fout(pathTickets);
			fout.close();
		}

		int number = 0;
		// открываем файл в режиме дозаписи
		fstream fst(pathTickets, ios::app);
		if (fst.is_open()) {

			// запись ФИО студента
			fst << student << endl;

			// запись основных вопросов
			for (int i = 0; i < mainQuests.size(); i++) {
				number++;
				fst << to_string(number) + ") " << mainQuests[i] << endl;
			}

			// запись дополнительных вопросов
			for (int i = 0; i < blitzQuests.size(); i++) {
				number++;

				string ticketQuest = blitzQuests[i];

				// получаем номер билета
				char ticket = ticketQuest[0];

				// получаем номер вопроса
				string quest = "";
				for (int j = 1; j < ticketQuest.size(); j++) {
					quest += ticketQuest[j];
				}

				fst << to_string(number) + ") " << "билет " << ticket << " вопрос " << quest << endl;
			}

			fst << " " << endl; // отступ для следующей записи
		}

		// ____Конец блока заполнения файла информацией о студенте и его вопросах


		// вывод в консоль вопросов
		for (int i = 0; i < mainQuests.size(); i++) {
			cout << to_string(i + 1) + ") " << mainQuests[i] << endl;
		}
		cout << "дополнительные вопросы 3) 4) объявляются экзаменатором после ответа на вопросы 1) 2)" << endl;

	}
	else {
		cout << "(!) Для получения вопросов не подготовлены основные файлы!" << endl;
	}
	
}
