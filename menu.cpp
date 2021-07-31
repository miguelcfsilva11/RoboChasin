#include "menu.h"

Menu::Menu()
{
    currentScreen = MENU;
}

/******************************************************************************/

void Menu::changeScreen(const int &newScreen)
{
    currentScreen = newScreen;
}

/******************************************************************************/

bool Menu::displayScreen() const
{
    if(currentScreen == MENU)
        displayMenu();
    else if(currentScreen == RULES)
        displayRules();
    else if(currentScreen == WINNERS)
    {
        if(displayWinners(askHighScores()))
            return true;
    }

    return false;
}

/******************************************************************************/

void Menu::clearScreen() const
{
    for(unsigned short i = 0; i < 10; i++)
    {
        cout << "\n\n\n\n\n\n\n\n\n\n";
    }
}

/******************************************************************************/

void Menu::displayMenu() const
{
    cout << "Welcome to Robots Game! Please select one of the options below.\n" << endl
         << "0) Exit." << endl
         << "1) Rules." << endl
         << "2) Play." << endl
         << "3) Winners." << endl;
}

/******************************************************************************/

void Menu::displayRules() const
{
    cout << "Welcome to the Rules section!" << endl
         << "(Hit ENTER to go back to the menu)\n" << endl
         << "-> When you select the option to play the game in the menu screen you will be prompted to choose wich level you want to play." << endl
         << "-> After choosing the level, you will be placed in a maze made up of high-voltage fences and posts." << endl
         << "-> Some posts are electrified ('*') and others are not ('+')." << endl
         << "-> There will also be some interceptor robots that will try to destroy you, be careful!" << endl
         << "-> If at any moment you touch the high-voltage fences and posts or the robots you lose the game." << endl
         << "-> Every time you move, each robot will also move one cell closer to you." << endl  
         << "-> In order to move you have to type Q, W, E, A, S, D, Z, X, or C." << endl
         << "-> There will be some exit gates (represented by 'O'), in order to win, you must reach one of this gates." << endl;
}

/******************************************************************************/

bool Menu::displayWinners(const string &winnersFile) const
{
    if(winnersFile == "")
        return true;

    clearScreen();
    int mazeNumber = stoi(winnersFile.substr(5, 2));

    cout << "Welcome to Maze " << mazeNumber <<  " winners section!" << endl
         << "(Hit ENTER to go back to the menu)\n" << endl;
    
    ifstream f(winnersFile);
    if(f.is_open())
        cout << f.rdbuf();
    f.close();
    cout << endl;

    return false;
}

/******************************************************************************/

string Menu::selectMaze() const
{
    bool mazeLoaded = false;
    int mazeNumber;
    string mazeFile;

    while(!mazeLoaded)
    {        
        cout << "Pick an existent maze: ";
        mazeNumber = getInt();

        if(mazeNumber == INT_MAX)
        {
            cout << "Pick a valid number, please!" << endl;
            continue;
        }

        if(mazeNumber == INT_MIN)
            return "";

        if(mazeNumber < 10)
            mazeFile = "levels/MAZE_0" + to_string(mazeNumber) + ".TXT";
        else
            mazeFile = "levels/MAZE_" + to_string(mazeNumber) + ".TXT";

        ifstream fin(mazeFile);
        if(!fin.good())
        {
            cout << "That maze doesn't exist!" << endl;
            continue;
        }

        mazeLoaded = true;
        fin.close();

    }

    return mazeFile;

}


/******************************************************************************/

string Menu::askHighScores() const
{

    string mazeFile;
    bool validFile = false;
    
    while(!validFile)
    {
        mazeFile = selectMaze();

        if(mazeFile == "")
            return "";

        ifstream fin("levels/" + mazeFile.substr(0, 7) + "_WINNERS.TXT");
        if(!fin.good())
        {
            cout << "There are no winners for that maze! Pick a valid one!" << endl;
            continue;
        }
        
        fin.close();
        validFile = true;
    }

    return "levels/" + mazeFile.substr(0, 7) + "_WINNERS.TXT";

}

/******************************************************************************/

bool Menu::menuLoop()
{
    while(true)
    {
        clearScreen();
        displayScreen();

        int userInput = getInt(0, 3);

        if(userInput == INT_MIN || userInput == 0)
            return true;

        if(userInput == INT_MAX)
            continue;

        else if(userInput == RULES || userInput == WINNERS)
        {
            changeScreen(userInput);
            clearScreen();
            if(displayScreen())
                return true;
            getchar();
        }
        else if(userInput == PLAY)
        {
            clearScreen();
            return false;
        }
        changeScreen(MENU);
    }
}