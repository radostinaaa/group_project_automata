#ifndef STATE_H_
#define STATE_H_
#include <cstring>

class State{
public:
	State(const char[] = " ");
	~State();
	State(const State&);
	State& operator=(const State);
	int setEnd();
	int setNotEnd();
	char* getName();
	bool isName(char*);
	bool getIsEnd();
private:
	char* name;
	bool isEnd;
};
#endif