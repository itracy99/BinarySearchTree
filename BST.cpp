//
// Created by Ian on 12/6/2019.
//

#include "BST.h"
#include "BSTNode.h"
#include <vector>
#include <queue>
#include <stack>
#include <stdexcept>
#include <iostream>

using namespace std;

BST::BST() {
    this->root = nullptr;
    this->size = 0;
}

BST::~BST() {
    this->destructTree(this->root);
}

bool BST::isEmpty() const {
    return this->size == 0;
}

int BST::getSize() const {
    return this->size;
}

void BST::insert(int key) {
        this->root = this->insert_h(key, this->root);
        this->size++;
}

BSTNode* BST::find(int key) {
    BSTNode* location = find_h(key, this->root);
    if (location == nullptr) {
        throw runtime_error("BST::find, key not present in BST");
    }
    return location;
}

void BST::remove(int key) {
   this->root= this->remove_h(key, this->root);
}

bool BST::contain(int key) {
    BSTNode* location = find_h(key, this->root);
    return location != nullptr;
}

vector<int> BST::preOrder() {
    vector<int> vals;
    this->preOrder_h(this->root, vals);
    return vals;
}

vector<int> BST::inOrder() {
    vector<int> vals;
    this->inOrder_h(this->root, vals);
    return vals;
}

vector<int> BST::postOrder() {
    vector<int> vals;
    this->postOrder_h(this->root, vals);
    return vals;
}

// Helper functions
BSTNode* BST::insert_h(int key, BSTNode *curr) {
    if (curr == nullptr) {
        return new BSTNode(key);
    }
    if (key < curr->key) {
        curr->left = insert_h(key, curr->left);
    }else if (key > curr->key) {
        curr->right = insert_h(key, curr->right);
    }
    return curr;
}

BSTNode* BST::find_h(int key, BSTNode *curr) {
    if (curr == nullptr) {
        return curr;
    }
    if (key < curr->key) {
        curr->left = remove_h(key, curr->left);
    }else if (key > this->root->key) {
        curr->right = remove_h(key, curr->right);
    }else{
        return curr;
    }
}

BSTNode* BST::remove_h(int key, BSTNode *curr) {
    if (curr == nullptr) {
        return curr;
    }
    if (key < curr->key) {
        curr->left = remove_h(key, curr->left);
    }else if (key > curr->key) {
        curr->right = remove_h(key, curr->right);
    }else{
        if(curr->right == nullptr && curr->left == nullptr)
        {
            delete curr;
            curr = nullptr;
        }
        else if(curr->right == nullptr)
        {
            BSTNode * temp = curr;
            curr= curr->left;
            delete temp;
        }
        else if(curr->left == nullptr)
        {
            BSTNode * temp = curr;
            curr= curr->right;
            delete temp;
        }
            //two child
        else
        {
            BSTNode* temp = getMax(curr->left);
            curr->key = temp->key;
            curr->left = remove_h(temp->key, curr->left);
        }
    }
    return curr;
}

/**
 * getMax finds the node containing the maximal key in the tree
 * @param curr the root of the tree in which we are searching
 * @return a pointer to the BSTNode containing the maximal key
 * @throws runtime_error if current is an empty tree
 */
BSTNode* BST::getMax(BSTNode *curr) {
    if(this->root== nullptr)
        return nullptr;
    while(this->root->right != nullptr)
    {
        this->root = this->root->right;
    }
    return this->root;
}

void BST::preOrder_h(BSTNode *curr, vector<int> &v) {
    if (curr != nullptr) {
        v.push_back(curr->key);
        this->preOrder_h(curr->left, v);
        this->preOrder_h(curr->right, v);
    }
}

void BST::inOrder_h(BSTNode *curr, vector<int> &v) {
    if (curr != nullptr) {
        this->inOrder_h(curr->left, v);
        v.push_back(curr->key);
        this->inOrder_h(curr->right, v);
    }
}

void BST::postOrder_h(BSTNode *curr, vector<int> &v) {
    if (curr != nullptr) {
        this->postOrder_h(curr->left, v);
        this->postOrder_h(curr->right, v);
        v.push_back(curr->key);
    }
}

void BST::destructTree(BSTNode *curr) {
    if (curr != nullptr) {
        destructTree(curr->left);
        destructTree(curr->right);
        delete curr;
    }
}

int BST::getHeight_h(BSTNode *current) {
    if(current == nullptr){
        return -1;
    }else{
        int  n1, n2;
        n1 = getHeight_h(current->left);
        n2 = getHeight_h(current->right);
        return  max(n1,n2)+1;
    }
}

int BST::getHeight() {
    int height = getHeight_h(this->root);
    return height;
}

int BST::getMax() {
    this->root = getMax(this->root);
    return this->root->key;
}

stack<int> BST::inOrderNonRecursive() {
    stack<BSTNode *> s;
    BSTNode *curr = root;

    while (curr != nullptr || !s.empty())
    {
        while (curr !=  nullptr)
        {
            s.push(curr);
            curr = curr->left;
        }

        curr = s.top();
        s.pop();
        cout << curr->key << " ";
        curr = curr->right;
    }

}

stack<int> BST::postOrderNonRecursive() {
    if (this->root == nullptr)
        throw runtime_error("BST::postOrderNonRecursive, tree is empty");

    stack<BSTNode *> s1, s2;

    s1.push(this->root);
    BSTNode* node;

    while (!s1.empty()) {
        node = s1.top();
        s1.pop();
        s2.push(node);

        if (node->left)
            s1.push(node->left);
        if (node->right)
            s1.push(node->right);
    }

    while (!s2.empty()) {
        node = s2.top();
        s2.pop();
        cout << node->key << " ";
    }
}

vector<int> BST::levelOrder() {
    vector<int> vals;
    this->levelOrder_h(this->root, vals);
    return vals;
}

bool BST::isBalanced(BSTNode*curr) {
    int LH;
    int RH;

    if (curr == nullptr){
        throw runtime_error("BST::isBalanced, tree is empty");
    }
    LH = getHeight_h(curr->left);
    RH = getHeight_h(curr->right);

    return abs(LH - RH) <= 1;

}

void BST::levelOrder_h(BSTNode *current, vector<int> &v) {
    // Base Case
    if (root == nullptr)  return;

    // Create an empty queue for level order traversal
    queue<BSTNode *> q;

    // Enqueue Root and initialize height
    q.push(root);

    while (!q.empty())
    {
        // Print front of queue and remove it from queue
        BSTNode *node = q.front();
        v.push_back(node->key);
        q.pop();

        /* Enqueue left child */
        if (node->left != nullptr)
            q.push(node->left);

        /*Enqueue right child */
        if (node->right != nullptr)
            q.push(node->right);
    }
}

bool BST::dataBalance(){
    bool balance = isBalanced(this->root);
    return balance;
}
