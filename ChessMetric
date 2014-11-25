#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <time.h>
#include <map>
using namespace std;
class ChessMetric
{
private:
    long memo[100][100][50];
    int dx[16] = {1, -1, 0, 0, -1, 1, -1, 1, 2, -2, -2, 2, 1, -1, 1, -1};
    int dy[16] = {0, 0, 1, -1, -1, 1, 1, -1, 1, -1, 1, -1, 2, -2, -2, 2};
    long howMany(int size, int startx, int starty, int endx, int endy, int numMoves);
    long howManyDP(int size, int startx, int starty, int endx, int endy, int numMoves);
public:
    ChessMetric()
    {
        memset(memo, -1, sizeof(memo));
    }
    long howMany(int size, int start[2], int end[2], int numMoves);
};

long ChessMetric::howManyDP(int size, int startx, int starty, int endx, int endy, int numMoves)
{
    memset(memo, 0, sizeof(memo));
    memo[startx][starty][0] = 1;

    for (int k = 1; k <= numMoves; ++k)
    {
        for (int x = 0; x < size; ++x)
         {
             for (int y = 0; y < size; ++y)
             {
                 for (int i = 0; i < 16; ++i)
                 {
                     int deltax = x + dx[i];
                     int deltay = y + dy[i];
                     if ((deltax >= 0 && deltax < size) && (deltay >= 0 && deltay < size))
                     {
                         long temp = memo[deltax][deltay][k - 1];
                         memo[x][y][k] +=temp;
                     }
                 }
             }
         }
     }
    
    return memo[endx][endy][numMoves];
}

long ChessMetric::howMany(int size, int startx, int starty, int endx, int endy, int numMoves)
{
    long maxMoves = 0;
    if (numMoves == 0)
    {
        return startx == endx && starty == endy ? 1 : 0;
    }
    else
    {
        long m = memo[startx][starty][numMoves];
        
        if (m != -1)
            return m;

        for (int i = 0; i < 16; ++i)
        {
            int deltax = startx + dx[i];
            int deltay = starty + dy[i];
            if ((deltax >= 0 && deltax < size) && (deltay >= 0 && deltay < size))
            {
                long temp = howMany(size, deltax, deltay, endx, endy, numMoves - 1);
                memo[deltax][deltay][numMoves - 1] = temp;
                maxMoves +=temp;
            }
        }
    }
    return maxMoves;
}

long ChessMetric::howMany(int size, int start[2], int end[2], int numMoves)
{
    
    return howManyDP( size,  start[0],  start[1],  end[0],  end[1],  numMoves);
}

void TEST(int size, int startA[2], int endA[2], int numMoves, long expected)
{
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    ChessMetric chessMetric;
    
    long result = chessMetric.howMany(size, startA, endA, numMoves);
    
    assert( result == expected );
    
    end = clock();
    cpu_time_used = ((double) (end - start));
    cout<<"Time taken : "<<cpu_time_used<<endl;
}

void Test1()
{
    int start[2] = {0,0};
    int end[2] = {1,0};
    TEST(3, start, end, 1, 1);
}

void Test2()
{
    int start[2] = {0,0};
    int end[2] = {1,2};
    TEST(3, start, end, 1, 1);
}

void Test3()
{
    int start[2] = {0,0};
    int end[2] = {0,0};
    TEST(3, start, end, 2, 5);
}

void Test4()
{
    int start[2] = {5,5};
    int end[2] = {9,9};
    TEST(10, start, end, 4, 133);
}
void Test5()
{
    int start[2] = {4,4};
    int end[2] = {4,4};
    TEST(8, start, end, 6, 246460);
}
void Test6()
{
    int start[2] = {3,7};
    int end[2] = {11,5};
    TEST(13, start, end, 4, 4);
}
void Test7()
{
    int start[2] = {0,0};
    int end[2] = {0,99};
    TEST(100, start, end, 50, 243097320072600);
}

int main()
{
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    Test7();
    return 0;
}
