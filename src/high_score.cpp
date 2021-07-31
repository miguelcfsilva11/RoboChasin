#include "high_score.h"

using namespace std;


highScores::highScores()
{
    vector<highScoreEntry> highScoreEntrys;
}

/******************************************************************************/

bool highScores::read(const string &filename)
{
    ifstream highScoresFile("levels/" + filename);

    if(!highScoresFile.good())
        return false;

    string line;
    highScoreEntry highScore;
    
    int i = 0;
    while(getline(highScoresFile, line))
    {
        if(i < 2)
        {
            i++;
            continue;
        }

        size_t separator = line.find('-');
        highScore.name = line.substr(0, separator);
        highScore.time = stoi(line.substr(separator + 2));
        highScoreEntrys.push_back(highScore);

    }

    return true;
}

/******************************************************************************/

void highScores::write(const string &filename) const
{
    ofstream highScoresFile("levels/" + filename);
    highScoresFile << "Player         - Time\n----------------------\n";
    for(size_t i = 0; i < highScoreEntrys.size(); i++)
    {
        highScoresFile << highScoreEntrys[i].name << "- " << highScoreEntrys[i].time << endl;
    }
    highScoresFile.close();
}

/******************************************************************************/

void highScores::add(const string &name, const int &time)
{
    highScoreEntrys.push_back({ name, time });
}

/******************************************************************************/

void highScores::sortHighScores()
{
    bool swap = true;
    highScoreEntry tmp;
    while(swap)
    {
        swap = false;
        for(size_t i = 0; i < highScoreEntrys.size() - 1; i++)
        {
            if(highScoreEntrys[i].time > highScoreEntrys[i + 1].time)
            {
                swap = true;
                tmp = highScoreEntrys[i];
                highScoreEntrys[i] = highScoreEntrys[i + 1];
                highScoreEntrys[i + 1] = tmp;
            }
        }
    }
}

string highScores::getName() const
{
    string playerName;
    bool validName = false;
    size_t nameLength;
    const size_t MAX_NAME_LENGTH = 15;

    while(!validName)
    {
        cout << "Enter your name (up to 15 characters): ";
        getline(cin, playerName);
        int nonAsciiChars = 0;
        nameLength = 0;
        bool hyphenChar = false;

        // Count the length of the given name,
        // taking into account the possibility
        // of existing non-ascii characters.

        for(int i = 0; playerName[i]; i++)
        {
            if(int(playerName[i]) >= 0)
                nameLength++;
            else
                nonAsciiChars++;
            if(playerName[i] == '-')
            {
                hyphenChar = true;
                break;
            }
        }
        nameLength += nonAsciiChars / 2;

        // Check if the given name is whithin
        // the allowed name length and if it does
        // not contain any ' - '. We don't allow
        // the use of this character because it
        // would interfere with the reading of
        // the high scores file.

        if(nameLength > MAX_NAME_LENGTH)
        {
            cout << "Please enter a shorter name!" << endl;
            continue;
        }
        if(hyphenChar)
        {
            cout << "Please don't enter a name with a '-'" << endl;
            continue;
        }
        validName = true;
    }

    return playerName + string(MAX_NAME_LENGTH - nameLength, ' ');
}
    
/******************************************************************************/

void highScores::handle(const string &filename, const int &time)
{
    read(filename);
    add(getName(), time);
    sortHighScores();
    write(filename);
}