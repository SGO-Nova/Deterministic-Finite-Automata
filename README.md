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
The syntax order for the funcations is that the nodes: function has to be the first function so it can create the nodes and give them pointers as the other functions do not know what to do with information given if it is not created first. Also **The first line must either be blank or the regular expression of the DFA**, because the code prints the first line to the console as a regular expression hint.\
\
An example 'code' would be:
```
(a + b)* (ab + ba) (a + b)*
nodes:
q0,q1,q2,q3

start:
q0

body:
q0,a,q1
q0,b,q2
q1,a,q1
q1,b,q3
q2,a,q3
q2,b,q2
q3,a,q3
q3,b,q3

end:
q3

```
Same automatans can be writen different ways, so it does not matter which order the user gives the transition relation.\
For example:
```
(a + b)* (ab + ba) (a + b)* String must contain at least one 'a' and one 'b'
nodes:
q0,q1,q2,q3

end:
q3

body:
q3,b,q3
q0,b,q2
q0,a,q1
q2,b,q2
q1,a,q1
q1,b,q3
q2,a,q3
q3,a,q3

start:
q0

```
This is due the specific mapping to a pointer based on the string given. Everything node given in the nodes: function will have their own pointer and therefore needs to be exactly the same with capitalization.\
At the end of all functions there must be a blank line between so the different functions can be recognized and not pulled into a different function.

The name of the file the user must name it is: *DFA.txt*. No other file will be read and an error will occur if trying to run. As long as the name of the file is correct, there is a blank line right after the functions, the node function is the first function, the user only uses stated nodes, the user only uses *'a'* or *'b'* for the alphabet, and there is a starting node, the DFA will work.

## Transition relation
The transition relation uses the 5-tuple given or made to make an easy to read relationship between nodes for computers to tell the difference in relations. It is also easy for humans to type out or figure out the transition relation between nodes which makes it easier to input a DFA into the program. The syntax for the transition relation is: *Node_from, alphabet_given, Node_to* In the example above, [this]() DFA was used to figure out the transition relation. Although it is hard to tell in the second example, it is still the same DFA as the first. Users should try to input the relations in a order they seem fit, and keep to that order. This could be a numbering order, or even a left to right sequence. The user should then only type where the node is going and not what nodes lead to it. After finishing the transition relation, the user should double check to make sure their transition relation has no duplicates and all relations are valid.\
If there are duplicate or mulitple alphabets given from the same node, *ie. the letter 'a' goes to two different nodes*, then the last relation given with that alphabet for that node will be used and overwrite the first relation. An example of this would be:
```
a(a + b)*
nodes:
q0,q1

start:
q0

body:
q0,a,q1
q0,b,q0
q1,a,q1
q1,b,q1
q1,a,q0

end:
q1

```
The very last line of the body function adds the relation *q1 -> q0 via the letter 'a'*  which overwites the relation *q1 -> q1 via the letter 'a'* two lines above that. This would mess up the DFA the user was trying to present and give a possible wrong answer.

## How my code works
