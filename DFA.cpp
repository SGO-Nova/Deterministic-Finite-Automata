#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <map>

using namespace std;

#define MAX_CHAR 1000

struct Node{
	const char* name;
	bool terminator;
	Node *a;
	Node *b;
};

Node *start, *current;
Node* pointers[21];
int global_counter = 0;
std::map<std::string, int> nodes;

void create_Node(string str){ //Creates the nodes for the automata
	Node *temp = (Node*)malloc(sizeof(Node));
	temp -> name = str.c_str(); //Easier to find later for dev purposes
	temp -> terminator = false; //Final state node or not
	temp -> a = NULL; //Node to go to for 'a' input
	temp -> b = NULL; //Node to go to for 'b' input
	pointers[global_counter] = temp; //Moves Node into array
	nodes[str] = global_counter; //Notes the string given to the pointer
	global_counter++; 
}

void automata(){
	ifstream file ("DFA.txt");
	string str;
	char* string_;
	char* token;
	char* from;
	char* to;
	char* how;

	
	if(file.is_open()){
		getline(file, str);
		cout << "The language is: L = {s| a,b are elements of s}" << endl;
		cout << "Enter a string to check if it is accepted by the regular expression: \n" << str << endl;
		while(getline(file, str)){ //Gets line by line of file
			if(str.find("nodes:")!= string::npos){
				getline(file,str);
				string_ = const_cast<char*>(str.c_str());
				token = strtok(string_,",");
				while(token != NULL){
					create_Node(token);
					token = strtok(NULL,",");
				}
			}
			else if(str.find("start:")!= string::npos){
				getline(file,str);
				string_ = const_cast<char*>(str.c_str());
				token = strtok(string_,",");
				start = pointers[nodes[token]];
			}
			else if(str.find("end:")!= string::npos){
				getline(file,str);
				string_ = const_cast<char*>(str.c_str());
				token = strtok(string_,",");
				while(token != NULL){
					pointers[nodes[token]] -> terminator = true;
					token = strtok(NULL,",");
				}
			}
			else if(str.find("body:")!= string::npos){
				while(getline(file, str)){
					if(str.compare("")== 0){
						break;
					}
					else{
						string_ = const_cast<char*>(str.c_str());
						token = strtok(string_,",");
						from = token;
						token = strtok(NULL,",");
						how = token;
						token = strtok(NULL,",");
						to = token;
						if(std::string(how).compare("a")==0){
							pointers[nodes[from]] -> a = pointers[nodes[to]];
						}
						else if(std::string(how).compare("b")==0){
							pointers[nodes[from]] -> b = pointers[nodes[to]];
						}
					}
				}
			}
		}
		file.close();
	}
	else{
		cout << "Unable to open the file designated: DFA.txt"<< endl;
		cout << "Ending Program" << endl;
		exit(1);
	}
}

bool calculate(char str[201]){
	current = start;
	for(int i = 0; i < 200; i++){
		if(str[i] == '\0' && current -> terminator == true){
			return true;
		}
		else if(str[i] == '\0' && current -> terminator == false){
			break;
		}
		else if(str[i] == 'a' && current -> a != NULL){
			current = current -> a;
		}
		else if(str[i] == 'b' && current -> b != NULL){
			current = current -> b;
		}
		else{
			cout << "This string does not use the alphabet given!" << endl;
			exit(2);
		}
	}
	return false;
	
}

int main(int argc, char *argv[]){
	cout<<endl;
	char input[201];
	automata();
	
	cout << "> ";
	cin >> input;
	cout<<endl;
	if(calculate(input)){
		cout << "'" << input << "' is accepted by the Automata!" << endl;
	}
	else{
		cout << "'" << input << "' is NOT accepted by the Automata!" << endl;
	}
	cout <<endl;
	cout <<"Press enter to exit ";
	getchar();
	return 0;
}