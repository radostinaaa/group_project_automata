#include "State.h"

State::State(const char _name[]){
	if (_name != nullptr){
		name = new char[strlen(_name) + 1];
		strcpy_s(name, strlen(_name) + 1, _name);
	}
	isEnd = false;
}



State::State(const State & state){
	isEnd = state.isEnd;
	if (state.name != nullptr){
		name = new char[strlen(state.name) + 1];
		strcpy_s(name, strlen(state.name) + 1, state.name);
	}
}

State::~State(){
	if (name != nullptr){
		delete[]name;
		name = nullptr;
	}
}

State& State::operator=(const State state){
	isEnd = state.isEnd;
	if (state.name != nullptr){
		name = new char[strlen(state.name) + 1];
		strcpy_s(name, strlen(state.name) + 1, state.name);
	}
	return *this;
}

char* State::getName(){
	return name;
}

int State::setEnd(){
	isEnd = true;
	return 0;
}

bool State::isName(char* _name){
	if (_name != nullptr){
		if (strcmp(_name, name) == 0)return true;
	}
	return false;
}

bool State::getIsEnd(){
	return isEnd;
}

int State::setNotEnd(){
	isEnd = false;
	return 0;
}