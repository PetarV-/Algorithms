/*
 Petar 'PetarV' Velickovic
 Data Structure: Binary Search Tree
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
#define MAX_N 100001
using namespace std;
typedef long long lld;

struct TreeNode
{
    int key;
    TreeNode *left;
    TreeNode *right;
    TreeNode() {}
    TreeNode(int val)
    {
        key = val;
        left = NULL;
        right = NULL;
    }
};
TreeNode *root;

//Naivna implementacija stabla binarne pretrage
//Slozenost: O(log N) po operaciji

inline void insert(int val)
{
    if (root == NULL)
    {
        root = new TreeNode(val);
        return;
    }
    TreeNode *ptr = root;
    while (true)
    {
        if (val < ptr->key)
        {
            if (ptr->left == NULL)
            {
                ptr->left = new TreeNode(val);
                break;
            }
            else ptr = ptr->left;
        }
        else if (val > ptr->key)
        {
            if (ptr->right == NULL)
            {
                ptr->right = new TreeNode(val);
                break;
            }
            else ptr = ptr->right;
        }
        else return;
    }
}

inline bool find(int val)
{
    TreeNode *ptr = root;
    while (true)
    {
        if (val < ptr->key)
        {
            if (ptr->left == NULL) return false;
            ptr = ptr->left;
        }
        else if (val > ptr->key)
        {
            if (ptr->right == NULL) return false;
            ptr = ptr->right;
        }
        else return true;
    }
}

inline void Delete(TreeNode *ptr, int val)
{
    if (ptr == NULL) return;
    if (val < ptr->key) Delete(ptr->left, val);
    else if (val > ptr->key) Delete(ptr->right, val);
    else
    {
        TreeNode *tmp;
        if (ptr->left == NULL)
        {
            tmp = ptr->right;
            delete ptr;
            ptr = tmp;
        }
        else if (ptr->right == NULL)
        {
            tmp = ptr->left;
            delete ptr;
            ptr = tmp;
        }
        else
        {
            tmp = ptr->right;
            TreeNode *parent = NULL;
            while (tmp->left != NULL)
            {
                parent = tmp;
                tmp = tmp->left;
            }
            ptr->key = tmp->key;
            if (parent != NULL) Delete(parent->left, parent->left->key);
            else Delete(ptr->right, ptr->right->key);
        }
    }
}

int main()
{
    insert(8);
    insert(3);
    insert(10);
    insert(1);
    insert(6);
    insert(4);
    insert(7);
    insert(14);
    insert(13);
    printf("%d\n",find(4) ? 1 : 0);
    printf("%d\n",find(0) ? 1 : 0);
    Delete(root, 8);
    printf("%d\n",find(8) ? 1 : 0);
    printf("%d\n",find(13) ? 1 : 0);
    return 0;
}
