#include <iostream>
#include <string>
#include <vector>
using namespace std;
int TransformIntoNumber(vector<int>);
void ShuntingYard(string);
bool isNumber(char);
bool isOperator(char);
bool comparePrecendence(char, char);
int main()
{
	string input;
	cin >> input; //da se opravi cheteneto na intervalite
	ShuntingYard(input);
	return 0;
}
void ShuntingYard(string input)
{
	vector<char> numbers;
	vector<char> operators;
	vector<int> currentNumber;
	char lastElementInOperators;
	for (int i = 0; i < input.length(); ++i)
	{
		//while (isNumber(input[i]) && i<input.length())
		//{
		//	currentNumber.push_back(input[i]-48);
		//	++i;
		//}
		if (isNumber(input[i]))
		{
			numbers.push_back(input[i]);
			continue;
		}
		//currentNumber.clear();
		//if (i == input.length()) break;
		if (input[i] == '^')
		{
			numbers.push_back(input[i]);
			continue;
		}
		if (isOperator(input[i]))
		{
			char o1 = input[i];
			if (operators.size() > 0)
			{
				char o2 = operators[operators.size() - 1];
				while (isOperator(o2) && comparePrecendence(o1, o2))
				{
					operators.pop_back();
					numbers.push_back(o2);
					if (operators.size() > 0) o2 = operators[operators.size()-1];
					else break;
				}
			}
			operators.push_back(o1);
			continue;
		}
		if (input[i] == '(')
		{
			operators.push_back(input[i]);
			continue;
		}
		if (input[i] == ')')
		{
			lastElementInOperators = operators[operators.size() - 1];
			while (lastElementInOperators != '(')
			{
				char op = lastElementInOperators;
				numbers.push_back(op);
				operators.pop_back();
				if(operators.size()>0) lastElementInOperators = operators[operators.size() - 1];
				else
				{
					cout << "NaN";
					return;
				}
			}	
		}
		lastElementInOperators = operators[operators.size() - 1];
		if (lastElementInOperators == '(') operators.pop_back();
		lastElementInOperators = operators[operators.size() - 1];
		if (lastElementInOperators == '^')
		{
			char op = lastElementInOperators;
			numbers.push_back(op);
			operators.pop_back();
		}
	}
	while (operators.size() > 0)
	{
		lastElementInOperators = operators[operators.size() - 1];
		if (lastElementInOperators == '(' || lastElementInOperators == ')')
		{
			cout << "NaN";
			return;
		}
		char op = lastElementInOperators;
		numbers.push_back(op);
		operators.pop_back();
	}
	for (int i = 0; i < numbers.size(); ++i)
	{
		cout << numbers[i];
	}
}
int TransformIntoNumber(vector<int> currentNumber)
{
	int number = 0;
	for (int i = 0; i < currentNumber.size(); ++i)
	{
		number *= 10;
		number += currentNumber[i];
	}
	return number;
}
bool isNumber(char symbol)
{
	return (symbol > 47 && symbol < 58) ? true : false;
}
bool isOperator(char symbol)
{
	return (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/' || symbol == '^') ? true : false;
}
bool comparePrecendence(char first, char sec)
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
	}
}