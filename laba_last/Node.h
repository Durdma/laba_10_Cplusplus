#pragma once

#include <iostream>
#include <memory>

using namespace std;

class Node
{

public:

	using pointer = shared_ptr<Node>;

	pointer left{nullptr};
	pointer right{nullptr};
	pointer parent{nullptr};

	Node() = default;
	Node(char in_symb, float in_probability) : symbol(in_symb), probability(in_probability) {}
	Node(float in_probability, const string &in_name) : probability(in_probability), name(in_name) {}

	bool operator<(const Node &oth) const
	{

		return probability < oth.probability;

	}

	friend ostream &operator<<(ostream &os, const Node &node);

	float get_probability() const
	{

		return probability;

	}

	void set_probability(float in_probability)
	{

		probability = in_probability;

	}

	string code() const
	{

		return code_huffman;

	}

	void code(const string &c)
	{

		code_huffman = c;

	}

	string get_name() const
	{

		if (symbol == 0)
		{

			return name;

		}
		else
		{
			return string(1, symbol);
		}

	}

	char get_symb() const
	{

		return symbol;

	}

private:

	char symbol = 0;

	float probability = 0;

	string code_huffman = "";
	string name = "";

};

ostream &operator<<(ostream &os, const Node &node)
{

	return os << node.get_name() << " --- " << setprecision(5) << node.probability;

}

class LowestPriority
{

public:

	bool operator() (const Node::pointer &left, const Node::pointer &right)
		const {

		return left->get_probability() > right->get_probability();

	}

};