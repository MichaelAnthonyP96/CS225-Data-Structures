/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */
	//check whether the Dimension is valid
	if(curDim < 0 || curDim > Dim){
		return false;
	}
	//if there is a tie, break the tie with the overloaded operator
	if(first[curDim] == second[curDim]){
		return first < second;
	}
	//besides the two base cases, return whether first's value
	//is smaller than second's value
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
	for(int i = 0; i < Dim; i++){
		distance += (p1[i] - p2[i]) * (p1[i] - p2[i]);
	}
	return distance;
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
	
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

    return Point<Dim>();
}

