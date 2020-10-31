/* Name: Ian Tracy
*About this project: The program is an implementation of a binary search tree data structure
*Comments: The program find function return a directory as expected, but it might not be the most useful,
 * as it returns the memory address.
*/

#include <iostream>
#include "BST.h"
using namespace std;

void print(vector<int> v) {
    cout << "vec: ";
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << ", ";
    }
    cout << endl;
}

void print(stack<int> s){
    cout << "stack: ";
    for (int i = 0; i < s.size(); i++) {
        cout << s.top();
        s.pop();
    }
    cout << endl;
}

int main() {
    BST tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(2);

    tree.insert(12);
    tree.insert(11);
    tree.insert(14);


    vector<int> v1 = tree.preOrder();
    print(v1);
    vector<int> v2 = tree.inOrder();
    print(v2);
    vector<int> v3 = tree.postOrder();
    print(v3);
    cout << "inOrderNonRecursive: ";
    tree.inOrderNonRecursive();
    cout << endl;
    cout << "postOrderNonRecursive: ";
    tree.postOrderNonRecursive();
    cout << endl;
    cout << "levelOrder ";
    vector<int> v4 = tree.levelOrder();
    print(v4);

    cout << "getHeight: " <<tree.getHeight()<< endl;
    cout << "getMax: " << tree.getMax() << endl;
    cout << "find(2): " << tree.find(2) << endl;
    cout << "isBalanced: " << tree.dataBalance() << endl;

    tree.remove(15);
    cout << "getMax: " << tree.getMax() << endl;


    return 0;
}