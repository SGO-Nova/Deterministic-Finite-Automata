# Deterministic Finite Automata

## Introduction
This is using the inforamtion I have learned about Deterministic Finite Automata. The idea with Desterministic vs Nondeterministic is that there would not be any branchs in the paths to figure out wether a string is accepted or not based on the given system. The path that is taken for the Automata is deterministic, meaning one path. A picture of the difference between the two can be found [here](https://i.imgur.com/aGs1l3b.png). I got this idea while driving and thinking about my [scanner project](https://github.com/SGO-Nova/Scanner) and realizing how bad the code was for creating the Automata.

## The Idea
My idea for this program was to allow users to give a **.txt** file that would act as "code" to my program that would automattically generate the Automatan with little to no effort. The user can then enter a string from the alphabet and find out if the string would be accepted or not. This was first thought to allow users to use the whole english alphabet, but for now it only uses the letters '*a*' and '*b*' as possible directions.

## The 'Code'
I wanted users to be able to create many different automatans without having to change the code and worry about pointers, strings, and bugs.... many many bugs. Using a given format, the user can input the **transition relation** with some slight modifiation to give the right code and create their automata easily. 
The code syntax includes 4 functions:
* nodes:
* body:
* start:
* end:

**nodes:** -> This lists all the nodes or points within the automata\
  Nodes must be seperated by commas and no space between anything\
**start:** -> This gives the node inside the starting pointer\
  There should only be one node in the argument or the function will not recongnize which node is the starting node\
**end:** -> This turns the terminator/end node boolean to true\
  Nodes must be seperated by commas and no space between anything\
**body:** -> This is where the user will be allowed to enter the transition relation\
  The syntax only allows one relation per line. *ie. Start_Node, transition_alphabet, Next_Node* For a better example, look at the 'code' below.\
\
The only syntax order for the funcations is that the nodes() function has to be the first function so it can create the nodes and give them pointers as the other functions do not know what to do with information given if it is not created first.\
\
An example 'code' would be:
```
nodes: //Lists all possible nodes taht can be visited
q0,q1,q2,q3 


start: //Lists the starting node
q0


body: //Gives the transition relation for the automata
q0,a,q1 
q0,b,q2
q1,a,q1
q1,b,q3
q2,a,q3
q2,b,q2
q3,a,q3
q3,b,q3


end: //Lists the end/final state node
q3

```
Same automatans can be writen different ways, so it does not matter which order the user gives the transition relation.\
At the end of all functions there must be a blank line between so the different functions can be recognized and not pulled into a different function.\

The name of the file the user must name it is: *DFA.txt*. No other file will be read and an error will occur if trying to run. As long as the name of the file is correct, there is a blank line right after the functions, the node function is the first function, the user only uses stated nodes, the user only uses *'a'* or *'b'* for the alphabet, and there is a starting node, the DFA will work.
## 
