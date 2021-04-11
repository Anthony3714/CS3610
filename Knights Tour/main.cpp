/*
Name: Anthony Giordano
File: main.cpp
Date: 04/09/21
Brief: Internal and external sorting algorithms
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;
struct multiList{
  int value; // Value
  int list; // The list it came from
  bool operator<(const multiList &a)const{return(value>a.value);} //Needed for sorting. The std::heap is a max heap, so return opposite than expected
};
void swap(vector<int>& list, int a, int b){ //swaps two array positions
  int c = list[a];
  list[a] = list[b];
  list[b] = c;

}
int partition(vector<int>& list, int first, int last) {
  // finds median of 3
  int median[3] = {list[first], list[(list.size())/2 - 1], list[last]};
  //only sorts 3 no matter array size so it will not cause slowdown
  sort(begin(median), end(median));
  //finds the index value of the pivot
  int pivotindex;
  if(median[1] == list[first]){pivotindex = first;}
  else if(median[1] == list[(list.size())/2 -1]){pivotindex = list.size()/2 - 1;}
  else{pivotindex = last;}

  //swaps pivot to the end of array
  swap(list, last, pivotindex);

  //using quicksort algorithm to sort the left and right subarrays and finds the index of where the pivot should be
  int split = first;
  for(int j = first; j < last; j++){
    if(list[j] < list[last]){
      swap(list, split, j);
      split++;
    }
  }

  //places pivot back in the split place.
  swap(list, split, last);
  return(split);
}


void quicksort(vector<int>& list, int first, int last) {
  if (first < last){ //checks to see if first < last. Sees if there is more to be sorted
    int split =  partition(list, first, last); // splits the list into two sublists
    quicksort(list, first, split-1); //lower list
    quicksort(list, split + 1, last); // higher list
  }
}
void add_to_heap(vector<vector<int>>& input_lists,vector<multiList>& multiway_heap,int row){ //This function adds to heap and erases old values
  multiList temp;                                       // Temp storage for push_back
  temp.value = input_lists[row][0];                     // stores highest value of a certain row
  temp.list = row;                                      // stores row value
  multiway_heap.push_back(temp);                        // pushes back temp into multiway heap
  input_lists[row].erase(input_lists[row].begin());     // Erases front value of array                              
  make_heap(multiway_heap.begin(), multiway_heap.end());// Makes min heap               
}
void multiway_merge(vector<vector<int> >& input_lists, vector<int>& output_list) {
  vector<multiList> multiway_heap;                // The heap of multilist values
  int removedList;                                // stores the removed list
  for (size_t i = 0; i < input_lists.size(); i++){add_to_heap(input_lists,multiway_heap,i);} // Creates initial heap, the smallest values in each row
  for(int count = 0;!multiway_heap.empty(); count++){
    output_list[count] = multiway_heap[0].value;          //stores smallest value in output
    removedList = multiway_heap[0].list;                  //Replace value with the next item in an array
    pop_heap(multiway_heap.begin(),multiway_heap.end());  // Sends the head of the heap to the end
    multiway_heap.pop_back();                             //pops back of array
    if(!input_lists[removedList].empty()){add_to_heap(input_lists,multiway_heap,removedList);} //checks to make sure removed list isn't empty. prevents seg faults
  }  
}

int main(int argc, char** argv) {
  int n, m;
  cin >> n >> m;

  vector<vector<int> > input_lists(n, vector<int>(m));

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      cin >> input_lists[i][j];
    }
  }

  // Quicksort k sublists
  for (unsigned long int i = 0; i < input_lists.size(); ++i)
    quicksort(input_lists[i], 0, m-1);

  // Merge n input sublists into one sorted list
  vector<int> output_list(n * m);
  multiway_merge(input_lists, output_list);
  for (unsigned long int i = 0; i < output_list.size(); ++i)
    cout << output_list[i] << " ";
  cout << endl;
}