/*
 Petar 'PetarV' Velickovic
 Data Structure: Trie
*/

#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <complex>
#include <chrono>
#include <random>
#include <unordered_map>

typedef long long lld;
typedef unsigned long long llu;
using namespace std;

/*
 The trie data structure holds a compact representation of all prefixes of
 a given dictionary of strings, enabling linear-time lookups.
 Complexity:    O(n) for adding a string in the dictionary
                O(n) for testing whether a string is in the dictionary
*/

struct TrieNode
{
    bool leaf;
    unordered_map<char, TrieNode*> chd; // can also use an array, or a regular map
    
    TrieNode() : leaf(false) { }
};

TrieNode *root;

void insert(TrieNode* x, string s, int pos)
{
    if (pos == s.length()) x -> leaf = true;
    else
    {
        char cur = s[pos];
        if (x -> chd[cur] == NULL)
        {
            x -> chd[cur] = new TrieNode();
        }
        insert(x -> chd[cur], s, pos + 1);
    }
}

bool find(TrieNode* x, string s, int pos)
{
    if (pos == s.length()) return (x -> leaf);
    if (x -> chd[s[pos]] == NULL) return false;
    return find(x -> chd[s[pos]], s, pos+1);
}

int main()
{
    string s1 = "911";
    string s2 = "97625999";
    string s3 = "91125426";
    
    root = new TrieNode();
    
    insert(root, s1, 0);
    insert(root, s2, 0);
    insert(root, s3, 0);
    
    cout << (find(root, "9", 0) ? "1" : "0") << endl;
    cout << (find(root, "91", 0) ? "1" : "0") << endl;
    cout << (find(root, "911", 0) ? "1" : "0") << endl;
    cout << (find(root, "9112", 0) ? "1" : "0") << endl;
    cout << (find(root, "91125426", 0) ? "1" : "0") << endl;
    cout << (find(root, "911254267", 0) ? "1" : "0") << endl;
    
    return 0;
}
