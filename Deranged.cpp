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
/* http://community.topcoder.com/stat?c=problem_statement&pm=2013 */
#define SIZEOFSTRINGARRAY(s) sizeof(s)/sizeof(s[0])
#define REP(i,n) for(int i=0;i<(n);++i)
#define LOOP(i,v,n) for(i=v;i<(n);++i)
#define LL long long

LL memo[15][1<<15];

class Deranged {
    int mNum;
    LL rec(const vector <int> &nums, int index, LL mask)
    {
        if (index >= mNum) return 1;
        LL memov = memo[index][mask];
        
        if (memov != -1) return memov;
        
        LL derangements = 0;
        int j = 0;
        
        REP(i, mNum)
        {
            if ((mask & (1 << i)) != 0 || nums[i] == nums[index])
                continue;
            
            LOOP(j, 0, i)
            {
                if ((mask & (1 << j)) != 0)
                    continue;
                
                if (nums[i] == nums[j])
                    break;
            }
            
            if (i != j) continue;
            
            derangements += rec(nums, index + 1, mask | (1 << i));
        }
        memo[index][mask] = derangements;
        
        return derangements;
    }
public:
    LL numDerangements(vector <int> nums) {
        memset(memo, -1, sizeof(memo));
        mNum = (int)nums.size();
        assert(mNum <= 15);

        return rec(nums, 0, 0);
    }
};

void TEST(vector <int> nums, long long expected)
{
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    Deranged deranged;
    
    LL result = deranged.numDerangements(nums);
    
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
    int test[] = {1,1,2,2,3};
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 4);
}

void Test2()
{
    int test[] = {0,0,0,1,1,1};
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 1);
}

void Test3()
{
    int test[] = {0,0,0,1,1,1,1};
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 0);
}

void Test4()
{
    int test[] = {0,0,0,0,0,0,0,1,1,1,1,1,1,1,2};
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 14);
}

void Test5()
{
    int test[] = {0,5,4,2,3,6,6};
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 640);
}

void Test6()
{
    int test[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14};
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 481066515734);
}

void Test7()
{
    int test[] = {4, 5, 10, 3, 4, 1, 6, 3, 0, 9, 6, 11}	;
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 12563896);
}

void Test8()
{
    int test[] = {6, 4, 3, 0, 13, 3, 6, 0, 1, 0, 14, 5, 10, 12, 14};
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), 4053826542);
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
