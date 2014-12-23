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
using namespace std;
/* http://community.topcoder.com/stat?c=problem_statement&pm=4668&rd=7227 */
#define SIZEOFSTRINGARRAY(s) sizeof(s)/sizeof(s[0])
class AlphabetCount
{
    int dx[8] = {-1, 0, 1, 1, 1, 0, -1, -1};
    int dy[8] = {-1, 1, 1, 0, -1, -1, 1, 0};
    
public:
   	long count(vector<string> grid, int length);
};
long dp[50][50];

long AlphabetCount::count(vector<string> grid, int length)
{
    
    size_t h = grid.size();
    size_t w = grid[0].length();
    long max = INT_MIN;

    for (char alpha = 'A'; alpha < 'Z'; ++alpha) {
        long res = INT_MIN;
        if (alpha + (length - 1) > 'Z') break;
        memset(dp, 0, sizeof(dp));
        for (char curChar = alpha; curChar < alpha + length && curChar <= 'Z'; ++curChar) {
            long temp = 0;

            for (size_t i = 0; i < h; ++i) {
                for (size_t j = 0; j < w; ++j) {
                    if (curChar == 'A')
                    {
                        dp[i][j] = grid[i][j] == 'A' ? 1 : 0;
                        temp += dp[i][j];
                    }
                    else if (grid[i][j] == curChar) {
                        for (size_t x = 0; x < 8; ++x) {
                            int dX = (int)i + dx[x];
                            int dY = (int)j + dy[x];

                            if (dX >= 0 && dX < h && dY >= 0 && dY < w && grid[dX][dY] == curChar - 1)
                            {
                                if (!dp[dX][dY]) dp[dX][dY] = 1;
                                
                                dp[i][j] += dp[dX][dY];
                            }
                        }
                        temp += dp[i][j];
                    }
                }
                if(temp > 0)
                    res = temp;
            }
        }
        max = std::max(res, max);
    }

    /*for (size_t i = 0; i < h; ++i) {
        for (size_t j = 0; j < w; ++j) {
            cout<<dp[i][j]<<" ";
        }
        cout<<endl;
    }*/
    return std::min(max, (long)1000000000);
}

void TEST(vector<string> grid, int length, long expected)
{
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    AlphabetCount alphabetCount;
    
    long result = alphabetCount.count(grid, length);
    
    assert( result == expected );
    
    end = clock();
    cpu_time_used = ((double) (end - start));
    cout<<"Time taken : "<<cpu_time_used<<endl;
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

void Test1()
{
    string test[] = { "ABC",
        "CBZ",
        "CZC",
        "BZZ",
        "ZAA" };
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 3, 7);
}

void Test2()
{
    string test[] = { "AAAA",
        "AAAA",
        "AAAA" };
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 1, 12);
}

void Test3()
{
    string test[] = { "ABAB",
        "BABA",
        "ABAB",
        "BABA" };
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 2, 24);
}

void Test4()
{
    string test[] = { "ABAB",
        "BABA",
        "ABAB",
        "BABA" };
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 2, 24);
}

void Test5()
{
    string test[] = { "HIJKLMNOPQZZZONMLKHIDZYQR",
        "GYXWVUTSRASTZZPSTUJGECPXS",
        "FZABCDEFARQPUQRAAAVWFBOWT",
        "EONMJIHGAJMNOVAAAAAYXANUV",
        "DCBLKDEFIEKLEDWAAAZFGHMLK",
        "UVAZYBCGHFDFCAYXNPQZEDIJA",
        "TSWXAKLZGCZBGZIJOMZRUTCBZ",
        "RQPONMJIHBAZZHZZKLZZSVWXY" };
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 26, 7);
}

void Test6()
{
    string test[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 26, 1000000000);
}

void Test7()
{
    string test[] = { "CZC",
        "ZBZ",
        "AZA" };
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 3, 4);
}

void Test8()
{
    string test[] = { "BDBCBACABDDCCADCBDDCBDDDBCCCCABACADDDCCCBADDDBADCA",
        "DCBBBACBDBACCADABCCAABACDBADBCBBABACBCADADCBDABBBD" };
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 4, 20);
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
    cout<<"success";
    
    getchar();
    return 0;
}
