/*
 Petar 'PetarV' Velickovic
 Data Structure: Binary Search Tree (Microchallenge)
*/

#include <stdio.h>
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
#define MAX_D 10001
using namespace std;
typedef long long lld;

/*
 A naive implementation of a Binary Search Tree data structure.
 Used for efficient insertion, deletion and retreival of keys.
 Complexity: average case O(log N) per operation
*/

class BST;

class Node
{
    public:
    
        char key;
        int satelliteData;
    
        Node();
        Node(char key, int satelliteData);
    
        BST *left;
        BST *right;
        Node *parent;
    
        BST *myTree;
};

class BST
{
    public:
    
        Node *root;
 
        BST();
        BST(Node *root);
    
        bool isEmpty();
    
        Node *search(char key);
    
        Node *minimum();
        Node *maximum();
    
        Node *predecessor(Node *x);
        Node *successor(Node *x);
    
        void Insert(Node *x);
        void Delete(Node *del);
    
        void set(char key, int value);
    
        void inOrderPrint(bool brackets);
    
        void prettyPrint();
};
         
Node::Node(char key, int satelliteData)
{
    this -> key = key;
    this -> satelliteData = satelliteData;
    this -> left = NULL;
    this -> right = NULL;
    this -> parent = NULL;
    this -> myTree = NULL;
}

BST::BST()
{
    this -> root = NULL;
}

BST::BST(Node *root)
{
    this -> root = root;
}

bool BST::isEmpty()
{
    return (root == NULL);
}

Node *BST::search(char key)
{
    if (isEmpty()) return NULL;
    if (root -> key > key) return root -> left -> search(key);
    else if (root -> key < key) return root -> right -> search(key);
    else return root;
}

Node *BST::minimum()
{
    if (isEmpty()) return NULL;
    if (root -> left == NULL) return root;
    return root -> left -> minimum();
}

Node *BST::maximum()
{
    if (isEmpty()) return NULL;
    if (root -> right == NULL) return root;
    return root -> right -> maximum();
}

Node *BST::predecessor(Node *x)
{
    if (x -> left != NULL) return x -> left -> maximum();
    Node *top = x -> parent;
    while (top != NULL && top -> key > x -> key)
    {
        x = top;
        top = top -> parent;
    }
    return top;
}

Node *BST::successor(Node *x)
{
    if (x -> right != NULL) return x -> right -> minimum();
    Node *top = x -> parent;
    while (top != NULL && top -> key < x -> key)
    {
        x = top;
        top = top -> parent;
    }
    return top;
}

void BST::Insert(Node *x)
{
    if (isEmpty())
    {
        Node *n = new Node(x -> key, x -> satelliteData);
        n -> parent = NULL;
        n -> myTree = this;
        root = n;
        return;
    }
    
    Node *curr = root;
    
    while (true)
    {
        if (x -> key < curr -> key)
        {
            if (curr -> left == NULL)
            {
                BST *L = new BST();
                Node *n = new Node(x -> key, x -> satelliteData);
                n -> parent = curr;
                n -> myTree = L;
                L -> root = n;
                curr -> left = L;
                return;
            }
            else curr = curr -> left -> root;
        }
        else if (x -> key > curr -> key)
        {
            if (curr -> right == NULL)
            {
                BST *R = new BST();
                Node *n = new Node(x -> key, x -> satelliteData);
                n -> parent = curr;
                n -> myTree = R;
                R -> root = n;
                curr -> right = R;
                return;
            }
            else curr = curr -> right -> root;
        }
        else return; //Node with such key already exists in the tree
    }
}

void BST::Delete(Node *del)
{
    Node *tmp;
    
    if (del -> left == NULL && del -> right == NULL) //leaf
    {
        if (del -> parent != NULL)
        {
            if (del -> parent -> left != NULL && del -> parent -> left -> root -> key == del -> key)
            {
                del -> parent -> left = NULL;
            }
            else if (del -> parent -> right != NULL && del -> parent -> right -> root -> key == del -> key)
            {
                del -> parent -> right = NULL;
            }
        }
        delete del;
        return;
    }
    
    if (del -> left == NULL)
    {
        tmp = del -> right -> root;
        if (del -> parent != NULL)
        {
            if (del -> parent -> left != NULL && del -> parent -> left -> root -> key == del -> key)
            {
                del -> parent -> left = tmp -> myTree;
            }
            else if (del -> parent -> right != NULL && del -> parent -> right -> root -> key == del -> key)
            {
                del -> parent -> right = tmp -> myTree;
            }
        }
        tmp -> parent = del -> parent;
        delete del;
        return;
    }
    
    if (del -> right == NULL)
    {
        tmp = del -> left -> root;
        if (del -> parent != NULL)
        {
            if (del -> parent -> left != NULL && del -> parent -> left -> root -> key == del -> key)
            {
                del -> parent -> left = tmp -> myTree;
            }
            else if (del -> parent -> right != NULL && del -> parent -> right -> root -> key == del -> key)
            {
                del -> parent -> right = tmp -> myTree;
            }
        }
        tmp -> parent = del -> parent;
        delete del;
        return;
    }
    
    else
    {
        tmp = successor(del);
        del -> key = tmp -> key;
        del -> satelliteData = tmp -> satelliteData;
        Delete(tmp);
    }
}

void BST::set(char key, int value)
{
    if (search(key) != NULL)
    {
        Insert(new Node(key, value));
    }
}

void BST::inOrderPrint(bool brackets)
{
    if (root == NULL)
    {
        if (brackets) printf("{}");
        return;
    }
    if (brackets) printf("{");
    if (root -> left != NULL) root -> left -> inOrderPrint(brackets);
    if (root != NULL) printf(" %c ", root -> key);
    if (root -> right != NULL) root -> right -> inOrderPrint(brackets);
    if (brackets) printf("}");
}

void BST::prettyPrint()
{
    if (isEmpty()) return;
    
    //do a breadth-first traversal of the tree to get the depth and extract the level by level node ordering.
    //include non-existent nodes as empty space keys.
    int depth = 0;
    vector<char> Tree[MAX_D];
    queue<Node *> bfs_q;
    queue<int> bfs_d;
    bfs_q.push(root);
    bfs_d.push(0);
    while (!bfs_q.empty())
    {
        Node *curr = bfs_q.front();
        int dt = bfs_d.front();
        
        bfs_q.pop();
        bfs_d.pop();
        
        Tree[dt].push_back(curr -> key);
        
        if (curr -> key != ' ' && dt > depth) depth = dt;
        if (curr -> key == ' ' && dt > depth+1) break;
        
        if (curr -> left != NULL)
        {
            bfs_q.push(curr -> left -> root);
            bfs_d.push(dt + 1);
        }
        else
        {
            bfs_q.push(new Node(' ', 0));
            bfs_d.push(dt + 1);
        }
        
        if (curr -> right != NULL)
        {
            bfs_q.push(curr -> right -> root);
            bfs_d.push(dt + 1);
        }
        else
        {
            bfs_q.push(new Node(' ', 0));
            bfs_d.push(dt + 1);
        }
    }
    
    if (depth == 0)
    {
        printf("%c", root -> key);
        return;
    }
    
    //reconstruct fancy tree in a bottom-up fashion. :)
    
    int height = (1 << depth) + depth;
    int width = (1 << (depth+1)) - 1;
    
    vector<vector<char> > fancyTree;
    fancyTree.resize(height + 5);
    for (int i=0;i<height;i++)
    {
        fancyTree[i].resize(width + 5);
        fill(fancyTree[i].begin(),fancyTree[i].end(),' ');
    }
    
    std::set<int> pos;
    bool ok[1000001];
    
    int ii = 0;
    while (ii < width)
    {
        pos.insert(ii);
        ok[ii] = false;
        ii += 2;
    }
    
    int currLevel = height - 1;
    int levelZ = 0;
    
    for (int i=depth;i>=0;i--)
    {
        if (i == 0)
        {
            fancyTree[0][(*pos.begin())] = Tree[0][0];
            break;
        }
        int jj = 0;
        
        for (std::set<int>::iterator it = pos.begin(); it != pos.end(); it++)
        {
            fancyTree[currLevel][(*it)] = Tree[i][jj];
            if (Tree[i][jj++] != ' ') ok[(*it)] = true;
        }
        
        currLevel--;
        int hem = 0;
        while (hem < (1 << levelZ))
        {
            std::set<int> help;
            for (std::set<int>::iterator it = pos.begin(); it != pos.end();)
            {
                help.insert((*it) + 1);
                ok[(*it)+1] = ok[(*it)];
                if (ok[(*it)]) fancyTree[currLevel][(*it)] = '/';
                it++;
                help.insert((*it) - 1);
                ok[(*it)-1] = ok[(*it)];
                if (ok[(*it)]) fancyTree[currLevel][(*it)] = '\\';
                it++;
            }
            currLevel--;
            hem++;
            pos = std::set<int> (help);
        }
        levelZ++;
    }
    for (int i=0;i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
            printf("%c",fancyTree[i][j]);
        }
        if (i < height - 1) printf("\n");
    }
}

int main()
{
    
    char response[55];
    bool fancy = false;
    
    printf("Do you want to test with fancy BST output? (Y/N)\n");
    while (true)
    {
        scanf("%s", response);
        if (response[0] == 'Y' || response[0] == 'y') { fancy = true; break; }
        else if (response[0] == 'N' || response[0] == 'n') break;
        printf("Incorrect character! You must input 'Y' or 'N'. Retry: \n");
    }
    
    printf("Do you want to write the results to file? (Y/N)\n");
    while (true)
    {
        scanf("%s", response);
        if (response[0] == 'Y' || response[0] == 'y') break;
        else if (response[0] == 'N' || response[0] == 'n') break;
        printf("Incorrect character! You must input 'Y' or 'N'. Retry: \n");
    }
    
    if (response[0] == 'Y' || response[0] == 'y')
    {
        if (!fancy) freopen("/Users/PetarV/TestLogs/BST-Test-Regular.txt","w",stdout);
        else freopen("/Users/PetarV/TestLogs/BST-Test-Fancy.txt","w",stdout);
    }
    
    time_t t = time(0);
    struct tm *now = localtime(&t);
    
    printf("BST Microchallenge testing protocol started.\n");
    printf("Testing carried out on %d-%d-%d, by Petar Velickovic.", now -> tm_year + 1900, now -> tm_mon + 1, now -> tm_mday);
    printf("\n---------------------------------------------------------------\n");
    
    printf("Creating an empty BST.\n");
    BST *testRoot = new BST();
    if (!fancy) { printf("BST contains: "); testRoot -> inOrderPrint(true); }
    else { printf("BST contains: \n"); testRoot -> prettyPrint(); }
    printf("\n---------------------------------------------------------------\n");
    
    printf("Inserting 'D'.\n");
    testRoot -> Insert(new Node('D', 0));
    if (!fancy) { printf("BST contains: "); testRoot -> inOrderPrint(true); }
    else { printf("BST contains: \n"); testRoot -> prettyPrint(); }
    printf("\n---------------------------------------------------------------\n");
    
    printf("Inserting 'I'.\n");
    testRoot -> Insert(new Node('I', 0));
    if (!fancy) { printf("BST contains: "); testRoot -> inOrderPrint(true); }
    else { printf("BST contains: \n"); testRoot -> prettyPrint(); }
    printf("\n---------------------------------------------------------------\n");
    
    printf("Inserting 'N'.\n");
    testRoot -> Insert(new Node('N', 0));
    if (!fancy) { printf("BST contains: "); testRoot -> inOrderPrint(true); }
    else { printf("BST contains: \n"); testRoot -> prettyPrint(); }
    printf("\n---------------------------------------------------------------\n");
    
    printf("Inserting 'O'.\n");
    testRoot -> Insert(new Node('O', 0));
    if (!fancy) { printf("BST contains: "); testRoot -> inOrderPrint(true); }
    else { printf("BST contains: \n"); testRoot -> prettyPrint(); }
    printf("\n---------------------------------------------------------------\n");
    
    printf("Inserting 'S'.\n");
    testRoot -> Insert(new Node('S', 0));
    if (!fancy) { printf("BST contains: "); testRoot -> inOrderPrint(true); }
    else { printf("BST contains: \n"); testRoot -> prettyPrint(); }
    printf("\n---------------------------------------------------------------\n");
    
    printf("Inserting 'A'.\n");
    testRoot -> Insert(new Node('A', 0));
    if (!fancy) { printf("BST contains: "); testRoot -> inOrderPrint(true); }
    else { printf("BST contains: \n"); testRoot -> prettyPrint(); }
    printf("\n---------------------------------------------------------------\n");
    
    printf("Inserting 'U'.\n");
    testRoot -> Insert(new Node('U', 0));
    if (!fancy) { printf("BST contains: "); testRoot -> inOrderPrint(true); }
    else { printf("BST contains: \n"); testRoot -> prettyPrint(); }
    printf("\n---------------------------------------------------------------\n");
    
    printf("Inserting 'R'.\n");
    testRoot -> Insert(new Node('R', 0));
    if (!fancy) { printf("BST contains: "); testRoot -> inOrderPrint(true); }
    else { printf("BST contains: \n"); testRoot -> prettyPrint(); }
    printf("\n---------------------------------------------------------------\n");
    
    printf("Searching for the predecessor of 'D'.\n");
    printf("Predecessor of 'D' is '%c'.", testRoot -> predecessor(testRoot -> search('D')) -> key);
    printf("\n---------------------------------------------------------------\n");
    
    printf("Deleting 'I'.\n");
    testRoot -> Delete(testRoot -> search('I'));
    if (!fancy) { printf("BST contains: "); testRoot -> inOrderPrint(true); }
    else { printf("BST contains: \n"); testRoot -> prettyPrint(); }
    printf("\n---------------------------------------------------------------\n");
    
    printf("Searching for the maximal key in the tree.\n");
    printf("The maximal key is '%c'.", testRoot -> maximum() -> key);
    printf("\n---------------------------------------------------------------\n");
    
    printf("Inserting 'Z'.\n");
    testRoot -> Insert(new Node('Z', 0));
    if (!fancy) { printf("BST contains: "); testRoot -> inOrderPrint(true); }
    else { printf("BST contains: \n"); testRoot -> prettyPrint(); }
    printf("\n---------------------------------------------------------------\n");
    
    printf("Searching for the successor of 'R'.\n");
    printf("Successor of 'R' is '%c'.", testRoot -> successor(testRoot -> search('R')) -> key);
    printf("\n---------------------------------------------------------------\n");

    printf("Deleting 'S'.\n");
    testRoot -> Delete(testRoot -> search('S'));
    if (!fancy) { printf("BST contains: "); testRoot -> inOrderPrint(true); }
    else { printf("BST contains: \n"); testRoot -> prettyPrint(); }
    printf("\n---------------------------------------------------------------\n");
    
    printf("Inserting 'T'.\n");
    testRoot -> Insert(new Node('T', 0));
    if (!fancy) { printf("BST contains: "); testRoot -> inOrderPrint(true); }
    else { printf("BST contains: \n"); testRoot -> prettyPrint(); }
    printf("\n---------------------------------------------------------------\n");
    
    printf("Testing completed.\n");
    return 0;
}