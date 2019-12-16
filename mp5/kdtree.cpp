/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>
#include <iostream>

//using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
	// check whether the Dimension is valid
	if(curDim < 0 || curDim > Dim){
		return false;
	}
	//if there is a tie, break the tie with the overloaded operator
	if(first[curDim] == second[curDim]){
		return first < second;
	}
	// besides the two base cases, return whether first's value
	// is smaller than second's value
    return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
	//calculate the distance between the target and currentBest
	int d1 = calculateDistance(target, currentBest);
	//calculate the distance between the target and potential
	int d2 = calculateDistance(target, potential);
	//if the two distances are equal, break the tie using the overloaded operator
	if(d1 == d2){
		return potential < currentBest;
	}
	//return whether the potential Point's distance is smaller than
	//the currentBest's distance
     return d2 < d1;
}

template <int Dim>
int KDTree<Dim>::calculateDistance(const Point<Dim>& p1, const Point<Dim>& p2)const{
	int distance = 0;
	//loop over all dimensions in the Points
	for(int i = 0; i < Dim; ++i){
		distance += (p1[i] - p2[i]) * (p1[i] - p2[i]);
	}
	return distance;
}

template <int Dim>
KDTree<Dim>::KDTree(const std::vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */

    if(newPoints.size() == 0){
        root = NULL;
        size = 0;
    } else {
        std::vector<Point<Dim>> otherPoints = newPoints;
        size = 0;
        buildKDTree(otherPoints, 0, newPoints.size() - 1, 0, root);
    }

}

template <int Dim>
void KDTree<Dim>::buildKDTree(std::vector<Point<Dim>>& otherPoints, int left, int right, int dimension, KDTreeNode*& root)
{
    if(left > right){
        return;
    }
    int median = (left + right) / 2;
    Point<Dim> node = quickSelect(otherPoints, left, right, median, dimension);
    root = new KDTreeNode(node);
    ++size;

    buildKDTree(otherPoints, left, median - 1, (dimension + 1) % Dim, root->left);
    buildKDTree(otherPoints, median + 1, right, (dimension + 1) % Dim, root->right);
}
template <int Dim>
KDTree<Dim>::KDTree(const KDTree& other) {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree& rhs) {
  /**
   * @todo Implement this function!
   */

  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree() {
  /**
   * @todo Implement this function!
   */
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return nearestNeighborHelper(query, root, 0);
}

template <int Dim>
Point<Dim> KDTree<Dim>::nearestNeighborHelper(const Point<Dim>& query, KDTreeNode* root, int dim) const {

    if(isLeaf(root))
        return root->point;
    Point<Dim> found;
    // search left if query is less than the current root in the current dimension
    if (smallerDimVal(query, root->point, dim)) {
        if(root->left != NULL){
            found = nearestNeighborHelper(query, root->left, (dim + 1) % Dim);
            if (shouldReplace(query, found, root->point)) {
                found = root->point;
            }
            double radius = calculateDistance(found, query);
            double planeDistance = (root->point[dim] - query[dim]) * (root->point[dim] - query[dim]);
            if (radius >= planeDistance && root->right != NULL) {
                Point<Dim> tmp = nearestNeighborHelper(query, root->right, (dim + 1) % Dim);
                if(shouldReplace(query, found, tmp)){
                    found = tmp;
                }
            }
        } else {
            found = root->point;
        }
    // search right if the query is greater than the current root in the current dimension
    } else if (smallerDimVal(root->point, query, dim)) {
        if (root->right != NULL) {
            found = nearestNeighborHelper(query, root->right, (dim + 1) % Dim);
            if (shouldReplace(query, found, root->point)) {
                found = root->point;
            }
            double radius = calculateDistance(found, query);
            double planeDistance = (root->point[dim] - query[dim]) * (root->point[dim] - query[dim]);
            if (radius >= planeDistance && root->left != NULL) {
                Point<Dim> tmp = nearestNeighborHelper(query, root->left, (dim + 1) % Dim);
                if(shouldReplace(query, found, tmp)){
                    found = tmp;
                }
            }
        } else {
            found = root->point;
        }
    } else {
        return root->point;
    }

    return found;
}

/**
 * Quickselect Helper method
 */
template <int Dim>
int KDTree<Dim>::partition(std::vector<Point<Dim>>& Points, int left, int right, int pivotIndex, int dimension)
{
    Point<Dim> pivotValue = Points[pivotIndex];
    // swap the two Points
    Points[pivotIndex] = Points[right];
    Points[right] = pivotValue;
    Point<Dim> tmp;
    int storeIndex = left;
    for(int i = left; i < right; ++i){
        if(smallerDimVal(Points[i], pivotValue, dimension)) {
            // swap the two Points
            tmp = Points[i];
            Points[i] = Points[storeIndex];
            Points[storeIndex] = tmp;
            ++storeIndex;
        }
    }
    // swap the two Points
    tmp = Points[right];
    Points[right] = Points[storeIndex];
    Points[storeIndex] = tmp;
    return storeIndex;
}

template <int Dim>
Point<Dim> KDTree<Dim>::quickSelect(std::vector<Point<Dim>>& Points, int left, int right, int k, int dimension)
{
    while(true){
        if(left == right)
            return Points[left];
        int pivotIndex = (left + right) / 2;
        pivotIndex = partition(Points, left, right, pivotIndex, dimension);
        if(k == pivotIndex) {
            return Points[k];
        } else if(k<pivotIndex){
            right = pivotIndex - 1;
        } else {
            left = pivotIndex + 1;
        }
    }
}

template <int Dim>
bool KDTree<Dim>::isLeaf(KDTreeNode *root) const {

    if(root->left == NULL &&
       root->right == NULL){
        return true;
    } else {
        return false;
    }
}

