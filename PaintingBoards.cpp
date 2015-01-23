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
/* http://community.topcoder.com/stat?c=problem_statement&pm=8516&rd=11124 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define REP(i,n) for(int i=0;i<(n);++i)
#define LOOP(i,v,n) for(int i=v;i<(n);++i)
#define LL long long
#define memSet(m, v) memset(m, v, sizeof(m))


class PaintingBoards
{
    int mBoardLen;
    int mPainters;
    map<pair<LL, int>, double> memo;
    double solve(int l, LL mask, const vector<int> &boardLength, const vector<int> &painterSpeed)
    {
        if (mask == ((1 << mBoardLen) - 1)) return 0;
        
        map<pair<LL, int>, double>::iterator itr = memo.find(make_pair(mask, l));
        
        if (itr != memo.end()) return itr->second;
        
        
        double ret = INT_MAX;
        
        REP(i, mPainters)
        {
            if ((l & (1 << i)) != 0) continue;
            
            double min = 0.0;
            double temp = 0.0;
            REP(j, mBoardLen)
            {
                if ((mask & (1 << j)) != 0)
                {
                    min = 0.0;
                    continue;
                }
                
                min += (1.0 / (double)painterSpeed[i]) * boardLength[j];
                LL m = 1;
                
                if (j != 0)
                    m = ((LL)1 << (j + 1)) - 1;
                
                temp = std::max(min, solve(j | (1 << i), mask | m, boardLength, painterSpeed));
                ret = std::min(ret, temp);

            }
            
        }
        memo.insert(make_pair(make_pair(mask, l), ret));
        
        return ret;
    }
public:
    double minimalTime(vector<int> boardLength, vector<int> painterSpeed)
    {

        mBoardLen = (int)boardLength.size();
        mPainters = (int)painterSpeed.size();
        
        return solve(0, 0, boardLength, painterSpeed);
    }
};

void TEST(vector<int> boardLength, vector<int> painterSpeed, double expected)
{
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    PaintingBoards paintingBoards;
    double result = paintingBoards.minimalTime(boardLength, painterSpeed);
    
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
    int boardLength[] = {5,3,2};
    int painterSpeed[] = {2,3,5};
    TEST(convert(boardLength, SIZEOFARRAY(boardLength)),
         convert(painterSpeed, SIZEOFARRAY(painterSpeed)), 1.0);
}

void Test2()
{
    int boardLength[] = {1,2,1,4,2,1,1};
    int painterSpeed[] = {1,2,3};
    TEST(convert(boardLength, SIZEOFARRAY(boardLength)),
         convert(painterSpeed, SIZEOFARRAY(painterSpeed)), 2.0);
}

void Test3()
{
    int boardLength[] = {3,3,20};
    int painterSpeed[] = {9,1};
    TEST(convert(boardLength, SIZEOFARRAY(boardLength)),
         convert(painterSpeed, SIZEOFARRAY(painterSpeed)), 2.888888888888889);
}

void Test4()
{
    int boardLength[] = {40, 46, 82, 89, 33, 46, 3, 50, 95,
        81, 69, 40, 94, 93, 90, 98, 17, 34,
        45, 18, 93, 28, 43, 38, 35};
    int painterSpeed[] = {49, 51, 35, 27, 48, 36, 54, 10};
    TEST(convert(boardLength, SIZEOFARRAY(boardLength)),
         convert(painterSpeed, SIZEOFARRAY(painterSpeed)), 4.686274509803922);
}

void Test5()
{
}

void Test6()
{
}

void Test7()
{
}

void Test8()
{
}

void Test9()
{
}

void Test10()
{
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
