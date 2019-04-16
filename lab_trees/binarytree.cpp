/**
 * @file binarytree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "TreeTraversals/InorderTraversal.h"
#include <iostream>
/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    cout << endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror()
{
    //your code here
    //edge case of an empty tree
    if(root == NULL) return;
    else mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node* subRoot){
    if(subRoot == NULL) return;
    else{
        Node* temp = subRoot->left;
        subRoot->left = subRoot->right;
        subRoot->right = temp;
        mirror(subRoot->left);
        mirror(subRoot->right);
    }
}

/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    // your code here
    //bool goo = false;
    if(this->getRoot() == NULL) return true;
    InorderTraversal<int> iot(this->getRoot());
    int currentMaximum;
    int nextMaximum;
    for (TreeTraversal<int>::Iterator it = iot.begin(); it != iot.end(); ) {
  		currentMaximum = (*it)->elem;
      if(*(++it) == NULL) break;
      nextMaximum = (*(++it))->elem;
      if(currentMaximum > nextMaximum) return false;
  	}
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{

    // your code here
    if(isOrderedRecursive(root)) return true;
    return false;
}

//recursive helper function
template <typename T>
bool BinaryTree<T>::isOrderedRecursive(const Node* subRoot) const
{
    bool left = false, right = false;
    int leftMax = 0, rightMax = 0;
    if(subRoot == NULL) return true;
    //if subroot's left is not empty then recursively find out if left is ordered
    if(subRoot->left != NULL){
        left = isOrderedRecursive(subRoot->left);
        rightMax = farthestRight(subRoot->left);
    }
    //subroot's left is empty, so it is technically sorted
    else{
        left = true;
        rightMax = subRoot->elem;
    }
    //subroot's right is not empty then recursively find out if the right is ordered
    if(subRoot->right != NULL){
        right = isOrderedRecursive(subRoot->right);
        leftMax = farthestLeft(subRoot->right);
    }
    //subroot's right is empty, so it is technically sorted
    else{
        right = true;
        leftMax = subRoot->elem;
    }
    //if the left and right are ordered
    //and the leftMax is greater than or equal to rightMax, return true
    if(right && left && (leftMax >= rightMax))
        return true;
    return false;
}
/**
 * creates vectors of all the possible paths from the root of the tree to any leaf
 * node and adds it to another vector.
 * Path is, all sequences starting at the root node and continuing
 * downwards, ending at a leaf node. Paths ending in a left node should be
 * added before paths ending in a node further to the right.
 * @param paths vector of vectors that contains path of nodes
 */
template <typename T>
void BinaryTree<T>::printPaths(vector<vector<T> > &paths) const
{
    // your code here
}

/**
 * Each node in a tree has a distance from the root node - the depth of that
 * node, or the number of edges along the path from that node to the root. This
 * function returns the sum of the distances of all nodes to the root node (the
 * sum of the depths of all the nodes). Your solution should take O(n) time,
 * where n is the number of nodes in the tree.
 * @return The sum of the distances of all nodes to the root
 */
template <typename T>
int BinaryTree<T>::sumDistances() const
{
    // your code here
    return -1;
}

//helper function to determine the element of the farthest right Node from the subroot, recursively
template <typename T>
T BinaryTree<T>::farthestRight(const Node* subRoot)const{
    if(subRoot->right == NULL) return subRoot->elem;
    return farthestRight(subRoot->right);
}

//helper function to determine the element of the farthest left Node from the subroot, recursively
template <typename T>
T BinaryTree<T>::farthestLeft(const Node* subRoot) const{
    if(subRoot->left == NULL) return subRoot->elem;
    return farthestLeft(subRoot->left);
}
