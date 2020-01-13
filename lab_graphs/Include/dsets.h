/* Your code here! */
#ifndef DSETS_H
#define DSETS_H
#include <vector>

class DisjointSets{
public:
	//Creates n unconnected root nodes at the end of the vector.
	void addelements(int num);
	//This function should compress paths and works as described in lecture. 
	int find(int elem);
	//Unions two sets together
	void setunion(int a, int b);
	//
	int size(int elem);
private:
	//this vector will store the disjoint sets
	std::vector<int> dSets;
};
#endif