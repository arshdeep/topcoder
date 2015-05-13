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
/* http://community.topcoder.com/stat?c=problem_statement&pm=12351&rd=15187 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define REP(i,n) for(int i=0;i<(n);++i)
#define LOOP(i,v,n) for(i=v;i<(n);++i)
#define LL long long
#define memSet(m, v) memset(m, v, sizeof(m))

class MonstersValley2
{
    int N;
    vector<int> dread;
    vector<int> price;
    
    int go(int index, long curDread)
    {
        if (index == N - 1)
            return curDread > dread[index] ? 0 : price[index];
        
        if (curDread > dread[index])
            return std::min(go(index + 1, curDread + dread[index]) + price[index],
                           go(index + 1, curDread));
        else
             return go(index + 1, curDread + dread[index]) + price[index];
    }
public:
    int minimumPrice(vector<int> dread, vector<int> price)
    {
        N = dread.size();
        this->dread = dread;
        this->price = price;
        
        return go (0, 0);
    }
};

void TEST(vector<int> dread, vector<int> price, int expected)
{
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    MonstersValley2 monstersValley2;
    int result = monstersValley2.minimumPrice(dread, price);
    
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
    int a[] = {8, 5, 10};
    int b[] = {1, 1, 2};

    TEST(convert(a, SIZEOFARRAY(a)),convert(b, SIZEOFARRAY(b)), 2);
}

void Test2()
{
    int a[] = {1, 2, 4, 1000000000};
    
    int b[] = {1, 1, 1, 2};
    
    TEST(convert(a, SIZEOFARRAY(a)),convert(b, SIZEOFARRAY(b)), 5);
}

void Test3()
{
    int a[] = {200, 107, 105, 206, 307, 400};
    int b[] = {1, 2, 1, 1, 1, 2};
    
    TEST(convert(a, SIZEOFARRAY(a)),convert(b, SIZEOFARRAY(b)), 2);
}

void Test4()
{
    int a[] = {5216, 12512, 613, 1256, 66, 17202, 30000, 23512, 2125, 33333};
    
    int b[] = {2, 2, 1, 1, 1, 1, 2, 1, 2, 1};
    
    TEST(convert(a, SIZEOFARRAY(a)),convert(b, SIZEOFARRAY(b)), 5);
}

void Test5()
{
    int a[] = {1, 2, 4, 6, 16, 19, 64, 105, 256, 464, 1024, 1463, 4096, 4515, 16384, 21445, 65536, 68543, 262144, 479277};
    
    int b[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
    
    TEST(convert(a, SIZEOFARRAY(a)),convert(b, SIZEOFARRAY(b)), 28);
}

void Test6()
{
    int a[] = {117426, 417423, 6529466, 13572907, 20582830, 3355360, 56555551, 6642336, 186172523, 186804224, 15277581, 59444651, 254457068, 310528342, 423416841, 782884539, 743464702, 369610019, 643257039};
    
    int b[] = {1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 2, 1, 2, 2, 2, 2, 1};
    
    TEST(convert(a, SIZEOFARRAY(a)),convert(b, SIZEOFARRAY(b)), 10);
}

void Test7()
{
    int a[] = {138742, 878514, 852494, 542526, 953090, 618335, 834947, 451187, 818761, 498817, 701160, 996792, 845435, 145660, 183611, 150459, 635733, 718307};
    
    int b[] = {2, 1, 1, 1, 2, 1, 1, 1, 2, 2, 1, 2, 1, 1, 2, 2, 2, 2};
    
    TEST(convert(a, SIZEOFARRAY(a)),convert(b, SIZEOFARRAY(b)), 3);
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
    cout<<"success"<<endl;
    return 0;
}
