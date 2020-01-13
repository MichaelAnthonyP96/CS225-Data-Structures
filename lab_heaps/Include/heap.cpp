
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

#include <math.h>

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    // @TODO Update to return the index you are choosing to be your root.
    // using 1 based indexing
    return 1;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the left child.
    // using 1 based indexing
    return (2*currentIdx);
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the right child.
    // using 1 based indexing
    return (2*currentIdx + 1);
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // @TODO Update to return the index of the parent.
    // using 1 based indexing
    return floor(currentIdx/2);
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // @TODO Update to return whether the given node has a child
    if((currentIdx * 2) < _elems.size()) return true;
    else return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    // @TODO Update to return the index of the child with highest priority
    ///   as defined by higherPriority()
    // get the left and right child indices
    size_t leftIdx = leftChild(currentIdx);
    size_t rightIdx = rightChild(currentIdx);
    //if the right node index is valid, since we know the children are added
    //left then right order
    if(((currentIdx *2) + 1) < _elems.size()){
        //if the left is higher priority
        if(higherPriority(_elems[leftIdx], _elems[rightIdx])){
            //then return it
            return leftIdx;
        }
        else{
            //if not then return the right
            return rightIdx;
        }
    }
    //return the left child as default if the right child doesn't exist 
    return currentIdx*2;;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // @TODO Implement the heapifyDown algorithm.
    //if at the leaves then do nothing
    if(!hasAChild(currentIdx)) return;
    //get the highest priority child index
    size_t childIdx = maxPriorityChild(currentIdx);
    //if the child is higher priority than its parent, then swap and recurse
    if(higherPriority(_elems[childIdx],_elems[currentIdx])){
        //swap the higher priority with the parent
        std::swap(_elems[currentIdx],_elems[childIdx]);
        //recursive heapify down
        heapifyDown(childIdx);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    // @TODO Depending on your implementation, this function may or may
    ///   not need modifying
    //used for 1 based indexing
    _elems.push_back(0);
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    // @TODO Construct a heap using the buildHeap algorithm
    //for 1 based indexing, insert 0 at the first element
    _elems.push_back(0);
    //get the size of the elements vector
    size_t size = elems.size();
    //push the elements into the vector
    for(size_t i = 0; i < size; i++){
        _elems.push_back(elems[i]);
    }
    //call heapify down on each element starting at the leaf farthest to the right
    //and work backwards
    for(int i = parent(size + 1); i > 0; --i){
        heapifyDown(i);
    }
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // @TODO Remove, and return, the element with highest priority
    //if the vector is empty then return a blank Template
    if(_elems.size() == 1) return T();
    //hold the highest priority element
    T temp = _elems[1];
    //replace the first element in the vector with the last
    _elems[1] = _elems[_elems.size() - 1];
    //remove the last element from the vector
    _elems.pop_back();
    //restore order in the tree starting at the root node
    heapifyDown(1);
    return temp;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // @TODO Return, but do not remove, the element with highest priority
    return _elems[1];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    // @TODO Add elem to the heap
    //add new element to the bottom of the tree
    _elems.push_back(elem);
    //then heapifyUp to restore properties
    heapifyUp(_elems.size() - 1 );
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    // @TODO Determine if the heap is empty
    if(_elems.size() == 1) return true;
    else return false;
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}