/*
 Petar 'PetarV' Velickovic
 Algorithm: Huffman Coding
*/

#include <stdio.h>
#include <math.h>
#include <string.h>
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

typedef long long lld;
typedef unsigned long long llu;
using namespace std;

/*
 The Huffman coding scheme assigns a variable-length prefix code to each character
 in a given set of characters, constructing an optimal lossless coding scheme with
 respect to the character distribution's entropy.
 
 The version implemented here analyses a given ASCII character string in order to
 obtain optimal codes based on character frequencies in the string. A more general
 version would receive a probability distribution instead.
 
 Complexity:    O(n) time to construct
                O(H) time (on average) to encode/decode, where H is the entropy
*/

// The string to analyse
string str;

// Maps the encountered characters to their relative frequencies
map<char, double> P;

// The Huffman Tree
struct HuffTreeNode
{
    double p;
    bool leaf;
    char letter;
    
    HuffTreeNode *parent;
    HuffTreeNode *l;
    HuffTreeNode *r;
    
    // nonleaf node
    HuffTreeNode(double p, HuffTreeNode *l, HuffTreeNode *r)
    {
        this -> p = p;
        this -> leaf = false;
        this -> letter = '\0';
        
        this -> parent = NULL;
        this -> l = l;
        this -> r = r;
        l -> parent = this;
        r -> parent = this;
    }
    
    // leaf node
    HuffTreeNode(double p, char c)
    {
        this -> p = p;
        this -> leaf = true;
        this -> letter = c;
        this -> parent = this -> l = this -> r = NULL;
    }
};

// Comparator of two node pointers
struct CmpNodePtrs
{
    // As priority_queue is a max heap rather than min-heap,
    // invert the meaning of the < operator,
    // in order to get lower probabilities at the top
    bool operator()(const HuffTreeNode* lhs, const HuffTreeNode* rhs) const
    {
        return (lhs -> p) > (rhs -> p);
    }
};

// the root of the tree
HuffTreeNode *root;

// mapping each character to its leaf node (for quick encoding)
map<char, HuffTreeNode*> leaf;

// Produces the probability distribution (may be omitted if known in advance)
inline void analyse()
{
    for (int i=0;i<str.length();i++)
    {
        P[str[i]]++;
    }
    for (auto it = P.begin();it!=P.end();it++)
    {
        P[it -> first] = it -> second / str.length();
    }
}

// Construct the Huffman Tree using the probability distribution
inline void build_tree()
{
    priority_queue<HuffTreeNode*, vector<HuffTreeNode*>, CmpNodePtrs> pq;
    
    // First construct the leaves, and fill the priority queue
    for (auto it = P.begin();it!=P.end();it++)
    {
        leaf[it -> first] = new HuffTreeNode(it -> second, it -> first);
        pq.push(leaf[it -> first]);
    }
    
    while (pq.size() > 1)
    {
        HuffTreeNode* L = pq.top(); pq.pop();
        HuffTreeNode* R = pq.top(); pq.pop();
        
        // Spawn a new node generating the children
        HuffTreeNode* par = new HuffTreeNode((L -> p) + (R -> p), L, R);
        pq.push(par);
    }
    
    root = pq.top(); pq.pop();
}

// Huffman-encode a given character
inline string encode(char c)
{
    string ret = "";
    
    HuffTreeNode* curr = leaf[c];
    while (curr -> parent != NULL)
    {
        if (curr == curr -> parent -> l) ret += "0";
        else if (curr == curr -> parent -> r) ret += "1";
        
        curr = curr -> parent;
    }
    
    reverse(ret.begin(), ret.end());
    return ret;
}

// Huffman-encode the given string
inline string encode(string s)
{
    string ret = "";
    
    for (int i=0;i<s.length();i++)
    {
        ret += encode(s[i]);
    }
    
    return ret;
}

// Huffman-decode the given string
inline string decode(string s)
{
    string ret = "";
    
    int i = 0;
    HuffTreeNode* curr;
    
    while (i < s.length())
    {
        curr = root;
        while (!(curr -> leaf))
        {
            if (s[i++] == '0') curr = curr -> l;
            else curr = curr -> r;
        }
        ret += curr -> letter;
    }
    return ret;
}

int main()
{
    str = "this is an example of a huffman tree";
    
    analyse();
    build_tree();
    
    string test = " aefhimnstloprux";
    for (int i=0;i<test.length();i++)
    {
        cout << "Encode(" << test[i] << ") = " << encode(test[i]) << endl;
    }
    
    cout << encode("this is real") << endl;
    cout << decode("1100001010110011111101100111110010010111100") << endl;
    
    cout << decode(encode("this is real")) << endl;
    
    return 0;
}
