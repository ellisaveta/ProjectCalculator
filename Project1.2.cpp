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
#include "AdditionalFunctions.h"
using namespace std;

void Calculator(const string&);

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

void Calculator(const string& input)
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