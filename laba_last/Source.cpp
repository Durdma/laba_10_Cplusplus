//����������� ���������

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

//����������� ������

#include "Node.h"

using namespace std;

//���������, � ������� ���������� ��� ������ � ������ �������

struct letter
{

	char	symbol;					//��� ������
	int		symb_code;				//��� �������
	int		quantity		= 0;	//���������� ��������� ������� � ������
	float	probability		= 0;	//����������� ��������� ������� � ������
	float	entropy			= 0;	//�������� �������
	string  shennon			= "";	//��� �������-���� �������
	string	huffman			= "";	//��� �������� �������

};

//��������� ��� ���������� ������������� ������� ascii � ������

struct second_table
{

	float	uncert			= 0; //���������������� ����
	int		numb_codes		= 0; //���������� �������� ����
	float	abs_excess		= 0; //���������� ������������
	float	relat_excess	= 0; //������������� ������������

};

//������� ������ ������ �� �����

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

	cout << "��������: ������ ������ \"������� �������\" ����� 1-2" << endl;
	cout << "����� ������: " << input.length() << endl;
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

//������� �������� ���������� ��������� ������� � ������

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

//������� ���������� ������� �������� �� ����������� ���� �������

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

//������� ������� ����������� ��������� ������� � ������

void f_probability			(string &input, vector<letter> &alphabet)
{

	int		counter		= 0;
	float	summ		= 0;

	for (int i = 0; i < alphabet.size(); i++)
	{

		alphabet.at(i).probability = static_cast<float>(alphabet.at(i).quantity) / static_cast<float>(input.length());

	}

}

//������� ������� �������� �������

void f_entropy				(vector<letter> &alphabet)
{

	for (int i = 0; i < alphabet.size(); i++)
	{

		alphabet.at(i).entropy = -(alphabet.at(i).probability * log2f(alphabet.at(i).probability));

	}

}

//������� ��� ���������� 1-�� ������� ������������ ������ �8

void f_table_first			(const vector<letter> &alphabet, float &entropy_sum)
{
	
	float probability_sum	= 0;

	for (int i = 0; i < 117; i++)
	{

		cout<< "*";

	}
	
	cout << endl;

	cout << "*";
	cout << setw(22) << " ������ " << "|" << setw(22) << " ��� ������� " << "|" << setw(22) << " ����� ��������� " << "|"
		 << setw(22) << " ����������� ��������� " << "|" << setw(22) << " �������� " << "*" << endl;

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

	cout << "  |" << setw(22) << "����� �����������";
		
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

	cout << "* " << "���������� ���������� ��������: " << setw(8) << alphabet.size();

	cout << "    |" << setw(22) << "����� ��������";

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

//������� ��� ������� �������������� ascii � ������

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

//������� ��� ���������� 2-�� ������� ������������ ������ �8

void f_table_second			(struct second_table &ascii, struct second_table &hurtly)
{

	for (int i = 0; i < 124; i++)
	{

		cout << "*";

	}

	cout << endl;

	cout << "*" << setw(21) << " ��������� " << "|" << setw(22) << " ���������������� " << "|" 
		 << setw(22) << " ����������� ���� " << "|" << setw(22) << " ���������� ������������ " 
		 << "|" << setw(22) << " ������������� ������������ " << "*" << endl;

	for (int i = 0; i < 124; i++)
	{

		cout << "*";

	}

	cout << endl;

	cout << "*" << setw(21) << "������� ASCII" << "|" << setw(22) << fixed << setprecision(5) << ascii.uncert 
		 << "|" << setw(22) << ascii.numb_codes << "|" << setw(22) << fixed << setprecision(5) << ascii.abs_excess
		 << "   |" << setw(22) << fixed << setprecision(5) << ascii.relat_excess << "      *" << endl;

	cout << "*" << setw(21) << "���� ������" << "|" << setw(22) << fixed << setprecision(5) << hurtly.uncert
		 << "|" << setw(22) << hurtly.numb_codes << "|" << setw(22) << fixed << setprecision(5) << hurtly.abs_excess
		 << "   |" << setw(22) << fixed << setprecision(5) << hurtly.relat_excess << "      *" << endl;

	for (int i = 0; i < 124; i++)
	{

		cout << "*";

	}

	cout << endl;

}

//������� ����������� ������� �������-����

void f_shennon				(vector<letter> &alphabet, string  branch, string &fullBranch, int start, int end)
{

	double		dS			= 0;							//���������� ��� �������� ��������� ������������ ���� ���������
	double		S			= 0;							//��� �������� ����� ������������ ������ ���������

	int			i			= 0;							//��������

	string		cBranch		= "";							//������ ��� �������� ���� ������������������ ����

	cBranch = fullBranch+branch;

	if (start == end)										//���������� ������� ���������� �������� ������
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

//������� ��� ���������� ������� � ������ �������-����

void f_table_shennon		(const vector<letter> &alphabet)
{

	cout << endl;
	cout << endl;

	cout << "����������� ������� �������-����" << endl;

	float shennon_entropy = 0;
	float shennon_capacity = 0;

	cout << endl;

	for (int i = 0; i < 91; i++)
	{

		cout << "*";

	}

	cout << endl;

	cout << "*" << left << setw(29) << "������" << "|" << setw(29) << "�����������" << "|"
		<< setw(29) << "��� �������" << "*" << endl;

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
	cout << "*" << "�������� ���� ������� �����: " << setw(60) << setprecision(3) << shennon_entropy << "*" << endl;

	for (int i = 0; i < 91; i++)
	{

		cout << "*";

	}

	cout << endl;
	cout << "*" << "������� ���������� �������� �������� �����: " << setw(45) << setprecision(2) << shennon_capacity << "*" << endl;

	for (int i = 0; i < 91; i++)
	{

		cout << "*";

	}

	cout << endl;

}

//������� ������������� ���� �������-����

void f_encode_shennon		(const vector<letter> &alphabet, string &input)
{

	string	text				= "";	//������ �������� ���������
	string	text_code			= "";	//������� ���������� �������
	string	output				= "";	//�������������� ���������

	int		position;					//��������

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
	cout << "������������ ��������� �� 10 �������� ������� �������-����, � ����� ������������" << endl;
	cout << endl;
	cout << "������ ������ �������� ��������� ������: " << text << endl;
	cout << endl;
	cout << "�������������� ����� ������� ������ ��������: " << text_code << endl;
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

	cout << "�������������� ������ ��������: " << output << endl;
	cout << endl;

}

//������� ����������� ������� ��������(���������� ������� �������� ����������� ����)

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

//������� �������� "������" �� ������ ��������

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

//������� ��� ���������� ������� � ������ ��������

void f_table_huffman		(const vector<letter> &alphabet)
{

	cout << endl;
	cout << endl;

	cout << "����������� ������� ��������" << endl;

	cout << endl;

	float huffman_entropy = 0;
	float huffman_capacity = 0;

	for (int i = 0; i < 91; i++)
	{

		cout << "*";

	}

	cout << endl;

	cout << "*" << left << setw(29) << "������" << "|" << setw(29) << "�����������" << "|"
		<< setw(29) << "��� ��������" << "*" << endl;

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
	cout << "*" << "�������� ���� �������� �����: " << setw(59) << setprecision(3) << huffman_entropy << "*" << endl;

	for (int i = 0; i < 91; i++)
	{

		cout << "*";

	}

	cout << endl;
	cout << "*" << "������� ���������� �������� �������� �����: " << setw(45) << setprecision(2) << huffman_capacity << "*" << endl;

	for (int i = 0; i < 91; i++)
	{

		cout << "*";

	}

	cout << endl;

}

//������� ������������� ���� ��������

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
	cout << "������������ ��������� �� 10 �������� ������� ��������, � ����� ������������" << endl;
	cout << endl;
	cout << "��������� ������ �������� ��������� ������: " << text << endl;
	cout << endl;
	cout << "�������������� ����� ������� ������ ��������: " << text_code << endl;
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

	cout << "�������������� ������ ��������: " << output << endl;
	cout << endl;


}

int main()
{

	SetConsoleCP(1251);												//��������� ����� �������
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "ru");

	using text				= string;								//�������� ���������� ��� string

	text					input;									//������ ��� �������� ����������� �� ����� ������
	text					fullBranch;								//������ ��� �������� ������� ���� ������� ��� ����������� ��������
	text					branch;									//������ ��� �������� 0 ��� 1 ��� ������ �������

	vector<letter>			alphabet;								//���������� �������, � ������� ����� ��������� ������� � ���������� � ���

	float	entropy_sum				= 0;							//������ ����� ��������

	bool	proove					= 0;							//�������� �� ��������� ��������� �������

	int		start					= 0;

	second_table			ascii;									//���������� ���������, � ������� �������� �������������� ascii
	second_table			hurtly;									//���������� ���������, � ������� �������� �������������� ������

	f_input(input);

	letter					new_letter;								//���������� ���������, � ������� �������� ���������� � ������� 

	new_letter.symbol				= input[0];
	new_letter.symb_code			= static_cast<int>(input[0]);

	alphabet.push_back(new_letter);

	//��������� � ������ alphabet ����� ��������

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

	//������ ���������� ��������� ������� �������

	for (int i = 0; i < alphabet.size(); i++)
	{

		f_quantity(input, alphabet.at(i));

	}

	//����� ������� ����������

	f_sort(alphabet, new_letter);

	//����� ������� ������� �����������

	f_probability(input, alphabet);

	//����� ������� ������� ��������

	f_entropy(alphabet);

	//����� ������� ���������� 1-�� ������� ��� ������������ �8

	f_table_first(alphabet, entropy_sum);

	//����� ������� ��� ������� �������� 2-�� ������� ��� ������������ �8

	f_sec_part(alphabet.size(), ascii, hurtly, entropy_sum);

	//����� ������� ���������� 2-�� ������� ��� ������������ �8

	f_table_second(ascii, hurtly);

	//���������� ������� �������� � ������� �������� �����������

	sort(alphabet.begin(), alphabet.end(), [](letter b, letter a) {return (a.probability < b.probability); });

	int	end = alphabet.size() - 1;	//�������� ������ ���������� �������� �������

	//����� ������� �������� ���� �������

	f_shennon(alphabet, branch, fullBranch, start, end);

	//����� ������� ���������� ������� � ����� �������

	f_table_shennon(alphabet);

	//����� ������� ������������� ���� �������

	f_encode_shennon(alphabet, input);

	//����� ������� �������� ���� ��������

	f_huffman(alphabet);

	//����� ������� ���������� ������� � ����� ��������

	f_table_huffman(alphabet);

	//����� ������� ������������� ���� ��������

	f_encode_huffman(alphabet, input);

}