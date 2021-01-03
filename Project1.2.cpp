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
* <main functionality of Calculator>
*
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>
using namespace std;
int TransformIntoNumber(const vector<int>);
void Calculator(string);
bool Validation(string&);
bool IsNumber(const char);
bool IsOperator(const char);
bool ComparePrecendence(const char, const char);
double Calculate(const double, const double, const char, bool&);
int main()
{
	string input;
	ifstream inputFile("InputFile.txt");
	if (!inputFile.is_open())
	{
		cout << "File does not open correctly!";
		return 0;
	}
	getline(inputFile, input);
	if (!Validation(input))
	{
		cout << "NaN";
		return 0;
	}
	Calculator(input);
	inputFile.close();
	return 0;
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
				input.insert(j+1, "0");
				++i;
			}
			else if (j < 0)
			{
				input.insert(0, "0");
				++i;
			}
		}
		else if (IsNumber(input[i])==false && IsOperator(input[i])==false && input[i]!=' ' && input[i]!='(' && input[i]!=')') return false;
	}
	return true;
}

void Calculator(string input)
{
	//Shunting-Yard algorithm...
	vector<char> shYardString;
	vector<char> operators;
	char lastElementInOperators;
	for (int i = 0; i < input.length(); ++i)
	{
		if (IsNumber(input[i]))
		{
			do
			{
				shYardString.push_back(input[i]);
				++i;
			} while ((IsNumber(input[i])) && i < input.length());
			shYardString.push_back(' ');
			--i;
		}
		else if (IsOperator(input[i]))
		{
			char o1 = input[i];
			if (operators.size() > 0)
			{
				char o2 = operators[operators.size() - 1];
				while (IsOperator(o2) && ComparePrecendence(o2, o1))
				{
					operators.pop_back();
					shYardString.push_back(o2);
					shYardString.push_back(' ');
					if (operators.size() > 0)
					{
						o2 = operators[operators.size() - 1];
					}
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
				if (operators.size() > 0)
				{
					lastElementInOperators = operators[operators.size() - 1];
				}
				else
				{
					cout << "NaN"; //Incorrect use of "()"
					return;
				}
			}
			if (operators.size() > 0)
			{
				lastElementInOperators = operators[operators.size() - 1];
			}
			if (lastElementInOperators == '(') operators.pop_back(); //remove the '('
			if (operators.size() > 0)
			{
				lastElementInOperators = operators[operators.size() - 1];
			}
		}
	}
	while (operators.size() > 0)
	{
		lastElementInOperators = operators[operators.size() - 1];
		if (lastElementInOperators == '(' || lastElementInOperators == ')')
		{
			cout << "NaN"; //Incorrect use of "()"
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
		if (IsNumber(shYardString[i]))
		{
			currentNumber.clear();
			do
			{
				currentNumber.push_back(shYardString[i] - 48);
				++i;
			} while (IsNumber(shYardString[i]));
			result.push_back(TransformIntoNumber(currentNumber));
			--i;
		}
		else if (IsOperator(shYardString[i]) || shYardString[i] == '^')
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
			bool correct=true;
			double total = Calculate(a, b, shYardString[i], correct);
			if (!correct)
			{
				cout << "NaN";
				return;
			}
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

int TransformIntoNumber(const vector<int> currentNumber)
{
	int number = 0;
	for(auto& i : currentNumber)
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