#ifndef HIGHSCORE_H
#define HIGHSCORE_H

using namespace std;

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

struct highScoreEntry {

    string name;
    int time;
};

class highScores {
public:

    /**
     * Default constructor for highScores class.
     */
    highScores();


    /**
     * Go though the whole process of handling
     * a new high score entry.

     * @param filename The name of the file to read from.
     * @param time The time it took the user to beat the game.
     */
    void handle(const string &filename, const int &time);


private:

    vector<highScoreEntry> highScoreEntrys;

    /**
     * Sort a vector of high score entrys in
     * ascending order to time.
     */
    void sortHighScores();


    /**
     * Read the high scores from a file
     * and add them to a vector.
     *
     * @param filename The name of the file to read from.
     *
     * @return true if the file exists, false otherwise.
     */
    bool read(const string &filename);


    /**
     * Write a vector of high score entrys to a file.
     *
     * @param filename The name of the file to write to.
     */
    void write(const string &filename) const;


    /**
     * Add a new high score entry to a vector.
     *
     * @param name The name of the use who beat the game.
     * @param time The time it took the user to beat the game.
     */
    void add(const string &name, const int &time);


    /**
     * Asks the user to give input on his name
     * name when recording his highscore.
     */
    string getName() const;
};

#endif