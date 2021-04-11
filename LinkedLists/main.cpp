/**
 * @file main.cpp
 *
 * @brief Main file for template linked list
 *
 *
 * @author Anthony Giordano
 * Email: ag168918@ohio.edu
 *
 */
#include <iostream>
#include <string>
#include "linked_list.h"
using namespace std;


//Creates options for input and runs linked list functions
int main(int argc, char** argv) {
  //New Variables
  LinkedList<int> list;
  string input;

  cout << "Linked List Commands \na i=push_front\nd=pop_front\nr=reverse\np=print\nq=quit\n"<<endl;
  getline(cin, input);

  //runs until input is q
  while(!(input[0] == 'q')){
    if(input[0] == 'a'){
      //filters out letters in string to extract the number 
      string Numbers;
      for(size_t i =0; i < input.size(); i++ ){
        if(isdigit(input[i])){
          Numbers += input[i];
        }
      }
      //checks to make sure user put a number as an input
      if(Numbers.size() >= 1){
        int intInput = atoi(Numbers.c_str());
        list.push_front(intInput);
      }else{
        cout << "No number input Detected" << endl;
      }
    }
    //pops first item in linked list
    else if(input[0] == 'd'){
      list.pop_front();
    }
    //reverses list
    else if(input[0] == 'r'){
      list.reverse();
    }
    //prints list
    else if(input[0] == 'p'){
      cout << "List: ";
      list.print();
    }
    else{
      cout << "Unrecongnized Input" <<endl;
    }
  getline(cin, input);
  }
}
