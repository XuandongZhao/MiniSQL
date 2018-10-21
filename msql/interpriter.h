#pragma once
#ifndef MY_INTERPRETER_H
#define MY_INTERPRETER_H

#include <iostream>
#include "AttriValue.h"
#include "API.h"
#include "Condition.h"
#include <vector>
#include <string>

class Interpreter {
private:
	API myapi;
	std::string filename;
	std::string word;
	std::string getword(std::string s, int &num);
	bool exec_create(std::string s, int &num);
	bool exec_select(std::string s, int &num);
	bool exec_drop(std::string s, int &num);
	bool exec_delete(std::string s, int &num);
	bool exec_insert(std::string s, int &num);
public:
	Interpreter() {}
	~Interpreter() {}
	int interpreter(std::string s);	
};
class SyntaxException {};

#endif
