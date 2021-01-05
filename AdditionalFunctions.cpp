/**
*
* Solution to course project # 2
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2020/2021
*
* @author Elisaveta Georgieva
* @idnumber 62591
* @compiler VC
*
* <File with helper functions: Validation, TransformIntoNumber, IsNumber, IsOperator, ComparePrecendence, Calculate>
*
*/

#include <iostream>
#include <vector>
using namespace std;

int TransformIntoNumber(const vector<int>& currentNumber)
{
	int number = 0;
	for (auto& i : currentNumber)
	{
		number *= 10;
		number += i;
	}
	return number;
}

bool IsNumber(const char symbol)
{
	return (symbol > 47 && symbol < 58);
}

bool IsOperator(const char symbol)
{
	return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^');
}

bool ComparePrecendence(const char first, const char sec)
{
	if (sec == first) return true;
	switch (first)
	{
	case '+':
		if (sec == '-') return true;
		return false;
	case '-':
		if (sec == '+') return true;
		return false;
	case '*':
		if (sec == '+' || sec == '-' || sec == '/') return true;
		return false;
	case '/':
		if (sec == '+' || sec == '-' || sec == '*') return true;
		return false;
	case '^':
		return true;
	}
	return false;
}

double Calculate(const double a, const double b, const char symbol, bool& correct)
{
	switch (symbol)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		if (b == 0)
		{
			correct = false;
			return -1;
		}
		return a / b;
	case '^':
		return pow(a, b);
	}
	correct = false;
	return -1;
}

bool Validation(string& input)
{
	if (input.empty()) return false;
	for (int i = 0; i < input.length(); ++i)
	{
		if (input[i] == '/')
		{
			++i;
			while (i < input.length() && input[i] == ' ')
			{
				++i;
			}
			if (i < input.length())
			{
				if (input[i] == '0') return false;
				--i;
			}
			else return false;
		}
		else if (input[i] == '-')
		{
			int j = i - 1;
			while (j >= 0 && input[j] == ' ') --j;
			if (j >= 0 && input[j] == '(')
			{
				input.insert(j + 1, "0");
				++i;
			}
			else if (j < 0)
			{
				input.insert(0, "0");
				++i;
			}
		}
		else if (IsNumber(input[i]) == false && IsOperator(input[i]) == false && input[i] != ' ' && input[i] != '(' && input[i] != ')') return false;
	}
	return true;
}