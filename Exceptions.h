#ifndef EXCEPTIONS_H_
#define EXCEPTIONS_H_
#include "State.h"
#include<cstring>
#include <exception>
using namespace std;



class AutomatonException :public exception{

public:

	AutomatonException(char* _line){
		if (_line != nullptr){
			line = new char[strlen(_line) + 1];
			strcpy_s(line, strlen(_line) + 1, _line);
		}
	}

	char*  what()throw(){

		return line;
	}
	
private:
	char* line;

};

class AutomatonStateExcpetion :public exception{


public:
	AutomatonStateExcpetion(char*_line, unsigned _lineNumber){
		if (_line != nullptr){
			line = new char[strlen(_line) + 1];
			strcpy_s(line, strlen(_line) + 1, _line);
		}
		lineNumber = _lineNumber;
	}

	int  what()throw(){

		return lineNumber;
	}

private:
	char*line;
	unsigned lineNumber;
};


#endif 