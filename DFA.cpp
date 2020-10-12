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

Node *start;
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
	cout << "NODE " << global_counter << " WAS CREATED" << endl;
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
		while(getline(file, str)){ //Gets line by line of file
			if(str.find("nodes:")!= string::npos){
				getline(file,str);
				string_ = const_cast<char*>(str.c_str());
				token = strtok(string_,",");
				while(token != NULL){
					create_Node(token);
					token = strtok(NULL,",");
				}
				cout << "End of creation" << endl;
			}
			else if(str.find("start:")!= string::npos){
				getline(file,str);
				string_ = const_cast<char*>(str.c_str());
				token = strtok(string_,",");
				cout << "start: " << token <<endl;
				start = pointers[nodes[token]];
				cout << "End of start node" << endl;
			}
			else if(str.find("end:")!= string::npos){
				getline(file,str);
				string_ = const_cast<char*>(str.c_str());
				token = strtok(string_,",");
				while(token != NULL){
					pointers[nodes[token]] -> terminator = true;
					cout << "end: " << token <<endl;
					token = strtok(NULL,",");
				}
				cout << "End of end node" << endl;
			}
			else if(str.find("body:")!= string::npos){
				while(getline(file, str)){
					if(str.compare("")== 0){
						cout << "End of body stuff" << endl;
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
							cout << pointers[nodes[from]] -> name << " -> a -> " << pointers[nodes[to]] -> name << endl;
						}
						else if(std::string(how).compare("b")==0){
							pointers[nodes[from]] -> b = pointers[nodes[to]];
							cout << pointers[nodes[from]] -> name << " -> b -> " << pointers[nodes[to]] -> name << endl;
						}
						else{
							cout << "uh oo" << endl;
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


int main(int argc, char *argv[]){
	automata();
	
}