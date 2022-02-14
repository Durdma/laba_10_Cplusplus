//Подключение библиотек

#include <string> 
#include <stdio.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <vector>
#include <ctype.h>
#include <algorithm>
#include <queue>

//Подключение класса

#include "Node.h"

using namespace std;

//Структура, в которой содержатся все данные о каждом символе

struct letter
{

	char	symbol;					//Сам символ
	int		symb_code;				//Код символа
	int		quantity		= 0;	//Количество появлений символа в тексте
	float	probability		= 0;	//Вероятность появления символа в тексте
	float	entropy			= 0;	//Энтропия символа
	string  shennon			= "";	//Код Шеннона-Фано символа
	string	huffman			= "";	//Код Хаффмана символа

};

//Структура для построения сравнительной таблицы ascii и Хартли

struct second_table
{

	float	uncert			= 0; //Неопределенность кода
	int		numb_codes		= 0; //Количество разрядов кода
	float	abs_excess		= 0; //Абсолютная избытычность
	float	relat_excess	= 0; //Относительная избытычность

};

//Функция чтения текста из файла

void f_input				(string &input)
{

	string input_t;

	ifstream fin("TEXT.txt");

	while (fin)
	{


		cout << input_t << endl;
		getline(fin, input_t);
		input += input_t;

	}

	cout << "Источник: Бернар Вербер \"Империя ангелов\" Глава 1-2" << endl;
	cout << "Длина текста: " << input.length() << endl;
	cout << endl;

	for (int i = 0; i < input.length(); i++)
	{

		if (static_cast<int>(input[i]) >= -64 && static_cast<int>(input[i]) <= -33)
		{

			input[i] = static_cast<int>(input[i]) + 32;
			input[i] = static_cast<char>(input[i]);

		}

		if (static_cast<int>(input[i]) == -88)
		{

			input[i] = static_cast<int>(input[i]) + 16;
			input[i] = static_cast<char>(input[i]);

		}

		if (static_cast<int>(input[i]) == 32)
		{

			input[i] = static_cast<char>(input[i]);

		}

	}

}

//Функция подсчета количества появлений символа в тексте

void f_quantity				(const string &input, struct letter &new_letter)
{

	for (int i = 0; i < input.length(); i++)
	{


			if (new_letter.symbol == input[i])
			{

				new_letter.quantity++;

			}

	}

}

//Функция сортировки вектора символов по возрастанию кода символа

void f_sort					(vector<letter> &alphabet, struct letter &new_letter)
{

	vector<int>				codes;

	for (int i = 0; i < alphabet.size(); i++)
	{

		codes.push_back(alphabet.at(i).symb_code);

	}

	sort(codes.begin(), codes.end());

	for (int i = 0; i < codes.size(); i++)
	{

		for (int  j = 0; j < alphabet.size(); j++)
		{

			if (alphabet.at(j).symb_code == codes.at(i))
			{
				
				new_letter.symbol			= alphabet.at(i).symbol;
				new_letter.symb_code		= alphabet.at(i).symb_code;
				new_letter.quantity			= alphabet.at(i).quantity;

				alphabet.at(i).symbol		= alphabet.at(j).symbol;
				alphabet.at(i).symb_code	= alphabet.at(j).symb_code;
				alphabet.at(i).quantity		= alphabet.at(j).quantity;

				alphabet.at(j).symbol		= new_letter.symbol;
				alphabet.at(j).symb_code	= new_letter.symb_code;
				alphabet.at(j).quantity		= new_letter.quantity;

			}

		}

	}

}

//Функция расчета вероятности появления символа в тексте

void f_probability			(string &input, vector<letter> &alphabet)
{

	int		counter		= 0;
	float	summ		= 0;

	for (int i = 0; i < alphabet.size(); i++)
	{

		alphabet.at(i).probability = static_cast<float>(alphabet.at(i).quantity) / static_cast<float>(input.length());

	}

}

//Функция расчета энтропии символа

void f_entropy				(vector<letter> &alphabet)
{

	for (int i = 0; i < alphabet.size(); i++)
	{

		alphabet.at(i).entropy = -(alphabet.at(i).probability * log2f(alphabet.at(i).probability));

	}

}

//Функция для построения 1-ой таблицы лабораторной работы №8

void f_table_first			(const vector<letter> &alphabet, float &entropy_sum)
{
	
	float probability_sum	= 0;

	for (int i = 0; i < 117; i++)
	{

		cout<< "*";

	}
	
	cout << endl;

	cout << "*";
	cout << setw(22) << " Символ " << "|" << setw(22) << " Код символа " << "|" << setw(22) << " Число вхождений " << "|"
		 << setw(22) << " Вероятность вхождения " << "|" << setw(22) << " Энтропия " << "*" << endl;

	for (int i = 0; i < 117; i++)
	{

		cout << "*";

	}

	cout << endl;
	
	for (int i = 0; i < alphabet.size(); i++)
	{

		cout << "*";
		cout << endl;
		cout << "*";
		cout << setw(22) << alphabet.at(i).symbol << "|" << setw(22) << alphabet.at(i).symb_code << "|"
			 << setw(22) << alphabet.at(i).quantity << "|" << setw(22) << fixed << setprecision(5) << alphabet.at(i).probability 
			 << " |" << setw(22) << fixed << setprecision(5) << alphabet.at(i).entropy << "*" << endl;

	}

	cout << "*";

	for (int i = 0; i < 116; i++)
	{

		cout << "*";

	}

	cout << endl;

	cout << "*";

	for (int i = 0; i < 43; i++)
	{

		cout << " ";

	}

	cout << "  |" << setw(22) << "Общая вероятность";
		
	for (int i = 0; i < alphabet.size(); i++)
	{

		probability_sum += alphabet.at(i).probability;

	}

	cout << setw(22) << probability_sum << "  |" << setw(22) << " " << "*" << endl;

	cout << "*";

	for (int i = 0; i < 116; i++)
	{

		cout << "*";

	}

	cout << endl;

	cout << "* " << "Количесвто уникальных символов: " << setw(8) << alphabet.size();

	cout << "    |" << setw(22) << "Общая энтропия";

	for (int i = 0; i < alphabet.size(); i++)
	{

		entropy_sum += alphabet.at(i).entropy;

	}

	cout << setw(47) << entropy_sum << "*" << endl;

	for (int i = 0; i < 117; i++)
	{

		cout << "*";

	}

	cout << endl;
	cout << endl;

}

//Функция для расчета харакатеристик ascii и Хартли

void f_sec_part				(int i, struct second_table &ascii, struct second_table &hurtly, const float &entropy_sum)
{

	ascii.uncert		= log2f(255);
	ascii.numb_codes	= ceil(ascii.uncert);
	ascii.abs_excess	= ascii.uncert - entropy_sum;
	ascii.relat_excess	= ascii.abs_excess / ascii.uncert;

	hurtly.uncert		= log2f(i);
	hurtly.numb_codes	= ceil(hurtly.uncert);
	hurtly.abs_excess	= hurtly.uncert - entropy_sum;
	hurtly.relat_excess = hurtly.abs_excess / hurtly.uncert;

}

//Функция для построения 2-ой таблицы лабораторной работы №8

void f_table_second			(struct second_table &ascii, struct second_table &hurtly)
{

	for (int i = 0; i < 124; i++)
	{

		cout << "*";

	}

	cout << endl;

	cout << "*" << setw(21) << " Кодировка " << "|" << setw(22) << " Неопределенность " << "|" 
		 << setw(22) << " Разрядность кода " << "|" << setw(22) << " Абсолютная избыточность " 
		 << "|" << setw(22) << " Относительная избыточность " << "*" << endl;

	for (int i = 0; i < 124; i++)
	{

		cout << "*";

	}

	cout << endl;

	cout << "*" << setw(21) << "Таблица ASCII" << "|" << setw(22) << fixed << setprecision(5) << ascii.uncert 
		 << "|" << setw(22) << ascii.numb_codes << "|" << setw(22) << fixed << setprecision(5) << ascii.abs_excess
		 << "   |" << setw(22) << fixed << setprecision(5) << ascii.relat_excess << "      *" << endl;

	cout << "*" << setw(21) << "мера Хартли" << "|" << setw(22) << fixed << setprecision(5) << hurtly.uncert
		 << "|" << setw(22) << hurtly.numb_codes << "|" << setw(22) << fixed << setprecision(5) << hurtly.abs_excess
		 << "   |" << setw(22) << fixed << setprecision(5) << hurtly.relat_excess << "      *" << endl;

	for (int i = 0; i < 124; i++)
	{

		cout << "*";

	}

	cout << endl;

}

//Функция кодирования методом Шеннона-Фано

void f_shennon				(vector<letter> &alphabet, string  branch, string &fullBranch, int start, int end)
{

	double		dS			= 0;							//Переменная для хранения полусуммы вероятностей всех элементов
	double		S			= 0;							//Для хранения суммы вероятностей группы элементов

	int			i			= 0;							//Итератор

	string		cBranch		= "";							//Строка для хранения всей последовательности кода

	cBranch = fullBranch+branch;

	if (start == end)										//Присвоение кодовой комбинации листочку дерева
	{

		alphabet.at(start).shennon = cBranch;
		return;

	}

	for (i = start; i < end; i++)
	{

		dS	+= alphabet.at(i).probability;
	
	}
	
	dS		/= 2.;
	i		= start + 1;
	S		+= alphabet.at(start).probability;

	while ((fabsl(dS - (S + alphabet.at(i).probability)) < fabsl(dS - S)) && (i < end))
	{

		S	+= alphabet.at(i).probability;

		i++;

	}

		

		string zero		= "0";
		string one		= "1";

		f_shennon(alphabet, one, cBranch, start, i - 1);

		f_shennon(alphabet, zero, cBranch, i, end);

}

//Функция для построения таблицы с кодами Шеннона-Фано

void f_table_shennon		(const vector<letter> &alphabet)
{

	cout << endl;
	cout << endl;

	cout << "КОДИРОВАНИЕ МЕТОДОМ ШЕННОНА-ФАНО" << endl;

	float shennon_entropy = 0;
	float shennon_capacity = 0;

	cout << endl;

	for (int i = 0; i < 91; i++)
	{

		cout << "*";

	}

	cout << endl;

	cout << "*" << left << setw(29) << "Символ" << "|" << setw(29) << "Вероятность" << "|"
		<< setw(29) << "Код Шеннона" << "*" << endl;

	for (int i = 0; i < 91; i++)
	{

		cout << "*";

	}

	cout << endl;

	for (int i = 0; i < alphabet.size(); i++)
	{

		cout << "*" << left << setw(29) << alphabet.at(i).symbol << "|" << setw(29) << alphabet.at(i).probability << "|"
			<< setw(29) << alphabet.at(i).shennon << "*" << endl;

	}

	for (int i = 0; i < alphabet.size(); i++)
	{

		shennon_entropy += -(alphabet.at(i).probability * log2f(alphabet.at(i).probability));

		shennon_capacity += alphabet.at(i).probability * alphabet.at(i).shennon.length();

	}

	for (int i = 0; i < 91; i++)
	{

		cout << "*";

	}

	cout << endl;
	cout << "*" << "Энтропия кода Шеннона равна: " << setw(60) << setprecision(3) << shennon_entropy << "*" << endl;

	for (int i = 0; i < 91; i++)
	{

		cout << "*";

	}

	cout << endl;
	cout << "*" << "Средняя количество двоичных разрядов равно: " << setw(45) << setprecision(2) << shennon_capacity << "*" << endl;

	for (int i = 0; i < 91; i++)
	{

		cout << "*";

	}

	cout << endl;

}

//Функция декодирования кода Шеннона-Фано

void f_encode_shennon		(const vector<letter> &alphabet, string &input)
{

	string	text				= "";	//Хранит исходное сообщение
	string	text_code			= "";	//кодовую комбинацию Шеннона
	string	output				= "";	//декодированное сообщение

	int		position;					//Итератор

	for (int i = 0; i < 10; i++)
	{

		text += input[i];

	}

	for (int i = 0; i < text.length(); i++)
	{

		for (int j = 0; j < alphabet.size(); j++)
		{

			if (static_cast<int>(text[i]) == alphabet.at(j).symb_code)
			{

				text_code += alphabet.at(j).shennon;

			}

		}

	}

	cout << endl;
	cout << "Закодировать сообщение из 10 символов методом Шеннона-Фано, а затем декодировать" << endl;
	cout << endl;
	cout << "Первые десять символов исходного текста: " << text << endl;
	cout << endl;
	cout << "Закодированные кодом Шеннона дясять символов: " << text_code << endl;
	cout << endl;

	while (!text_code.empty())
	{
		for (int i = 0; i < alphabet.size(); i++)
		{

			position = text_code.find(alphabet.at(i).shennon);

			if (position == 0)
			{

				output += alphabet.at(i).symbol;

				text_code.erase(0, alphabet.at(i).shennon.length());

			}

		}

	}

	cout << "Декодированные десять символов: " << output << endl;
	cout << endl;

}

//Функция кодирования методом Хаффмана(присвоение каждому элементу уникального кода)

void f_make_huffman_code	(Node::pointer &node, string str, vector<string> codes, vector<letter> &alphabet)
{

	if (node->left != nullptr)
	{

		f_make_huffman_code(node->left, str + "0", codes, alphabet);

	}

	if (node->right != nullptr)
	{

		f_make_huffman_code(node->right, str + "1", codes, alphabet);

	}

	if (node->left == nullptr && node->right == nullptr)
	{

		node->code(str);

		for (int i = 0; i < alphabet.size(); i++)
		{

			if (node->get_symb() == alphabet.at(i).symbol)
			{

				alphabet.at(i).huffman = node->code();

			}

		}

	}

}

//Функция создания "дерева" по методу Хаффмана

void f_huffman				(vector<letter> &alphabet)
{

	using queue_t = priority_queue<Node::pointer, vector<Node::pointer>, LowestPriority>;

	queue_t queue;

	for (int i = 0; i < alphabet.size(); i++)
	{

		Node::pointer node = make_shared<Node>(alphabet.at(i).symbol, alphabet.at(i).probability);
		queue.push(node);

	}

	while (queue.size() > 1)
	{
		Node::pointer x = queue.top();
		queue.pop();

		Node::pointer y = queue.top();
		queue.pop();

		string name = x->get_name() + y->get_name();

		Node::pointer z = make_shared<Node>(x->get_probability() + y->get_probability(), name);

		z->left = x;
		z->right = y;

		x->parent = z;
		y->parent = z;

		queue.push(z);
	}

	Node::pointer root = queue.top();

	vector<string> codes;

	f_make_huffman_code(root, "", codes, alphabet);

}

//Функция для построения таблицы с кодами Хаффмана

void f_table_huffman		(const vector<letter> &alphabet)
{

	cout << endl;
	cout << endl;

	cout << "КОДИРОВАНИЕ МЕТОДОМ ХАФФМАНА" << endl;

	cout << endl;

	float huffman_entropy = 0;
	float huffman_capacity = 0;

	for (int i = 0; i < 91; i++)
	{

		cout << "*";

	}

	cout << endl;

	cout << "*" << left << setw(29) << "Символ" << "|" << setw(29) << "Вероятность" << "|"
		<< setw(29) << "Код Хаффмана" << "*" << endl;

	for (int i = 0; i < 91; i++)
	{

		cout << "*";

	}

	cout << endl;

	for (int i = 0; i < alphabet.size(); i++)
	{

		cout << "*" << left << setw(29) << alphabet.at(i).symbol << "|" << setw(29) << setprecision(5) << alphabet.at(i).probability << "|"
			<< setw(29) << alphabet.at(i).huffman << "*" << endl;

	}

	for (int i = 0; i < alphabet.size(); i++)
	{

		huffman_entropy += -(alphabet.at(i).probability * log2f(alphabet.at(i).probability));

		huffman_capacity += alphabet.at(i).probability * alphabet.at(i).huffman.length();

	}

	for (int i = 0; i < 91; i++)
	{

		cout << "*";

	}

	cout << endl;
	cout << "*" << "Энтропия кода Хаффмана равна: " << setw(59) << setprecision(3) << huffman_entropy << "*" << endl;

	for (int i = 0; i < 91; i++)
	{

		cout << "*";

	}

	cout << endl;
	cout << "*" << "Средняя количество двоичных разрядов равно: " << setw(45) << setprecision(2) << huffman_capacity << "*" << endl;

	for (int i = 0; i < 91; i++)
	{

		cout << "*";

	}

	cout << endl;

}

//Функция декодирования кода Хаффмана

void f_encode_huffman		(const vector<letter> &alphabet, string &input)
{

	string text = "";
	string text_code = "";
	string output = "";

	int text_code_length = 0;

	int position;

	for (int i = input.length()-10; i < input.length(); i++)
	{

		text += input[i];

	}

	for (int i = 0; i < text.length(); i++)
	{

		for (int j = 0; j < alphabet.size(); j++)
		{

			if (static_cast<int>(text[i]) == alphabet.at(j).symb_code)
			{

				text_code += alphabet.at(j).huffman;

			}

		}

	}

	cout << endl;
	cout << "Закодировать сообщение из 10 символов методом Хаффмана, а затем декодировать" << endl;
	cout << endl;
	cout << "Последние десять символов исходного текста: " << text << endl;
	cout << endl;
	cout << "Закодированные кодом Шеннона дясять символов: " << text_code << endl;
	cout << endl;

	text_code_length = text_code.length();

	while (!text_code.empty())
	{
		for (int i = 0; i < alphabet.size(); i++)
		{

			position = text_code.find(alphabet.at(i).huffman);

			if (position == 0)
			{

				output += alphabet.at(i).symbol;

				text_code.erase(0, alphabet.at(i).huffman.length());

			}

		}

	}

	cout << "Декодированные десять символов: " << output << endl;
	cout << endl;


}

int main()
{

	SetConsoleCP(1251);												//Установка языка консоли
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");

	using text				= string;								//Создание псевдонима для string

	text					input;									//Строка для хранения получаемого из файла текста
	text					fullBranch;								//Строка для хранения полного кода символа при кодировании Шенноном
	text					branch;									//Строка для хранения 0 или 1 для Метода Шеннона

	vector<letter>			alphabet;								//Объявление вектора, в котором будут храниться символы и информация о них

	float	entropy_sum				= 0;							//Хранит общую энтропию

	bool	proove					= 0;							//Проверка на повторное появление символа

	int		start					= 0;

	second_table			ascii;									//Объявление структуры, в которой хранятся характеристики ascii
	second_table			hurtly;									//Объявление структуры, в которой хранятся характеристики Хартли

	f_input(input);

	letter					new_letter;								//Объявление структуры, в которой хранится информация о символе 

	new_letter.symbol				= input[0];
	new_letter.symb_code			= static_cast<int>(input[0]);

	alphabet.push_back(new_letter);

	//Занесение в вектор alphabet новых символов

	for (int i = 1; i < input.length(); i++)
	{

			for (int j = 0; j < alphabet.size(); j++)
			{

				proove	= 1;

				if (input[i] == alphabet.at(j).symbol)
				{

					proove	= 0;

					break;

				}
			}

			if (proove == 1)
			{

				letter					new_letter;

				new_letter.symbol		= input[i];
				new_letter.symb_code	= static_cast<int>(input[i]);

				alphabet.push_back(new_letter);

			}

	}

	//Расчет количества появлений каждого символа

	for (int i = 0; i < alphabet.size(); i++)
	{

		f_quantity(input, alphabet.at(i));

	}

	//Вызов функции сортировки

	f_sort(alphabet, new_letter);

	//Вызов функции расчета вероятности

	f_probability(input, alphabet);

	//Вызов функции расчета энтропии

	f_entropy(alphabet);

	//Вызов функции построения 1-ой таблицы для лабораторной №8

	f_table_first(alphabet, entropy_sum);

	//Вызов функции для расчета значений 2-ой таблицы для лабораторной №8

	f_sec_part(alphabet.size(), ascii, hurtly, entropy_sum);

	//Вызов функции построения 2-ой таблицы для лабораторной №8

	f_table_second(ascii, hurtly);

	//Сортировка вектора символов в порядке убывания вероятности

	sort(alphabet.begin(), alphabet.end(), [](letter b, letter a) {return (a.probability < b.probability); });

	int	end = alphabet.size() - 1;	//Хранение номера последнего элемента вектора

	//Вызов функции создания кода Шеннона

	f_shennon(alphabet, branch, fullBranch, start, end);

	//Вызов функции построения таблицы с кодом Шеннона

	f_table_shennon(alphabet);

	//Вызов функции декодирования кода Шеннона

	f_encode_shennon(alphabet, input);

	//Вызов функции создания кода Хаффмана

	f_huffman(alphabet);

	//Вызов функции построения таблицы с кодом Хаффмана

	f_table_huffman(alphabet);

	//Вызов функции декодирования кода Хаффмана

	f_encode_huffman(alphabet, input);

}