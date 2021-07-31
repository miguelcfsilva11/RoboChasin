#include "maze.h"


Maze::Maze()
{
    this->numRows = 10;
    this->numCols = 10;

}

/******************************************************************************/

Maze::Maze(int numRows, int numCols){

    this->numRows = numRows;
    this->numCols = numCols;

}

/******************************************************************************/

void Maze::addPost(const Post &post){
    
    Posts.push_back(post);

}

/******************************************************************************/

void Maze::addGate(const Gate &gate){
    
    Gates.push_back(gate);

}

/******************************************************************************/

int Maze::getnumRows() const{

    return numRows;
}

/******************************************************************************/

int Maze::getnumCols() const{

    return numCols;
}

/******************************************************************************/

vector<Post> Maze::getPosts() const{
    return Posts;
}

/******************************************************************************/

vector<Gate> Maze::getGates() const{
    return Gates;
}