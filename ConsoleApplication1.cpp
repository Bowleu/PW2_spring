#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>
#include <conio.h>
#include <math.h>
using namespace std;

struct List {
	List* prev;
	List* next;
	int data;
};

void setTextColor(int textColorIndex) { // Смена цвета текста
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, (0 << 4) + textColorIndex);
}

List *createList(int length) {
	if (length) 
	{
		clock_t timeStart = clock();
		List* curr = nullptr,
			* next = nullptr;
		for (int i = 0; i < length; i++) {
			curr = new List;
			if (!curr) {
				cout << "Ошибка создания списка!\n";
				system("pause");
				return nullptr;
			}
			curr->next = next;
			if (next)
				next->prev = curr;
			next = curr;
		}
		curr->prev = nullptr;
		clock_t timeEnd = clock();
		double timeSpent = (double)(timeEnd - timeStart);
		cout << "Потраченное время: " << timeSpent << " мс.\n";
		system("pause");
		return curr;
	}
	return nullptr;
}

void fillRandom(List* curr) {
	srand(time(0));
	while (curr) {
		curr->data = rand() % 100;
		curr = curr->next;
	}
}

void fillByUser(List* curr, int values[]) {
	int i = 0;
	while (curr) {
		curr->data = values[i];
		curr = curr->next;
		i++;
	}
}

int* inputSeparation(string input, unsigned& length) {
	string temp = "";
	int *values = new int[input.length() / 2 + 1];
	for (int i = 0; i < input.length(); i++) {
		if (input[i] != ' ' and input[i] != '\t') {
			temp += input[i];
		}
		else if (temp != "") {
			values[length] = stoi(temp);
			length++;
			temp = "";
		}
	}
	if (temp != "") {
		values[length] = stoi(temp);
		length++;
	}

	int* tempArr = new int[length];
	for (int i = 0; i < length; i++)
		tempArr[i] = values[i];
	delete[] values;
	values = new int[length];
	for (int i = 0; i < length; i++)
		values[i] = tempArr[i];
	delete[] tempArr;
	return values;
}

List* addElement(unsigned index, List *curr) {
	int value;
	cout << "Введите значение Data нового элемента: ";
	cin >> value;
	clock_t timeStart = clock();
	List *newItem = new List;
	newItem->data = value;
	newItem->prev = nullptr;
	newItem->next = curr;
	for (int i = 0; i < index; i++) {
		curr = curr->next;
		if (curr)
			newItem->prev = curr->prev;
		else
			newItem->prev = newItem->next;
		newItem->next = curr;
	}
	if (newItem->prev)
		newItem->prev->next = newItem;
	if (newItem->next)
		newItem->next->prev = newItem;
	clock_t timeEnd = clock();
	double timeSpent = (double)(timeEnd - timeStart);
	cout << "Потраченное время: " << timeSpent << " мс.\n";
	system("pause");
	return newItem;
}

List * deleteElementByIndex(unsigned index, List* curr, bool needTimeSpent) {
	clock_t timeStart = clock();
	for (int i = 0; i < index; i++) {
		curr = curr->next;
	}
	if (curr->next)
		curr->next->prev = curr->prev;
	if (curr->prev)
		curr->prev->next = curr->next;
	List *nextBegin = curr->next;
	delete curr;
	if (needTimeSpent) {
		clock_t timeEnd = clock();
		double timeSpent = (double)(timeEnd - timeStart);
		cout << "Потраченное время: " << timeSpent << " мс.\n";
		system("pause");
	}
	return nextBegin;
}

List *deleteElementByValue(unsigned value, List* curr) {
	clock_t timeStart = clock();
	while (curr and curr->data != value) {
		curr = curr->next;
	}
	if (curr) {
		if (curr->next)
			curr->next->prev = curr->prev;
		if (curr->prev)
			curr->prev->next = curr->next;
		List* newBegin = curr->next;
		delete curr;
		clock_t timeEnd = clock();
		double timeSpent = (double)(timeEnd - timeStart);
		cout << "Потраченное время: " << timeSpent << " мс.\n";
		system("pause");
		return newBegin;
	}
	else {
		cout << "Элемента с таким значением нет в списке!\n";
	}
	system("pause");
	return curr;
}

void getElementByIndex(unsigned index, List* curr) {
	clock_t timeStart = clock();
	for (int i = 0; i < index; i++) {
		curr = curr->next;
	}
	cout << '\n';
	cout << setfill('#') << setw(20) << left << "";
	cout << '\n';
	cout << '#' << setfill(' ') << setw(18) << "" << '#';
	cout << '\n';
	cout << "# " << setw(9) << left << "Index:" << setw(7) << index << " #";
	cout << '\n';
	cout << "# " << setw(9) << left << "Data:" << setw(7) << curr->data << " #";
	cout << '\n';
	cout << '#' << setfill(' ') << setw(18) << "" << '#';
	cout << '\n';
	cout << setfill('#') << setw(20) << left << "";
	cout << '\n';
	cout << '\n';
	clock_t timeEnd = clock();
	double timeSpent = (double)(timeEnd - timeStart);
	cout << "Потраченное время: " << timeSpent << " мс.\n";
	system("pause");
}

void getElementByValue(unsigned value, List* curr) {
	clock_t timeStart = clock();
	int index = 0;
	while (curr and curr->data != value) {
		curr = curr->next;
		index++;
	}
	if (curr) {
		cout << '\n';
		cout << setfill('#') << setw(20) << left << "";
		cout << '\n';
		cout << '#' << setfill(' ') << setw(18) << "" << '#';
		cout << '\n';
		cout << "# " << setw(9) << left << "Index:" << setw(7) << index << " #";
		cout << '\n';
		cout << "# " << setw(9) << left << "Data:" << setw(7) << curr->data << " #";
		cout << '\n';
		cout << '#' << setfill(' ') << setw(18) << "" << '#';
		cout << '\n';
		cout << setfill('#') << setw(20) << left << "";
		cout << '\n';
		cout << '\n';
		clock_t timeEnd = clock();
		double timeSpent = (double)(timeEnd - timeStart);
		cout << "Потраченное время: " << timeSpent << " мс.\n";
	}
	else {
		cout << "Элемента с таким значением нет в списке!\n";
	}
	system("pause");
}

List* changeElements(unsigned id1, unsigned id2, List* curr) {
	clock_t timeStart = clock();
	List* begin = curr;
	for (int i = 0; i < id1; i++) {
		curr = curr->next;
	}
	List* elem1 = curr;
	curr = begin;
	for (int i = 0; i < id2; i++) {
		curr = curr->next;
	}
	List* elem2 = curr;
	/*swap(elem1->data, elem2->data);*/   // Обмен узлов данными
	if (elem1->next != elem2 and elem2->next != elem1) {
		if (elem1->next and elem2->next) {    // Обмен узлов адресами
			swap(elem1->next->prev, elem2->next->prev);
		}
		else if (elem1->next) {
			elem1->next->prev = elem2;
		}
		else if (elem2->next) {
			elem2->next->prev = elem1;
		}
		if (elem1->prev and elem2->prev) {
			swap(elem1->prev->next, elem2->prev->next);
		}
		else if (elem1->prev) {
			elem1->prev->next = elem2;
		}
		else if (elem2->prev) {
			elem2->prev->next = elem1;
		}
		swap(elem1->next, elem2->next);
		swap(elem1->prev, elem2->prev);
	}
	else {
		if (elem2->next == elem1)
			swap(elem1, elem2);
		if (elem1->prev)
			elem1->prev->next = elem2;
		if (elem2->next)
			elem2->next->prev = elem1;
		elem1->next = elem2->next;
		elem2->next = elem1;
		elem2->prev = elem1->prev;
		elem1->prev = elem2;
	}
	clock_t timeEnd = clock();
	double timeSpent = (double)(timeEnd - timeStart);
	cout << "Потраченное время: " << timeSpent << " мс.\n";
	system("pause");
	if (id2 == 0)
		return elem1;
	if (id1 == 0)
		return elem2;
	return nullptr;
}

void creationOutput(int current) {
	setTextColor(15);
	cout << "\tКак создать список?\n";
	setTextColor(6 - (current == 1 ? 5 : 0));
	cout << "[1] ";
	setTextColor(15);
	cout << "Заполнить список автоматически." << '\n';
	setTextColor(6 - (current == 2 ? 5 : 0));
	cout << "[2] ";
	setTextColor(15);
	cout << "Заполнить список вручную." << '\n';
	setTextColor(4 - (current == 3 ? 3 : 0));
	cout << "[ESC] ";
	setTextColor(15);
	cout << "Выход из программы." << '\n';
}

void actionOutput(int current) {
	setTextColor(15);
	cout << "\tВыберите действие.\n";
	setTextColor(6 - (current == 1 ? 5 : 0));
	cout << "[1] ";
	setTextColor(15);
	cout << "Вставить элемент." << '\n';
	setTextColor(6 - (current == 2 ? 5 : 0));
	cout << "[2] ";
	setTextColor(15);
	cout << "Удалить элемент по индексу." << '\n';
	setTextColor(6 - (current == 3 ? 5 : 0));
	cout << "[3] ";
	setTextColor(15);
	cout << "Удалить элемент по значению." << '\n';
	setTextColor(6 - (current == 4 ? 5 : 0));
	cout << "[4] ";
	setTextColor(15);
	cout << "Получить элемент по индексу." << '\n';
	setTextColor(6 - (current == 5 ? 5 : 0));
	cout << "[5] ";
	setTextColor(15);
	cout << "Получить элемент по значению." << '\n';
	setTextColor(6 - (current == 6 ? 5 : 0));
	cout << "[6] ";
	setTextColor(15);
	cout << "Обмен элементов." << '\n';
	setTextColor(6 - (current == 7 ? 5 : 0));
	cout << "[7] ";
	setTextColor(15);
	cout << "Вывод всего списка." << '\n';
	setTextColor(6 - (current == 8 ? 5 : 0));
	cout << "[8] ";
	setTextColor(15);
	cout << "Удаление нечетных элементов (ИДЗ-5)." << '\n';
	setTextColor(4 - (current == 9 ? 3 : 0));
	cout << "[ESC] ";
	setTextColor(15);
	cout << "Выход из программы." << '\n';
}

void fullListOutput(List* curr) {
	int counter = 0;
	cout << '\t';
	while (curr) {
		cout << setfill('#') << left << setw(20) << "";
		cout << "\n\t";
		cout << '#' << setfill(' ') << setw(18) << "" << '#';
		cout << "\n\t";
		cout << "# " << setw(9) << left << "Index:" << setw(7) << counter << " #";
		cout << "\n\t";
		cout << "# " << setw(9) << left << "Data:" << setw(7) << curr->data << " #";
		cout << "\n\t";
		cout << '#' << setfill(' ') << setw(18) << "" << '#';
		cout << "\n\t";
		cout << setfill('#') << setw(20) << left << "";
		cout << "\n\t";
		if (curr->next) {
			cout << setfill(' ') << right;
			wcout << setw(7) << L"↑" << setw(7) << "|" << "\n\t";
			cout << setw(7) << "|" << setw(7) << "|" << "\n\t";
			cout << setw(7) << "|" << setw(7) << "|" << "\n\t";
			cout << setw(7) << "|" << setw(7) << "|" << "\n\t";
			wcout << setw(7) << "|" << setw(7) << L"↓" << "\n\t";
		}
		counter++;
		curr = curr->next;
	}
	system("pause");
}

List *idz(List* curr, unsigned &length) {
	List* begin = curr;
	int* dynamicArray = new int[length];
	int i = 0;
	while (curr) {
		dynamicArray[i] = curr->data;
		i++;
		curr = curr->next;
	}
	curr = begin;
	//
	// List
	//
	clock_t timeStart = clock();
	unsigned index = 0;
	begin = begin->next;
	for (int i = 0; i < length; i++) {
		List* next = curr->next;
		if (i % 2 == 0) {
			if (curr->next)
				curr->next->prev = curr->prev;
			if (curr->prev)
				curr->prev->next = curr->next;
			delete curr;
		}
		curr = next;
	}
	clock_t timeEnd = clock();
	double timeList = (timeEnd - timeStart);
	//
	// Dynamic Array
	//
	timeStart = clock();
	int* tempArr = new int[length / 2];
	for (int i = 1; i < length; i += 2)
		tempArr[i / 2] = dynamicArray[i];
	delete[] dynamicArray;
	dynamicArray = new int[length / 2];
	for (int i = 1; i < length / 2; i += 2)
		dynamicArray[i] = tempArr[i];
	delete[] tempArr;
	timeEnd = clock();
	double timeArr = (timeEnd - timeStart); 
	//
	// Comparison
	//
	if (timeArr > timeList) {
		cout << "Список быстрее на " << timeArr - timeList << " мс.\n";
	}
	else if (timeArr < timeList) {
		cout << "Массив быстрее на " << timeList - timeArr << " мс.\n";
	}
	else {
		cout << "Затраченное время примерно одинаковое. Добавьте больше элементов.\n";
	}
	length /= 2;
	system("pause");
	return begin;
}

int main() {
	setlocale(LC_ALL, "");
	unsigned currentNum = 1;
	unsigned button;

	// Первое меню
	creationOutput(currentNum);
	while (true) {
		button = _getch();
		button = (button == 224) ? _getch() : button;
		if (button == 80 || button == 77) {
			system("cls");
			currentNum += 1;
			currentNum = currentNum == 4 ? 1 : currentNum;
			creationOutput(currentNum);
		}
		else if (button == 72 || button == 75) {
			system("cls");
			currentNum -= 1;
			currentNum = currentNum == 0 ? 3 : currentNum;
			creationOutput(currentNum);
		}
		else if (button >= 49 && button <= 50) {
			system("cls");
			currentNum = button - 48;
			creationOutput(currentNum);
			break;
		}
		else if (button == 13) {
			if (currentNum != 3)
				break;
			else {
				// Удаление массива
				return 0;
			}
		}
		else if (button == 27) {
            // Удаление массива
			return 0;
		}
	}
	system("cls");
	unsigned length = 0;
	string lengthString;
	List* begin = 0;
	switch (currentNum) {
	case 1:
		cout << "Введите длину массива: ";
		cin >> lengthString;
		for (int i = 0; i < lengthString.length(); i++) {
			if (not(lengthString[i] >= '0' and lengthString[i] <= '9')) {
				cout << "Неправильный ввод! Программа будет завершена!\n";
				system("pause");
				return 87;
			}
		}
		length = stoi(lengthString);
		begin = createList(length);
		fillRandom(begin);
		break;
	case 2:
		cout << "Введите значения узлов списка: ";
		unsigned valuesSize = 20;
		int* values;
		string input;
		char c = cin.get();
		while (c != '\n') {
			input += c;
			c = cin.get();
		}
		values = inputSeparation(input, length);
		begin = createList(length);
		fillByUser(begin, values);
		delete[] values;
		break;
	}               // Второе меню
	//

	system("cls");

	// Второе меню
	while (true) {
		system("cls");
		currentNum = 1;
		button = 0;
		actionOutput(currentNum);
		while (true) {
			button = _getch();
			button = (button == 224) ? _getch() : button;
			if (button == 80 || button == 77) {
				system("cls");
				currentNum += 1;
				currentNum = currentNum == 10 ? 1 : currentNum;
				actionOutput(currentNum);
			}
			else if (button == 72 || button == 75) {
				system("cls");
				currentNum -= 1;
				currentNum = currentNum == 0 ? 9 : currentNum;
				actionOutput(currentNum);
			}
			else if (button >= 49 && button <= 56) {
				system("cls");
				currentNum = button - 48;
				actionOutput(currentNum);
				break;
			}
			else if (button == 13) {
				if (currentNum != 9)
					break;
				else {
					// Удаление массива
					return 0;
				}
			}
			else if (button == 27) {
				// Удаление массива
				return 0;
			}
		}
		system("cls");
		switch (currentNum) {
		case 1:
		{
			unsigned index;
			string indexStr;
			cout << "Введите индекс элемента, перед которым хотите вставить новый узел (0 для вставки в начало списка): ";
			cin >> indexStr;
			for (int i = 0; i < indexStr.length(); i++) {
				if (not(indexStr[i] >= '0' and indexStr[i] <= '9')) {
					cout << "Неправильный ввод! Программа будет завершена!\n";
					system("pause");
					return 87;
				}
			}
			index = stoi(indexStr);
			if (index > length) {
				cout << "Неправильный ввод! Программа будет завершена!\n";
				system("pause");
				return 87;
			}
			List* newItem = addElement(index, begin);
			if (length != 0 and index == 0)
				begin = begin->prev;
			else if (index == 0)
				begin = newItem;
			length++;
		}
		break;
		case 2:
		{
			if (length) {
				unsigned index;
				string indexStr;
				cout << "Введите индекс элемента, который хотите удалить: ";
				cin >> indexStr;
				for (int i = 0; i < indexStr.length(); i++) {
					if (not(indexStr[i] >= '0' and indexStr[i] <= '9')) {
						cout << "Неправильный ввод! Программа будет завершена!\n";
						system("pause");
						return 87;
					}
				}
				index = stoi(indexStr);
				if (index >= length) {
					cout << "Неправильный ввод! Программа будет завершена!\n";
					system("pause");
					return 87;
				}

				List* newBegin = deleteElementByIndex(index, begin, 1);
				if (index == 0)
					begin = newBegin;
				length--;
			}
			else {
				cout << "Нельзя удалить элемент! В списке нет элементов!\n";
				system("pause");
			}
		}
		break;
		case 3:
		{
			if (length) {
				unsigned value;
				string valueStr;
				cout << "Введите значение элемента, который хотите удалить: ";
				cin >> valueStr;
				for (int i = 0; i < valueStr.length(); i++) {
					if (not(valueStr[i] >= '0' and valueStr[i] <= '9' or valueStr[i] != '-')) {
						cout << "Неправильный ввод! Программа будет завершена!\n";
						system("pause");
						return 87;
					}
				}
				value = stoi(valueStr);
				List* newBegin = deleteElementByValue(value, begin);
				if (value == begin->data)
					begin = newBegin;
			}
			else {
				cout << "Нельзя удалить элемент! В списке нет элементов!\n";
				system("pause");
			}
		}
		break;
		case 4:
		{
			if (length) {
				unsigned index;
				string indexStr;
				cout << "Введите индекс элемента, который хотите получить: ";
				cin >> indexStr;
				for (int i = 0; i < indexStr.length(); i++) {
					if (not(indexStr[i] >= '0' and indexStr[i] <= '9')) {
						cout << "Неправильный ввод! Программа будет завершена!\n";
						system("pause");
						return 87;
					}
				}
				index = stoi(indexStr);
				if (length != 0 and index >= length) {
					cout << "Неправильный ввод! Программа будет завершена!\n";
					system("pause");
					return 87;
				}
				getElementByIndex(index, begin);
			}
			else {
				cout << "В списке нет элементов!\n";
				system("pause");
			}
		}
		break;
		case 5:
		{
			if (length) {
				unsigned value;
				string valueStr;
				cout << "Введите значение элемента, который хотите получить: ";
				cin >> valueStr;
				for (int i = 0; i < valueStr.length(); i++) {
					if (not(valueStr[i] >= '0' and valueStr[i] <= '9' or valueStr[i] != '-')) {
						cout << "Неправильный ввод! Программа будет завершена!\n";
						system("pause");
						return 87;
					}
				}
				value = stoi(valueStr);
				getElementByValue(value, begin);
			}
			else {
				cout << "В списке нет элементов!\n";
				system("pause");
			}
		}
		break;
		case 6:
		{
			if (length > 1) {
				unsigned index1, index2;
				string indexStr1, indexStr2;
				cout << "Введите индексы элементов, которые хотите поменять: ";
				cin >> indexStr1 >> indexStr2;
				for (int i = 0; i < indexStr1.length(); i++) {
					if (not(indexStr1[i] >= '0' and indexStr1[i] <= '9')) {
						cout << "Неправильный ввод! Программа будет завершена!\n";
						system("pause");
						return 87;
					}
				}
				for (int i = 0; i < indexStr2.length(); i++) {
					if (not(indexStr2[i] >= '0' and indexStr2[i] <= '9')) {
						cout << "Неправильный ввод! Программа будет завершена!\n";
						system("pause");
						return 87;
					}
				}
				index1 = stoi(indexStr1);
				index2 = stoi(indexStr2);
				if (index1 >= length) {
					cout << "Неправильный ввод! Программа будет завершена!\n";
					system("pause");
					return 87;
				}
				if (index2 >= length) {
					cout << "Неправильный ввод! Программа будет завершена!\n";
					system("pause");
					return 87;
				}
				List* newBegin = changeElements(index1, index2, begin);
				if (newBegin)
					begin = newBegin;
			}
			else {
				cout << "В списке недостаточно элементов!\n";
				system("pause");
			}
		}
		break;
		case 7:
			fullListOutput(begin);
			break;
		case 8:
		{
			if (length)
				begin = idz(begin, length);
			else
			{
				cout << "В списке нет элементов!\n";
				system("pause");
			}
			
		}
			break;
		}
	}
	//

	return 0;
}