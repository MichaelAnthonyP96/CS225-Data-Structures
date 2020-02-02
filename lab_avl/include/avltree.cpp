/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V> V AVLTree<K, V>::find(const K &key) const {
  return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node *subtree, const K &key) const {
  if (subtree == NULL)
    return V();
  else if (key == subtree->key)
    return subtree->value;
  else {
    if (key < subtree->key)
      return find(subtree->left, key);
    else
      return find(subtree->right, key);
  }
}

template <class K, class V> void AVLTree<K, V>::rotateLeft(Node *&t) {
  functionCalls.push_back(
      "rotateLeft"); // Stores the rotation name (don't remove this)
  // your code here
  if (t == NULL || t->right == NULL) {
    return;
  }

  // allocate a temporary Pivot Node pointer
  Node *Pivot = t->right;
  // perform left rotation as described in lecture
  // detach Pivot from the rest of the tree
  t->right = Pivot->left;
  // reattach Pivot atop the old node
  Pivot->left = t;
  // recalculate the height of the new subtree
  t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
  // attach the correctly pivoted subtree back to the original root
  t = Pivot;
  // recalculate the height of the new correctly pivoted subtree
  t->height = max(heightOrNeg1(t->left), heightOrNeg1(t->right)) + 1;
}

template <class K, class V> void AVLTree<K, V>::rotateLeftRight(Node *&t) {
  functionCalls.push_back(
      "rotateLeftRight"); // Stores the rotation name (don't remove this)
  // Implemented for you:
  rotateLeft(t->left);
  rotateRight(t);
}

template <class K, class V> void AVLTree<K, V>::rotateRight(Node *&t) {
  functionCalls.push_back(
      "rotateRight"); // Stores the rotation name (don't remove this)
  // your code here

  if (t == NULL || t->left == NULL) {
    return;
  }

  // allocate a temporary Pivot Node pointer
  Node *Pivot = t->left;
  // perform right rotation as described in lecture
  // detach Pivot from the rest of the tree
  t->left = Pivot->right;
  // re-attach Pivot atop the old node
  Pivot->right = t;
  // recalculate the height of the new subtree
  calculateHeight(t);
  // attach the correctly pivoted subtree back to the original root
  t = Pivot;
  // recalculate the height of the new correctly pivoted subtree
  calculateHeight(t);
}

template <class K, class V> void AVLTree<K, V>::rotateRightLeft(Node *&t) {
  functionCalls.push_back(
      "rotateRightLeft"); // Stores the rotation name (don't remove this)
  // your code here
  rotateRight(t->right);
  rotateLeft(t);
}

template <class K, class V> void AVLTree<K, V>::rebalance(Node *&subtree) {
  // your code here
  if (subtree == NULL)
    return;
  calculateHeight(subtree);

  int right, left;
  if (subtree->right == NULL && subtree->left == NULL)
    return;

  if (subtree->right == NULL)
    right = -1;
  else
    right = subtree->right->height;

  if (subtree->left == NULL)
    left = -1;
  else
    left = subtree->left->height;

  if ((left - right) > 1) {
    if (subtree->left != NULL) {
      int balance = heightOrNeg1(subtree->left->left) -
                    heightOrNeg1(subtree->left->right);
      if (balance < 0) {
        return rotateLeftRight(subtree);
      }
    }
    return rotateRight(subtree);
  }
  if ((left - right) < -1) {
    if (subtree->right != NULL) {
      int balance = heightOrNeg1(subtree->right->left) -
                    heightOrNeg1(subtree->right->right);
      if (balance > 0) {
        return rotateRightLeft(subtree);
      }
    }
    return rotateLeft(subtree);
  }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K &key, const V &value) {
  insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node *&subtree, const K &key, const V &value) {
  // your code here
  if (subtree == NULL)
    subtree = new Node(key, value);
  else if (key < subtree->key) {
    // need to insert somewhere in the left subtree, recursive call
    insert(subtree->left, key, value);
    // get the balance factors of the left subtree and the overall tree
    int leftBalance =
        heightOrNeg1(subtree->left->right) - heightOrNeg1(subtree->left->left);
    int overallBalance =
        heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    // base cases of recursion, where the node actually needs to be inserted
    if (overallBalance == -2) {
      //"stick" case
      if (leftBalance == -1)
        rotateRight(subtree);
      //"elbow" case
      else
        rotateLeftRight(subtree);
    }
  } else if (key > subtree->key) {
    // need to insert somewhere in the right subtree. recursive call
    insert(subtree->right, key, value);
    // get the balance factors of the right subtree and the overall tree
    int rightBalance = heightOrNeg1(subtree->right->right) -
                       heightOrNeg1(subtree->right->left);
    int overallBalance =
        heightOrNeg1(subtree->right) - heightOrNeg1(subtree->left);
    // base cases of recursion, where the node actually needs to be inserted
    if (overallBalance == 2) {
      //"stick" case
      if (rightBalance == 1)
        rotateLeft(subtree);
      //"elbow" case
      else
        rotateRightLeft(subtree);
    }
  }
  // re-adjust the height even regardless of what insert was performed
  subtree->height =
      1 + max(heightOrNeg1(subtree->left), heightOrNeg1(subtree->right));
}

template <class K, class V> void AVLTree<K, V>::remove(const K &key) {
  remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node *&subtree, const K &key) {
  if (subtree == NULL) {
    return;
  }
  if (key < subtree->key) {
    // your code here
    // recursive call to find the key in the subtree
    remove(subtree->left, key);
    // rebalance the tree as the recursion unwinds
    rebalance(subtree);
  } else if (key > subtree->key) {
    // your code here
    // recursive call to find the key in the subtree
    remove(subtree->right, key);
    // rebalance the tree as the recursion unwinds
    rebalance(subtree);
  } else {
    // Since we know the key exists, we've found the key
    if (subtree->left == NULL && subtree->right == NULL) {
      /* no-child remove */
      // your code here
      // set the pointer by reference to NULL
      delete subtree;
      subtree = NULL;
    } else if (subtree->left != NULL && subtree->right != NULL) {
      /* two-child remove */
      // your code here
      // find the In Order Predecessor
      Node *&IOP = inOrderPredecessor(subtree->left);
      // swap the IOP and the subtree pointers
      swap(IOP, subtree);
      // delete the IOP pointer and set it equal to NULL
      delete IOP;
      IOP = NULL;
      calculateHeight(subtree->left);
    } else {
      /* one-child remove */
      // your code here
      // only a left child
      if (subtree->left != NULL) {
        // temp to hold the subtree left child, we would lose access to it
        // without the temp
        Node *temp = subtree->left;
        delete subtree;
        subtree = temp;
      }
      // only a right child
      else if (subtree->right != NULL) {
        // temp to hold the subtree right child, we would lose access to it
        // without the temp
        Node *temp = subtree->right;
        delete subtree;
        subtree = temp;
      }
    }
    rebalance(subtree);
  }
}

template <class K, class V>
typename AVLTree<K, V>::Node *&
AVLTree<K, V>::inOrderPredecessor(AVLTree<K, V>::Node *&subtree) {
  return subtree->right == NULL ? subtree : inOrderPredecessor(subtree->right);
}

template <class K, class V>
void AVLTree<K, V>::calculateHeight(Node *&subtree) {
  if (subtree->left == NULL && subtree->right == NULL) {
    subtree->height = 0;
  } else if (subtree->left == NULL) {
    subtree->height = subtree->right->height + 1;
  } else if (subtree->right == NULL) {
    subtree->height = subtree->left->height + 1;
  } else {
    subtree->height = max(subtree->right->height, subtree->left->height) + 1;
  }
}