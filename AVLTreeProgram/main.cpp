/*
Name: Anthony Giordano
Date: 3/13/21
file: avl_tree.h
Brief: This is the main file for the avl tree. Sets up the menu
Credit: This file was created by Jundong Liu
*/
#include <iostream>
#include "avl_tree.h"
using namespace std;

int main(int argc, char** argv) {
  AVLTree tree;

  char option;
  int key;

  do {
    cin >> option;
    switch(option) {
      case 'i':
        cin >> key;
        tree.insert(key);
        break;
      case 'r':
        cin >> key;
        tree.remove(key);
        break;
      case 'h':
         tree.print('h');
        break;
      case 'p':
         tree.print('p');
        break;
      default:
        break;
    }
  } while(option != 'q');
}
