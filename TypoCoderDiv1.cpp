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
#include <queue>
using namespace std;
/* http://community.topcoder.com/stat?c=problem_statement&pm=10543 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define REP(i,n) for(int i=0;i<(n);++i)
#define LOOP(i,v,n) for(i=v;i<(n);++i)
#define LL long long
#define memSet(m, v) memset(m, v, sizeof(m))
int dp[3000][50][2];

class TypoCoderDiv1
{

    int solve(vector<int> d, int x, int brown, int i)
    {
        if (i == d.size()) return 0;
        
        if (dp[x][i][brown] == -1)
        {
            if (brown == 1)
            {
                long rank = x + d[i - 1];
                
                if (rank - d[i] < 2200)
                {
                    dp[x][i][brown] = 1 + solve(d, std::max( 0, (int)(rank - d[i]) ), 0, i + 1);
                }
            }
            else {
                long rank = x - d[i];
                dp[x][i][brown] = solve(d, std::max(0, (int)rank), 0, i + 1);
                
                rank = x + d[i];
                int isBrown = rank >= 2200 ? 1 : 0;
                
                dp[x][i][brown] = std::max(dp[x][i][brown], isBrown + solve(d, isBrown == 1 ? x : (int)rank, isBrown, i + 1));
            }
        }
        
        return dp[x][i][brown];
    }
public:
    int getmax(vector<int> D, int X)
    {
        memSet(dp, -1);
        
        return solve(D, X, 0, 0);
    }
};

void TEST(vector<int> D, int X, int expected)
{
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    TypoCoderDiv1 typoCoderDiv1;
    int result = typoCoderDiv1.getmax(D, X);
    
    assert( result == expected );
    
    end = clock();
    cpu_time_used = ((double) (end - start));
    cout<<"Time taken : "<<cpu_time_used<<endl;
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
    int a[] = {100,200,100,1,1};
    TEST(convert(a, SIZEOFARRAY(a)), 2000, 3);
}

void Test2()
{
    int a[] = {0,0,0,0,0};
    TEST(convert(a, SIZEOFARRAY(a)), 2199, 0);
}

void Test3()
{
    int a[] = {2048,1024,5012,256,128,64,32,16,8,4,2,1,0};
    TEST(convert(a, SIZEOFARRAY(a)), 2199, 0);
}

void Test4()
{
    int a[] = {61,666,512,229,618,419,757,217,458,883,23,932,547,679,565,767,513,798,870,31,379,294,929,892,173,127,796,353,913,115,802,803,948,592,959,127,501,319,140,694,851,189,924,590,790,3,669,541,342,272};
    TEST(convert(a, SIZEOFARRAY(a)), 1223, 29);
}

void Test5()
{
    int a[] = {1000000000,1000000000,10000,100000,2202,1};
    TEST(convert(a, SIZEOFARRAY(a)), 1000, 4);
}

void Test6()
{
    int a[] = {34,64,43,14,58,30,2,16,90,58,35,55,46,24,14,73,96,13,9,42,64,36,89,42,42,64,52,68,53,76,52,54,23,88,32,52,28,96,70,32,26,3,23,78,47,23,54,30,86,32};
    TEST(convert(a, SIZEOFARRAY(a)), 1328, 20);
}

void Test7()
{
    int a[] = {90000,80000,70000,60000,50000,40000,30000,20000,10000};
    TEST(convert(a, SIZEOFARRAY(a)), 0, 1);
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
    cout<<"success";
    return 0;
}
