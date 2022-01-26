


#ifndef BST_H_KNOWN
#define BST_H_KNOWN


#include <iostream>
#include <string>
#include <queue>
using namespace std;

class BinarySearchTree {

protected:
    struct node { 
        int data;
        node* left_child;
        node* right_child;
        static int count_nodes;


        node(int d, node* left=nullptr, node* right=nullptr){
            data = d; ++count_nodes;
            left_child = left;
            right_child = right;
        }

        static int get_count_nodes() {return count_nodes; }
    };

    node* root = nullptr;
    int counter  = 0;

public:

    BinarySearchTree() = default;
    ~BinarySearchTree() { /*cout << "BST has been destroyed" << endl;*/ }
    void clear(node* root);
    void delete_Tree(node** root);

    node* get_root() {return root; }
    static int get_count_node() {return node::get_count_nodes(); }

    void insert(int new_data);
    node* add(node* root, int new_data);

    bool Search(node* root,  int target);

    void level_order(node* root);

    int height(node* root);
};

int BinarySearchTree::node::count_nodes = 0;

void BinarySearchTree::insert(int new_data)
{
    root = add(root, new_data);
    ++counter;
}

BinarySearchTree::node* BinarySearchTree::add(node* root, int new_data)
{
    if(root == nullptr)
        root = new node(new_data);
    else if(new_data < root->data)
        root->left_child = add(root->left_child, new_data);
    else if(new_data > root->data)
        root->right_child = add(root->right_child, new_data);
    else {
        //cout << "NO DUPLICATES ALLOWED" << endl;
    }

    return root;
}

bool BinarySearchTree::Search(node* root, int target)
{
    if(root == nullptr)
        return false;
    else if(root->data == target)
        return true;
    else if(target < root->data)
        return Search(root->left_child, target);
    else 
        return Search(root->right_child, target);
}

void BinarySearchTree::level_order(node* root)
{
    if(root == nullptr) return;

    queue<BinarySearchTree::node*> Q;

    Q.push(root);

    while(!Q.empty())
    {
        node* current = Q.front();
        cout << current->data << "  ";
        if(current->left_child != nullptr) Q.push(current->left_child);
        if(current->right_child != nullptr) Q.push(current->right_child);

        Q.pop();
    }
}

void BinarySearchTree::clear(node* root)
{
    if(root == nullptr) 
        return;
    clear(root->left_child);
    clear(root->right_child);

    //cout << "Deleting node: " << root->data <<  endl;
    delete root;
}

void BinarySearchTree::delete_Tree(node** root)
{
    clear(*root);
    *root = nullptr;
}

int maxx(int a, int b)
{
    return std::max(a, b);
}

int BinarySearchTree::height(node* root)
{
    if(root == nullptr)
        return -1;
    return maxx(height(root->left_child), height(root->right_child)) + 1;

}

#endif