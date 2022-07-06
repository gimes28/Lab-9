#ifndef BINARYTREE_h
#define BINARYTREE_h
#include <iostream>
#include "Exception.h"
#include "Words.h"
using namespace std;

template<class T>
class BinaryTree {
private:
    struct node {
        T* data = nullptr;
        node* left = nullptr;
        node* right = nullptr;
    };
    int size;
public:
    node* head = nullptr;
    BinaryTree();
    ~BinaryTree();
    void Insert(T* val);
    void RotateLL(node* gp, node* parent, node* pivot);
    void RotateRL(node* gp, node* parent, node* pivot);
    void RotateLR(node* gp, node* parent, node* pivot);
    void RotateRR(node* gp, node* parent, node* pivot);
    int NodeHeight(node* curr, node* parent);
    T* Find(T* val, node* curr);
    int Size();
    void GetAllAscending(node* curr); //returns a pointer to the first array element
    void GetAllDescending(node* curr); //same as above
    void EmptyTree(node* curr);
    T* Remove(T* val);
};
template<class T>
BinaryTree<T>::BinaryTree() {
    head = nullptr;
    size = 0;
}

template<class T>
BinaryTree<T>::~BinaryTree() {
    if (head == nullptr) {
        EmptyTree(head);
    }
    else {
        return;
    }
}

template<class T>
void BinaryTree<T>::Insert(T* val) {
    node* curr = head;
    node* prevCurr = nullptr;
    if (head == nullptr) {
        node* n = new node;
        n->data = val;
        head = n;
    }
    else {
        while ((curr->left != nullptr && *curr->data > *val) || (curr->right != nullptr && *curr->data < *val)) {
            if (*curr->data < *val) {
                curr = curr->right;
            }
            else {
                curr = curr->left;
            }
        }
        if (*curr->data == *val) {
            throw Exception("Data is already in tree");
        }
        else if (*curr->data < *val) {
            node* n = new node;
            n->data = val;
            curr->right = n;
        }
        else {
            node* n = new node;
            n->data = val;
            curr->left = n;
        }
        NodeHeight(head, prevCurr);
    }
    size++;
}

template <class T>
int BinaryTree<T>::NodeHeight(node* curr, node* parent) {
    if (curr == nullptr) {
        return 0;
    }
    int right, left;
    right = NodeHeight(curr->right, curr) + 1;
    left = NodeHeight(curr->left, curr) + 1;
    if (right - left > 1) {  // checks for LL or RL
        int currRight = NodeHeight(curr->right->right, curr->right);
        int currLeft = NodeHeight(curr->right->left, curr->right);
        if (currRight > currLeft) {
            RotateLL(parent, curr, curr->right);
        }
        else {
            RotateRL(parent, curr, curr->right->left);
        }
    }
    else if (left - right > 1) { //execute RR or LR
        int currRight = NodeHeight(curr->left->left, curr->left);
        int currLeft = NodeHeight(curr->left->right, curr->left);
        if (currRight > currLeft) {
            RotateRR(parent, curr, curr->left);
        }
        else {
            RotateLR(parent, curr, curr->left->right);
        }
    }
    if (right >= left) {
        return right;
    }
    else if (left > right) {
        return left;
    }
}

template<class T>
void BinaryTree<T>::RotateLL(node* gp, node* parent, node* pivot) {
    parent->right = pivot->left;
    pivot->left = parent;
    if (gp == nullptr) {
        head = pivot;
    }
    else if (*gp->data < *pivot->data) {
        gp->right = pivot;
    }
    else {
        gp->left = pivot;
    }
}

template<class T>
void BinaryTree<T>::RotateRL(node* gp, node* parent, node* pivot) {
    node* temp = parent->right;
    parent->right = pivot->left;
    temp->left = pivot->right;
    pivot->left = parent;
    pivot->right = temp;
    if (gp == nullptr) {
        head = pivot;
    }
    else if (*gp->data < *parent->data) {
        gp->right = pivot;
    }
    else {
        gp->left = pivot;
    }
}

template<class T>
void BinaryTree<T>::RotateLR(node* gp, node* parent, node* pivot) {
    node* temp = parent->left;
    parent->left = pivot->right;
    temp->right = pivot->left;
    pivot->right = parent;
    pivot->left = temp;
    if (gp == nullptr) {
        head = pivot;
    }
    else if (*gp->data < *parent->data) {
        gp->right = pivot;
    }
    else {
        gp->left = pivot;
    }
}

template<class T>
void BinaryTree<T>::RotateRR(node* gp, node* parent, node* pivot) {
    parent->left = pivot->right;
    pivot->right = parent;
    if (gp == nullptr) {
        head = pivot;
    }
    else if (*gp->data < *pivot->data) {
        gp->right = pivot;
    }
    else {
        gp->left = pivot;
    }
}

template<class T>
T* BinaryTree<T>::Find(T* val, node* curr) {
    if (curr == nullptr) {
        return nullptr;
    }
    if (size == 0) {
        throw(Exception("Tree is empty"));
    }
    if (*curr->data == *val) {
        return curr->data;
    }
    if (*val < *curr->data) {
        return Find(val, curr->left);
    }
    return Find(val, curr->right);
}


template<class T>
int BinaryTree<T>::Size() {
    return size;
}

template<class T>
void BinaryTree<T>::GetAllAscending(node* curr) {
    if (size == 0) {
        throw(Exception("Tree is empty"));
    }
    if (curr == nullptr) {
        return;
    }
    GetAllAscending(curr->left);
    //ascendArray[index] = *curr->data;
    //index++;
    curr->data->DisplayWord();
    GetAllAscending(curr->right);
    /*for (int i = 0; i < size; ++i) {
        cout << ascendArray[i] << endl;
    }*/
}

template<class T>
void BinaryTree<T>::GetAllDescending(node* curr) {
    if (size == 0) {
        throw(Exception("Tree is empty"));
    }
    if (curr == nullptr) {
        return;
    }
    GetAllDescending(curr->right);
    curr->data->DisplayWord();
    GetAllDescending(curr->left);
}

template<class T>
void BinaryTree<T>::EmptyTree(node* curr) {
    if (size == 0) {
        throw(Exception("Tree is empty"));
    }
    if (curr == nullptr) {
        return;
    }
    EmptyTree(curr->left);
    EmptyTree(curr->right);
    delete curr;
    size--;
}


template<class T>
T* BinaryTree<T>::Remove(T* val) {
    node* curr = head;
    node* prev = nullptr;
    T* retVal = nullptr;
    if (size == 0) {
        throw(Exception("Tree is empty"));
    }
    while (curr != nullptr && curr->data != val) { // finds the node we want to remove
        prev = curr;
        if (*val < *curr->data) {
            curr = curr->left;
        }
        else {
            curr = curr->right;
        }
    }
    if (curr == nullptr) {
        throw(Exception("Item is not in tree"));
    }

    if (curr->left == nullptr && curr->right == nullptr) { //if node has 0 children
        if (prev->left == curr) {
            prev->left = nullptr;
        }
        else {
            prev->right = nullptr;
        }
        retVal = curr->data;
    }
    else if ((curr->left == nullptr && curr->right != nullptr) || (curr->left != nullptr && curr->right == nullptr)) { // if node has 1 child
        retVal = curr->data;
        if (prev->left == curr) {
            if (curr->left != nullptr) {
                prev->left = curr->left;
            }
            else {
                prev->left = curr->right;
            }
        }
        else {
            if (curr->left != nullptr) {
                prev->right = curr->left;
            }
            else {
                prev->right = curr->right;
            }
        }
    }
    else if (curr->left != nullptr && curr->right != nullptr) { // if node has 2 children
        node* replace = curr->left;
        while (replace->right != nullptr) {
            replace = replace->right;
        }
        retVal = curr->data;
        curr->data = Remove(replace->data);
        return retVal;
    }
    size--;
    node* prevCurr = nullptr;
    NodeHeight(head, prevCurr);
    cout << *retVal << " was deleted" << endl;
    delete curr;
    return retVal;
}

#endif