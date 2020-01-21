/*
 * @file doublylinkedlist.h
 *
 * @brief
 *    Template for doubly linked list class.
 *
 * @author Judy Challinger & Javier Pardo
 * @date 1/1/16
 */

#ifndef CSCI_311_DOUBLYLINKEDLIST_H
#define CSCI_311_DOUBLYLINKEDLIST_H

template <class T>
class DoublyLinkedList {

 public:
   DoublyLinkedList();
   ~DoublyLinkedList();
   void append(T* data);
   bool empty() const { return (head == nullptr); }
   T* remove();
   T* first();
   T* next();

 private:
   class Node {
    public:
      Node();
      Node(T* data);
      Node* next;
      Node* prev;
      T* data;
   };
   Node* head;
   Node* tail;
   Node* current;
};

/**
 * @brief   Node default constructor.
 */

template <class T>
DoublyLinkedList<T>::Node::Node() {

   next = nullptr;
   prev = nullptr;
   data = nullptr;

}

/**
 * @brief Node constructor.
 */

template <class T>
DoublyLinkedList<T>::Node::Node(T* data) {

  next = nullptr;
  prev = nullptr;
  this->data = data;

}

/**
 * @brief   DoublyLinkedList constructor.
 */

template <class T>
DoublyLinkedList<T>::DoublyLinkedList() {

  head = nullptr;
  tail = nullptr;
  current = nullptr;

}

/**
 * @brief   DoublyLinkedList destructor.
 */

template <class T>
DoublyLinkedList<T>::~DoublyLinkedList() {

  Node* Nodeptr = head;
  while(Nodeptr != nullptr) //iterating through the list while deleting each node
  {
    Node* temp;
    temp = Nodeptr;
    Nodeptr = Nodeptr->next;
    delete temp;
  }

}

/**
 * @brief   Appends a new Node at the end of the DoublyLinkedList.
 * @param   data A pointer to the data to be stored in the new Node.
 * @return  Nothing.
 *
 * Creates a new Node to hold the data and appends the Node at the end
 * of the list. The current Node pointer is set to point to the newly
 * appended Node.
 */

template <class T>
void DoublyLinkedList<T>::append(T* data) {

  if(head == nullptr) //if the list is empty
  {
    head = new Node(data);
    tail = head;
    head->prev = nullptr;
    head->next = nullptr;
    current = head;
    return;
  }
  else      
  {
    Node* Nodeptr = tail;
    tail = new Node(data);
    Nodeptr->next = tail;
    tail->prev = Nodeptr;
    tail->next = nullptr;
    current = tail;
    return;
  }
}

/**
 * @brief   Get the first thing on the list.
 * @return  A pointer to the data stored in the first Node on the list,
 *          or nullptr if the list is empty.
 *
 * The current pointer is set to point to the first Node in the list,
 * or nullptr if the list is empty.
 */

template <class T>
T* DoublyLinkedList<T>::first() {

  if(head == nullptr) 
  {
    current = nullptr;
    return nullptr;
  }
  current = head;    
  return current->data;
}

/**
 * @brief   Get the next thing on the list.
 * @return  A pointer to the data stored in the next Node on the list. The next
 *          Node is the one following whatever the current pointer is pointing
 *          to. If there is no next Node then nullptr is returned.
 *
 * The current pointer is set to point to the next Node in the list,
 * or nullptr if there is no next Node.
 */

template <class T>
T* DoublyLinkedList<T>::next() {

  if(head == nullptr) 
  {
    current = nullptr;
    return nullptr;  
  }
  if(current->next == nullptr) //if current is pointing to the last node
  {
    current = nullptr; 
    return nullptr;
  }
  current = current->next; 
  return current->data;

}

/**
 * @brief   Remove the Node pointed to by the current pointer.
 * @return  A pointer to the data stored in the next Node on the list. The next
 *          Node is the one following the Node that was removed. If there is
 *          no next Node then nullptr is returned.
 *
 * The current pointer is set to point to the next Node in the list, following
 * the Node that was removed, or nullptr if there is no next Node.
 */

template <class T>
T* DoublyLinkedList<T>::remove() { 

  if(head == nullptr) 
  {
    current = nullptr;
    return nullptr;
  }
  Node* temp = current;
  if(temp->prev == temp->next) //if there is only one node, temp->prev has to point to null just like temp->next
  {
    head = nullptr;
    tail = nullptr;
    current = nullptr;
    delete temp;
    return nullptr;
  }
  if(temp->prev == nullptr && temp->next != nullptr) //first node
  {
    head = current->next;
    head->prev = nullptr;
    current = current->next;
    delete temp;
    return current->data; 
  }
  if(temp->next == nullptr && temp->prev != nullptr) //last node
  {
    tail = current->prev;
    tail->next = nullptr;
    delete temp;
    return nullptr;
  }
  current = temp->next;
  current->prev = temp->prev;
  temp->prev->next = current;
  delete temp;
  return current->data; 
}

#endif // CSCI_311_DOUBLYLINKEDLIST_H
