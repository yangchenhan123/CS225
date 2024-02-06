/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  clear();
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  ListNode* del = head_;
  ListNode* next;
  for (int i = 0; i < length_; i++){
    next = del->next;
    delete del;
    del = next;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
  /// @todo Graded in MP3.1
  ListNode* insert = new ListNode(ndata);
  insert->prev = nullptr;
  insert->next = head_; 

  if (length_ == 0){
    head_ = insert;
    tail_ = insert;
  }else{
    head_->prev = insert;
    head_ = insert;
  }

  length_ += 1;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
  /// @todo Graded in MP3.1
  ListNode* insert = new ListNode(ndata);
  insert->next = nullptr;
  insert->prev = tail_;

  if (length_ == 0){
    tail_ = insert;
    head_ = insert;
  }else{
    tail_->next = insert;
    tail_ = insert;
  }
  
  length_ += 1;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
    /// @todo Graded in MP3.1
  ListNode* curr = endPoint;
  ListNode* last = curr->prev;
  ListNode* next_end = curr->next;

  curr->prev = startPoint->prev;
  curr->next = last;
  curr = last;

  while(last != startPoint){
    last = curr->prev;
    curr->prev = curr->next;
    curr->next = last;
    curr = last;
  }

  curr->prev = curr->next;
  curr->next = next_end;

  if(head_ == startPoint){
    head_ = endPoint;
  }else{
    endPoint->prev->next = endPoint;
  }

  if(tail_ == endPoint){
    tail_ = startPoint;
  }else{
    next_end->prev = startPoint;
  }


}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  ListNode* curr_head = head_;
  ListNode* curr_tail = head_;
  int curr_len = length_;

  //loop until current lenghth is negtive
  while (curr_len > 0){
    //loop to find next tail
    for(int i = 0; i < (n-1); i++){
      if (curr_tail->next != nullptr){
        curr_tail = curr_tail->next;
      }
    }

    //reverse paritally
    reverse(curr_head, curr_tail);

    curr_head = curr_head->next;
    curr_tail = curr_head;

    curr_len -= n;
  }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
  /// @todo Graded in MP3.1
  ListNode* skip = head_;
  ListNode* remove = skip->next;

  while (remove->next != nullptr){
    //connect current skip with next skip
    skip->next = remove->next;
    remove->next->prev = skip;

    //update skip
    skip = skip->next;

    //connect current remove with tail
    remove->prev = tail_;
    remove->next = nullptr;
    tail_->next = remove;
    tail_ = remove;
    
    //update remove
    remove = skip->next;
  }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
    /// @todo Graded in MP3.2
    ListNode* split = start;
    
    for (int i = 0; i < splitPoint; i++){
      split = split->next;
    }

    split->prev->next = nullptr;
    split->prev = nullptr;

    return split;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode* temp1 = first;
  ListNode* temp2 = second;
  ListNode* temp3;
  ListNode* new_head;

  //get the new_head
  if (first->data < second->data){
    new_head = temp3 = first;
    temp1 = first->next;
    temp3->next = nullptr;
    if(temp1 != nullptr){
      temp1->prev = nullptr;
    }

  }else{
    new_head = temp3 = second;
    temp2 = second->next;
    temp3->next = nullptr;
    if(temp2 != nullptr){
      temp2->prev = nullptr;
    }
  }

  while ((temp1 != nullptr) && (temp2 != nullptr)){
    if (temp2->data < temp1->data){
      temp3->next = temp2;
      temp2->prev = temp3;    //connect temp3 with temp2
      temp3 = temp2;          //update temp3
      temp2 = temp2->next;    //update temp2
      //set nullptr
      temp3->next = nullptr;  
      if(temp2 != nullptr){
        temp2->prev = nullptr;
      }
    }else{
      temp3->next = temp1;
      temp1->prev = temp3;    //connect temp3 with temp1
      temp3 = temp1;          //update temp3
      temp1 = temp1->next;    //update temp1
      //set nullptr
      temp3->next = nullptr;  
      if(temp1 != nullptr){
        temp1->prev = nullptr;
      }
    }
  }
    

  if (temp1 == nullptr && temp2 != nullptr){
    temp3->next = temp2;
    temp2->prev = temp3;
  }else if(temp1 != nullptr && temp2 == nullptr){
    temp3->next = temp1;
    temp1->prev = temp3;
  }

  return new_head;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    /// @todo Graded in MP3.2
    if (chainLength == 1){
      return start;
    }

    ListNode* temp_head = split(start, chainLength / 2);
    start = mergesort(start, chainLength / 2);
    temp_head = mergesort(temp_head, chainLength - chainLength / 2);
    return merge(start, temp_head);
}
