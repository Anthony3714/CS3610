/*
Name: Anthony Giordano
Date: 3/13/21
file: avl_tree.cpp
Brief: This file sets up a self balancing avltree and implements functions from avl_tree.h
Credit: Some of the functions in this project were provided by Jundong Liu or from the book 
        Data Structures Using C++ by D.S. Malik. Additional modification of the functions were coded
        by me.
*/
#include <iostream>
#include <vector>
#include "avl_tree.h"
using namespace std;


void AVLTree::insert(const int newValue) {
  bool isTaller = false;
  AVLNode *newNode;
  newNode = new AVLNode(newValue);
  insertIntoAVL(root,newNode,isTaller);
  cout << nrleafCount(root) << endl;
}

void AVLTree::insertIntoAVL(AVLNode* &root, AVLNode *newNode, bool& isTaller){
  if (root == NULL){
    root = newNode;
    isTaller = true;
  }
  else if (root->value == newNode->value){
    cout << "Duplicate" << endl;
  }
  else if (root->value > newNode->value){

    insertIntoAVL(root->left, newNode,isTaller);

    if (isTaller){
      switch (root->bf)
      {
      case -1:
        balanceFromLeft(root);
        isTaller = false;
        break;

      case 0:
        root->bf = -1;
        isTaller = true;
        break;

      case 1:
        root->bf = 0;
        isTaller = false;
      }
    }
  }
  else{
    insertIntoAVL(root->right, newNode, isTaller);
    if(isTaller){
      switch(root->bf)
      {
      case -1:
        root->bf = 0;
        isTaller = false;
        break;
        
      case 0:
        root->bf = 1;
        isTaller = true;
        break;
        
      case 1:
        balanceFromRight(root);
        isTaller = false;
      }
    }
  }
}

void AVLTree::rotateToLeft(AVLNode* &root){
  AVLNode *p;
  
  if (root == NULL)
    cout << "Error in the tree" << endl;
  else if (root->right == NULL)
    cout << "Error in the tree: No right subtree to rotate." << endl;
  else{
    p = root->right;
    root->right = p->left;
    p->left = root;
    root = p; 
  }
}

void AVLTree::rotateToRight(AVLNode* &root){
  AVLNode *p;

  if (root == NULL)
    cout << "Error in the tree" << endl;
  else if (root->left == NULL)
    cout << "Error in the tree: No left subtree to rotate." << endl;
  else{
    p = root->left;
    root->left = p->right; 
    p->right = root;
    root = p; 
  }
}

void AVLTree::balanceFromLeft(AVLNode* &root){

  AVLNode *p;
  AVLNode *w;

  p = root->left;

  switch (p->bf)
    {
    case -1:
      root->bf = 0;
      p->bf = 0;
      rotateToRight(root);
      break;

    case 0:  
    //root will be left high since the left side wont be any shorter since it has 2 children
    //root->left will be right high since the left child will be moved up
			root->bf= 1;
			p->bf= -1;
			rotateToRight(root);
			break;

    case 1:
      w = p->right;

      switch (w->bf)
      {
      case -1:
        root->bf = 1;
        p->bf = 0;
        break;
      case 0:
        root->bf = 0;
        p->bf = 0;
        break;
      case 1:
        root->bf = 0;
        p->bf = -1;
      }
      
      w->bf = 0;
      rotateToLeft(p);
      root->left = p;
      rotateToRight(root);
    }
}


void AVLTree::balanceFromRight(AVLNode* &root){
  AVLNode *p;
  AVLNode *w;
  p = root->right;
  switch (p->bf)
    {
    case -1:
      w = p->left;
      switch (w->bf)
      {
      case -1:
        root->bf = 0;
        p->bf = 1;
        break;
      case 0:
        root->bf = 0;
        p->bf = 0;
        break;
      case 1:
        root->bf = -1;
        p->bf = 0;
      }
      
      w->bf = 0;
      rotateToRight(p);
      root->right = p;
      rotateToLeft(root);
      break;
    //opposite of balancefromleft since they are opposite functions
    case 0: 
			root->bf= -1;
			p->bf = 1;
			rotateToLeft(root);
			break;

    case 1:
      root->bf = 0;
      p->bf = 0;
      rotateToLeft(root);
    }
}

void AVLTree::print(char letter){
  if(letter == 'p'){
    cout << "The nodes inorder: " <<endl;
    inorderTraversal(root);
    cout << endl;
  }
  else
  {
    cout << "The height of each node in order is: " << endl;
    allHeight(root);
    cout << endl;
  }
  return; 
}

//Modified From textbook
void AVLTree::inorderTraversal(AVLNode* &root){
  if(root != NULL){
    inorderTraversal(root -> left);
    cout << root->value << " ";
    inorderTraversal(root->right);
  }
}

//uses inordertraversal
void AVLTree::allHeight(AVLNode* &root){
  if (root == NULL)
  return;
  allHeight(root->left);
  cout << nodeHeight(root) << " ";
  allHeight(root->right);

  return;
}
//modified code from book and powerpoint
int AVLTree::nodeHeight(AVLNode* &root){
  if (root == NULL){
    return 0;
  }
  else{
    return 1+(max(nodeHeight(root->left), nodeHeight(root->right)));
  }
}


//from book
AVLNode* AVLTree::getPred(AVLNode* node){
  if(node == NULL){return NULL;}
  node = node->left;
  while(node -> right != NULL){node = node -> right;}
  return(node);
}


void AVLTree::remove(int badValue){
  bool isShorter= false;
  remove(root, badValue,isShorter);
}

// This functions finds the node location and does cases 5 and 6
void AVLTree::remove(AVLNode* &root, int badValue, bool& isShorter)
{
	if (root == NULL){
		cout << "The badValue is not in the tree" << endl;
    return;
	}
  //case 5 this uses code for insert function
	else if( root->value < badValue)
  {
    remove(root->right, badValue, isShorter);  
    if (isShorter)
    {
      switch (root->bf)
      {
        // complete opposite of insert into avl since we are deleting
        // case -1 goes to case 1, balance from left goes to balance from right
        // true is set to false, etc....
				case -1:
        //if the left node of a right high function is 0 then it means the tree will not be shorter, else it means that the function will be rebalanced and it causes it to be shorter
					if (root->left->bf != 0){isShorter = true;}
					balanceFromLeft(root);
					break;
				case 0:
        //updates balance factor
					root->bf= -1;
					isShorter = false;
					break;
				case 1:
          //updates balance factor
					root->bf= 0;
					isShorter = true;
					break;
      }
    }	
	}
  //case 6
	else if (root->value > badValue)
	{
    remove(root->left, badValue,isShorter);
    if (isShorter)
    {
      switch (root->bf)
      {
        // complete opposite of insert into avl since we are deleting
        // case -1 goes to case 1, balance from left goes to balance from right
        // true is set to false, etc....
        case -1:
        //updates balance factor
          root->bf = 0;
          isShorter = true;
          break;
        case 0:
          //updates balance factor
          root->bf = 1;
          isShorter = false;
          break;
        case 1:
        //if the right node of a left high function is 0 then it means the tree will not be shorter, else it means that the function will be rebalanced and it causes it to be shorter
					if (root->right->bf != 0){isShorter = true;}
					balanceFromRight(root);
          break;
      }
    }	
  }
  else{removeCases(root, badValue, isShorter);}
}

//modified code from the book
//deleting temp results in an error, removed temp variable from book
void AVLTree::removeCases(AVLNode* &root, int badValue, bool& isShorter){
  //case 1 - checks to see if there is no child nodes
  if (root->left == NULL && root->right == NULL)
  {
    root = NULL;
    isShorter = true;
    return;
  }
  //case 2 right child
  else if (root->right == NULL)
  {
    root = root->left;
    isShorter = true;
    return;
  }
  //case 3 left child
  else if (root->left == NULL)
  {
    root = root->right;
    isShorter = true;
    return;
  }
  // Case 4
  else
  {
    //dont update left and right since it will cause part of the tree to be spliced out
    root->value = getPred(root) ->value;
    remove(root->left, root->value, isShorter);
    // updates balance factor
    root -> bf = nodeHeight(root->right) - nodeHeight(root->left);;
    // balances tree depending on balance factor
		if (root->bf > 1){balanceFromRight(root);}
    else if(root->bf <-1){balanceFromLeft(root);}	
  }
  return;
}

int AVLTree::leafCount(AVLNode* root, int count){
    if(root == NULL){return 0;}
    if(root->left == NULL && root->right == NULL){count++;}
    else{return leafCount(root->left, count) + leafCount(root->right, count);}
    return count;
}


int AVLTree::nrleafCount(AVLNode* &root){
  if (root == NULL){return 0;}  
  vector<AVLNode*> total; // adjust size depending on size of binary tree
  total.push_back(root);
  int count = 0;
  while(!total.empty()){
    AVLNode* temp = total.front();
    total.erase(total.begin());
    if(temp -> left != NULL){total.push_back(temp->left);}
    if(temp -> right != NULL){total.push_back(temp->right);}
    if(temp -> left == NULL && temp->right ==NULL){count++;}    
  }
  return count;
}
