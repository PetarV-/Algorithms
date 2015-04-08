/*
 Petar 'PetarV' Velickovic
 Data Structure: Suffix Automaton
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

#define MAX_N 250001
#define MAX_S 1000010
#define MAX_K 26

typedef long long lld;
typedef unsigned long long llu;
using namespace std;

/*
 The suffix automaton is a minimal deterministic finite automaton (DFA) accepting all
 suffices of a given string. It is useful for a variety of actions, one of which is efficiently
 computing the longest common substring (LCS) between two strings.
 Complexity:    O(n) for constructing the automaton (character by character)
                O(m) for computing the LCS
*/

char inp[MAX_N];

struct Node
{
    int len, prev;
    int adj[MAX_K];
};

Node DFA[MAX_S];
int tot = 0, sink;

inline void init_automaton()
{
    DFA[0].len = 0;
    DFA[0].prev = -1;
    for (int i=0;i<26;i++) DFA[0].adj[i] = -1;
    sink = 0;
    tot = 1;
}

inline void extend_automaton(char ch)
{
    int cc = ch - 'a';
    
    int tail = tot++;
    DFA[tail].len = DFA[sink].len + 1;
    for (int i=0;i<26;i++) DFA[tail].adj[i] = -1;
    
    int curr = sink;
    while (curr != -1 && DFA[curr].adj[cc] == -1)
    {
        DFA[curr].adj[cc] = tail;
        curr = DFA[curr].prev;
    }
    
    if (curr == -1)
    {
        DFA[tail].prev = 0;
    }
    else
    {
        int nxt = DFA[curr].adj[cc];
        if (DFA[nxt].len == DFA[curr].len + 1)
        {
            DFA[tail].prev = nxt;
        }
        else
        {
            int cl = tot++;
            DFA[cl].len = DFA[curr].len + 1;
            DFA[cl].prev = DFA[nxt].prev;
            for (int i=0;i<26;i++) DFA[cl].adj[i] = DFA[nxt].adj[i];
            
            while (curr != -1 && DFA[curr].adj[cc] == nxt)
            {
                DFA[curr].adj[cc] = cl;
                curr = DFA[curr].prev;
            }
            
            DFA[tail].prev = DFA[nxt].prev = cl;
        }
    }
    sink = tail;
}

inline string lcs(string needle)
{
    int curr_len = 0;
    int best_len = 0, best_pos = -1;
    int st = 0;
    
    for (int i=0;i<needle.length();i++)
    {
        char cc = needle[i] - 'a';
        if (DFA[st].adj[cc] == -1)
        {
            while (st != -1 && DFA[st].adj[cc] == -1)
            {
                st = DFA[st].prev;
            }
            if (st == -1)
            {
                st = 0, curr_len = 0;
                continue;
            }
            curr_len = DFA[st].len;
        }
        curr_len++;
        if (best_len < curr_len)
        {
            best_len = curr_len;
            best_pos = i;
        }
        st = DFA[st].adj[cc];
    }
    return needle.substr(best_pos - best_len + 1, best_len);
}

int main()
{
    string s1 = "alsdfkjfjkdsal";
    string s2 = "fdjskalajfkdsla";
    
    init_automaton();
    for (int i=0;i<s1.length();i++) extend_automaton(s1[i]);
    
    cout << lcs(s2) << endl;
    
    return 0;
}
