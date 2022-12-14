#include "AVLTree.hpp"
using namespace std;

// Insert new node, rotate tree accordingly, return sorted root
Node* AVLTree::InsertHelper(Node* node, string name, string ufid)
{
    if (node == nullptr)
    {
        cout << "successful" << endl;
        return new Node(name, ufid);
    }

    if (ufid < node->ufid)
        node->left = InsertHelper(node->left, name, ufid);
    else if (ufid > node->ufid)
        node->right = InsertHelper(node->right, name, ufid);
    else
        cout << "unsuccessful" << endl;

    return Rotate(node); // Rotate for every node along path
}

void AVLTree::Insert(string name, string ufid) 
{
    this->root = InsertHelper(this->root, name, ufid); // Call helper function for recursion
    this->height = Height(this->root);
}

// Rotate tree based on balance factor, return rotated tree root; some code from module 4 slides
Node* AVLTree::Rotate(Node* currentRoot) 
{
    int bfRoot = Height(currentRoot->left) - Height(currentRoot->right); // BF of root

    if (bfRoot == 2) // Either left-left or left-right setting
    {
        int bfLeft = Height(currentRoot->left->left) - Height(currentRoot->left->right); // BF of root->left

        if (bfLeft == -1) // Left-right case, left-right rotation
        {
            Node* newChild = currentRoot->left;
            Node* newParent = currentRoot->left->right;

            currentRoot->left = newParent->right;
            newChild->right = newParent->left;
            newParent->right = currentRoot;
            newParent->left = newChild;

            return newParent;
        }
        else // Left-left case, right rotation
        {
            Node* grandchild = currentRoot->left->right;
            Node* newParent = currentRoot->left;

            newParent->right = currentRoot;
            currentRoot->left = grandchild;

            return newParent;
        }
    }
    else if (bfRoot == -2) // Either right-right or right-left setting
    {
        int bfRight = Height(currentRoot->right->left) - Height(currentRoot->right->right); // BF of root->right

        if (bfRight == 1) // Right-left case, right-left rotation, mirror of left-right case
        {
            Node* newChild = currentRoot->right;
            Node* newParent = currentRoot->right->left;

            currentRoot->right = newParent->left;
            newChild->left = newParent->right;
            newParent->left = currentRoot;
            newParent->right = newChild;

            return newParent;
        }
        else // Right-right case, left rotation, mirror of left-left case
        {
            Node* grandchild = currentRoot->right->left;
            Node* newParent = currentRoot->right;

            newParent->left = currentRoot;
            currentRoot->right = grandchild;

            return newParent;
        }
    }

    return currentRoot;
}

int AVLTree::Height(Node* node) // Calculate height for given node recursively by using max() function
{
    if (node == nullptr)
        return 0;
    else
        return 1 + max(Height(node->left), Height(node->right));
}

// Recursively travel through tree and delete once UFID match found
Node* AVLTree::RemoveHelper(Node* node, string ufid) 
{
    if (node == nullptr) // Node to be deleted not found
    {
        cout << "unsuccessful" << endl;
        return node;
    }

    if (ufid < node->ufid) // UFID less than local root
        node->left = RemoveHelper(node->left, ufid);
    else if (ufid > node->ufid) // UFID greater than local root
        node->right = RemoveHelper(node->right, ufid);
    else // UFID == local root, delete this node
    {
        // 0 or 1 children
        if (node->left == nullptr)
        {
            Node* temp = node->right;
            delete node;
            cout << "successful" << endl;
            return temp;
        }
        else if (node->right == nullptr)
        {
            Node* temp = node->left;
            delete node;
            cout << "successful" << endl;
            return temp;
        }
        
        // Node has 2 children
        // Get inorder successor and copy into this node
        Node* temp = FindSuccessor(node->right);
        node->ufid = temp->ufid;
        node->name = temp->name;

        // Delete successor after copying
        node->right = RemoveHelper(node->right, temp->ufid);
    }

    return node;
}

// Find inorder successor for local root
Node* AVLTree::FindSuccessor(Node* node)
{
    while (node->left != nullptr)
        node = node->left;

    return node;
}

void AVLTree::Remove(string ufid) // Call RemoveHelper
{
    this->root = RemoveHelper(this->root, ufid);
}

void AVLTree::SearchIDHelper(Node* node, string ufid)
{
    if (node == nullptr)
    {
        cout << "unsuccessful" << endl;
        return;
    }
    else if (ufid < node->ufid)
        SearchIDHelper(node->left, ufid);
    else if (ufid > node->ufid)
        SearchIDHelper(node->right, ufid);
    else // UFID found
        cout << node->name << endl;
}

void AVLTree::SearchID(string ufid)
{
    SearchIDHelper(this->root, ufid);
}

void AVLTree::SearchNameHelper(Node* node, string name, vector<string>& names)
{
    if (node == nullptr)
    {
        return;
    }
    else
    {
        if (name == node->name)
            names.push_back(node->ufid);
        SearchNameHelper(node->left, name, names);
        SearchNameHelper(node->right, name, names);
    }
}

void AVLTree::SearchName(string name)
{
    vector<string> names;
    SearchNameHelper(this->root, name, names);

    if (names.size() == 0)
        cout << "unsuccessful" << endl;
    else
    {
        for (string s : names)
            cout << s << endl;
    }
}

void AVLTree::InorderHelper(Node* node, vector<string>& names)
{
    if (node == nullptr)
        return;

    InorderHelper(node->left, names);
    names.push_back(node->name);
    InorderHelper(node->right, names);
}

vector<string> AVLTree::PrintInorder()
{
    vector<string> names;
    InorderHelper(this->root, names);

    cout << names[0];

    for (int i = 1; i < names.size(); i++)
        cout << ", " << names[i];

    cout << endl;
    return names;
}

void AVLTree::PreorderHelper(Node* node, vector<string>& names)
{
    if (node == nullptr)
        return;

    names.push_back(node->name);
    PreorderHelper(node->left, names);
    PreorderHelper(node->right, names);
}

vector<string> AVLTree::PrintPreorder()
{
    vector<string> names;
    PreorderHelper(this->root, names);

    cout << names[0];

    for (int i = 1; i < names.size(); i++)
        cout << ", " << names[i];

    cout << endl;
    return names;
}

void AVLTree::PostorderHelper(Node* node, vector<string>& names)
{
    if (node == nullptr)
        return;

    PostorderHelper(node->left, names);
    PostorderHelper(node->right, names);
    names.push_back(node->name);
}

vector<string> AVLTree::PrintPostorder()
{
    vector<string> names;
    PostorderHelper(this->root, names);

    cout << names[0];

    for (int i = 1; i < names.size(); i++)
        cout << ", " << names[i];

    cout << endl;
    return names;
}

void AVLTree::PrintlevelCount()
{
    cout << this->height << endl;
}

void AVLTree::RemoveInorderHelper(Node* node, vector<string>& ufids)
{
    if (node == nullptr)
        return;

    RemoveInorderHelper(node->left, ufids);
    ufids.push_back(node->ufid);
    RemoveInorderHelper(node->right, ufids);
}

void AVLTree::RemoveInorder(int n)
{
    vector<string> ufids;
    RemoveInorderHelper(this->root, ufids);

    if (n < ufids.size())
        Remove(ufids[n]);
    else   
        cout << "unsuccessful" << endl;
}