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
* <file with helper functions>
*
*/
#pragma once
#include <iostream>
#include <vector>
using namespace std;

int TransformIntoNumber(const vector<int>& currentNumber);
bool IsNumber(const char symbol);
bool IsOperator(const char symbol);
bool ComparePrecendence(const char first, const char sec);
double Calculate(const double a, const double b, const char symbol, bool& correct);
bool Validation(string& input);