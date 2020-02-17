/* Your code here! */
#include "dsets.h"
#include <vector>

/*Creates n unconnected root nodes at the end of the vector.
 *Parameters :
 *	num	The number of nodes to create
 */
void DisjointSets::addelements(int num) {
  for (auto i = 0; i < num; ++i) {
    dSets.push_back(-1);
  }
}
/*This function should compress paths and works as described in lecture.
 *Returns :
 *	The index of the root of the up-tree in which the parameter element
 *resides.
 */
int DisjointSets::find(int elem) {
  if (dSets[elem] < 0) {
    return elem;
  } else {
    dSets[elem] = find(dSets[elem]);
    return dSets[elem];
  }
}
/*This function should be implemented as union-by-size.
 *That is, when you setunion two disjoint sets, the smaller (in terms of number
 *of nodes) should point at the larger. This function works as described in
 *lecture, except that you should not assume that the arguments to setunion are
 *roots of existing uptrees. Your setunion function SHOULD find the roots of its
 *arguments before combining the trees. If the two sets are the same size, make
 *the tree containing the second argument point to the tree containing the
 *first. (Note that normally we could break this tie arbitrarily, but in this
 *case we want to control things for grading.) Parameters a	Index of the
 *first element to union b	Index of the second element to union
 */
void DisjointSets::setunion(int a, int b) {
  // find the two sets to union together
  auto A = find(a);
  auto B = find(b);
  // if we are trying to union the same set to itself then do nothing
  if (A == B)
    return;

  auto AB = dSets[A] + dSets[B];
  if (dSets[A] > dSets[B]) {
    dSets[A] = B;
    dSets[B] = AB;
  } else {
    dSets[B] = A;
    dSets[A] = AB;
  }
}

int DisjointSets::size(int elem) {
  auto idx = find(elem);
  auto val = dSets[idx];
  int count = 0;
  for (size_t i = 0; i < dSets.size(); ++i) {
    if (dSets[i] == val) {
      count++;
    }
  }
  return count;
}
