#ifndef GAME_H
#define GAME_H

#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <map>

#include "maze.h"
#include "robot.h"
#include "player.h"
#include "movement.h"
#include "input.h"


using namespace std;

class Game {
public:

    /**
     * Class Constructor
     *
     * @param filename A string that holds information on which maze should be loaded
     */
    Game(const string &filename);


    /**
     * Main game loop: while the user is alive,
     * keep asking for input that represents the
     * direction the user wants to move to.
     *
     * @return true if the player wins
     * @return false if the player loses
     */
    bool play();


    /**
     * Inspects whether the position the player 
     * desires to move to is occupied by either a 
     * dead robot or a non-electrified fence.
     *
     * @param playerMove Movement struct that represents the direction the user is trying to move to
     *
     * @return true if the player moves to a valid spot, even when causing his death
     * @return false if he moves to the place of one of the objects above
     */
    bool validMove(Movement playerMove);


    /**
     * Compares the player's position to the location
     * of the maze's exit gate, and checks whether he
     * has reached it or not.
     *
     * @return true if the player has reached the gate
     * @return false if otherwise
     */
    bool reachedGate();

    /**
     * The interface constructor, creates
     * the window and the renderer that'll be
     * used for the game graphics and visuals
     * 
     * @param title The window's title
     * @param xpos The window's position on the x-axis
     * @param ypos The window's position on the y-axis
     * @param width The window's width
     * @param height The window's height
     * @param fullscreen Command to run the window in fullscreen
     * 
     * @return
     */
    void initInterface(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    /**
     * Event handler, method that looks
     * for the user's response and decisions
     * throughout the gameplay
     * 
     * @return
     */
    void handleEvents();

    /**
     * Updates and renders the game objects
     * onto the screen after the user's move
     *
     * @return
     */
    void updateRender();

    /**
    * Renders the map
    * 
    * @return
    */
    void drawMap();

    /**
    * Destroys the window and the renderer
    * tied to it, quitting the application
    * afterwards.
    * 
    * @return
    */
    void clean();

    /**
     * Checks whether the engine is
     * running as it should, returning the
     * boolean that holds that information
     * 
     * @return true if the interface is running
     * @return false if otherwise
     */
    bool running();


private:

    /**
     * Checks if an given robot has collided with any fence
     * there is left on the maze, causing his death.
     *
     * @param robot A functioning robot there is still on the maze
     * @param Posts A Post object that is present in the maze
     *
     * @return true if it collides with any of them
     * @return false if otherwise
     */
    bool collide(Robot &robot, Post& Post);

    /**
     * Checks if the player has collided with any fence
     * there is left on the maze, causing his death.
     *
     * @param player The human there is on the maze
     * @param Posts A vector of Post objects that are present in the maze
     *
     * @return true if he collides with any of them
     * @return false if otherwise
     */
    bool collide(Player &player, vector<Post>& Posts); 


    /**
     * Checks if an given robot has collided with the player
     *
     * @param robot A functioning robot there is still on the maze
     * @param player The human there is on the maze
     *
     * @return true if the robot has collided with the human
     * @return false if otherwise
     */
    bool collide(Robot &robot, Player& player);


    /**
     * Checks if an given robot has collided with another robot
     *
     * @param firstRobot A functioning robot there is still on the maze
     * @param secondRobot A functioning robot there is still on the maze
     *
     * @return true if the robot has collided with the robot
     * @return false if otherwise
     */
    bool collide(Robot &firstRobot, Robot &secondRobot);

    bool isRunning;
    bool moveMade;

    Maze maze;
    Player player;
    vector<Robot> robots; 
 
    SDL_Window* window; // Game Window
    SDL_Renderer* renderer; // Renderer tied to the entities
};

#endif