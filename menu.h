#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <limits>
#include <string>
#include <fstream>

#include "input.h"

using namespace std;

class Menu {

public:

    /**
     * Default Menu constructor.
     */
    Menu();


    /**
     * Control the display of
     * all the menu sections
     * according to input given
     * by the user.
     *
     * @return true to close the game.
     * @return false to play the game.
     */
    bool menuLoop();


    /**
     * Asks the user for the number of the
     * maze that they want to play until
     * they enter a valid number.
     *
     * @return an empty string to exit the game.
     * @return the name of the maze file.
     */
    string selectMaze() const;
    
private:

    int currentScreen;
    enum menuScreens { MENU, RULES, PLAY, WINNERS };


    /**
     * Displays the current menu screen.
     *
     * @return true to exit the game, false otherwise.
     */
    bool displayScreen() const;

    /**
     * Clears the screen by outputting 100 new lines.
     */
    void clearScreen() const;

    /**
     * Changes the current menu screen.
     */
    void changeScreen(const int &newScreen);

    /**
     * Display the main menu screen.
     */
    void displayMenu() const;

    /**
     * Display the rules of the game.
     */
    void displayRules() const;


    /**
     * Display the winners of a given maze.
     *
     * @param winnersFile The name of the file containing the winners
     *
     * @return true to exit the game or false otherwise.
     */
    bool displayWinners(const string &winnersFile) const;


    /**
     * Prompts the user to choose
     * a number of a maze to display
     * the winners for.
     *
     * @return an empty string to exit the game.
     * @return the name of the winners file.
     */
    string askHighScores() const;
};

#endif