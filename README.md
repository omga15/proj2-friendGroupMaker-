# Project Finding Friend Group README

Student 1: Patrick Wang (924885084)

Student 2: _______ ______ (______)

## Project Status
This the current status of the project

## Known Issues
The project fails to function properly in 

## Code References
* [Different ways to initialize variables](https://stackoverflow.com/questions/22543875/different-ways-to-initialize-variables)
* [Some other link](https://stackoverflow.com)
## Our Code references
* [Idea of Key and value](https://www.mongodb.com/resources/basics/databases/key-value-database#how-do-key-value-databases-work)
* [Union data structue(used instructor code instead)](https://www.baeldung.com/cs/disjoint-set-union-data-structure)
* [Lambda's in vectors](https://www.geeksforgeeks.org/cpp/capture-std-vector-in-lambda-function/)
    * [Lambda Captures](https://www.geeksforgeeks.org/cpp/lambda-capture-clause-in-cpp/)
* [Makefile tuto](https://makefiletutorial.com/)
* [__________](____________)
* [__________](____________)
* [__________](____________)
* [__________](____________)


## Generative AI Use
I used ClaudAi for clarification as what the For Each function can be possible used for. The instructions given which is "Executes the fun function on every key/value pair". Was baffling to me when the instructor gave a code of what seems to just be accesing a binary tree and going through every branch. And I needed to have some extra idea of what I could use this binary tree for. 

### Prompt 1
can you help explain to me what would be the uses two function

void ForEach(CMap<K,V>::TEntityFunction fun) override{
            if(DRoot){
                DRoot->ForEach(fun);
            }

and 

void ForEach(CMap<K,V>::TEntityFunction fun){
                if(DLeft){
                    DLeft->ForEach(fun);
                }
                fun(DKey,DValue);
                if(DRight){
                    DRight->ForEach(fun);
                }
            }

### Response 1
That left, me, right order is in-order traversal. In a binary search tree it visits keys in sorted order. The if(DLeft) and if(DRight) checks are the base case: a node with no children just calls fun on itself and returns.

Why two functions

The tree is built from many SNode objects, and the map only holds a pointer to the root. The map can’t loop over nodes the way it would over an array, so each node is responsible for its own subtree, and the map just kicks it off at the to
Example

Suppose you add the names “Bob”, “Alice”, “Carol” (with IDs 0, 1, 2), giving this tree:

    Bob
   /   \
Alice  Carol

Calling ForEach(fun) runs like this:

The map calls Bob->ForEach(fun).
Bob goes left first, so Alice->ForEach(fun) runs. Alice has no children, so it calls fun("Alice", 1) and returns.
Back in Bob, it calls fun("Bob", 0).
Bob goes right, so Carol->ForEach(fun) runs and calls fun("Carol", 2).

### Changes 1

# Template for Ai use
## Generative AI Use
I used ChatGPT for Prompt 1, and ZZZZZ for Prompt 2....

### Prompt 1
How do I iterate over all characters in a string in C++17?
### Response 1
In C++17, you can iterate over all characters in a string using a range-based for loop. Here's an example:
```cpp
#include <iostream>
#include <string>

int main() {
    std::string myString = "Hello, World!";

    // Using range-based for loop to iterate over characters in the string
    for (char c : myString) {
        std::cout << c << " ";
    }

    return 0;
}
```
In this example, the `for (char c : myString)` loop iterates over each character in the string `myString`, and the variable `c` takes on the value of each character in turn. The loop body prints each character followed by a space.

This is a concise and readable way to iterate over the characters in a string in C++17.

### Changes 1
I only needed the `for` loop part, and my string was named `bar` so I changed it to just:
```cpp
// AI Generated
for (char c : bar) {
```

### Prompt 2
My other prompt...

### Response 2
The other response...

### Changes 2
The other changes made...