/**
 * @file graph_tools.cpp
 * This is where you will implement several functions that operate on graphs.
 * Be sure to thoroughly read the comments above each function, as they give
 *  hints and instructions on how to solve the problems.
 */

#include "graph_tools.h"

/**
 * Finds the minimum edge weight in the Graph graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @return the minimum weighted edge
 *
 * @todo Label the minimum edge as "MIN". It will appear blue when
 *  graph.savePNG() is called in minweight_test.
 *
 * @note You must do a traversal.
 * @note You may use the STL stack and queue.
 * @note You may assume the graph is connected.
 *
 * @hint Initially label vertices and edges as unvisited.
 */
using namespace std;
int GraphTools::findMinWeight(Graph& graph)
{
    //TODO: YOUR CODE HERE
    //first mark all vertices as UNEXPLORED
    vector <Vertex> v = graph.getVertices();
	for(size_t i = 0; i < v.size(); i++){
	    graph.setVertexLabel(v[i], "UNEXPLORED");
	}
    //mark all edges as unexplored to begin with
    markUnexplored(graph);
    //initialize the queue for potential use
    queue<Vertex> q;
    //set the first vertex as VISITED
    graph.setVertexLabel(v[0],"VISITED");
    //add the first vertex to the queue
    q.push(v[0]); 
    //while the queue is not empty
    //initialize source and destination vertices 
    Vertex source = v[0];
    Vertex destination = (graph.getAdjacent(v[0]))[0];
    //initialize the minEdgeWeight as the very first edge weight
    int minEdgeWeight = graph.getEdgeWeight(source, destination);

    while(!q.empty()){
    	//Look at the front of the queue
    	Vertex x = q.front();
    	//get this Vertex's adjacent vertexs
    	vector<Vertex> adjacentX = graph.getAdjacent(x);
    	//remove the old vertex from the queue
    	q.pop();
    	//iterate over all the adjacent vertices
    	for(size_t i = 0; i < adjacentX.size(); ++i){
    		if(graph.getVertexLabel(adjacentX[i]) == "UNEXPLORED"){
    		//if the current vertex is smaller than the current minEdgeWeight
	    		if(graph.getEdgeWeight(adjacentX[i],x) < minEdgeWeight){
	    			//overwrite the old minWeight
	    			minEdgeWeight = graph.getEdgeWeight(adjacentX[i],x);
	    			source = x;
	    			destination = adjacentX[i];
	    		}
	    		//set the current edge to be labeled as a DISCOVERY edge
	    		graph.setEdgeLabel(x,adjacentX[i],"DISCOVERY");
	    		//set the current vertex to be labeled as VISITED
	    		graph.setVertexLabel(adjacentX[i],"VISITED");
	    		//add the adjacent vertex to the queue so that we can explore its adjacent vertices
	    		q.push(adjacentX[i]);
    		}
    		else if(graph.getEdgeLabel(x,adjacentX[i]) == "UNEXPLORED"){
    			if(graph.getEdgeWeight(adjacentX[i],x) < minEdgeWeight){
    				//overwrite the old minWeight
	    			minEdgeWeight = graph.getEdgeWeight(adjacentX[i],x);
	    			source = x;
	    			destination = adjacentX[i];
    			}
    			//mark the edge as a Cross
    			graph.setEdgeLabel(x,adjacentX[i],"CROSS");
    		}
    	}
	}
graph.setEdgeLabel(source,destination,"MIN");
return minEdgeWeight;
}

/**
 * Returns the shortest distance (in edges) between the Vertices
 *  start and end.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to search
 * @param start - the vertex to start the search from
 * @param end - the vertex to find a path to
 * @return the minimum number of edges between start and end
 *
 * @todo Label each edge "MINPATH" if it is part of the minimum path
 *
 * @note Remember this is the shortest path in terms of edges,
 *  not edge weights.
 * @note Again, you may use the STL stack and queue.
 * @note You may also use the STL's unordered_map, but it is possible
 *  to solve this problem without it.
 *
 * @hint In order to draw (and correctly count) the edges between two
 *  vertices, you'll have to remember each vertex's parent somehow.
 */
int GraphTools::findShortestPath(Graph& graph, Vertex start, Vertex end)
{
    //TODO: YOUR CODE HERE
    //(void) graph;
    //(void) start;
    //(void) end;
    //mark all vertices as UNEXPLORED
    vector<Vertex> v = graph.getVertices();
	for(size_t i = 0; i < v.size(); i++){
	    graph.setVertexLabel(v[i], "UNEXPLORED");
	}
	//mark all edges as UNEXPLORED
    markUnexplored(graph);
	//initialize queue and map 
	queue <Vertex> q;
	//push the starting point to the queue
	q.push(start);
	//map to keep track of each vertex's parent
	unordered_map <Vertex,Vertex> merp;
	//set the starting vertex as VISITED
	graph.setVertexLabel(start,"VISITED");
	//while the queue is not empty, traverse the graph
	while(!q.empty()){
		//Look at the front of the queue
    	Vertex x = q.front();
    	//get this Vertex's adjacent vertexs
    	vector<Vertex> adjacentX = graph.getAdjacent(x);
    	//remove the old vertex from the queue
    	q.pop();
    	//iterate over all the adjacent vertices
    	for(size_t i = 0; i < adjacentX.size(); ++i){
    		//if the vertex is UNEXPLORED, investigate it
    		if(graph.getVertexLabel(adjacentX[i]) == "UNEXPLORED"){
    			//create a pair for our map of adjacent vertex and its parent
    			pair <Vertex,Vertex> verticePair(adjacentX[i],x);
    			//add the pair to the map
    			merp.insert(verticePair);
    			//push the vertex to the queue to investigate its adjacents later
    			q.push(adjacentX[i]);
    			//mark the current vertex as visited
    			graph.setVertexLabel(adjacentX[i],"VISITED");
    			//mark the adjacent edge as a DISCOVERY edge
    			//cout << "line148" << endl;
    			graph.setEdgeLabel(x,adjacentX[i],"DISCOVERY");
    		}
    		//the vertex has been explored before, so if the edge between them 
    		//is marked as UNEXPLORED then we mark the edge as a CROSS
    		else if(graph.getEdgeLabel(x,adjacentX[i]) == "UNEXPLORED"){
    			graph.setEdgeLabel(x,adjacentX[i],"CROSS");
    		}
    	}
	}
	//backtrack through the map from the end back to the start updating
	//the distance as we go
	size_t distance = 0;
	while(start != end){
		++distance;
		//mark the path as MINPATH as we go backwards
		//cout << "line164" << endl;
		graph.setEdgeLabel(end,merp[end],"MINPATH");
		end = merp[end];
	}
    return distance;
}

/**
 * Finds a minimal spanning tree on a graph.
 * THIS FUNCTION IS GRADED.
 *
 * @param graph - the graph to find the MST of
 *
 * @todo Label the edges of a minimal spanning tree as "MST"
 *  in the graph. They will appear blue when graph.savePNG() is called.
 *
 * @note Use your disjoint sets class from MP 7.1 to help you with
 *  Kruskal's algorithm. Copy the files into the dsets.h and dsets.cpp .
 * @note You may call std::sort instead of creating a priority queue.
 */
void GraphTools::findMST(Graph& graph)
{
    //TODO: YOUR CODE HERE
    /*
    *1.Get a list of all edges in the graph and sort them by increasing weight.
	*2.Create a disjoint sets structure where each vertex is represented by a set.
    *	Since a Vertex is a string but you need integers to implement disjoint set, how will you solve it?
	*3.Traverse the list from the start (i.e., from lightest weight to heaviest).
	*	Inspect the current edge. If that edge connects two vertices from different sets, union their respective sets and mark the edge as part of the MST. Otherwise there would be a cycle, so do nothing.
    *	Repeat this until n−1 edges have been added, where n is the number of vertices in the graph.
    */

    // get all the vertices in the graph
    vector<Vertex> v = graph.getVertices();
    // map which takes a vertex as the key and the set number as the value
    unordered_map<Vertex, int> map;
    // get all edges in the graph
    vector<Edge> ve = graph.getEdges();
    // sort the edges in increasing order by their edge weights
    sort(ve.begin(), ve.end(), sortEdge);
    // assign each vertex a number
    for(size_t i = 0; i < v.size(); ++i)
      map[v[i]] = i;

    // create a default disjointSets object
    DisjointSets vertexSets;
    // now initialize all the sets within the DisjointSets vector to -1
    vertexSets.addelements(v.size());
    // iterate over all of the graph's edges
    for(size_t i = 0; i < ve.size(); ++i){
    	// if two vertices are not in the same set, then union them
    	if( vertexSets.find(map[(ve[i]).source]) != vertexSets.find(map[(ve[i]).dest]) ){
    		// mark the edge as apart of the Minimum spanning tree
    		graph.setEdgeLabel(ve[i].source, ve[i].dest, "MST");
    		// Union the two sets since the are not in the same set
    		vertexSets.setunion(map[ve[i].source], map[ve[i].dest]);
    	}
    }
}

void GraphTools::markUnexplored(Graph& g){
	//get all edges from the graph
	vector<Edge> e = g.getEdges();
	//iterate over all the those edges
	for(size_t j = 0; j < e.size(); ++j){
		//mark all edges from source to destination as UNEXPLORED
		g.setEdgeLabel(e[j].source,e[j].dest,"UNEXPLORED");
	}
}

bool GraphTools::sortEdge(Edge source, Edge destination){
	return (source.getWeight() < destination.getWeight());
}