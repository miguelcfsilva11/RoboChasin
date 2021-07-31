#ifndef MOVEMENT_H
#define MOVEMENT_H

struct Movement
{
    int dRow, dCol; // displacement, taking into account the chosen movement
};

struct Position
{
    int row, col;
};

#endif