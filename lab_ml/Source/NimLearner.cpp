/**
 * @file NimLearner.cpp
 * CS 225: Data Structures
 */

#include "NimLearner.h"
#include <ctime>


/**
 * Constructor to create a game of Nim with `startingTokens` starting tokens.
 *
 * This function creates a graph, `g_` representing all of the states of a
 * game of Nim with vertex labels "p#-X", where:
 * - # is the current player's turn; p1 for Player 1, p2 for Player2
 * - X is the tokens remaining at the start of a player's turn
 *
 * For example:
 *   "p1-4" is Player 1's turn with four (4) tokens remaining
 *   "p2-8" is Player 2's turn with eight (8) tokens remaining
 *
 * All legal moves between states are created as edges with initial weights
 * of 0.
 *
 * @param startingTokens The number of starting tokens in the game of Nim.
 */
NimLearner::NimLearner(unsigned startingTokens) : g_(true, true) {
  /* Your code goes here! */
  // if you have ten tokens, you have 11 states including zero.
  // insert the tokens into the graph
  for(long int i = 0; i <= startingTokens; ++i){
    // std::cout << "p1-" + std::to_string(i) << std::endl;
    // std::cout << "p2-" + std::to_string(i) << std::endl;
    g_.insertVertex("p1-" + to_string(i));
    g_.insertVertex("p2-" + to_string(i));
    // set the appropriate vertex name
    g_.setVertexLabel("p1-" + std::to_string(i), "p1-" + std::to_string(i) );
    g_.setVertexLabel("p2-" + std::to_string(i), "p2-" + std::to_string(i) );

    // insert the two edges connected to each vertex
    for(long int j = i - 2; j < i; ++j) {
      if(j >= 0) {
        g_.insertEdge(g_.getVertexByLabel("p2-" + to_string(i)), g_.getVertexByLabel("p1-" + to_string(j)));
        g_.insertEdge(g_.getVertexByLabel("p1-" + to_string(i)), g_.getVertexByLabel("p2-" + to_string(j)));
        g_.setEdgeWeight(g_.getVertexByLabel("p2-" + to_string(i)), g_.getVertexByLabel("p1-" + to_string(j)), 0);
        g_.setEdgeWeight(g_.getVertexByLabel("p1-" + to_string(i)), g_.getVertexByLabel("p2-" + to_string(j)), 0);
      }
      // std::cout << "I,J is equal to: " << i << "," << j << std::endl;
    }
  }
  // set the starting vertex of the game. Ex: p1-10
  startingVertex_ = g_.getVertexLabel("p1-" + to_string(startingTokens));
}

/**
 * Plays a random game of Nim, returning the path through the state graph
 * as a vector of `Edge` classes.  The `origin` of the first `Edge` must be
 * the vertex with the label "p1-#", where # is the number of starting
 * tokens.  (For example, in a 10 token game, result[0].origin must be the
 * vertex "p1-10".)
 *
 * @returns A random path through the state space graph.
 */
std::vector<Edge> NimLearner::playRandomGame() const {
  vector<Edge> path;
  /* Your code goes here! */
  // if flag is true, it is currently player 1's turn in the game
  bool flag = true;
  Vertex source = startingVertex_;
  int randNum = 0;
  while(true){
    randNum = (rand() % 2) + 1;
    std::string currVertex = g_.getVertexLabel(source);
    int currNum = std::stoi(currVertex.substr(currVertex.find('-') + 1));
    // check that you don't overshoot the last Vertex
    if(randNum > currNum){
      --randNum;
    }
    Vertex destination = g_.getVertexByLabel(flag ? "p2-" + to_string(currNum - randNum) :
        "p1-"  + to_string(currNum - randNum));
    path.push_back(g_.getEdge(source , destination));
    // update which player's turn it is
    flag = !flag;
    // update the "iterator" vertex
    source = destination;
    if(g_.getVertexLabel(source) == "p1-0" || g_.getVertexLabel(source) == "p2-0"){
      break;
    }
  }
  return path;
}

/*
 * Updates the edge weights on the graph based on a path through the state
 * tree.
 *
 * If the `path` has Player 1 winning (eg: the last vertex in the path goes
 * to Player 2 with no tokens remaining, or "p2-0", meaning that Player 1
 * took the last token), then all choices made by Player 1 (edges where
 * Player 1 is the source vertex) are rewarded by increasing the edge weight
 * by 1 and all choices made by Player 2 are punished by changing the edge
 * weight by -1.
 *
 * Likewise, if the `path` has Player 2 winning, Player 2 choices are
 * rewarded and Player 1 choices are punished.
 *
 * @param path A path through the a game of Nim to learn.
 */
void NimLearner::updateEdgeWeights(const std::vector<Edge> & path) {
 /* Your code goes here! */
 // determine who won the game
 bool flag; // true if p1 wins
 std::string finalVertexLabel = g_.getVertexLabel(path.back().dest);
 if(finalVertexLabel == "p1-0"){
    flag = false;
 } else if (finalVertexLabel == "p2-0"){
    flag = true;
 } else {
   std::cout << "The last edge in the game path returns :" << path.front().getLabel() << std::endl;
   exit(1);
 }
 for(Edge e : path){
   std::string destName = g_.getVertexLabel(e.dest);
   // if the destination vertex is p1-*, then this move was made by p2
   if(destName.substr(0,destName.find('-')) == "p1"){
     if(flag){ // if flag is true, p1 won the game and this edge should be "punished"
       g_.setEdgeWeight(e.source, e.dest, e.getWeight() - 1);
     } else { // p2 won the game and this edge should be "rewarded"
        g_.setEdgeWeight(e.source, e.dest, e.getWeight() + 1);
     }
   } else if (destName.substr(0,destName.find('-')) == "p2"){
     // if the destination vertex is p2-*, then this move was made by p1
     if(flag){ // if flag is true, p1 won the game and this edge should be "rewarded"
       g_.setEdgeWeight(e.source, e.dest, e.getWeight() + 1);
     } else { // if flag is false, p2 won the game and this edge should be "punished"
       g_.setEdgeWeight(e.source, e.dest, e.getWeight() - 1);
     }
   }
 }

}

/**
 * Label the edges as "WIN" or "LOSE" based on a threshold.
 */
void NimLearner::labelEdgesFromThreshold(int threshold) {
  for (const Vertex & v : g_.getVertices()) {
    for (const Vertex & w : g_.getAdjacent(v)) {
      int weight = g_.getEdgeWeight(v, w);

      // Label all edges with positve weights as "WINPATH"
      if (weight > threshold)           { g_.setEdgeLabel(v, w, "WIN"); }
      else if (weight < -1 * threshold) { g_.setEdgeLabel(v, w, "LOSE"); }
    }
  }
}

/**
 * Returns a constant reference to the state space graph.
 *
 * @returns A constant reference to the state space graph.
 */
const Graph & NimLearner::getGraph() const {
  return g_;
}
