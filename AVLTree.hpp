#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <string>
using namespace std;

// Class to denote nodes in AVL tree
struct Node
{
    string ufid;
    string name;
    Node* left;
    Node* right;
    int balanceFactor;

    Node() : name(""), ufid(""), left(nullptr), right(nullptr), balanceFactor(0) {};
    Node(string name, string ufid) : name(name), ufid(ufid), left(nullptr), right(nullptr), balanceFactor(0) {};
    ~Node() {};
};

// Class to denote the AVL tree
class AVLTree
{
    Node* root;
    int height; // 1-based height of tree

    Node* InsertHelper(Node* node, string name, string ufid); // Returns new root after inserting and rotating
    void InorderHelper(Node* node, vector<string>& names);
    void PreorderHelper(Node* node, vector<string>& names);
    void PostorderHelper(Node* node, vector<string>& names);
    Node* RemoveHelper(Node* node, string ufid);
    Node* FindSuccessor(Node* currentRoot);
    void SearchIDHelper(Node* node, string ufid);
    void SearchNameHelper(Node* node, string name, vector<string>& names);
    Node* Rotate(Node* currentRoot); // Returns new root after rotating (called within InsertHelper)
    int Height(Node* node);
    void RemoveInorderHelper(Node* node, vector<string>& ufids);

public:
    void Insert(string name, string ufid);
    void Remove(string ufid);
    void SearchID(string ufid);
    void SearchName(string name);
    vector<string> PrintInorder();
    vector<string> PrintPreorder();
    vector<string> PrintPostorder();
    void PrintlevelCount();
    void RemoveInorder(int n);

    AVLTree() : root(nullptr), height(0) {}
    ~AVLTree() { delete root; };
};