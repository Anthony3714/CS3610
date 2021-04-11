/*
Name: Anthony Giordano
Date: 3/13/21
file: avl_tree.h
Brief: This is the header file for avl tree
Credit: Some of the functions in this project were provided by Jundong Liu or from the book 
        Data Structures Using C++ by D.S. Malik. Additional functions were added by me
*/
#ifndef AVL_TREE_H
#define AVL_TREE_H
#include <iostream>

struct AVLNode {
  AVLNode(const int value) : value(value), left(NULL), right(NULL), bf(0) {}
  ~AVLNode() {
    delete left;
    delete right;
    left = right = NULL;
  }
  int value;
  AVLNode *left;
  AVLNode *right;
  int bf;
};

class AVLTree {
public:
  AVLTree() : root(NULL) {}
  ~AVLTree() { 
    delete root;
  }
  int nrleafCount(AVLNode* &root);
  void insert(const int newValue);
  void remove(int badValue);
  void inorderTraversal(AVLNode* &node);
  void print(char letter);
  int nodeHeight(AVLNode* &root);
  void allHeight(AVLNode* &root);
  AVLNode* getPred(AVLNode* node);
  void removeCases(AVLNode* &root, int badValue, bool& isShorter);
  int leafCount(AVLNode* root, int count);
private:
  void insertIntoAVL(AVLNode* &root, AVLNode *newNode, bool& isTaller);
  
  void rotateToLeft(AVLNode* &root);
  void rotateToRight(AVLNode* &root);
  
  void balanceFromLeft(AVLNode* &root);
  void balanceFromRight(AVLNode* &root);
  
  void remove(AVLNode* &root, int badValue, bool& isShorter);
  
  AVLNode* root;
};

#endif

