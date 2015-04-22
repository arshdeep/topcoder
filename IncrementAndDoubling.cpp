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
/* http://community.topcoder.com/stat?c=problem_solution&cr=23084185&rd=15708&pm=12790 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define REP(i,n) for(int i=0;i<(n);++i)
#define LOOP(i,v,n) for(i=v;i<(n);++i)
#define LL long long
#define memSet(m, v) memset(m, v, sizeof(m))

class IncrementAndDoubling
{

public:
    int getMin(vector<int> desiredArray)
    {
        int res= 0;
        for (size_t i = 0, size = desiredArray.size();
             i < size; ++i)
        {
            int num = desiredArray[i];
            
            res += __builtin_popcount(num);
        }
        
        int max = *(std::max_element(desiredArray.begin(), desiredArray.end()));
        
        res += ((sizeof(int) * 8) - __builtin_clz(max)) - 1;
        
        return res;
    }
};

void TEST(vector<int> D, int expected)
{
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    IncrementAndDoubling incrementAndDoubling;
    int result = incrementAndDoubling.getMin(D);
    
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
    int a[] = {2, 1};
    TEST(convert(a, SIZEOFARRAY(a)), 3);
}

void Test2()
{
    int a[] = {16, 16, 16};
    TEST(convert(a, SIZEOFARRAY(a)), 7);
}

void Test3()
{
    int a[] = {100};
    TEST(convert(a, SIZEOFARRAY(a)), 9);
}

void Test4()
{
    int a[] = {0, 0, 1, 0, 1};
    TEST(convert(a, SIZEOFARRAY(a)), 2);
}

void Test5()
{
    int a[] = {123, 234, 345, 456, 567, 789};
    TEST(convert(a, SIZEOFARRAY(a)), 40);
}

void Test6()
{
    int a[] = {7,5,8,1,8,6,6,5,3,5,5,2,8,9,9,4,6,9,4,4,1,9,9,2,8,4,7,4,8,8,6,3,9,4,3,4,5,1,9,8,3,8,3,7,9,3,8,4,4,7};
    TEST(convert(a, SIZEOFARRAY(a)), 84);
}

void Test7()
{
    int a[] = 	{685, 655, 114, 407, 212, 7, 161, 524, 200, 298, 142, 591, 407, 551, 260, 312, 894, 758, 936, 705, 822, 660, 652, 624, 69, 122, 932, 970, 911, 51, 598, 239, 827, 124, 974, 505, 926, 500, 969, 530, 413, 981, 509, 92, 555, 161, 278, 259, 886, 381};
    TEST(convert(a, SIZEOFARRAY(a)), 264);
}

void Test8()
{
    int a[] = 	{862, 933, 642, 85, 742, 504, 954, 702, 368, 717, 319, 559, 497, 960, 413, 141, 81, 914, 422, 894, 541, 166, 177, 725, 271, 821, 553, 271, 714, 113, 845, 879, 154, 786, 866, 661, 290, 290, 536, 965, 691, 471, 882, 956, 379, 81, 555, 617, 728, 611};
    TEST(convert(a, SIZEOFARRAY(a)), 270);
}

void Test9()
{
    int a[] = 	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    TEST(convert(a, SIZEOFARRAY(a)), 0);
}

void Test10()
{
    int a[] = {959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959, 959};
    TEST(convert(a, SIZEOFARRAY(a)), 459);
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
    cout<<"success"<<endl;
    return 0;
}
