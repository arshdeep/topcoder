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
LL INF = 51 * 1000000000000L;

class MonstersValley2
{
    int N;
    vector<LL> dread;
    vector<LL> price;
    
    LL go(int index, LL curDread)
    {
        if (index == N - 1)
            return curDread > dread[index] ? 0 : price[index];
        
        if (curDread > dread[index]) {
            LL t1 = go(index + 1, curDread + dread[index]) + price[index];
            LL t2 = go(index + 1, curDread);
			return t1 > t2 ? t2 :t1;
		}
        else
             return go(index + 1, curDread + dread[index]) + price[index];
    }
	bool printD(vector< vector<LL> > &dp, int index, LL cost, LL maxDread)
	{
		if (maxDread == 0) return true;
		for (int m = index; m <= N; ++m)
		{
			if (printD(dp, m + 1, cost, maxDread - dread[m - 1]))
			{
				cout<<m - 1<< " ";
				return true;
			}
		}
		return false;
	}

public:
    int minimumPrice(vector<LL> dread, vector<LL> price)
    {
        N = dread.size();
        this->dread = dread;
        this->price = price;

        vector< vector<LL> > dp( 2 * N + 1, vector<LL>(N + 1) );
		LL res = INF;
		for (int p = 0, size = 2 * N; p <= size; ++p)
		{
			for (int m = 1; m <= N; ++m)
			{
				dp[p][m] = -INF;
				if (p >= price[m - 1])
				{
					dp[p][m] = dp[p - price[m - 1]][m - 1] + dread[m - 1];
				}
				if (dp[p][m - 1] > dread[m - 1])
				{
					dp[p][m] = std::max(dp[p][m], dp[p][m - 1]);
				}
			}
			if (dp[p][N] >= 0 && res == INF)
				res = p;
		}
		printD(dp, 1, res, dp[res][N]);
		return res;
    }
};

void TEST(vector<LL> dread, vector<LL> price, int expected)
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
    LL a[] = {8, 5, 10};
    LL b[] = {1, 1, 2};

    TEST(convert(a, SIZEOFARRAY(a)),convert(b, SIZEOFARRAY(b)), 2);
}

void Test2()
{
    LL a[] = {1, 2, 4, 1000000000};
    LL b[] = {1, 1, 1, 2};
    
    TEST(convert(a, SIZEOFARRAY(a)),convert(b, SIZEOFARRAY(b)), 5);
}

void Test3()
{
    LL a[] = {200, 107, 105, 206, 307, 400};
    LL b[] = {1, 2, 1, 1, 1, 2};
    
    TEST(convert(a, SIZEOFARRAY(a)),convert(b, SIZEOFARRAY(b)), 2);
}

void Test4()
{
    LL a[] = {5216, 12512, 613, 1256, 66, 17202, 30000, 23512, 2125, 33333};
    
    LL b[] = {2, 2, 1, 1, 1, 1, 2, 1, 2, 1};
    
    TEST(convert(a, SIZEOFARRAY(a)),convert(b, SIZEOFARRAY(b)), 5);
}

void Test5()
{
    LL a[] = {1, 2, 4, 6, 16, 19, 64, 105, 256, 464, 1024, 1463, 4096, 4515, 16384, 21445, 65536, 68543, 262144, 479277};
    
    LL b[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
    
    TEST(convert(a, SIZEOFARRAY(a)),convert(b, SIZEOFARRAY(b)), 28);
}

void Test6()
{
    LL a[] = {117426, 417423, 6529466, 13572907, 20582830, 3355360, 56555551, 6642336, 186172523, 186804224, 15277581, 59444651, 254457068, 310528342, 423416841, 782884539, 743464702, 369610019, 643257039};
    
    LL b[] = {1, 1, 1, 1, 1, 2, 2, 2, 1, 1, 1, 2, 2, 1, 2, 2, 2, 2, 1};
    
    TEST(convert(a, SIZEOFARRAY(a)),convert(b, SIZEOFARRAY(b)), 10);
}

void Test7()
{
    LL a[] = {138742, 878514, 852494, 542526, 953090, 618335, 834947, 451187, 818761, 498817, 701160, 996792, 845435, 145660, 183611, 150459, 635733, 718307};
    LL b[] = {2, 1, 1, 1, 2, 1, 1, 1, 2, 2, 1, 2, 1, 1, 2, 2, 2, 2};
    
    TEST(convert(a, SIZEOFARRAY(a)),convert(b, SIZEOFARRAY(b)), 3);
}

void Test8()
{
    LL a[] = {138742, 878514, 852494, 542526, 953090, 618335, 834947, 451187, 818761, 498817, 701160, 996792, 845435, 145660, 183611, 150459, 635733, 718307};
    LL b[] = {2, 1, 1, 1, 2, 1, 1, 1, 2, 2, 1, 2, 1, 1, 2, 2, 2, 2};
    
    TEST(convert(a, SIZEOFARRAY(a)),convert(b, SIZEOFARRAY(b)), 3);
}

void Test9()
{
	LL a[] = {8589934592, 4294967296, 2147483648, 1073741824, 536870912, 268435456, 134217728, 67108864, 33554432, 16777216, 8388608, 4194304, 2097152, 1048576, 524288, 262144, 131072, 65536, 32768, 16384, 8192, 4096, 2048, 1024, 512, 256, 128, 64, 32, 16, 8, 4, 2, 1, 89011169278, 900913592218, 573105180887, 579137087003, 149698905839, 832047692813, 558111502004, 253561629925, 876887316333, 235624898040, 155336388121, 197770970131, 463071223829, 345224747632, 921657583888, 881486688024};
	LL b[] = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 1, 2, 2, 2, 2, 2, 2, 1, 2, 1, 1, 1, 2, 2};
    TEST(convert(a, SIZEOFARRAY(a)),convert(b, SIZEOFARRAY(b)), 5);
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
