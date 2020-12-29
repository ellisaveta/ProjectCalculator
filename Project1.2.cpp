#include <iostream>
#include <string>
#include <vector>
using namespace std;
int TransformIntoNumber(vector<int>);
void Calculator(string);
bool isNumber(char);
bool isOperator(char);
bool comparePrecendence(char, char);
double Calculate(double, double, char);
int main()
{
	string input;
	cin >> input; //da se opravi cheteneto na intervalite
	Calculator(input);
	return 0;
}
void Calculator(string input)
{
//Shunting-Yard algorithm...
	vector<char> shYardString;
	vector<char> operators;
	char lastElementInOperators;
	for (int i = 0; i < input.length(); ++i)
	{
		if (isNumber(input[i]))
		{
			do
			{
				shYardString.push_back(input[i]);
				++i;
			} while ((isNumber(input[i])) && i < input.length());
			shYardString.push_back(' ');
			--i;
		}
		else if (input[i] == '^')
		{
			operators.push_back(input[i]);
		}
		else if (isOperator(input[i]))
		{
			char o1 = input[i];
			if (operators.size() > 0)
			{
				char o2 = operators[operators.size() - 1];
				while (isOperator(o2) && comparePrecendence(o2, o1))
				{
					operators.pop_back();
					shYardString.push_back(o2);
					shYardString.push_back(' ');
					if (operators.size() > 0) o2 = operators[operators.size() - 1];
					else break;
				}
			}
			operators.push_back(o1);
		}
		else if (input[i] == '(')
		{
			operators.push_back(input[i]);
		}
		else if (input[i] == ')')
		{
			lastElementInOperators = operators[operators.size() - 1];
			while (lastElementInOperators != '(')
			{
				char op = lastElementInOperators;
				shYardString.push_back(op);
				shYardString.push_back(' ');
				operators.pop_back();
				if (operators.size() > 0) lastElementInOperators = operators[operators.size() - 1];
				else
				{
					cout << "NaN"; //Not correct use of "()"
					return;
				}
			}
			if (operators.size() > 0) lastElementInOperators = operators[operators.size() - 1];
			if (lastElementInOperators == '(') operators.pop_back();
			if (operators.size() > 0) lastElementInOperators = operators[operators.size() - 1];
			if (lastElementInOperators == '^')
			{
				char op = lastElementInOperators;
				shYardString.push_back(op);
				shYardString.push_back(' ');
				operators.pop_back();
			}
		}
	}
	while (operators.size() > 0)
	{
		lastElementInOperators = operators[operators.size() - 1];
		if (lastElementInOperators == '(' || lastElementInOperators == ')')
		{
			cout << "NaN"; //Not correct use of "()"
			return;
		}
		char op = lastElementInOperators;
		shYardString.push_back(op);
		shYardString.push_back(' ');
		operators.pop_back();
	}
//Reversed Polish Notation algorithm...
	vector<double> result;
	vector<int> currentNumber;
	for (int i = 0; i < shYardString.size(); ++i)
	{
		if (isNumber(shYardString[i]))
		{
			currentNumber.clear();
			do
			{
				currentNumber.push_back(shYardString[i] - 48);
				++i;
			}while (isNumber(shYardString[i]));
			result.push_back(TransformIntoNumber(currentNumber));
			--i;
		}
		else if (isOperator(shYardString[i]) || shYardString[i] == '^')
		{
			if (result.size() < 2)
			{
				cout << "NaN"; //Not enought numbers
				return;
			}
			double b = result[result.size() - 1];
			result.pop_back();
			double a = result[result.size() - 1];
			result.pop_back();
			double total = Calculate(a, b, shYardString[i]);
			result.push_back(total);
		}
	}
	if (result.size() == 1) cout << result[0];
	else
	{
		cout << "NaN"; //Too many numbers
		return;
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
double Calculate(double a, double b, char symbol)
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
		return a / b;
	case '^':
		double total = 1;
		for (int i = 0; i < b; ++i)
		{
			total *= a;
		}
		return total;
	}
}