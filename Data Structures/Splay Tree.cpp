/*
 Petar 'PetarV' Velickovic
 Data Structure: Splay Tree
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
using namespace std;
typedef long long lld;
typedef unsigned long long llu;

/*
 Splay Tree data structure is an efficient self-balancing implementation of a binary search tree.
 Complexity:    O(log N) amortized for all operations
*/

struct TreeNode
{
    int key;
    TreeNode* parent;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int key)
    {
        this -> key = key;
        this -> parent = NULL;
        this -> left = NULL;
        this -> right = NULL;
    }
};

class SplayTree
{
    TreeNode *root;
    
    void zig(TreeNode*);
    void zig_zig(TreeNode*);
    void zig_zag(TreeNode*);
    
    void splay(TreeNode*);
    
public:
    SplayTree();
    SplayTree(TreeNode*);
    TreeNode* find(int);
    void insert(int);
    void Delete(int);
    void inOrderPrint(bool);
};

void SplayTree::zig(TreeNode *x)
{
    TreeNode *p = x -> parent;
    if (p -> left == x)
    {
        TreeNode *A = x -> left;
        TreeNode *B = x -> right;
        TreeNode *C = p -> right;
        
        x -> parent = NULL;
        x -> right = p;
        
        p -> parent = x;
        p -> left = B;
        
        if (B != NULL) B -> parent = p;
    }
    else
    {
        TreeNode *A = p -> left;
        TreeNode *B = x -> left;
        TreeNode *C = x -> right;
        
        x -> parent = NULL;
        x -> left = p;
        
        p -> parent = x;
        p -> right = B;
        
        if (B != NULL) B -> parent = p;
    }
}

void SplayTree::zig_zig(TreeNode *x)
{
    TreeNode *p = x -> parent;
    TreeNode *g = p -> parent;
    if (p -> left == x)
    {
        TreeNode *A = x -> left;
        TreeNode *B = x -> right;
        TreeNode *C = p -> right;
        TreeNode *D = g -> right;
        
        x -> parent = g -> parent;
        x -> right = p;
        
        p -> parent = x;
        p -> left = B;
        p -> right = g;
        
        g -> parent = p;
        g -> left = C;
        
        
        if (x -> parent != NULL)
        {
            if (x -> parent -> left == g) x -> parent -> left = x;
            else x -> parent -> right = x;
        }
        
        if (B != NULL) B -> parent = p;
        
        if (C != NULL) C -> parent = g;
    }
    else
    {
        TreeNode *A = g -> left;
        TreeNode *B = p -> left;
        TreeNode *C = x -> left;
        TreeNode *D = x -> right;
        
        x -> parent = g -> parent;
        x -> left = p;
        
        p -> parent = x;
        p -> left = g;
        p -> right = C;
        
        g -> parent = p;
        g -> right = B;
        
        if (x -> parent != NULL)
        {
            if (x -> parent -> left == g) x -> parent -> left = x;
            else x -> parent -> right = x;
        }
        
        if (B != NULL) B -> parent = g;
        
        if (C != NULL) C -> parent = p;
    }
}

void SplayTree::zig_zag(TreeNode *x)
{
    TreeNode *p = x -> parent;
    TreeNode *g = p -> parent;
    if (p -> right == x)
    {
        TreeNode *A = p -> left;
        TreeNode *B = x -> left;
        TreeNode *C = x -> right;
        TreeNode *D = g -> right;
        
        x -> parent = g -> parent;
        x -> left = p;
        x -> right = g;
        
        p -> parent = x;
        p -> right = B;
        
        g -> parent = x;
        g -> left = C;
        
        if (x -> parent != NULL)
        {
            if (x -> parent -> left == g) x -> parent -> left = x;
            else x -> parent -> right = x;
        }
        
        if (B != NULL) B -> parent = p;
        
        if (C != NULL) C -> parent = g;
    }
    else
    {
        TreeNode *A = g -> left;
        TreeNode *B = x -> left;
        TreeNode *C = x -> right;
        TreeNode *D = p -> right;
        
        x -> parent = g -> parent;
        x -> left = g;
        x -> right = p;
        
        p -> parent = x;
        p -> left = C;
        
        g -> parent = x;
        g -> right = B;
        
        if (x -> parent != NULL)
        {
            if (x -> parent -> left == g) x -> parent -> left = x;
            else x -> parent -> right = x;
        }
        
        if (B != NULL) B -> parent = g;
        
        if (C != NULL) C -> parent = p;
    }
}

void SplayTree::splay(TreeNode *x)
{
    while (x -> parent != NULL)
    {
        TreeNode *p = x -> parent;
        TreeNode *g = p -> parent;
        if (g == NULL) zig(x);
        else if (g -> left == p && p -> left == x) zig_zig(x);
        else if (g -> right == p && p -> right == x) zig_zig(x);
        else zig_zag(x);
    }
    this -> root = x;
}

SplayTree::SplayTree()
{
    this -> root = NULL;
}

SplayTree::SplayTree(TreeNode *rt)
{
    this -> root = rt;
}

TreeNode* SplayTree::find(int x)
{
    TreeNode *ret = NULL;
    TreeNode *curr = this -> root;
    TreeNode *prev = NULL;
    while (curr != NULL)
    {
        prev = curr;
        if (x < curr -> key) curr = curr -> left;
        else if (x > curr -> key) curr = curr -> right;
        else
        {
            ret = curr;
            break;
        }
    }
    if (ret != NULL) splay(ret);
    else if (prev != NULL) splay(prev);
    return ret;
}

void SplayTree::insert(int x)
{
    if (root == NULL)
    {
        root = new TreeNode(x);
        return;
    }
    TreeNode *curr = this -> root;
    while (curr != NULL)
    {
        if (x < curr -> key)
        {
            if (curr -> left == NULL)
            {
                TreeNode *newNode = new TreeNode(x);
                curr -> left = newNode;
                newNode -> parent = curr;
                splay(newNode);
                return;
            }
            else curr = curr -> left;
        }
        else if (x > curr -> key)
        {
            if (curr -> right == NULL)
            {
                TreeNode *newNode = new TreeNode(x);
                curr -> right = newNode;
                newNode -> parent = curr;
                splay(newNode);
                return;
            }
            else curr = curr -> right;
        }
        else
        {
            splay(curr);
            return;
        }
    }
}

TreeNode* subtree_max(TreeNode *subRoot)
{
    TreeNode *curr = subRoot;
    while (curr -> right != NULL) curr = curr -> right;
    return curr;
}

TreeNode* subtree_min(TreeNode *subRoot)
{
    TreeNode *curr = subRoot;
    while (curr -> left != NULL) curr = curr -> left;
    return curr;
}

void SplayTree::Delete(int x)
{
    TreeNode *del = find(x);
    if (del == NULL)
    {
        return;
    }
    TreeNode *L = del -> left;
    TreeNode *R = del -> right;
    if (L == NULL && R == NULL)
    {
        this -> root = NULL;
    }
    else if (L == NULL)
    {
        TreeNode *M = subtree_min(R);
        splay(M);
    }
    else if (R == NULL)
    {
        TreeNode *M = subtree_max(L);
        splay(M);
    }
    else
    {
        TreeNode *M = subtree_max(L);
        splay(M);
        M -> right = R;
        R -> parent = M;
    }
    delete del;
}

void printTree(TreeNode *root, bool brackets)
{
    if (root == NULL)
    {
        if (brackets) printf("{}");
        return;
    }
    if (brackets) printf("{");
    if (root -> left != NULL) printTree(root -> left, brackets);
    if (root != NULL) printf(" %c ", root -> key);
    if (root -> right != NULL) printTree(root -> right, brackets);
    if (brackets) printf("}");
}

void SplayTree::inOrderPrint(bool brackets)
{
    printTree(this -> root, brackets);
}

int main()
{
    SplayTree *sTree = new SplayTree();
    sTree -> inOrderPrint(true);
    printf("\n---------------------------------------------------------------\n");
    
    sTree -> insert('D');
    sTree -> inOrderPrint(true);
    printf("\n---------------------------------------------------------------\n");
    
    sTree -> insert('I');
    sTree -> inOrderPrint(true);
    printf("\n---------------------------------------------------------------\n");
    
    sTree -> insert('N');
    sTree -> inOrderPrint(true);
    printf("\n---------------------------------------------------------------\n");
    
    sTree -> insert('O');
    sTree -> inOrderPrint(true);
    printf("\n---------------------------------------------------------------\n");
    
    sTree -> insert('S');
    sTree -> inOrderPrint(true);
    printf("\n---------------------------------------------------------------\n");
    
    sTree -> insert('A');
    sTree -> inOrderPrint(true);
    printf("\n---------------------------------------------------------------\n");
    
    sTree -> insert('U');
    sTree -> inOrderPrint(true);
    printf("\n---------------------------------------------------------------\n");
    
    sTree -> insert('R');
    sTree -> inOrderPrint(true);
    printf("\n---------------------------------------------------------------\n");
    
    sTree -> Delete('I');
    sTree -> inOrderPrint(true);
    printf("\n---------------------------------------------------------------\n");
    
    sTree -> insert('Z');
    sTree -> inOrderPrint(true);
    printf("\n---------------------------------------------------------------\n");
    
    sTree -> Delete('S');
    sTree -> inOrderPrint(true);
    printf("\n---------------------------------------------------------------\n");
    
    sTree -> insert('S');
    sTree -> inOrderPrint(true);
    printf("\n---------------------------------------------------------------\n");
    
    return 0;
}

