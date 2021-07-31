#ifndef MAZE_H
#define MAZE_H

#include "movement.h"
#include "post.h"
#include "gate.h"
#include <vector>

using namespace std;


class Maze {

public:


    /**
     * Class Default Constructor
     */
    Maze();

    /**
     * Class Constructor
     *
     * @param numRows Integer that represents the number of rows in the maze
     * @param numRows Integer that represents the number of cols in the maze
     */
    Maze(int numRows, int numCols);


    /**
     * Adds a post to the vector that stores them
     *
     * @param post Post object that must be added to the vector
     */
    void addPost(const Post &post);


    /**
     * Adds a gate to the vector that stores them
     *
     * @param gate Gate object that must be added to the vector
     */
    void addGate(const Gate &gate);

    
    int getnumRows() const;
    int getnumCols() const;
    vector<Post> getPosts() const;
    vector<Gate> getGates() const;

private:

    int numRows, numCols;
    vector<Post> Posts;
    vector<Gate> Gates;

};

#endif