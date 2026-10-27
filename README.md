# Project Finding Friend Group README

Student 1: Patrick Wang (924885084)

Student 2: Qian Yu Guo (927297132)

## Project Status
This the current status of the project is that its finished. 

## Known Issues
The project fails to function properly in Analysis wher ethe time table 

## Code References
* [Different ways to initialize variables](https://stackoverflow.com/questions/22543875/different-ways-to-initialize-variables)
* [Some other link](https://stackoverflow.com)
## Our Code references
* [Idea of Key and value](https://www.mongodb.com/resources/basics/databases/key-value-database#how-do-key-value-databases-work)
* [Union data structue(used instructor code instead)](https://www.baeldung.com/cs/disjoint-set-union-data-structure)
* [Lambda's in vectors](https://www.geeksforgeeks.org/cpp/capture-std-vector-in-lambda-function/)
    * [Lambda Captures](https://www.geeksforgeeks.org/cpp/lambda-capture-clause-in-cpp/)
* [Makefile tuto](https://makefiletutorial.com/)
* [Union By Rank and Path Compression in Union-Find Algorithm](https://www.geeksforgeeks.org/dsa/union-by-rank-and-path-compression-in-union-find-algorithm/)
* [Union Find(disjoint set)](https://www.geeksforgeeks.org/dsa/introduction-to-disjoint-set-data-structure-or-union-find-algorithm/)
* [Mutable: changing const to not constant ](https://www.geeksforgeeks.org/cpp/c-mutable-keyword/)
* [Vector are const](https://stackoverflow.com/questions/27065617/const-vector-implies-const-elements)
* [Back() for vectors](https://www.geeksforgeeks.org/cpp/vector-back-in-cpp-stl/)
* [Vector functions](https://www.geeksforgeeks.org/cpp/vector-in-cpp-stl/)
* [Swap function](https://www.geeksforgeeks.org/cpp/vector-swap-in-cpp-stl/) 
* [Union by rank and path compression](https://www.geeksforgeeks.org/dsa/union-by-rank-and-path-compression-in-union-find-algorithm/)
* [https://www.geeksforgeeks.org/dsa/implementation-of-hash-table-in-c-using-separate-chaining/](https://www.geeksforgeeks.org/dsa/implementation-of-hash-table-in-c-using-separate-chaining/)
* []()
* []()


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
none

### Prompt 2
How to run a loop in makefile

### Reponse 2
Make has no native loop construct, so you use either a shell loop inside a recipe or Make’s own functions. Here are the common approaches.

1. Shell for loop in a recipe

```makefile
make
DIRS := src lib tests

build:
	for dir in $(DIRS); do \
		echo "Building $$dir"; \
		$(MAKE) -C $$dir; \
	done

Notes:
```

Use $$ so the shell sees $dir (a single $ would be expanded by Make).
Each line of a recipe runs in its own shell, so the loop must be joined with \ line continuations and ; separators.
To stop on the first failure, add || exit 1 after the command (or use set -e; at the start):

### Changes 2
made to help write using prev makefile knowledge 

```cp
run_makefriends: run_valgrind_makefriends
	for f in $(DATA_DIR)/*.csv; do 		\
	    echo "== $$f"; 					\
	    $(MAKE_FRIENDS_TARGET) -f $$f;	\
	done
``` 
### Prompt 3
can you show me an example code in cpp of a Weighted Quick Union w/ Path Compression – Compress paths while doing union, almost constant amortized time?

### Response 3
```cpp
#include <iostream>
#include <vector>
#include <numeric>

class WeightedQuickUnionPC {
private:
    std::vector<int> parent;   // parent[i] = parent of node i
    std::vector<int> sz;       // sz[i] = size of tree rooted at i
    int count;                 // number of connected components

public:
    explicit WeightedQuickUnionPC(int n) : parent(n), sz(n, 1), count(n) {
        std::iota(parent.begin(), parent.end(), 0);  // parent[i] = i
    }

    // Path halving: point every other node on the path to its grandparent
    int find(int p) {
        while (p != parent[p]) {
            parent[p] = parent[parent[p]];
            p = parent[p];
        }
        return p;
    }

    bool connected(int p, int q) {
        return find(p) == find(q);
    }

    void unite(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ) return;

        // Weighting: attach the smaller tree under the larger one
        if (sz[rootP] < sz[rootQ]) {
            parent[rootP] = rootQ;
            sz[rootQ] += sz[rootP];
        } else {
            parent[rootQ] = rootP;
            sz[rootP] += sz[rootQ];
        }
        --count;
    }

    int components() const { return count; }
};

int main() {
    WeightedQuickUnionPC uf(10);

    uf.unite(4, 3);
    uf.unite(3, 8);
    uf.unite(6, 5);
    uf.unite(9, 4);
    uf.unite(2, 1);

    std::cout << std::boolalpha;
    std::cout << uf.connected(8, 9) << "\n";   // true
    std::cout << uf.connected(5, 4) << "\n";   // false
    std::cout << uf.components() << "\n";      // 5

    return 0;
}
```
Notes

union is a reserved keyword in C++, so the method is named unite.
find is non-const because path compression modifies parent, so connected is non-const too.
Compile with: g++ -std=c++17 -O2 uf.cpp -o uf

Full (two-pass) path compression variant

Swap in this find to point every node on the path directly at the root:

``` cpp
int find(int p) {
    int root = p;
    while (root != parent[root]) root = parent[root];
    while (p != root) {
        int next = parent[p];
        parent[p] = root;
        p = next;
    }
    return root;
}
``` 

Embedded note: if you want this on an Arduino or similar, swap std::vector for fixed-size arrays (e.g., int parent[N]; int sz[N]; with N as a compile-time constant), since dynamic allocation is usually best avoided on small microcontrollers. Happy to write that version if useful.
### Changes 3 
Gave me an idea of how the algroithm for Weighted Quick Union w/ Path Compression. for Add element, Union, and Find

```cpp
    mutable std::vector<TElementID> DParent;
    std::vector<std::size_t> DGroup;       // size of the group
    std::size_t Dcount;

    TElementID AddElement(){
        TElementID NewElementID = DParent.size();
        DParent.push_back(NewElementID);
        DGroup.push_back(1);
        Dcount++;
        return NewElementID;
    }

    bool Union(TElementID a, TElementID b){
        if(!IsValidElementID(a) || !IsValidElementID(b)){
            return false;
        }
        auto AGroup = Find(a);
        auto BGroup = Find(b);
        if(AGroup==BGroup){
            return false;
        }

        if(DGroup[AGroup] < DGroup[BGroup]){
            std::swap(AGroup,BGroup);

        } else {
            std::swap(AGroup,BGroup);

        }
        return true ;
        ++Dcount;
    }
    
    TGroupID Find(TElementID a) const{
        if(!IsValidElementID(a)){
            return InvalidGroupID;
        }
        TElementID root = a;
        while(root != DParent[root]){
            root = DParent[root];
        }
        while(a != root){
            TElementID next = DParent[a];
            DParent[a] = root;
            a = next;
        }
        return root;
    }
```
### Prompt 4
how to swap two values in a vector?
### Response 4
```cpp

#include <vector>
#include <algorithm>   // std::swap (also in <utility>)

std::vector<int> v = {10, 20, 30, 40};

std::swap(v[0], v[3]);   // v is now {40, 20, 30, 10}

```
### Changes 4

Didn't need to use this code of swapping manually and adding the root. 
```cpp
if (sz[rootP] < sz[rootQ]) {
            parent[rootP] = rootQ;
            sz[rootQ] += sz[rootP];
```

```cpp
 std::swap(AGroup,BGroup);

 and then added reduction
 DParent[AGroup] = BGroup;
 DGroup[BGroup] += DGroup[AGroup];
```
### Prompt 5
can you make a can you make a hash table that in cpp?

### Response 5
```cpp
#include <iostream>
#include <list>
#include <string>

class HashTable {
private:
    static const int numBuckets = 10; 
    // Array of lists to handle collisions via separate chaining
    std::list<std::pair<int, std::string>> table[numBuckets];

    // Simple hash function to map a key to a bucket index
    int hashFunction(int key) {
        return key % numBuckets;
    }

public:
    // Insert a key-value pair into the hash table
    void insert(int key, std::string value) {
        int hashValue = hashFunction(key);
        auto& bucket = table[hashValue];
        
        // Check if key already exists, update if found
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                it->second = value; 
                return;
            }
        }
        
        // If not found, insert new pair
        bucket.emplace_back(key, value);
    }

    // Retrieve a value by its key
    std::string get(int key) {
        int hashValue = hashFunction(key);
        auto& bucket = table[hashValue];
        
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                return it->second;
            }
        }
        return "Key not found"; 
    }

    // Remove a key-value pair from the hash table
    void remove(int key) {
        int hashValue = hashFunction(key);
        auto& bucket = table[hashValue];
        
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->first == key) {
                bucket.erase(it);
                std::cout << "Key " << key << " removed.\n";
                return;
            }
        }
        std::cout << "Key " << key << " not found to remove.\n";
    }
};

```
### Change 5 
Gave the code element for Hashtable algroithm. Used for Add, Remove, and Find

```cpp

bool Add(const K &key, V val) override{
            size_t index = CustomHash<K>()(key) % DTable.size();
            
            // 检查是否已经存在
            for(auto &pair : DTable[index]){
                if(pair.first == key){
                    return false; 
                }
            }
            
            // 不存在就放到末尾
            DTable[index].push_back(std::make_pair(key, val));
            DSize++;
            return true;
        }

        bool Remove(const K &key) override{
            size_t index = CustomHash<K>()(key) % DTable.size();
            
            for(auto it = DTable[index].begin(); it != DTable[index].end(); ++it){
                if(it->first == key){
                    DTable[index].erase(it);
                    DSize--;
                    return true;
                }
            }
            return false;
        }

        bool Find(const K &key, V &val) const override{
            size_t index = CustomHash<K>()(key) % DTable.size();
            
            for(const auto &pair : DTable[index]){
                if(pair.first == key){
                    val = pair.second;
                    return true;
                }
            }
            return false;
        }
```

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