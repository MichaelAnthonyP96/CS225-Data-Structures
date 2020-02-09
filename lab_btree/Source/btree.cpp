/**
 * @file btree.cpp
 * Implementation of a B-tree class which can be used as a generic dictionary
 * (insert-only). Designed to take advantage of caching to be faster than
 * standard balanced binary search trees.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

using std::vector;

/**
 * Finds the value associated with a given key.
 * @param key The key to look up.
 * @return The value (if found), the default V if not.
 */
template <class K, class V> V BTree<K, V>::find(const K &key) const {
  return root == nullptr ? V() : find(root, key);
}

/**
 * Private recursive version of the find function.
 * @param subroot A reference of a pointer to the current BTreeNode.
 * @param key The key we are looking up.
 * @return The value (if found), the default V if not.
 */
template <class K, class V>
V BTree<K, V>::find(const BTreeNode *subroot, const K &key) const {
  /* TODO Finish this function */
  // std::cout << *subroot << std::endl;

  size_t first_larger_idx = insertion_idx(subroot->elements, key);

  /* If first_larger_idx is a valid index and the key there is the key we
   * are looking for, we are done. */

  /* Otherwise, we need to figure out which child to explore. For this we
   * can actually just use first_larger_idx directly. E.g.
   * | 1 | 5 | 7 | 8 |
   * Suppose we are looking for 6. first_larger_idx is 2. This means we want to
   * explore the child between 5 and 7. The children vector has a pointer for
   * each of the horizontal bars. The index of the horizontal bar we want is
   * 2, which is conveniently the same as first_larger_idx. If the subroot is
   * a leaf and we didn't find the key in it, then we have failed to find it
   * anywhere in the tree and return the default V.
   */
  // if first_larger_idx does not exceed the length of the vector and the
  // subroot is not empty
  if ((first_larger_idx < subroot->elements.size()) &&
      !(subroot->elements.empty())) {
    // if the element at the first_larger_idx of the current subroot is equal to
    // the key, return its value. Otherwise search its children
    if (subroot->elements[first_larger_idx].key == key) {
      return subroot->elements[first_larger_idx].value;
    }
  }
  /*If the subroot is a leaf and we didn't find the key in it, then we have
   * failed to find it anywhere in the tree and return the default V.
   */
  if (subroot->is_leaf)
    return V();
  else
    // else search for the key in the subroot's children
    return find(subroot->children[first_larger_idx], key);
}

/**
 * Inserts a key and value into the BTree. If the key is already in the
 * tree do nothing.
 * @param key The key to insert.
 * @param value The value to insert.
 */
template <class K, class V>
void BTree<K, V>::insert(const K &key, const V &value) {
  /* Make the root node if the tree is empty. */
  if (root == nullptr) {
    root = new BTreeNode(true, order);
  }
  insert(root, DataPair(key, value));
  /* Increase height by one by tossing up one element from the old
   * root node. */
  if (root->elements.size() >= order) {
    BTreeNode *new_root = new BTreeNode(false, order);
    new_root->children.push_back(root);
    split_child(new_root, 0);
    root = new_root;
  }
}

/**
 * Splits a child node of a BTreeNode. Called if the child became too
 * large.
 * @param parent The parent whose child we are trying to split.
 * @param child_idx The index of the child in its parent's children
 * vector.
 */
template <class K, class V>
void BTree<K, V>::split_child(BTreeNode *parent, size_t child_idx) {
  /* Assume we are splitting the 3 6 8 child.
   * We want the following to happen.
   *     | 2 |
   *    /     \
   * | 1 |   | 3 | 6 | 8 |
   *
   *
   * Insert a pointer into parent's children which will point to the
   * new right node. The new right node is empty at this point.
   *     | 2 |   |
   *    /     \
   * | 1 |   | 3 | 6 | 8 |
   *
   * Insert the mid element from the child into its new position in the
   * parent's elements. At this point the median is still in the child.
   *     | 2 | 6 |
   *    /     \
   * | 1 |   | 3 | 6 | 8 |
   *
   * Now we want to copy over the elements (and children) to the right
   * of the child median into the new right node, and make sure the left
   * node only has the elements (and children) to the left of the child
   * median.
   *     | 2 | 6 |
   *    /   /     \
   * | 1 | | 3 | | 8 |
   *
   */

  /* The child we want to split. */
  BTreeNode *child = parent->children[child_idx];
  /* The "left" node is the old child, the right child is a new node. */
  BTreeNode *new_left = child;
  BTreeNode *new_right = new BTreeNode(child->is_leaf, order);

  /* E.g.
   * | 3 | 6 | 8 |
   * Mid element is at index (3 - 1) / 2 = 1 .
   * Mid child (bar) is at index 4 / 2 = 2 .
   * E.g.
   * | 2 | 4 |
   * Mid element is at index (2 - 1) / 2 = 0 .
   * Mid child (bar) is at index 2 / 2 = 1 .
   * This definition is to make this BTree act like the visualization
   * at
   * https://www.cs.usfca.edu/~galles/visualization/BTree.html
   */
  size_t mid_elem_idx = (child->elements.size() - 1) / 2;
  size_t mid_child_idx = child->children.size() / 2;

  /* Iterator for where we want to insert the new child. */
  auto child_itr = parent->children.begin() + child_idx + 1;
  /* Iterator for where we want to insert the new element. */
  auto elem_itr = parent->elements.begin() + child_idx;
  /* Iterator for the middle element. */
  auto mid_elem_itr = child->elements.begin() + mid_elem_idx;
  /* Iterator for the middle child. */
  auto mid_child_itr = child->children.begin() + mid_child_idx;

  /* TODO Your code goes here! */
  // following instructions as detailed above
  // first get the middle element to be "thrown up"
  DataPair bTreeInsert = *mid_elem_itr;
  // insert that element into its parent node's elements vector
  parent->elements.insert(elem_itr, bTreeInsert);
  // insert a pointer to into the parent's children vector
  parent->children.insert(child_itr, new_right);
  // assign all elements to the right of the original middle as the children
  // of the new right element
  new_right->elements.assign(mid_elem_itr + 1, new_left->elements.end());
  // assign all elements to the left of the original middle as the children of
  // the new left element
  new_left->elements.assign(new_left->elements.begin(), mid_elem_itr);
  if (!new_left->is_leaf) {
    // assign children to the new right element, pointers to the old right hand
    // children
    new_right->children.assign(mid_child_itr, new_left->children.end());
    // assign children to the new left element, pointers to the old left hand
    // children
    new_left->children.assign(new_left->children.begin(), mid_child_itr);
  }
}

/**
 * Private recursive version of the insert function.
 * @param subroot A reference of a pointer to the current BTreeNode.
 * @param pair The DataPair to be inserted.
 * Note: Original solution used std::lower_bound, but making the students
 * write an equivalent seemed more instructive.
 */
template <class K, class V>
void BTree<K, V>::insert(BTreeNode *subroot, const DataPair &pair) {
  /* There are two cases to consider.
   * If the subroot is a leaf node and the key doesn't exist subroot, we
   * should simply insert the pair into subroot.
   * Otherwise (subroot is not a leaf and the key doesn't exist in subroot)
   * we need to figure out which child to insert into and call insert on it.
   * After this call returns we need to check if the child became too large
   * and thus needs to be split to maintain order.
   */

  size_t first_larger_idx = insertion_idx(subroot->elements, pair);

  /* TODO Your code goes here! */
  // base cases
  // checking to see if the current subroot is valid and the key doesnt already
  // exist
  if ((first_larger_idx < subroot->elements.size()) &&
      !subroot->elements.empty()) {
    // if the key of the Pair we are going to insert already exists do nothing
    if (subroot->elements[first_larger_idx].key == pair.key)
      return;
  }
  // we now know that we have a non repeated key and we can insert at the leaf
  if (subroot->is_leaf) {
    // if the subroot is a leaf then insert the pair into its elements at the
    // correct index
    subroot->elements.insert(subroot->elements.begin() + first_larger_idx,
                             pair);
  }
  // subroot is not a leaf and the key doesn't exist in subroot
  else {
    // get the child Node we are going to insert into
    BTreeNode *Node = subroot->children[first_larger_idx];
    // recursive call on the child with the pair to be inserted
    insert(Node, pair);
    // once we have inserted, check to see if child became too big and needs to
    // be split
    if (Node->elements.size() == order) {
      // split the parent at the first larger index
      split_child(subroot, first_larger_idx);
    }
  }
}