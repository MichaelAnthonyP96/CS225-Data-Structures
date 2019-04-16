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
//what is the difference between clear() and destructor above
template <class T>
void List<T>::clear() {
  /// @todo Graded in MP3.1
  ListNode* temp = head_; //points to beginning of linked list
  while(temp != NULL){
    ListNode* previous = temp;//holds the past link while we move to the next
    temp = temp->next;//move onto next link
    delete previous; //deletes the old link
  }
  tail_ = NULL;//sets tail and head pointers to null
  head_ = NULL;
  length_ = 0;

}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode* node = new ListNode(ndata);
  if(head_ == NULL){
    //this is the only node in the list
    node->prev = NULL;
    node->next = NULL;
    //now the head and tail point to the new Node
    head_ = node;
    tail_ = head_;
  }
  else{
    node->next = head_; // new Node's next is the second Node
    head_->prev = node; //second Node's previous is the New Node
    head_ = node; //head points to the new Node at the front
  }
  length_++;
  node = NULL; // old node pointer is recycled since head now points to it
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  ListNode* node = new ListNode(ndata);
  if(tail_ == NULL){
    //this is the only node in the list
    node->prev = NULL;
    node->next = NULL;
    //now the head points to the new Node & tail points to only node as well
    head_ = node;
    tail_ = head_;
  }
  else{
    node->prev = tail_; // new Node's prev is the second to last Node
    tail_->next = node; //second to last Node's next is the New Node
    tail_ = node; //tail points to the new Node at the back
  }
  length_++;
  node = NULL; // old node pointer is recycled since tail now points to it
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  //if list is empty do nothing
  if((head_ == NULL) || (tail_ == NULL)) return;
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
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.1
  //if the list is empty, or has one node in it. then return
  if((startPoint == NULL) || (endPoint == NULL) || (startPoint == endPoint)) return;
  ListNode *originalFront = startPoint;
  ListNode *originalBack = endPoint;
  //must save the head and the tail pointers so that we can reassign them at the end
  ListNode *originalFrontPrev = startPoint->prev;
  ListNode *originalBackNext = endPoint->next;

  //iterates through the list and switches their next and prev pointers, moving from the end backwards
  while(startPoint != endPoint){
    //hold onto the next, it will be overwritten
    ListNode * temp1 = endPoint->next;
    //assign the next the previous, reversing direction of linked list
    endPoint->next = endPoint->prev;
    //assign the prev to the old next, reversing direction of linked list
    endPoint->prev = temp1;
    //Move to the old previous node, which is now held in the next pointer
    endPoint = endPoint->next;

  }
  //now need to switch the old head with the old tail
  ListNode * temp2 = endPoint->next;
  //temp holds pointer to second to last element in linked list
  endPoint->next = originalBackNext;
  //now the old front of the list points to the original back's next
  endPoint->prev = temp2;
  //links back to the second to last element
  startPoint = originalBack;
  //start point is now the back of the original list
  startPoint->prev = originalFrontPrev;
  //link the old tail to the new startpoint
  //Now need to reasign the head and the tail of the list
  //If the original front's prev was NULL, then just use the startpoint
  if(originalFrontPrev == NULL)
    head_ = startPoint;
  else
    originalFrontPrev->next = startPoint;
  //If the original back's next was NULL, then just use the endpoint
  if(originalBackNext == NULL)
    tail_ = endPoint;
  else
    originalBackNext->prev = endPoint;
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
  if(head_ == NULL) return; //empty list
  ListNode * startPoint = head_;
  ListNode * endPoint = startPoint;
  int originalN = n;
  while(endPoint->next != NULL && startPoint->next != NULL){
    endPoint = startPoint;
    while(n > 1){
      if(endPoint->next == NULL) break;
      else{
        --n;
        endPoint = endPoint->next;
      }
    }
    //reset the n back to the original for the next block of the list
    n = originalN;
    //reverse the current block n
    reverse(startPoint,endPoint);
    //move startPoint to the next block
    startPoint = endPoint->next;
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
  //if the list is empty do nothing
  if(head_== NULL || head_->next == NULL) return;
  //initialize the temporary pointers
  ListNode * curr = head_;
  ListNode * temp1 = curr->next;
  while(curr->next->next != NULL && temp1->next != NULL){
    //advance curr one down the list to the value to be put at the back
    curr = curr->next;
    //skipping over the value put at the back, link the front to the back
    curr->next->prev = curr->prev;
    //skipping over the value put at the back, link the back to the front
    curr->prev->next = curr->next;
    //now add the skipped value to the end, tail links forward to curr
    tail_->next = curr;
    //move temp1 to the next node after the jump, which curr's next still points to
    temp1 = curr->next;
    //curr links backward to the tail
    curr->prev = tail_;
    //set the new end of the list's next to NULL and make it the new tail
    tail_ = curr;
    curr->next = NULL;
    //reset the curr position and start the process over
    curr = temp1;
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
    //split is exceeds the length of the list
    //return an empty list
    if (splitPoint > length_)
        return List<T>();
    //invalid splitPoint, so set to zero, thus returning an original list
    if (splitPoint < 0)
        splitPoint = 0;
    //
    ListNode * secondHead = split(head_, splitPoint);

    int originalLength = length_;
    if (secondHead == head_) {
        // if both heads point to the same place then the list is empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // setup the first list
        //marching through the list and finding the end
        tail_ = head_;
        while (tail_ -> next != NULL)
            tail_ = tail_->next;
        //reseting the length
        length_ = splitPoint;
    }

    //intialize the second list
    List<T> second;
    second.head_ = secondHead;
    second.tail_ = secondHead;
    //finding the second list's tail
    if (second.tail_ != NULL) {
        while (second.tail_->next != NULL)
            second.tail_ = second.tail_->next;
    }
    second.length_ = originalLength - splitPoint;
    return second;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.2
  //empty list edge case
  //if its an empty list then return startpoint pointer
  if(start == NULL || splitPoint <= 0) return start;
  else{
    ListNode * temp1 = head_;
    while(splitPoint > 0){
      //move down the list until you get to the startPoint of list 2
      --splitPoint;
      temp1 = temp1->next;
    }
    //now I am at the start of the new list, need to disconnect from the original list
    temp1->prev->next = NULL;
    temp1->prev = NULL;
    return temp1;
  }
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T> & otherList) {
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
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
    //two empty lists, return NULL
    if(first == NULL && second == NULL) return NULL;
    //merging the same list, results in the same list
    if(first == second) return first;
    //if one is empty then return the other
    if(first == NULL) return second;
    if(second == NULL) return first;

    ListNode* returnHead = first;
    ListNode* tempFirst = first;
    ListNode* tempSecond = second;
    ListNode* tempFinal = returnHead;
    //Initializes the pointers before iterating down the lists
    //whichever list has the smaller starting node, place the 
    //start of the resulting list there
    if(first->data < second->data){
      tempFirst = first->next;
    }
    else{
      returnHead = second;
      tempFinal = returnHead;
      tempSecond = second->next;
    }
    //Now iterate now both lists, extracting the smaller value
    while(tempFirst != NULL && tempSecond != NULL){
      if(tempFirst->data < tempSecond->data || tempSecond == NULL){
        //first's data is smaller, so the final's next points to that data
        tempFinal->next = tempFirst;
        //set the previous to point to data as well
        tempFirst->prev = tempFinal;
        //move the resulting pointer up one up the final list
        tempFinal = tempFinal->next;
        //move the first pointer up one on the first list
        tempFirst = tempFirst->next;
      }
      else{
        //second's data is smaller, so the final's next points to that data
        tempFinal->next = tempSecond;
        //set the previous to point to data as well
        tempSecond->prev = tempFinal;
        //move the resulting pointer up one up the final list
        tempFinal = tempFinal->next;
        //move the second pointer up one on the second list
        tempSecond = tempSecond->next;
      }
    }
    //now either the first or second list's pointer points to NULL
    if(tempFirst == NULL){
      //now the rest of the final list is what remains of the second list
      tempFinal->next = tempSecond;
      tempSecond->prev = tempFinal;
    }
    if(tempSecond == NULL){
      //now the rest of the final list is what remains of the first list
      tempFinal->next = tempFirst;
      tempFirst->prev = tempFinal;
    }
  return returnHead;
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
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  ListNode * mergedListHead = start;
  //base case of when the chainlength is 1 or 0
  if(chainLength <= 1){
    start->next = NULL;
    start->prev = NULL;
    return start;
  }
  else{
    ListNode * temp = start;
    //move temp down the list to the splitpoint
    for(int i = 0; i < chainLength/2; ++i){
      temp = temp->next;
    }
    //end the first list
    temp->prev->next = NULL;
    temp->prev = NULL;
    //recursively merge the first half of the list
    start = mergesort(start, chainLength/2);
    //recursivelt merge the second half of the list
    //this works with odd list lengths due to integer division
    temp = mergesort(temp,chainLength - chainLength/2);
    //merge the two lists together
    mergedListHead = merge(start, temp);
  }
  return mergedListHead;
}
