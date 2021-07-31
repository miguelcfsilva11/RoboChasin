#include <iostream>
#include <limits>
#include <climits>
#include <string>

using namespace std;


/**
 * Ask the user for an integer.
 * 
 * @return INT_MAX if the input was invalid.
 * @return INT_MIN to exit the program.
 */
int getInt();


/**
 * Ask the user for an integer between 2 numbers.
 * 
 * @param LowerBound sets the interval lowerbound that the user must respect
 * @param LowerBound sets the interval lowerbound that the user must respect
 *
 * @return INT_MAX if the input was invalid.
 * @return INT_MIN to exit the program.
 */
int getInt(const int &lowerBound, const int &upperBound);


/**
 * Ask the user for a character.
 *
 * @return 0 to exit the program.
 * @return 1 if the input was invalid.
 */
char getChar();