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

struct State
{
    int s;
    int c;
    int time;
    State(int chars = 0, int clip = 0, int t = 0) : s(chars), c(clip), time(t) {
    }
};
bool flag[2000][1000];
class EmoticonsDiv1
{

public:
    int printSmiles(int smiles)
    {
        memSet(flag, 0);
        queue<State> bfs;
        bfs.push(State(1, 0));
        
        while (!bfs.empty()) {
            State top = bfs.front();
            
            bfs.pop();
            if (flag[top.s][top.c]) continue;
            
            if (top.s == smiles)
                return top.time;
            
            flag[top.s][top.c] = true;
            // Copy
            if (top.s < smiles)
                bfs.push(State(top.s, top.s, top.time + 1));
            //Paste
            if (top.c > 0 && top.s + top.c < 2 * smiles)
                bfs.push(State(top.s + top.c, top.c, top.time + 1));
            
            // Delete
            if (top.s > 1)
                bfs.push(State(top.s - 1, top.c, top.time + 1));
            
        }
        return 0;
    }
};

void TEST(int smiles, int expected)
{
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    EmoticonsDiv1 emoticonsDiv1;
    int result = emoticonsDiv1.printSmiles(smiles);
    
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
    TEST(2, 2);
    TEST(4, 4);
    TEST(6, 5);
    TEST(18, 8);
    TEST(11, 8);
    TEST(100, 14);
    TEST(968, 20);
    TEST(509, 20);
    TEST(33, 11);
    TEST(510, 19);
    TEST(833, 22);
    TEST(1000, 21);
}

void Test2()
{

}

void Test3()
{

}

void Test4()
{

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
    cout<<"success";
    return 0;
}
