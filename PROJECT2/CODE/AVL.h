

#pragma once

#include <iostream>
#include <string>
#include "BST.h"

using namespace std;

class AVL_Tree : public BinarySearchTree
{

public:

    AVL_Tree() = default;
    ~AVL_Tree() { /*cout << "AVL tree has been destroyed" << endl;*/ }

    int getBalanceFactor(node* root);
    int height(node* root);

    node* rightRotate(node* y);
    node* leftRotate(node* x);

    node* add(node* root, int new_value);
    void insert(int new_value);

};

void AVL_Tree::insert(int new_value)
{
    root = add(root, new_value);
    ++counter;
}

AVL_Tree::node* AVL_Tree::add(node* root, int new_value)
{
    if(root == nullptr) {
        root = new node(new_value);
        return root;
    }
    else if(new_value < root->data)
        root->left_child = add(root->left_child, new_value);
    else if(new_value > root->data)
        root->right_child = add(root->right_child, new_value);
    else {
        //cout << "NO DUPLICATES ALLOWED" << endl;
        return root;
    } 

    int balance_factor = getBalanceFactor(root);

    //if we know that there is imbalance
    //we also have to determine what type of imbalance occured
    // and there are 4 cases

    
    if (balance_factor > 1 && new_value < root->left_child->data)
        return rightRotate(root);  

    if (balance_factor < -1 && new_value > root->right_child->data)
        return leftRotate(root); 
 
    if (balance_factor > 1 && new_value > root->left_child->data)
    {
        root->left_child = leftRotate(root->left_child);
        return rightRotate(root);
    }

    if (balance_factor < -1 && new_value < root->right_child->data)
    {
        root->right_child = rightRotate(root->right_child);
        return leftRotate(root);
    }

    return root;
}

int AVL_Tree::getBalanceFactor(node* root)
{
    if(root == nullptr)
        return -1;
    else
        return (height(root->left_child) - height(root->right_child));
}

int max(int a, int b)
{
    return std::max(a, b);
}

int AVL_Tree::height(node* root)
{
    if(root == nullptr)
        return -1;
    return max(height(root->left_child), height(root->right_child)) + 1;

}

AVL_Tree::node* AVL_Tree::rightRotate(node* y)
{
    node *x = y->left_child;
    node *T2 = x->right_child;

    x->right_child = y;
    y->left_child = T2;

    return x;
}

AVL_Tree::node* AVL_Tree::leftRotate(node* x)
{
    node *y = x->right_child;
    node *T2 = y->left_child;
 
    // Perform rotation
    y->left_child = x;
    x->right_child = T2;

    return y;
}


