#include <algorithm>
#include <string>
#include <iostream>
#include <vector>
#include <cassert>
#include <time.h>
#include <map>
#include <list>
#include <queue>
using namespace std;
/* http://topcoder.bgcoder.com/print.php?id=180 */

#define SIZEOFINTARRAY(a) sizeof(a)/sizeof(int)
#define SIZEOFSTRINGARRAY(s) sizeof(s)/sizeof(s[0])
#define MAXELEMENTS 20

struct node
{
    int player1X;
    int player1Y;
    int player2X;
    int player2Y;
    int steps;
    node() : player1X(0), player1Y(0), player2X(0), player2Y(0), steps(0) {}
    node(int x1, int y1, int x2, int y2, int steps) : player1X(x1), player1Y(y1), player2X(x2), player2Y(y2), steps(steps) {}
};

class PathFinding
{
private:
    bool visited[MAXELEMENTS][MAXELEMENTS][MAXELEMENTS][MAXELEMENTS];

    queue<node> bfs;
    void pushToQueue(node n);
    struct node getStart(vector<string> board);
public:
    int minTurns(vector<string> board);
};

void PathFinding::pushToQueue(node n)
{
    if (visited[n.player1X][n.player1Y][n.player2X][n.player2Y]) {
        return;
    }
    bfs.push(n);
    //cout<<" "<< n.player1X<< " "<< n.player1Y<<" "<< n.player2X<< " "<< n.player2Y<<endl;
    visited[n.player1X][n.player1Y][n.player2X][n.player2Y] = 1;
}

struct node PathFinding::getStart(vector<string> board)
{
    queue< pair<int, int> > bfs;
    size_t height = board.size();
    size_t width = board[0].length();
    
    struct node start;
    bool visited2[MAXELEMENTS][MAXELEMENTS];

    memset(visited2, 0, sizeof(visited2));
    
    bfs.push(make_pair(0, 0));
    visited2[0][0] = true;
    bool foundA = false;
    bool foundB = false;
    
    while (!bfs.empty()) {
        pair<int, int> n = bfs.front();
        bfs.pop();
        if (n.first >= 0 && n.first < height
            && n.second >= 0 && n.second < width)
        {
            if (board[n.first][n.second] == 'A')
            {
                start.player1X = n.first;
                start.player1Y = n.second;
                foundA = true;
            }
            if (board[n.first][n.second] == 'B')
            {
                start.player2X = n.first;
                start.player2Y = n.second;
                foundB = true;
            }

            if (foundA && foundB) break;
            

            pair<int, int> right = make_pair(n.first + 1, n.second);
            pair<int, int> down = make_pair(n.first, n.second + 1);
            pair<int, int> diagonal = make_pair(n.first + 1, n.second + 1);
            
            if (!visited2[right.first][right.second])
            {
                bfs.push(right);
                visited2[right.first][right.second] = true;
            }
            if (!visited2[down.first][down.second])
            {
                bfs.push(down);
                visited2[down.first][down.second] = true;
            }
            if (!visited2[diagonal.first][diagonal.second])
            {
                bfs.push(diagonal);
                visited2[diagonal.first][diagonal.second] = true;
            }
        }
    }
    assert(foundA && foundB);
    return start;
}

int PathFinding::minTurns(vector<string> board)
{
    memset(visited, 0, sizeof(visited));
    size_t height = board.size();
    size_t width = board[0].length();
    
    node start = getStart(board);
    pushToQueue(start);

    while (!bfs.empty()) {
        node front = bfs.front();
        bfs.pop();
        //cout<<" "<< front.player1X<< " "<< front.player1Y<<" "<< front.player2X<< " "<< front.player2Y<<endl;
        if (front.player2X == start.player1X && front.player2Y == start.player1Y
                && front.player1X == start.player2X && front.player1Y == start.player2Y) {
            return front.steps;
        }
        
        for (int deltaX1 = -1; deltaX1 <= 1; ++deltaX1) {
            for (int deltaY1 = -1; deltaY1 <= 1; ++deltaY1) {
                for (int deltaX2 = -1; deltaX2 <= 1; ++deltaX2) {
                    for (int deltaY2 = -1; deltaY2 <= 1; ++deltaY2) {
                        int dX1 = front.player1X + deltaX1;
                        int dY1 = front.player1Y + deltaY1;
                        int dX2 = front.player2X + deltaX2;
                        int dY2 = front.player2Y + deltaY2;
                        
                        if ((front.player2X == dX1 && front.player2Y == dY1
                                && front.player1X == dX2 && front.player1Y == dY2) || ( dX1 == dX2 && dY1 == dY2)) {
                            continue;
                        }
                        
                        if (dX1 >= 0 && dX1 < height && dY1 >= 0 && dY1 < width
                            && dX2 >= 0 && dX2 < height && dY2 >= 0 && dY2 < width)
                        {
                            if (board[dX1][dY1] != 'X' && board[dX2][dY2] != 'X')
                                pushToQueue(node(dX1, dY1, dX2, dY2, front.steps + 1));
                        }
                    }
                }
            }
        }
    }
    return -1;
}

vector<string> convert(string *list, int n)
{
    vector<string> ret;
    
    for (int i = 0; i< n; ++i)
    {
        ret.push_back(list[i]);
    }
    
    return ret;
}

void TEST(vector<string> board, int expected)
{
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    PathFinding pathFinding;
    
    long result = pathFinding.minTurns(board);
    
    assert( result == expected );
    
    end = clock();
    cpu_time_used = ((double) (end - start));
    cout<<"Time taken : "<<cpu_time_used<<endl;
}

void Test1()
{
    string test[] = {"....",
        ".A..",
        "..B.",
        "...."};
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 2);
}

void Test2()
{
    string test[] = {"XXXXXXXXX",
        "A...X...B",
        "XXXXXXXXX"};
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), -1);
}

void Test3()
{
    string test[] = {"XXXXXXXXX",
        "A.......B",
        "XXXXXXXXX"};
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), -1);
}

void Test4()
{
    string test[] = {"XXXXXXXXX",
        "A.......B",
        "XXXX.XXXX"};
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 8);
}

void Test5()
{
    string test[] = {"...A.XXXXX.....",
        ".....XXXXX.....",
        "...............",
        ".....XXXXX.B...",
        ".....XXXXX....."};
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 13);
}

void Test6()
{
    string test[] = {"AB.................X",
        "XXXXXXXXXXXXXXXXXXX.",
        "X..................X",
        ".XXXXXXXXXXXXXXXXXXX",
        "X..................X",
        "XXXXXXXXXXXXXXXXXXX.",
        "X..................X",
        ".XXXXXXXXXXXXXXXXXXX",
        "X..................X",
        "XXXXXXXXXXXXXXXXXXX.",
        "X..................X",
        ".XXXXXXXXXXXXXXXXXXX",
        "X..................X",
        "XXXXXXXXXXXXXXXXXXX.",
        "X..................X",
        ".XXXXXXXXXXXXXXXXXXX",
        "X..................X",
        "XXXXXXXXXXXXXXXXXXX.",
        "...................X",
        ".XXXXXXXXXXXXXXXXXXX"};
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 379);
}
void Test7()
{
    string test[] = {"..X.....XX........X", ".XX.....X.XXXXXXXX.", ".X......X.X.....X.X", ".X......X.X....X.X.", ".X......X.X...X.X..", "X.X.....X.X..X.X...", ".X.X....X.X.X.X....", "..X.X...X.XX.X.....", "...X.X..X.X.X......", "....X.X.XAXX.X.....", ".....X.XXBX.X.X....", "......X.X.X..X.X...", ".....X.XX.X...X.X..", "....X.X.X.X....X.X.", "...X.X..X.X.....X.X", "..X.X...X.X......X.", ".X.X....X.X......X.", "X.X.....X.X......X.", ".XXXXXXXX.X.....XX.", "X........XX.....X.."};
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 39);
}

void Test8()
{
    string test[] = {"X.XXX.X....XX.X.", "..XXXX..X..XX.XX", "X...X..XX.......", ".X.....XX.XXX.XX", "AXXX.XXXX.X..X.X", "..X....X.X....X.", "............XX.X", ".XX.XXXX...XXX..", ".X....XX..XX..X.", ".XX.X..XXX.X..XX", "....XX.XX.X.XXX.", ".XX..XXX..XXXX..", "XX...X.X..X..XX.", ".X.XX.XX..X...X.", "...XXX.XX....XXX", "X.X...XX.X...X..", "X.X.X.XX....XX.B", "...XXX...X...XX.", "..XX....XXX.X.XX", "......X..X......"};
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), -1);
}

void Test9()
{
    string test[] = {"..X.X.XX..X.X.", "AXXX.XXXX.XXXX", "X..XXXXX.X.XX.", ".X.XX.X.X..XXX", "..XXXXXX..X.XB", "X.XXXXX.XXXX.X", "XX.X...XX.XXXX", ".X..XXXXXX.XX.", "XXXXXXX.X.XXXX", "..XXXX..X.X.XX", ".XX.X.X..XX.XX", "X...XX........", "XXXXX.X.X.X..X", "..XX..XX..XXX.", "X.X.X.XX.....X", "X....X.X..XX..", "..X.X.XXX.XX.X", "..XXXX.XX.XX.X", "XXXXX..X......", "X.X.X.XX.X.X.."}	;
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 21);
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
    Test8();
    Test9();
    return 0;
}
