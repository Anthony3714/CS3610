/*
 * @file linked_list.h
 *
 * @brief header file for template linked list
 *
 *
 * @author Anthony Giordano
 * Email: ag168918@ohio.edu
 *
 */
template <typename T>
class LinkedList {

//Linked List and List Node class and struct defintion
public:
  LinkedList() : head(NULL) {}
  ~LinkedList();

  void push_front(const T data);
  void pop_front();
  void reverse();
  void print() const;

private:
  struct ListNode {
    ListNode(const T data) : data(data), next(NULL) {}

    T data;
    ListNode* next;
  };
  ListNode* head;
};


//destructor for unused linked lists
template <typename T>
LinkedList<T>::~LinkedList(){
  ListNode* rmptr;
  while(head != NULL){
    rmptr=head;
    head = head->next;
    delete rmptr;
  }
}

//pushes a variable to the front of the list
template <typename T>
void LinkedList<T>::push_front(const T data){
  if(head == NULL){
    head = new ListNode(data);
  }
  else{
    ListNode* tmp = new ListNode(data);
    tmp -> next = head;
    head = tmp;
  }

}


//removes the first item in the list, also checks for empty sets
template <typename T>
void LinkedList<T>::pop_front(){
  if(head == NULL){
    std::cout << "Empty" <<std::endl;
    return;
  }
  ListNode* tmp = NULL;
  tmp = head;
  head = head->next;
  delete  tmp;
}


//reverses list by having 3 variables recording positions to be able to set the node in reverse without losing any data
template <typename T>
void LinkedList<T>::reverse(){
  if(head==NULL){
    std::cout << "Empty" <<std::endl;
    return;
  }
  if(head->next==NULL){
    return;
  }
  ListNode* cursor = head;
  ListNode* prevCursor = NULL;
  ListNode* nextCursor =NULL;
    while (cursor != NULL) {
      //sends next forward then sets the current variable to the previous one, then moves all values down the list
      nextCursor = cursor->next;
      cursor->next = prevCursor;
      prevCursor = cursor;
      cursor= nextCursor;
    }
    //sets head to previous since it is at the end of the list
    head = prevCursor;
}

//prints list by going through the list until NULL
template <typename T>
void LinkedList<T>::print() const{
  if(head == NULL){
    std::cout << "Empty" <<std::endl;
    return;
  }
  ListNode* cursor = head;
  while (cursor != NULL){
    std::cout<<cursor->data <<" ";
    cursor = cursor->next;
  }
    std::cout <<std::endl;
}
