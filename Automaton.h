#ifndef AUTOMATON_H_
#define AUTOMATON_H_

#include <iostream>
#include <fstream>
#include <cstring>
#include <exception>
#include <Windows.h>
#include "State.h"
#include "Exceptions.h"
using namespace std;


template <typename T> class DTA{
public:
	DTA();
	DTA(unsigned, State*, State, int, unsigned, T*, unsigned, int**);
	DTA(const DTA&);
	~DTA();
	DTA& operator=(const DTA&);
	int readKDB();
	int readFile(fstream&);
	int changeBeginning();
	int checkIfState(char*);
	int readWord(char*)const;
	int inAlph(char a)const;
	int writeFile(fstream&);
	bool sameAlphabet(T* otherAplhabet, unsigned otherSize);
	DTA operator^(int);
	DTA operator^(const DTA&);
	DTA operator|(const DTA&);
	DTA operator & (const DTA&);
	friend ostream & operator <<(ostream& os, const DTA<T>& automaton){
		
		os << endl << "States:" << endl;
		for (unsigned  i = 0; i < automaton.states - 1; i++){
			os << automaton.Q[i].getName() << ", ";
		}
		os << automaton.Q[automaton.states - 1].getName() << endl;


		os << endl << "Alphabet:" << endl;
		for (unsigned i = 0; i < automaton.alphCount - 1; i++){
			os << automaton.alphabet[i] << ", ";
		}
		os << automaton.alphabet[automaton.alphCount - 1] << endl;

		State _beginning = automaton.beginning;

		os << endl << "Beginning state:" << endl;
		os << _beginning.getName()<< endl;

		os << endl << "Ending states:" << endl;
		for (unsigned i = 0; i < automaton.states; i++){
			if (automaton.Q[i].getIsEnd())os << automaton.Q[i].getName() << " ";
		}
		os << endl;
		
		os << endl << "Transitions:" << endl;

		if (automaton.table != nullptr){

			os << "\t";

			for (unsigned i = 0; i < automaton.alphCount; i++){
				os << automaton.alphabet[i] << "\t";
			}
			os << endl;



			for (unsigned i = 0; i < automaton.states; i++){



				if (automaton.table[i] == nullptr){
					os << "COMP ERROR" << endl;
				}
				os << automaton.Q[i].getName() << "\t";

				for (unsigned j = 0; j < automaton.alphCount; j++){
					int k = automaton.table[i][j];
					os << automaton.Q[k].getName() << "\t";
				}
				os << endl;
			}
		}
		return os;
	};

	friend fstream& operator >>(fstream& myfile, DTA<T>& automaton){
		automaton.readFile(myfile);
		return myfile;
	}

	friend fstream& operator <<(fstream& myfile, DTA<T>& automaton){
		automaton.writeFile(myfile);
		return myfile;
	}

bool created;

private:
	unsigned states;
	State* Q;
	State beginning; 
	int beginningPosition;
	unsigned alphCount;
	unsigned endCount;
	int** table;
	T* alphabet;
	
};


template <typename T>

DTA<T>::DTA(){
	states = 0;
	Q = nullptr;
	beginning = State();
	alphCount = 0;
	alphabet = nullptr;
	endCount = 0;
	table = nullptr;
	created = false;
}


template <typename T>
DTA<T>::DTA(unsigned _states, State* _Q, State _beginning, int _beginningPosition, unsigned  _alphCount, T* _alphabet, unsigned  _endCount, int** _table){
	states = _states;

	Q = new State[states];

	for (unsigned i = 0; i < states; i++){
		Q[i] = _Q[i];
	}

	beginning = _beginning;

	alphCount = _alphCount;

	beginningPosition = _beginningPosition;

	alphabet = new T[alphCount];

	for (unsigned i = 0; i < alphCount; i++){
		alphabet[i] = _alphabet[i];
	}

	endCount = _endCount;


	table = new int*[states];

	for (unsigned i = 0; i < states; i++){
		table[i] = new int[alphCount];
		for (unsigned j = 0; j < alphCount; j++){
			table[i][j] = _table[i][j];
		}
	}

	created = true;
}

template<typename T>
DTA<T>::DTA(const DTA& rhs){
	states = rhs.states;

	Q = new State[states];

	for (unsigned i = 0; i < states; i++){
		Q[i] = rhs.Q[i];
	}

	beginning = rhs.beginning;

	alphCount = rhs.alphCount;

	beginningPosition = rhs.beginningPosition;

	
	alphabet = new T[alphCount];

	for (unsigned i = 0; i < alphCount; i++){
		alphabet[i] = rhs.alphabet[i];
	}

	endCount = rhs.endCount;

	table = new int*[states];

	for (unsigned i = 0; i < states; i++){
		table[i] = new int[alphCount];
		for (unsigned j = 0; j < alphCount; j++){
			table[i][j] = rhs.table[i][j];
		}
	}
}

template<typename T>
DTA<T>::~DTA(){

	for (unsigned i = 0; i < states; i++){
		if (table[i] != nullptr){
			delete[] table[i];
			table[i] = NULL;
		}
	}

	if (table != nullptr){
		delete[]table;
		table = NULL;
	}


	if (alphabet != nullptr){
		delete[] alphabet;
		alphabet = NULL;
	}

	if (Q != nullptr){
		delete[]Q;
		Q = NULL;
	}


}

template<typename T>
DTA<T>& DTA<T>::operator=(const DTA& rhs){


	states = rhs.states;

	if (Q != nullptr){
		delete[]Q;
	}

	Q = new State[states];

	for (unsigned i = 0; i < states; i++){
		Q[i] = rhs.Q[i];
	}

	beginning = rhs.beginning;

	alphCount = rhs.alphCount;

	beginningPosition = rhs.beginningPosition;

	if (alphabet != nullptr){
		delete[]alphabet;
	}


	alphabet = new T[alphCount];

	for (unsigned i = 0; i < alphCount; i++){
		alphabet[i] = rhs.alphabet[i];
	}

	endCount = rhs.endCount;

	if (table != nullptr){
		delete[]table;
	}

	table = new int*[states];

	for (unsigned i = 0; i < states; i++){
		table[i] = new int[alphCount];
		for (unsigned j = 0; j < alphCount; j++){
			table[i][j] = rhs.table[i][j];
		}
	}

	return *this;
}

template<typename T>
int DTA<T>::readFile(fstream& myfile){

	char* line = new char[120];
	if (myfile.is_open())
	{

		myfile >> states;
		Q = new State[states];

		for (unsigned i = 0; i < states; i++){
			myfile >> line;
			Q[i] = State(line);
		}
		myfile >> alphCount;
		alphabet = new T[alphCount];
		for (unsigned i = 0; i < alphCount; i++){
			myfile >> alphabet[i];
		}
		table = new int*[states];
		for (unsigned i = 0; i < states; i++){
			table[i] = new int[alphCount];

			for (unsigned j = 0; j < alphCount; j++){
				myfile >> line;

				for (unsigned k = 0; k < states; k++){
					if (Q[k].isName(line)){
						table[i][j] = k;
						break;
					}
				}
			}
		}

		myfile >> line;
		beginning = State(line);

		myfile >> endCount;
		for (unsigned i = 0; i < endCount; i++){
			myfile >> line;
			for (unsigned k = 0; k < states; k++){
				if (Q[k].isName(line)){
					Q[k].setEnd();
					break;
				};
			}
		}


		created = true;
		myfile.close();
		delete[]line;

		return 0;

	}
	else cout << "Unable to open file";
	delete[] line;


	return 0;

}

template<typename T>
int DTA<T>::readKDB(){
	//SetConsoleCP(1251);
	//SetConsoleOutputCP(1251);
	//cout << "Моля въведете брой състоянията :" << endl;
	cout << "Please enter number of states:" << endl;

	cin >> states;
	cin.ignore();
	if (Q != nullptr){
		delete[]Q;
	}
	Q = new State[states];
	for (unsigned i = 0; i < states; i++){

		//cout << endl << "Моля въведете състояние номер [" << (i + 1) << "] ";	
		cout << endl << "Please enter state number [" << (i + 1) << "] " << endl;

		char* name = new char[10];

		cin.getline(name, 9);
		Q[i] = State(name);
		delete[] name;
	}


	//cout << endl << "Моля въведете брой символи в азбуката на автомата :";
	cout << endl << "Please enter number of alphabet symbols:" << endl;
	cin >> alphCount;
	if (alphabet != nullptr){
		delete[]alphabet;
	}
	alphabet = new T[alphCount];

	for (unsigned i = 0; i < alphCount; i++){
		//	cout << endl << "Моля въведете символ номер [" << (i + 1) << "] ";
		cout << endl << "Please enter symbol number [" << (i + 1) << "] " << endl;
		cin >> alphabet[i];
	}
	if (table != nullptr){
		delete[]table;
	}
	table = new int*[states];
	cin.ignore();
	for (unsigned i = 0; i < states; i++){
		table[i] = new int[alphCount];

		for (unsigned j = 0; j < alphCount; j++){
			cout << endl << "Please enter (" << Q[i].getName() << ", " << alphabet[j] << "):" << endl;

			table[i][j] = -1;
			char* name = new char[10];
			cin.getline(name, 9);
			bool flag = false;
			int k;
			while (!flag){
				try{
					k = checkIfState(name);
					if (k == -1)throw AutomatonStateExcpetion(name, __LINE__);
					table[i][j] = k;
					flag = true;

				}
				catch (AutomatonStateExcpetion e){
					cout << "AutomatonState exception trigerred on line: " << e.what() << ". State with name: " << name << " does not exist." << " Please enter existing state name: ";
					cin.getline(name, 9);
				}
			}

			delete[] name;
		}
	}


	cout << endl << "Please enter beginning state" << endl;
	char* name = new char[10];
	cin.getline(name, 9);
	bool flag = false;
	int k;
	while (!flag){
		try{
			int j = strlen(name);
			for (int i = 0; i < j; i++){
				if (name[i] == ' '){
					name[i] = '\0';
					j = i;
					throw AutomatonException(name);
				};
			}
			k = checkIfState(name);
			if (k == -1)throw AutomatonStateExcpetion(name, __LINE__);
			beginning = Q[k];
			beginningPosition = k;
			flag = true;
		}
		catch (AutomatonException e){
			cout << "AutomatonException triggered. More than one states on input: " << e.what() << endl << " ONLY " << name << " WILL BE PROCESSED." << endl;
			try{
				k = checkIfState(name);
				if (k == -1)throw AutomatonStateExcpetion(name, __LINE__);
				beginning = Q[k];
				beginningPosition = k;
				flag = true;
			}
			catch (AutomatonStateExcpetion e){
				cout << "AutomatonState exception trigerred on line: " << e.what() << ". State with name: " << name << " does not exist." << " Please enter existing state name: ";
				cin.getline(name, 9);
			}
		}
		catch (AutomatonStateExcpetion e){
			cout << "AutomatonState exception trigerred on line: " << e.what() << ". State with name: " << name << " does not exist." << " Please enter existing state name: ";
			cin.getline(name, 9);
		}
	}

	delete[] name;

	//cout << endl << "Моля въведете брой крайни състояния" << endl;
	cout << endl << "Please enter number of ending states" << endl;
	cin >> endCount;
	cin.ignore();
	for (unsigned i = 0; i < endCount; i++){
		//cout << endl << "Моля въведете крайно състояние номер [" << (i + 1) << "] ";
		cout << endl << "Please enter ending state  [" << (i + 1) << "] ";

		char* name = new char[10];
		cin.getline(name, 9);
		flag = false;
		int k;
		while (!flag){
			try{
				k = checkIfState(name);
				if (k == -1)throw AutomatonStateExcpetion(name, __LINE__);
				Q[k].setEnd();
				flag = true;

			}
			catch (AutomatonStateExcpetion e){
				cout << "AutomatonState exception trigerred on line: " << e.what() << ". State with name: " << name << " does not exist." << " Please enter existing state name: ";
				cin.getline(name, 9);
			}
		}

		delete[] name;
	}

	created = true;

	return 0;
}


template <typename T>
int DTA<T>::inAlph(char a)const{
	if (typeid(T) == typeid(int)){
		for (unsigned i = 0; i < alphCount; i++){
			if (a - '0' == alphabet[i])return i;
		}
		return -1;
	}
	for (unsigned i = 0; i < alphCount; i++){
		if (a == alphabet[i])return i;
	}
	return -1;
}



template <typename T>
int  DTA<T>::readWord(char* word)const{
	unsigned len = strlen(word);
	int currentState = beginningPosition;
	for (unsigned i = 0; i < len; i++){
		cout << Q[currentState].getName() << " -> " << word[i] << " -> ";
		int alphPosition = inAlph(word[i]);
		if (alphPosition == -1)return -1;
		else{
			currentState = table[currentState][alphPosition];
		}
	}
	cout << Q[currentState].getName() << endl;
	if (Q[currentState].getIsEnd())return 1;

	return 0;
}


template <typename T>
int DTA<T>::changeBeginning(){
	cout << "Current beginning state is " << Q[beginningPosition].getName() << ". Enter 1 for change and any other number to cancel:" << endl;
	int i;
	cin >> i;
	if (i == 1){
		cout << "Please enter new beginning state:" << endl;

		bool flag = false;
		char* name = new char[10];
		cin.ignore();
		cin.getline(name, 9);
		int k;
		while (!flag){
			try{
				k = checkIfState(name);
				if (k == -1)throw AutomatonStateExcpetion(name, __LINE__);
				beginning = Q[k];
				beginningPosition = k;
				flag = true;

			}
			catch (AutomatonStateExcpetion e){
				cout << "AutomatonState exception trigerred on line: " << e.what() << ". State with name: " << name << " does not exist." << " Please enter existing state name: ";
				cin.getline(name, 9);
			}
		}

		delete[] name;
	}
	return 0;
}



template<typename T>
int DTA<T>::checkIfState(char* name){


	if (Q != nullptr){
		for (unsigned k = 0; k < states; k++){
			if (Q[k].isName(name)){
				return k;
				break;
			};
		}
	}

	return -1;
}


template<typename T>
int DTA<T>::writeFile(fstream& myfile){

	if (myfile.is_open()){

		myfile << endl << "States:" << endl;
		for (unsigned i = 0; i < states - 1; i++){
			myfile << Q[i].getName() << ", ";
		}
		myfile << Q[states - 1].getName() << endl;


		myfile << endl << "Alphabet:" << endl;
		for (unsigned i = 0; i < alphCount - 1; i++){
			myfile << alphabet[i] << ", ";
		}
		myfile << alphabet[alphCount - 1] << endl;

		State _beginning = beginning;

		myfile << endl << "Beginning state:" << endl;
		myfile << _beginning.getName() << endl;

		myfile << endl << "Ending states:" << endl;
		for (unsigned i = 0; i < states; i++){
			if (Q[i].getIsEnd())myfile << Q[i].getName() << " ";
		}
		myfile << endl;

		myfile << endl << "Transitions:" << endl;

		if (table != nullptr){

			myfile << "\t";

			for (unsigned i = 0; i < alphCount; i++){
				myfile << alphabet[i] << "\t";
			}
			myfile << endl;



			for (unsigned i = 0; i < states; i++){



				if (table[i] == nullptr){
					myfile << "COMP ERROR" << endl;
					break;
				}
				myfile << Q[i].getName() << "\t";
			

				for (unsigned j = 0; j < alphCount; j++){
					int k = table[i][j];
					myfile << Q[k].getName() << "\t";
				}
				myfile << endl;
			}

		}
	}
	return 0;
}



template <typename T>
DTA<T> DTA<T>::operator &(const DTA<T>& rhs){

	if (!sameAlphabet(rhs.alphabet, rhs.alphCount)){
		cout << endl << "Different alphabets - section cannot be calculated" << endl;
		DTA<T> result;
		return result;

		}
	unsigned newEndCount = 0;
	unsigned newStates = states*rhs.states;
	State* newQ = new State[newStates];
	int** newTable = new int*[newStates];
	int k = 0;
	for (unsigned i = 0; i < states; i++){
		for (unsigned j = 0; j < rhs.states; j++){
			int len1 = strlen(Q[i].getName());
			int len2 = strlen(rhs.Q[j].getName());
			char* newName = new char[len1 + len2+1];
	
			strcpy_s(newName, len1 + 1, Q[i].getName());
			strcat_s(newName, len1 + len2 + 1, Q[j].getName());

			newQ[k] = State(newName);

			if (Q[i].getIsEnd() && rhs.Q[j].getIsEnd()){
				newQ[k].setEnd(); 
				newEndCount++;
			}
			newTable[k] = new int[alphCount];
			
			for (unsigned t = 0; t < alphCount; t++){
				newTable[k][t] = table[i][t] * rhs.states + rhs.table[j][t];
			}
			
			k++;
		}
		
	}	


	State other = rhs.beginning;
	int len1 = strlen(beginning.getName());
	int len2 = strlen(other.getName());
	char* newName = new char[len1 + len2 + 1];


	strcpy_s(newName, len1+1, beginning.getName());
	strcat_s(newName, len1+len2+1, other.getName());
	State newBeginning = State(newName);

	unsigned newPosition = beginningPosition*rhs.states + rhs.beginningPosition;


	DTA<T> result = DTA<T>(newStates, newQ, newBeginning, newPosition, alphCount, alphabet, newEndCount, newTable);
	
	delete[]newName;
	delete[]newQ;
	delete[]newTable;

	return result;
}


template <typename T>
DTA<T> DTA<T>::operator |(const DTA<T>& rhs){
	if (!sameAlphabet(rhs.alphabet, rhs.alphCount)){
		cout << endl << "Different alphabets - unification cannot be calculated" << endl;
		DTA<T> result;
		return result;

	}
	unsigned newEndCount = 0;
	unsigned newStates = states*rhs.states;
	State* newQ = new State[newStates];
	int** newTable = new int*[newStates];
	int k = 0;
	for (unsigned i = 0; i < states; i++){
		for (unsigned j = 0; j < rhs.states; j++){
			int len1 = strlen(Q[i].getName());
			int len2 = strlen(rhs.Q[j].getName());
			char* newName = new char[len1 + len2 + 1];

			strcpy_s(newName, len1 + 1, Q[i].getName());
			strcat_s(newName, len1 + len2 + 1, Q[j].getName());

			newQ[k] = State(newName);

			if (Q[i].getIsEnd() || rhs.Q[j].getIsEnd()){
				newQ[k].setEnd();
				newEndCount++;
			}
			newTable[k] = new int[alphCount];

			for (unsigned t = 0; t < alphCount; t++){
				newTable[k][t] = table[i][t] * rhs.states + rhs.table[j][t];
			}

			k++;
		}

	}


	State other = rhs.beginning;
	int len1 = strlen(beginning.getName());
	int len2 = strlen(other.getName());
	char* newName = new char[len1 + len2 + 1];


	strcpy_s(newName, len1 + 1, beginning.getName());
	strcat_s(newName, len1 + len2 + 1, other.getName());
	State newBeginning = State(newName);

	unsigned newPosition = beginningPosition*rhs.states + rhs.beginningPosition;


	DTA<T> result = DTA<T>(newStates, newQ, newBeginning, newPosition, alphCount, alphabet, newEndCount, newTable);

	delete[]newName;
	delete[]newQ;
	delete[]newTable;

	return result;
}


template <typename T>
DTA<T> DTA<T>::operator ^ (int a){

	DTA<T> result = *this;
	for (unsigned i = 0; i < states; i++){
		if (result.Q[i].getIsEnd()){
			result.Q[i].setNotEnd();
		}
		else{
			result.Q[i].setEnd();
		}
	}

	return result; 
}


template<typename T>
DTA<T> DTA<T>::operator^(const DTA& rhs){
	DTA<T> result = *this|rhs;
	result = result ^ 1;
	return result;
}

template<typename T>
bool DTA<T>::sameAlphabet(T* otherAlphabet, unsigned otherSize){

	if (alphCount != otherSize)return false;
	for (unsigned i = 0; i < alphCount; i++){
		if (alphabet[i] == otherAlphabet[i])break;
		else return false;
	}
	
	return true;
}


#endif