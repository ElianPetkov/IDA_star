#include <iostream>
#include <cmath>
#include "tuple"
#include "HelpingFunc.h"
#include <queue>
#include <cstring>
#include <vector>
#include <string>

using namespace std;
int N,M,squareSize;//N is the size of the board -1 , M is the position of the empty element
tuple<int,int> desiredPositions[100];//sorted positions of numbers from 1 to N , represented as tuple(x,y)

struct Table
{
public:
    int table[6][6];
    int zeroXPosition;
    int zeroYPosition;
    char previousMove[7];
    int heuristic;

    bool operator==( const Table& t ) const
    {
        for( int i = 0; i < squareSize; i++ )
            for( int j = 0; j < squareSize; j++ )
                if( table[i][j] != t.table[i][j] )
                    return false;
        return true;
    }


    int getInversionsCount()//return the inversions of the current table , using createInversionTable() . One table is solvable if the inversion in even number.
    {
        int inv_count = 0;
        createInversionTable();

        for (int i = 0; i < N; i++)
            for (int j = i + 1; j < N; j++)
                if (this->inversionTable[i] > this->inversionTable[j])
                    inv_count++;

        return inv_count;
    }

    int calculateHeuristicForTable() //calculate the heuristic for the table
    {
        int heuristic = 0;
        for(int i = 0; i<squareSize; i++)
            for(int j=0; j<squareSize; j++)
            {
                if(this->table[i][j]!=0)
                {
                    tuple<int,int> position=takeDesirePosition(desiredPositions,this->table[i][j]);
                    heuristic=heuristic+manhattanDistance(i,get<0>(position),j,get<1>(position));
                }
            }
        this->heuristic=heuristic;
        return heuristic;
    }

    void printTable()
    {
        for(int i =0 ; i<squareSize ; i++)
        {
            for(int j=0 ; j<squareSize; j++)
            {
                cout<<table[i][j]<<" ";
            }
            cout<<endl;
        }
    }
private:
    int inversionTable[100];
    /*initialize the inversion array which we use to check if the table is solvable*/
    void createInversionTable()
    {
        int inversionTableIterator=0;
        for(int i=0; i<squareSize; i++)
        {
            for(int j=0; j<squareSize; j++)
                if(this->table[i][j]!=0)
                {
                    this->inversionTable[inversionTableIterator]=this->table[i][j];
                    inversionTableIterator++;
                }
                else
                    continue;
        }
    }
} startTable;

void checkIsItValidSuccessor(Table &successor,char* direction,vector<Table> &successors)
{
    if(isOddTableSolvable(squareSize,successor))
    {
        strcpy(successor.previousMove,direction);
        successors.push_back(successor);
    }
    else if(isEvenTableSolvable(squareSize,successor))
    {
        strcpy(successor.previousMove,direction);
        successors.push_back(successor);
    }
}
void findHeuristicFromPrevTableByXIndex(Table &currTable,Table &candidateSucc)
{
    tuple<int,int> oldPosition=takeDesirePosition(desiredPositions,currTable.table[candidateSucc.zeroXPosition][currTable.zeroYPosition]);
    tuple<int,int> newPosition=takeDesirePosition(desiredPositions,candidateSucc.table[currTable.zeroXPosition][candidateSucc.zeroYPosition]);

    candidateSucc.heuristic = currTable.heuristic
                              -manhattanDistance(candidateSucc.zeroXPosition,get<0>(oldPosition),currTable.zeroYPosition,get<1>(oldPosition))
                              +manhattanDistance(currTable.zeroXPosition,get<0>(newPosition),candidateSucc.zeroYPosition,get<1>(newPosition));
}
void findHeuristicFromPrevTableByYIndex(Table &currTable, Table &candidateSucc)
{
    tuple<int,int> oldPosition=takeDesirePosition(desiredPositions,currTable.table[currTable.zeroXPosition][candidateSucc.zeroYPosition]);
    tuple<int,int> newPosition=takeDesirePosition(desiredPositions,candidateSucc.table[candidateSucc.zeroXPosition][currTable.zeroYPosition]);

    candidateSucc.heuristic = currTable.heuristic
                              -manhattanDistance(candidateSucc.zeroXPosition,get<0>(oldPosition),candidateSucc.zeroYPosition,get<1>(oldPosition))
                              +manhattanDistance(currTable.zeroXPosition,get<0>(newPosition),currTable.zeroYPosition,get<1>(newPosition));
}

void findSuc(Table &currTable,vector<Table> &successors)
{
    if(currTable.zeroXPosition - 1 >=0)
    {
        Table candidateSucc=currTable;
        swap(candidateSucc.table[currTable.zeroXPosition][candidateSucc.zeroYPosition],candidateSucc.table[currTable.zeroXPosition-1][candidateSucc.zeroYPosition]);
        candidateSucc.zeroXPosition-=1;

        findHeuristicFromPrevTableByXIndex(currTable,candidateSucc);
        checkIsItValidSuccessor(candidateSucc,"down",successors);

    }
    if(currTable.zeroXPosition + 1 <=squareSize - 1)
    {
        Table candidateSucc=currTable;
        swap(candidateSucc.table[currTable.zeroXPosition][candidateSucc.zeroYPosition],candidateSucc.table[currTable.zeroXPosition+1][candidateSucc.zeroYPosition]);
        candidateSucc.zeroXPosition+=1;

        findHeuristicFromPrevTableByXIndex(currTable,candidateSucc);
        checkIsItValidSuccessor(candidateSucc,"up",successors);

    }

    if(currTable.zeroYPosition -1 >= 0)
    {
        Table candidateSucc=currTable;
        swap(candidateSucc.table[currTable.zeroXPosition][candidateSucc.zeroYPosition],candidateSucc.table[currTable.zeroXPosition][candidateSucc.zeroYPosition-1]);
        candidateSucc.zeroYPosition-=1;


        findHeuristicFromPrevTableByYIndex(currTable,candidateSucc);
        checkIsItValidSuccessor(candidateSucc,"right",successors);

    }
    if(currTable.zeroYPosition + 1 <=squareSize-1)
    {
        Table candidateSucc=currTable;
        swap(candidateSucc.table[currTable.zeroXPosition][candidateSucc.zeroYPosition],candidateSucc.table[currTable.zeroXPosition][candidateSucc.zeroYPosition+1]);
        candidateSucc.zeroYPosition+=1;

        findHeuristicFromPrevTableByYIndex(currTable,candidateSucc);
        checkIsItValidSuccessor(candidateSucc,"left",successors);
    }

}
int search(int g,int threshold,vector<Table> &visited,vector<string> &path)
{

    Table currTable = visited.back();
    path.push_back(currTable.previousMove);

    int h=currTable.heuristic;
    int f=g+h;

    if(f > threshold)
    {
        return f;
    }

    if(h == 0)
    {
        int length=path.size();
        cout<<length-1<<endl;
        for(string move :path)
            cout<<move<<endl;
        return 0;
    }

    int min=9999999;
    vector<Table> successors;
    findSuc(currTable,successors);
    for(Table successor :successors)
    {
        if(!hasVectorMember(successor,visited))
        {
            visited.push_back(successor);
            int candidateThreshold =search(g+1,threshold,visited,path);

            if(candidateThreshold == 0)
                return 0;

            if(candidateThreshold<min)
                min=candidateThreshold;

            path.pop_back();
            visited.pop_back();
        }
    }
    return min;
}



void IDA_star()
{

    startTable.calculateHeuristicForTable();
    int threshold=startTable.heuristic;

    vector<Table> visited;
    visited.push_back(startTable);
    vector<string> path;

    while(1)
    {
        int nextThreshold=search(0,threshold,visited,path);
        path.pop_back();
        if(nextThreshold==0)
            return;
        if(nextThreshold==9999999)
        {
            cout<<"Unsolvable table :(";
            return;
        }
        threshold = nextThreshold;

    }
}

int startGame()//read data from the console initialize the start table
{
    cin>>N;
    cin>>M;
    squareSize = (int)sqrt(N+1);

    makeArrayOfTupplesForDesiredPositions(N,desiredPositions);

    if(M == -1)
    {
        startTable.zeroXPosition=squareSize-1;
        startTable.zeroYPosition=squareSize-1;
        startTable.table[startTable.zeroXPosition][startTable.zeroYPosition]=0;
    }
    else
    {
        tuple<int,int> zeroPosition = takeDesirePosition(desiredPositions,M);
        startTable.zeroXPosition = get<0>(zeroPosition);
        startTable.zeroYPosition = get<1>(zeroPosition);
        startTable.table[startTable.zeroXPosition][startTable.zeroYPosition]=0;
    }

    for(int i=0; i<squareSize; i++)
        for(int j=0; j<squareSize ; j++)
        {
            if(i==startTable.zeroXPosition && j==startTable.zeroYPosition)
                continue;
            else
                cin>>startTable.table[i][j];
        }

    IDA_star();
}
int main()
{
    startGame();
}
