﻿/* 6. Написать метод, который будет проверять, является ли строка правильным
идентификатором, удовлетворяющим следующим требованиям: имя может содержать от 1
до 127 символов; первым символом не должна быть цифра; символами идентификатора
могут быть буквы (строчные или прописные), цифры (от 0 до 9) и символ подчеркивания.
Если обнаружена ошибка, необходимо выдать сообщение, квалифицирующее ее. */

#include<iostream>
#include<string>
#include<fstream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::fstream;


int checkN(string n); // Проверка ввода
bool contin(); // Интерфейс
string solution(string); // Проверка идентификатора
bool alph(char*, char);	// Проверка, явл-ся ли символ русской буквой
void mistake(); // Вывод сообщ-я об ошибке
void end(); // Вывод сообщ-я о завершении раб-ты

int main()
{
	setlocale(0, "");

	while (true)
	{	// Чтение файла
		fstream fin = fstream("TextFile.txt");
		if (!fin) { cout << "Ошибка в чтении файла!" << endl;	end();	break;	}

		// Ввод выбора примера исходных данных
		cout << "Какой пример использовать?" << endl << "от (1)-го до (7)-го / Закрыть программу (0)" << endl;
		string chex;
		getline(cin, chex);

		// Проверка верности введённого знач-ия и запуск заного из-за ошибки или завершение работы прогр-мы
		int ex = checkN(chex);
		if (ex == -1)	{	continue;	}
		else if (ex == 0)	{	break; }
		
		// Вычленение из файла запрашиваемого примера
		string str;
		int i = 0;
		while (i != ex)
		{	getline(fin, str);	++i;	}

		// Вывод исходных данных и результата работы прогр-мы
		cout << "Строка в файле:" << endl << "\"" << str << "\"" << endl;
		cout << "Результат проверки идентификатора:" << endl << solution(str) /* Проверка идентификатора */ << endl;

		// Интерфейс
		if (contin())
			continue;
		break;	}

	return 0;
}

// Проверка ввода
int checkN(string n)
{	
	// Если введённое значение длиннее 1-го симв-ла или не цифра
	if (n.length() != 1 || !isdigit(n[0]))
	{	mistake();	return -1; }
	
	// Раз цифра, то какая 
	int b = atoi(n.c_str());
	if (b >= 0 || b <= 7)	{	return b;	} // Если от 0 до 7, то её и возврщаем
	else	{	mistake();	return -1;	} // Если нет, то ошибка
}

// Проверка идентификатора
string solution(string str)
{
	char rus[67] = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЬЫЭЮЯабвгдеёжзийклмнопрстуфхцчшщъьыэюя"; // Русские буквы
	int len = str.length(); // Длинна строки
	if (len == 0 || len > 127) {	return "Имя может содержать от 1 до 127 символов"; } // Ошибка, связанная с длинной строки
	else if (isdigit(str[0])) {	return "Первым символом не должна быть цифра"; } // Ошибка, если первый символ - цифра
	
	// Проходимся по каждому эл-ту строки
	for (int i = 0; i < len; ++i)
	{	char s = str[i]; // Каждый эл-т строки (для краткости записи следующего if-а)
		// Если символ не подчеркивание, не цифра, не английская или русская буква, выводим соответствующую ошибку
		if (s != '_' && !isdigit(s) && (s < 'A' || s > 'Z') && (s < 'a' || s > 'z') && (!alph(rus, s)))
		{	return "Cимволами идентификатора могут быть толкько буквы (строчные или прописные), цифры(от 0 до 9) и символ подчеркивания";	}	}

	// Если ни одно из усл-й ошибок не выполнено, возвращаем в вывод верный идентификатор
	return "Ваш идентификатор: " + str;
}

// Проверка, явл-ля ли символ русской буквой
bool alph(char *rus, char s)
{	// Проходимся по каждой букве и сравниваем с символом
	for (int j = 0; j < 67; ++j)
		{	if (s == rus[j]) {	return 1;	}	}
	return 0;
}

// Интерфейс
bool contin()
{
	while (true)
	{	string c;
		cout << "\nЗапустить программу сначала (1) / Закрыть программу (0)" << endl;
		getline(cin, c);

		if (c == "0")
		{	cout << "Закрытие программы..." << endl;	return 0;	break;	}
		
		else if (c == "1")
		{	return 1;	break;	}

		else
		{	mistake();	continue;	}

		break;	}	}

// Вывод сообщения об ошибке
void mistake()
{	cout << "Некорректный ввод, попробуйте снова!" << endl << endl;	}

// Вывод сообщения о заверш-нии раб-ты прогр-мы
void end()
{	cout << "Закрытие программы..." << endl;	}