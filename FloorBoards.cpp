#include <iostream>
#include <cstdio>
#include <vector>
#include <cassert>
#include <sstream>
#include <set>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <time.h>
#include <stdlib.h>
using namespace std;
/* http://community.topcoder.com/stat?c=problem_statement&pm=6095&rd=9917 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define REP(i,n) for(int i=0;i<(n);++i)
#define LOOP(i,v,n) for(i=v;i<(n);++i)
#define LL long long
#define memSet(m, v) memset(m, v, sizeof(m))

int memo[1<<10][10][10];

class FloorBoards
{
    size_t mWidth;
    size_t mHeight;
    
    int solve(int i, int j, int mask, const vector<string> &mat)
    {
        if (i == mHeight) return 0;
        int &memv = memo[mask][i][j];
        
        if (memv != -1) return memv;
        
        if (mat[i][j] == '#')
            return solve(i + (j + 1) / mWidth, (j + 1) % mWidth, mask & ~(1 << j), mat);

        int vertical = solve(i + (j + 1) / mWidth, (j + 1) % mWidth, mask | (1 << j), mat);
        
        if ((mask & (1 << j)) == 0)
            ++vertical;
        int horizontal = solve(i + (j + 1) / mWidth, (j + 1) % mWidth, mask & ~(1 << j), mat);
        
        if (j == 0 || mat[i][j - 1] == '#' || (mask & (1 << (j - 1))) != 0)
            ++horizontal;
        
        memv = std::min(horizontal, vertical);
        
        return memv;
    }
public:
    int howMany(vector<string> mat)
    {
        mWidth = mat[0].length();
        mHeight = mat.size();
        
        memSet(memo, -1);
        return solve(0, 0, 0, mat);
    }
};

void TEST(vector<string> mat, int expected)
{
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    FloorBoards floorBoards;
    int result = floorBoards.howMany(mat);
    
    assert(result == expected);
    
    end = clock();
    cpu_time_used = ((double)(end - start));
    cout << "Time taken : " << cpu_time_used << endl;
}

template <class T>
vector<T> convert(T *list, int n)
{
    vector<T> ret;
    
    for (int i = 0; i< n; ++i)
    {
        ret.push_back(list[i]);
    }
    
    return ret;
}

void Test1()
{
    string test[] = { "....."
        , "....."
        , "....."
        , "....."
        , "....." };
    TEST(convert(test, SIZEOFARRAY(test)), 5);
}

void Test2()
{
    string test[] = { "......."
        , ".#..##."
        , ".#....."
        , ".#####."
        , ".##..#."
        , "....###" };
    TEST(convert(test, SIZEOFARRAY(test)), 7);
}

void Test3()
{
    string test[] = { "####"
        , "####"
        , "####"
        , "####" };
    TEST(convert(test, SIZEOFARRAY(test)), 0);
}

void Test4()
{
    string test[] = { "...#.."
        , "##...."
        , "#.#..."
        , ".#...."
        , "..#..."
        , "..#..#" }
    ;
    TEST(convert(test, SIZEOFARRAY(test)), 9);
}

void Test5()
{
    string test[] = { ".#...."
        , "..#..."
        , ".....#"
        , "..##.."
        , "......"
        , ".#..#." };
    TEST(convert(test, SIZEOFARRAY(test)), 9);
}

void Test6()
{
    string test[] = {"..........", ".....#..#.", "...#...#.#", ".#....##.#", "#.........", "..##..#...", "...###..#.", "#..#.....#", "#..##..#..", "..##......"};
    TEST(convert(test, SIZEOFARRAY(test)), 22);
}

void Test7()
{
    string test[] = 	{"......#..#", "..###.....", "......#.#.", "#..#.#...#", "..##..##..", "#.........", ".#.#.###..", "..##.#.#..", ".........#", ".....#..##"};
    TEST(convert(test, SIZEOFARRAY(test)), 23);
}

void Test8()
{
    string test[] = {"###...#..#", "##.....#.#", "#.....#.#.", "....#..#..", ".#.#......", ".##....##.", "...#......", ".#..#.....", ".#......#.", "##....#..#"};
    TEST(convert(test, SIZEOFARRAY(test)), 21);
}

void Test9()
{
    string test[] = {"..#.......", ".#.....#..", "...#..#...", "#.##..#...", "...##..#..", ".##...#..#", "#......#..", ".#...#.#..", "##...#....", ".###.#..#."};
    TEST(convert(test, SIZEOFARRAY(test)), 24);
}

void Test10()
{
    string test[] = 	{".#..#..#..", "###.#.####", "##..#.....", "###.#.###.", "#...#..##.", "###.#.###.", "##..#...#.", "###.#.###.", "#......##.", "#########."};
    TEST(convert(test, SIZEOFARRAY(test)), 14);
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
    Test10();
    cout << "success";
    return 0;
}
