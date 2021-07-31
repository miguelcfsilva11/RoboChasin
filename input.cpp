#include "input.h"

using namespace std;

int getInt()
{
    int userInput;
    cin >> userInput;

    if(cin.fail())
    {
        if(cin.eof())
            return INT_MIN;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return INT_MAX;
    }
    else 
    {
        if(cin.peek() != '\n')
        {
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            return INT_MAX;
        }

        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        return userInput;
    }
}

/******************************************************************************/

int getInt(const int &lowerBound, const int &upperBound)
{
    int userInput = getInt();

    if(userInput >= lowerBound && userInput <= upperBound)
        return userInput;

    if(userInput == INT_MIN)
        return INT_MIN;

    return INT_MAX;
}

/******************************************************************************/

char getChar()
{
    char userInput;
    cin >> userInput;

    if(cin.fail())
    {
        if(cin.eof())
            return 0;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        return 1;
    }
    else 
    {
        if(cin.peek() != '\n')
        {
            cin.ignore(numeric_limits<streamsize>::max(),'\n');
            return 1;
        }

        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        return userInput;
    }    
}