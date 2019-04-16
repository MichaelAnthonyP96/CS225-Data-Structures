/* Your code here! */
#include "dsets.h"
#include "maze.h"
#include <queue>
#include <vector>
#include <iostream>
#include <sys/time.h>

//No parameter constructor for a cell in the maze
SquareMaze::cell::cell(){
	//initialize a cell as not visited with no bottom or right wall
	visited = false;
	bottomWall = true;
	rightWall = true;
}

//No parameter constructor. Creates an empty maze.
SquareMaze::SquareMaze(){

}

//destructor of the maze
SquareMaze::~SquareMaze(){
	clear();
}

//destructor helper function
void SquareMaze::clear(){
	//iterate over the array of cell array pointers to over arrays and delete them
	for(int i = 0; i < w; ++i){
		delete[] maze[i];
	}
	//delete the initial array of cell array pointers
	delete[] maze;
}

/*Makes a new SquareMaze of the given height and width.If this object already
 *represents a maze it will clear all the existing data before doing so. You
 *will start with a square grid (like graph paper) with the specified height and
 *width. You will select random walls to delete without creating a cycle, until
 *there are no more walls that could be deleted without creating a cycle. Do not
 *delete walls on the perimeter of the grid.
 *Hints: You only need to store 2 bits per square: the "down" and "right" walls.
 *The finished maze is always a tree of corridors.)
 *Parameters :
 *    width	The width of the SquareMaze (number of cells)
 *    height	The height of the SquareMaze (number of cells)
 */
void SquareMaze::makeMaze(int width, int height){

	DisjointSets sets;
	h = height;
	w = width;
	int totalCells = h * w;
	//seeding the random number generator as seen on stack over flow and piazza
	struct timeval time;
	gettimeofday(&time, NULL);
	srand((time.tv_sec * 1000) + (time.tv_usec / 1000));
	//creat totalCells number of disjoint sets
	sets.addelements(totalCells);
	//create array of cell pointers
	maze = new cell *[w];
	//initialize each cell pointer to an array of cells,
	//thus constructs a 2D array of cells
	for(int i = 0; i < w; ++i){
		maze[i] = new cell[h];
	}
	//not srand(NULL), can use rand() or gettimeofday according to piazza
	//possible global variable as seed to the generate two different mazes
	rand();
	int count = 0;
	int xPos = 0;
	int yPos = 0;
	//since we start in a cell, its totalCells-1
	//iterate over all cells
	while(count != (totalCells -1)){
		//get random places in the matrix and a random flag for whether to
		//remove the walls in the maze
		//rand is seeded correctly that we get different mazes each time we call make maze
		xPos = std::rand() % w;
		yPos = std::rand() % h;
		bool removeWall = std::rand() % 2;
		//check if its a valid yPos and removeWall is true
		if( (removeWall == false) && ( (yPos + 1) < h) ){
			//if the cell and the cell below it are not in the same set, union them,
			//remove wall, and increase count of visited cells
			if( (sets.find(h * xPos + yPos) ) != (sets.find(h * xPos + yPos + 1) ) ){
				count++;
				sets.setunion(sets.find(h * xPos + yPos), sets.find(h * xPos + yPos + 1) );
				maze[xPos][yPos].bottomWall = false;
			}
		}
		//check if its a valid xPos and removeWall is true
		else if((removeWall == true) && ((xPos + 1) < w) ){
			//if the cell and the cell to its right it are not in the same set, union them,
			//remove wall, and increase count of visited cells
			if( (sets.find(h * (xPos + 1) + yPos) ) != (sets.find(h * xPos + yPos) ) ){
				count++;
				sets.setunion(sets.find(h * (xPos + 1) + yPos), sets.find(h * xPos + yPos) );
				maze[xPos][yPos].rightWall = false;
			}
		}
	}
}


/*
 *This uses your representation of the maze to determine whether it is possible
 *to travel in the given direction from the square at coordinates (x,y).
 *For example, after makeMaze(2,2), the possible input coordinates will be
 *(0,0), (0,1), (1,0), and (1,1).
 *    dir = 0 represents a rightward step (+1 to the x coordinate)
 *    dir = 1 represents a downward step (+1 to the y coordinate)
 *    dir = 2 represents a leftward step (-1 to the x coordinate)
 *    dir = 3 represents an upward step (-1 to the y coordinate)
 *You can not step off of the maze or through a wall.
 *This function will be very helpful in solving the maze. It will also be used
 *by the grading program to verify that your maze is a tree that occupies the
 *whole grid, and to verify your maze solution. So make sure that this function
 *works!
 *Parameters :
 *    x	The x coordinate of the current cell
 *    y	The y coordinate of the current cell
 *    dir	The desired direction to move from the current cell
 *Returns :
 *    whether you can travel in the specified direction
 */
bool SquareMaze::canTravel(int x, int y, int dir) const{
	switch(dir){
		//move right
		case 0 :{
			//check if the cell's right wall is true, or if we are at the right end of the maze
			if( (x >= w-1) || (maze[x][y].rightWall == true) ) return false;
			else return true;
		}
		//move down
		case 1 :{
			//check if the cell's bottom wall is true, or if we are at the bottom end of the maze
			if( (y >= h-1) || (maze[x][y].bottomWall == true) ) return false;
			else return true;
		}
		//move left
		case 2 :{
			//check if the cell to the left's right wall is true, or if we are at the left end of the maze
			if( (x == 0) || (maze[x-1][y].rightWall == true) ) return false;
			else return true;
		}
		//move up
		case 3 :{
			//check if the cell above's bottom wall is true, or if we are at the top of the maze
			if( (y == 0) || (maze[x][y-1].bottomWall == true) ) return false;
			else return true;
		}
		default:{
			std::cout << "bad directional input" << std::endl;
			return false;
		}
	}
}

/*Sets whether or not the specified wall exists.
 *This function should be fast (constant time). You can assume that in grading
 *we will not make your maze a non-tree and then call one of the other member
 *functions. setWall should not prevent cycles from occurring, but should simply
 * set a wall to be present or not present. Our tests will call setWall to copy
 *a specific maze into your implementation.
 *Parameters :
 *    x	The x coordinate of the current cell
 *    y	The y coordinate of the current cell
 *    dir	Either 0 (right) or 1 (down), which specifies which wall to set (same
 * as the encoding explained in canTravel). You only need to support setting the
 * bottom and right walls of every square in the grid.
 *    exists	true if setting the wall to exist, false otherwise
 */
 void SquareMaze::setWall(int x, int y, int dir, bool exists){
 	//sets the rightWall to the exists values
 	if(dir == 0){
 		maze[x][y].rightWall = exists;
 	}
 	//sets the bottomWall to the exists value
 	else if(dir == 1){
 		maze[x][y].bottomWall = exists;
 	}
 }
/*
 *Solves this SquareMaze.
 *For each square on the bottom row (maximum y coordinate), there is a distance
 *from the origin (i.e. the top-left cell), which is defined as the length
 *(measured as a number of steps) of the only path through the maze from the
 *origin to that square.
 *Select the square in the bottom row with the largest distance from the origin
 *as the destination of the maze. solveMaze() returns the winning path from
 *the origin to the destination as a vector of integers, where each integer
 *represents the direction of a step, using the same encoding as in canTravel().
 *If multiple paths of maximum length exist, use the one with the destination
 *cell that has the smallest x value.
 * Hint: this function should run in time linear in the number of cells in the maze.
 *Returns
 *     a vector of directions taken to solve the maze
 */
 vector<int> SquareMaze::solveMaze(){
 	//mark all cells as not visited to begin with
 	for(int i = 0; i < h; ++i){
 		for(int j = 0; j < w; ++j){
 			maze[j][i].visited = false;
 		}
 	}
 	//vector of negative ones to store the previous cell for all cells to begin with
 	vector<int> previous(w * h, -1);
 	//vector of zero's to store the distance from the start for all cells to begin with
 	vector<int> distance(w * h, 0 );
 	//queue to perform a BFS
 	queue<int> q;
 	//push the starting cell to the queue
 	q.push(0);
 	//mark the first cell as visited
 	maze[0][0].visited = true;
 	//maze position markers
 	int current, x, y;
 	//stores the directions of the max path
 	vector<int> directions;
  //traverse the maze
 	while(!q.empty()){
 		//look at the front of the queue
 		current = q.front();
 		//pop off the front of the queue
 		q.pop();
 		//translate 1D vector to 2D coordinates
 		y = current / h;
 		x = current % h;
 		//if the right cell hasn't been visited and there is not a wall there
 		//then visit it
 		if( canTravel(x,y,0) && (maze[x+1][y].visited == false) ){
 			//mark the right cell as visited
 			maze[x + 1][y].visited = true;
 			//add the right cell to the queue
 			q.push(current + 1);
 			//distance of the right cell is the distance of the current distance + 1
 			distance[current + 1] = distance[current] + 1;
 			//save the right cell's previous as this cell
 			previous[current + 1] = current;
 		}
 		//if the bottom cell hasn't been visited and there is not a wall there
 		//then visit it
 		if( canTravel(x,y,1) && (maze[x][y+1].visited == false) ){
 			//mark the right cell as visited
 			maze[x][y+1].visited = true;
 			//add the right cell to the queue
 			q.push(current + h);
 			//distance of the right cell is the distance of the current + 1
 			distance[current + h] = distance[current] + 1;
 			//save the cell below's previous as this cell
 			previous[current + h] = current;
 		}
 		//if the left cell hasn't been visited and there is not a wall there
 		//then visit it
 		if( canTravel(x,y,2) && (maze[x-1][y].visited == false) ){
 			//mark the right cell as visited
 			maze[x-1][y].visited = true;
 			//add the right cell to the queue
 			q.push(current - 1);
 			//distance of the right cell is the distance of the current + 1
 			distance[current - 1] = distance[current] + 1;
 			//save the left cell's previous as this cell
 			previous[current - 1] = current;
 		}
 		//if the cell above hasn't been visited and there is not a wall there
 		//then visit it
 		if(canTravel(x,y,3) && (maze[x][y-1].visited == false) ){
 			//mark the right cell as visited
 			maze[x][y-1].visited = true;
 			//add the right cell to the queue
 			q.push(current - h);
 			//distance of the right cell is the distance of the current + 1
 			distance[current - h] = distance[current] + 1;
 			//save the above cell's previous as this cell
 			previous[current - h] = current;
 		}
 	}
 	//initialize max to the theoretical max distance through the maze
 	//find the longest distance in the maze
 	int max = (h * w) - w;
 	endY = h-1;
 	for(int i = 1; i < w; ++i){
 		if(distance[(w*h) - w + i] > distance[max]) {
 			max = ((w*h) - w + i);
 			endX = i;
 		}
 	}
 	//set the maze's max to the local maximum
 	this->max = max;
 	int traveler = max;
 	//back track through the maze
 	while(previous[traveler] != -1){
 		y = current % h;
 		x = current / h;
 		//if previous cell was to the right
 		if(previous[traveler] == traveler + 1){
 			//push the left direction to the front of the vector
 			directions.insert(directions.begin(),2);
 			//move the traveler to the left
 			traveler = traveler + 1;
 		}
 		//if previous cell was the cell below
 		if(previous[traveler] == traveler + h){
 			//push the up direction to the front of the vector
 			directions.insert(directions.begin(),3);
 			//move the traveler to the cell below
 			traveler = traveler + h;
 		}
 		//if previous cell was the cell to the left
 		if(previous[traveler] == traveler - 1){
 			//push the right direction to the front of the vector
 			directions.insert(directions.begin(),0);
 			//move the traveler to the left
 			traveler = traveler - 1;
 		}
 		//if previous cell was the cell above
 		if(previous[traveler] == traveler - h){
 			//push the down direction to the front of the vector
 			directions.insert(directions.begin(),1);
 			//move the traveler up
 			traveler = traveler - h;
 		}
 	}
 	return directions;
 }

/*
 *Draws the maze without the solution.
 * First, create a new PNG. Set the dimensions of the PNG to (width*10+1,
 *height*10+1). where height and width were the arguments to makeMaze. Blacken
 *the entire topmost row and leftmost column of pixels, except the entrance
 *(1,0) through (9,0). For each square in the maze, call its maze coordinates
 *(x,y). If the right wall exists, then blacken the pixels with coordinates
 *((x+1)*10,y*10+k) for k from 0 to 10. If the bottom wall exists, then blacken
 * the pixels with coordinates (x*10+k, (y+1)*10) for k from 0 to 10.
 *The resulting PNG will look like the sample image, except there will be no
 *exit from the maze and the red line will be missing.
 *Returns
 *   a PNG of the unsolved SquareMaze
 */
cs225::PNG* SquareMaze::drawMaze() const{
	//first create a new PNG
	cs225::PNG * mazePNG = new cs225::PNG();
	//resize the maze to the correct dimensions
	mazePNG->resize((w * 10) + 1,(h * 10) +1 );
	//build the top wall of the maze as black pixels
	for(int i = 0; i < ((h * 10) + 1); ++i){
		//example from mp1
		//HSLAPixel * pixelPtr = png.getPixel(i,j);
		cs225::HSLAPixel &topWall = mazePNG->getPixel(0,i);
		topWall.h = 0.0;
		topWall.s = 0.0;
		topWall.l = 0.0;
		topWall.a = 1.0;
	}
	//build the left wall of the maze as black pixels
	for(int j = 10; j < ((w * 10) + 1); ++j){
		cs225::HSLAPixel &leftWall = mazePNG->getPixel(j,0);
		leftWall.h = 0.0;
		leftWall.s = 0.0;
		leftWall.l = 0.0;
		leftWall.a = 1.0;
	}
	//traverse the maze cells
	for(int k = 0; k < h; ++k){
		for(int r = 0; r < w; ++r){
			if(maze[k][r].rightWall == true){
				//black out the right wall of the cell
				for(int g = 0; g <= 10; ++g){
					cs225::HSLAPixel &currentCellRight = mazePNG->getPixel((k+1)*10,(r * 10) + g);
					currentCellRight.h = 0.0;
					currentCellRight.s = 0.0;
					currentCellRight.l = 0.0;
					currentCellRight.a = 1.0;
				}
			}
			if(maze[k][r].bottomWall == true){
				//black out the bottom wall of the cell
				for(int g = 0; g <= 10; ++g){
					cs225::HSLAPixel &currentCellBottom = mazePNG->getPixel((k*10) + g,(r+1) * 10);
					currentCellBottom.h = 0.0;
					currentCellBottom.s = 0.0;
					currentCellBottom.l = 0.0;
					currentCellBottom.a = 1.0;
				}
			}
		}
	}
  	return mazePNG;
}

/*
 *This function calls drawMaze, then solveMaze; it modifies the PNG from drawMaze
 * to show the solution vector and the exit.
 *Start at pixel (5,5). Each direction in the solution vector corresponds to a
 *trail of 11 red pixels in the given direction. If the first step is downward,
 *color pixels (5,5) through (5,15) red. (Red is 0,1,0.5,1 in HSLA). Then if the
 *second step is right, color pixels (5,15) through (15,15) red. Then if the
 *third step is up, color pixels (15,15) through (15,5) red. Continue in this
 *manner until you get to the end of the solution vector, so that your output
 *looks analogous the above picture.
 *Make the exit by undoing the bottom wall of the destination square: call the
 *destination maze coordinates (x,y), and whiten the pixels with coordinates
 *(x*10+k, (y+1)*10) for k from 1 to 9.
 *Returns
 *  a PNG of the solved SquareMaze
 */
cs225::PNG* SquareMaze::drawMazeWithSolution(){
	//draws the maze
	cs225::PNG* solvedMaze = drawMaze();
	//solves the maze
	vector<int> solutionPath = solveMaze();
	//initialize the maze starting point
	int xPos = 5;
	int yPos = 5;
	for(size_t p = 0; p < solutionPath.size(); ++p){
		//path corresponds to the cell to the right
		if(solutionPath[p] == 0){
			//color in the next ten pixels to the right
			for(int r = 0; r < 11; ++r){
				cs225::HSLAPixel &cellRight = solvedMaze->getPixel(xPos + r,yPos);
				cellRight.h = 0.0;
				cellRight.s = 1.0;
				cellRight.l = 0.5;
				cellRight.a = 1.0;
			}
			//update the cell Position
			xPos = xPos + 10;
		}
		//path corresponds to the cell below
		else if(solutionPath[p] == 1){
			for(int r = 0; r < 11; ++r){
				cs225::HSLAPixel &cellBelow = solvedMaze->getPixel(xPos,yPos + r);
				cellBelow.h = 0.0;
				cellBelow.s = 1.0;
				cellBelow.l = 0.5;
				cellBelow.a = 1.0;
			}
			//update the cell Position
			yPos = yPos + 10;
		}
		//path corresponds to the cell to the left
		else if(solutionPath[p] == 2){
			//color in the next ten pixels to the left
			for(int r = 0; r < 11; ++r){
				cs225::HSLAPixel &cellLeft = solvedMaze->getPixel(xPos - r,yPos);
				cellLeft.h = 0.0;
				cellLeft.s = 1.0;
				cellLeft.l = 0.5;
				cellLeft.a = 1.0;
			}
			//update the cell Position
			xPos = xPos - 10;
		}
		//path corresponds to the cell above
		else if(solutionPath[p] == 3){
			//color in the next ten pixels above
			for(int r = 0; r < 11; ++r){
				cs225::HSLAPixel &cellAbove = solvedMaze->getPixel(xPos,yPos - r);
				cellAbove.h = 0.0;
				cellAbove.s = 1.0;
				cellAbove.l = 0.5;
				cellAbove.a = 1.0;
			}
			yPos = yPos - 10;
		}
	}
	//after going through all the directions, make the exit
	for(int k = 1; k <= 9; ++k){
		//(x*10+k, (y+1)*10) for k from 1 to 9
		cs225::HSLAPixel &exit = solvedMaze->getPixel((endX * 10) + k, (endY + 1) * 10);
		exit.h = 0.0;
		exit.s = 0.0;
		exit.l = 1.0;
		exit.a = 1.0;
	}
	return solvedMaze;
}

void SquareMaze::creativeAdjust(){
	//set all the walls for the left side of the Block I
	for(int i = 20; i < 80; ++i){
		for(int j = 0; j < 35; ++j){
			maze[j][i].rightWall = true;
			maze[j][i].bottomWall = true;
		}
	}
	//set all the wall for the right side of the Block I
	for(int i = 20; i < 80; ++i){
		for(int j = 65; j < 100; ++j){
			maze[j][i].rightWall = true;
			maze[j][i].bottomWall = true;
		}
	}

}

cs225::PNG* SquareMaze::drawCreativeMaze(){

	//draws the maze
	cs225::PNG* mazePNG = drawMaze();
	//resize the maze to the correct dimensions
	mazePNG->resize((w * 10) + 1,(h * 10) +1 );
	//build the top wall of the maze as black pixels
	for(int i = 0; i < ((h * 10) + 1); ++i){
		//example from mp1
		//HSLAPixel * pixelPtr = png.getPixel(i,j);
		cs225::HSLAPixel &topWall = mazePNG->getPixel(0,i);
		topWall.h = 0.0;
		topWall.s = 0.0;
		topWall.l = 0.0;
		topWall.a = 1.0;
	}
	//build the left wall of the maze as black pixels
	for(int j = 10; j < ((w * 10) + 1); ++j){
		cs225::HSLAPixel &leftWall = mazePNG->getPixel(j,0);
		leftWall.h = 0.0;
		leftWall.s = 0.0;
		leftWall.l = 0.0;
		leftWall.a = 1.0;
	}

	//color in the left side of the Block I as black
	for(int i = 200; i < 800; ++i){
		for(int j = 0; j < 350; ++j){
			cs225::HSLAPixel &leftWall = mazePNG->getPixel(j,i);
			leftWall.h = 0.0;
			leftWall.s = 0.0;
			leftWall.l = 0.0;
			leftWall.a = 1.0;
		}
	}
	//color in the right side of the Block I as black
	for(int i = 200; i < 800; ++i){
		for(int j = 650; j < 1000; ++j){
			cs225::HSLAPixel &leftWall = mazePNG->getPixel(j,i);
			leftWall.h = 0.0;
			leftWall.s = 0.0;
			leftWall.l = 0.0;
			leftWall.a = 1.0;
		}
	}
	//traverse the maze cells
	for(int k = 0; k < h; ++k){
		for(int r = 0; r < w; ++r){
			if(maze[k][r].rightWall == true){
				//black out the right wall of the cell
				for(int g = 0; g <= 10; ++g){
					cs225::HSLAPixel &currentCellRight = mazePNG->getPixel((k+1)*10,(r * 10) + g);
					currentCellRight.h = 0.0;
					currentCellRight.s = 0.0;
					currentCellRight.l = 0.0;
					currentCellRight.a = 1.0;
				}
			}
			if(maze[k][r].bottomWall == true){
				//black out the bottom wall of the cell
				for(int g = 0; g <= 10; ++g){
					cs225::HSLAPixel &currentCellBottom = mazePNG->getPixel((k*10) + g,(r+1) * 10);
					currentCellBottom.h = 0.0;
					currentCellBottom.s = 0.0;
					currentCellBottom.l = 0.0;
					currentCellBottom.a = 1.0;
				}
			}
		}
	}
  	return mazePNG;
}

//solves the creative Maze
std::vector<int> SquareMaze::solveCreativeMaze(){
	//mark all cells as not visited to begin with
 	for(int i = 0; i < h; ++i){
 		for(int j = 0; j < w; ++j){
 			maze[j][i].visited = false;
 		}
 	}
	//set the left side of the Block I as visited
	for(int i = 20; i < 80; ++i){
		for(int j = 0; j < 35; ++j){
			maze[j][i].visited = true;
		}
	}
	//set the right side of the Block I as visited
	for(int i = 20; i < 80; ++i){
		for(int j = 65; j < 100; ++j){
			maze[j][i].visited = true;
		}
	}

 	//vector of negative ones to store the previous cell for all cells to begin with
 	vector<int> previous(w * h, -1);
 	//vector of zero's to store the distance from the start for all cells to begin with
 	vector<int> distance(w * h, 0 );
 	//queue to perform a BFS
 	queue<int> q;
 	//push the starting cell to the queue
 	q.push(0);
 	//mark the first cell as visited
 	maze[0][0].visited = true;
 	//maze position markers
 	int current, x, y;
 	//stores the directions of the max path
 	vector<int> directions;
  //traverse the maze
 	while(!q.empty()){
 		//look at the front of the queue
 		current = q.front();
 		//pop off the front of the queue
 		q.pop();
 		//translate 1D vector to 2D coordinates
 		y = current / h;
 		x = current % h;
 		//if the right cell hasn't been visited and there is not a wall there
 		//then visit it
 		if( canTravel(x,y,0) && (maze[x+1][y].visited == false) ){
 			//mark the right cell as visited
 			maze[x + 1][y].visited = true;
 			//add the right cell to the queue
 			q.push(current + 1);
 			//distance of the right cell is the distance of the current distance + 1
 			distance[current + 1] = distance[current] + 1;
 			//save the right cell's previous as this cell
 			previous[current + 1] = current;
 		}
 		//if the bottom cell hasn't been visited and there is not a wall there
 		//then visit it
 		if( canTravel(x,y,1) && (maze[x][y+1].visited == false) ){
 			//mark the right cell as visited
 			maze[x][y+1].visited = true;
 			//add the right cell to the queue
 			q.push(current + h);
 			//distance of the right cell is the distance of the current + 1
 			distance[current + h] = distance[current] + 1;
 			//save the cell below's previous as this cell
 			previous[current + h] = current;
 		}
 		//if the left cell hasn't been visited and there is not a wall there
 		//then visit it
 		if( canTravel(x,y,2) && (maze[x-1][y].visited == false) ){
 			//mark the right cell as visited
 			maze[x-1][y].visited = true;
 			//add the right cell to the queue
 			q.push(current - 1);
 			//distance of the right cell is the distance of the current + 1
 			distance[current - 1] = distance[current] + 1;
 			//save the left cell's previous as this cell
 			previous[current - 1] = current;
 		}
 		//if the cell above hasn't been visited and there is not a wall there
 		//then visit it
 		if(canTravel(x,y,3) && (maze[x][y-1].visited == false) ){
 			//mark the right cell as visited
 			maze[x][y-1].visited = true;
 			//add the right cell to the queue
 			q.push(current - h);
 			//distance of the right cell is the distance of the current + 1
 			distance[current - h] = distance[current] + 1;
 			//save the above cell's previous as this cell
 			previous[current - h] = current;
 		}
 	}
 	//initialize max to the theoretical max distance through the maze
 	//find the longest distance in the maze
 	int max = (h * w) - w;
 	endY = h-1;
 	for(int i = 1; i < w; ++i){
 		if(distance[(w*h) - w + i] > distance[max]) {
 			max = ((w*h) - w + i);
 			endX = i;
 		}
 	}
 	//set the maze's max to the local maximum
 	this->max = max;
 	int traveler = max;
 	//back track through the maze
 	while(previous[traveler] != -1){
 		y = current % h;
 		x = current / h;
 		//if previous cell was to the right
 		if(previous[traveler] == traveler + 1){
 			//push the left direction to the front of the vector
 			directions.insert(directions.begin(),2);
 			//move the traveler to the left
 			traveler = traveler + 1;
 		}
 		//if previous cell was the cell below
 		if(previous[traveler] == traveler + h){
 			//push the up direction to the front of the vector
 			directions.insert(directions.begin(),3);
 			//move the traveler to the cell below
 			traveler = traveler + h;
 		}
 		//if previous cell was the cell to the left
 		if(previous[traveler] == traveler - 1){
 			//push the right direction to the front of the vector
 			directions.insert(directions.begin(),0);
 			//move the traveler to the left
 			traveler = traveler - 1;
 		}
 		//if previous cell was the cell above
 		if(previous[traveler] == traveler - h){
 			//push the down direction to the front of the vector
 			directions.insert(directions.begin(),1);
 			//move the traveler up
 			traveler = traveler - h;
 		}
 	}
 	return directions;
}
