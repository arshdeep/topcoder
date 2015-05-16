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
/* http://community.topcoder.com/stat?c=problem_statement&pm=11835 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define REP(i,n) for(int i=0;i<(n);++i)
#define LOOP(i,v,n) for(int i=v;i<(n);++i)
#define LL long long
#define memSet(m, v) memset(m, v, sizeof(m))
LL INF = 51 * 1000000000000L;

class Stamp
{
public:
	int getMinimumCost(string desiredColor, int stampCost, int pushCost)
	{
		int n = desiredColor.length();
		int res = INT_MAX;
		LOOP(L, 1, n + 1)
		{
			vector<int> cost(n + 1, INT_MAX);
			cost[0] = 0;
			REP(i, n)
			{
				int color = 7;
				LOOP(j, i, n)
				{
					char ch = desiredColor[j];
					switch (ch)
					{
						case 'R':
							color &= 1;
							break;
						case 'G':
							color &= 2;
							break;
						case 'B':
							color &= (1<<2);
						case '*':
							color &= 7;
					}
					if (!color) break;
					int seg = j - i + 1;
					if (seg < L) continue;
					if (cost[i] != INT_MAX)
						cost[j + 1] = std::min(cost[j + 1], cost[i] +  ((seg + L - 1) / L) * pushCost);
				}
			}
			if (cost[n] != INT_MAX)
				res = std::min(res, cost[n] + L * stampCost);
		}
		return res;
	}
};

void TEST(string desiredColor, int stampCost, int pushCost, int expected)
{
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    Stamp stamp;
	int result = stamp.getMinimumCost(desiredColor, stampCost, pushCost);
    
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
	TEST("R*RR*GG", 10, 58, 204);
	TEST("RRGGBB", 1, 1, 5);
	TEST("R**GB*", 1, 1, 5);
	TEST("BRRB", 2, 7, 30);
	TEST("*B**B**B*BB*G*BBB**B**B*", 5, 2, 33);
	TEST("*R*RG*G*GR*RGG*G*GGR***RR*GG", 7, 1, 30);
	TEST("**************************************************", 100000, 100000, 1500000);
	TEST("RGBRGBRGBRGBRGBRGBRGBRGBRGBRGBRGBRGBRGBRGBRGBRGBRG", 100000, 100000, 5100000);
	TEST(	"RR****BBBB****R***R*R*G**GR**BGG**B*GB*GRRBG**G", 76223, 87458, 4186749);
	TEST(	"RR****BBBB****R***R*R*G**GR**BGG**B*GB*GRRBG**G", 76223, 87458, 4186749);
	TEST("BB*R*G*BBR*GRR*", 39197, 70687		,1099502	);
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
    cout<<"success"<<endl;
	getchar();
    return 0;
}
