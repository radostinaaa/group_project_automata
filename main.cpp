#include "Automaton.h"
#include "State.h"
#include<string>



template<typename T>
int reading(const DTA<T> result){

	char* word = new char[100];
	cout << "ENTER WORD:" << endl;
	cin.getline(word, 99);
	int k = result.readWord(word);
	if (k == 1){
		cout << endl << "FINAL STATE. AUTOMATON READS WORD" << endl;
	}
	else if (k == 0){
		cout << endl << "NOT A FINAL STATE. AUTOMATON DOES NOT READ WORD" << endl;
	}
	else cout << "AUTOMATON DOES NOT RECOGNIZE ALPHABET SYMBOL" << endl;
	delete[]word;
	word = nullptr;

	return 0;
}

template <typename T>
int read(){
	char a;
	DTA<T> automata;

	cout << endl<<"AUTOMATON CREATED" << endl;


	cout << "--------------------" << endl << endl;

	cout << "PICK OPTION:" << endl <<
		"ENTER 1 TO ENTER DATA FROM KEYBOARD" << endl
		<< "ENTER 2 TO ENTER DATA FROM FILE" << endl <<
		"ENTER ANY OTHER SYMBOL TO QUIT PROGRAM" << endl << endl;


	cin >> a;
	if (a == '1'){

		cout << "--------------------" << endl << endl;
		automata.readKDB();
		if (!automata.created){
			cout << endl<<"AN ERROR HAS OCCURED" << endl<<endl;
			return 0; 
		}
	}
	else if (a == '2'){

		cout << "--------------------" << endl << endl;
		cout << "Please enter file name:" << endl;
		string filename;
		cin >> filename;
		fstream myfile(filename.c_str());
		myfile >> automata;
		if (!automata.created){
			cout << endl << "AN ERROR HAS OCCURED" << endl << endl;
			return 0;
		}
		
	}
	else return 0;


	while (true){

		cout << "--------------------" << endl << endl;
		cout << endl << "PICK OPTION:" << endl <<
			"ENTER 1 TO SHOW BUILT AUTOMATON" << endl
			<< "ENTER 2 TO CHANGE BEGINNING STATE" << endl <<
			"ENTER 3 TO PROOF WORD" << endl <<
			"ENTER 4 FOR AUTOMATONS SECTION" << endl <<
			"ENTER 5 FOR AUTOMATONS UNIFICATION" << endl <<
			"ENTER 6 FOR AUTOMATON ADDENDUM" << endl<<
			"ENTER 7 FOR AUTOMATONS ADDENDUM"<<endl<<
			"ENTER ANY OTHER SYMBOL TO QUIT" << endl << endl;
		cin >> a;


		if (a == '1'){
			fstream myfile;
			myfile.open("write.txt");
			if (myfile.is_open()){
				cout <<endl<< "File \"write.txt\" was rewritten with the following automata information:" << endl;
				myfile << automata << endl;
			}
			myfile.close();
			cout << automata << endl;
		}
		else if (a == '2'){
			automata.changeBeginning();
		}
		else if (a == '3'){

			cout << "--------------------" << endl << endl;
			reading(automata);
		}
		else if (a == '4'){

			cout << "--------------------" << endl << endl;
			cout << "Please enter data for second automaton: " << endl;
			DTA<T> second;
			second.readKDB();
			cout << "You have successfully built the following automaton: " << endl << second;
			cout << endl << "Result of section:" << endl;
		
			DTA<T> result = automata&second;

				cout << result << endl;

				int b = 1;
				cout << "Enter 1 to check a word with the created section and any other number to return:" << endl;
				cin >> b;
				while (b == 1){
					cin.ignore();
					reading(automata);
					cout << "Enter 1 to check a word with the created section and any other number to return:" << endl;
					cin >> b;
				}
		}
		else if (a == '5'){
			cout << "Please enter data for second automaton: " << endl;
			DTA<T> second;
			second.readKDB();
			cout << "You have successfully built the following automaton: " << endl << second;
			cout << endl << "Result of unification:" << endl;

			DTA<T> result = automata|second;

				cout << result << endl;

				int b = 1;
				cout << "Enter 1 to check a word with the created unification and any other number to return:" << endl;
				cin >> b;
				while (b == 1){
					cin.ignore();
					reading(result);
					cout << "Enter 1 to check a word with the created section and any other number to return:" << endl;
					cin >> b;
				}

		}
		else if (a == '6'){
			cout << endl << "Automata addendum:" << endl;
			DTA<T> result = automata ^ 1;
			cout << result << endl;

			int b = 1;
			cout << "Enter 1 to check a word with the created addendum and any other number to return:" << endl;
			cin >> b;
			while (b == 1){
				cin.ignore();
				reading(result);
				cout << "Enter 1 to check a word with the created section and any other number to return:" << endl;
				cin >> b;
			}
		
		}
		else if (a == '7'){
	
			cout << "Please enter data for second automaton: " << endl;
			DTA<T> second;
			second.readKDB();
			cout << "You have successfully built the following automaton: " << endl << second;

			cout << endl << "Automata addendum:" << endl;
			DTA<T> result = automata ^ second;
			cout << result << endl;

			int b = 1;
			cout << "Enter 1 to check a word with the created addendum and any other number to return:" << endl;
			cin >> b;
			while (b == 1){
				cin.ignore();
				reading(result);
				cout << "Enter 1 to check a word with the created section and any other number to return:" << endl;
				cin >> b;
			}

		}
		else return 0;

	}

	return 0;
}


int options(){

	char a = '1';
	while (a == '1' || a == '2'){
		cout << "--------------------" << endl << endl;
		cout << "PICK OPTION:" << endl;
		cout << "ENTER 1 TO CREATE NEW DETERMINED FINITE AUTOMATON FROM TYPE INT" << endl
			<< "ENTER 2 TO CREATE NEW DETERMINED FINITE AUTOMATON FROM TYPE CHAR" << endl
			<< "ENTER ANY OTHER SYMBOL TO QUIT PROGRAM" << endl<<endl;

		cin >> a;
		if (a == '1'){
			read<int>();
		}
		else if (a == '2'){
			read<char>();
		}
	}
	return 0;
}




int main(){
	cout << "PROJECT AUTOMATON CSCB212" << endl <<
		"Created by:" << endl <<
		"Adriana Raykova" << endl <<
		"Radostina Nikolaeva" << endl<<endl;
		
	options();


	int a;
	cin >> a;

	return 0;
}