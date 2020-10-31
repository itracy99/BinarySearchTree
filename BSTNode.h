//
// Created by Ian on 12/6/2019.
//

#ifndef PROGRAM_8_BSTNODE_H
#define PROGRAM_8_BSTNODE_H

class BSTNode {
public:
    int key; 	    // can be called value or data too
    BSTNode *left;  // left child of the current TreeNode
    BSTNode *right; // right child of the current TreeNode

    BSTNode (int val, BSTNode *left=nullptr, BSTNode *right=nullptr){
        this->key = val;
        this->left = left;
        this->right = right;
    }
};


#endif //PROGRAM_8_BSTNODE_H
