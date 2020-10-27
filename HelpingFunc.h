#ifndef HELPINGFUNC_H
#define HELPINGFUNC_H
#include <iostream>
#include <algorithm>
#include "tuple"
#include <vector>

using namespace std;
void makeArrayOfTupplesForDesiredPositions(int size,tuple<int,int> array[])//makes array of tuples where arr[0] contains the correct position of 1
{
    int squareSize = (int)sqrt(size+1);
    int arrayCounter=0;

    for(int i=0; i<squareSize ; i++)
        for(int j=0; j<squareSize; j++)
        {
            array[arrayCounter]=tuple<int,int> (i,j);
            arrayCounter++;
        }

}

tuple<int,int> takeDesirePosition(tuple<int,int> array[],int number)//returns the position of a element in 2D dimension as tuple(x,y)
{
    return array[number-1];
}

int manhattanDistance(int x, int x1, int y, int y2) // calculate the distance between (x,y) and (x1,x2)
{
    return abs(x-x1)+abs(y-y2);
}

template <typename T>
bool hasVectorMember(T &candidate, vector<T> &visited) // search for a table in a vector and change the table heuristic with the found table
{

    if (std::find(visited.begin(), visited.end(), candidate) != visited.end())
        return true;

    return false;

}

template <typename T>
/*  a board has an even number of inversions, it is solvable*/
bool isOddTableSolvable(int size , T &table)
{
    return (size%2) != 0 && (table.getInversionsCount() %2)==0;
}

/* n is even, an n-by-n board is solvable if and only if the number of inversions plus the row of the blank square is odd*/
template<typename T>
bool isEvenTableSolvable(int size,T &table)
{
    return size%2 == 0 && (table.getInversionsCount() + table.zeroXPosition) %2!=0;
}



#endif
