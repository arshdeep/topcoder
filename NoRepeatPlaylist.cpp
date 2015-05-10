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
#include <regex>
#include <stdint.h>
using namespace std;
/* http://community.topcoder.com/stat?c=problem_statement&pm=11774 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define REP(i,n) for(int i=0;i<(n);++i)
#define LOOP(i,v,n) for(i=v;i<(n);++i)
#define LL int64_t
#define memSet(m, v) memset(m, v, sizeof(m))
LL dp[101][101];
class NoRepeatPlaylist
{
	int N, M, P;

	LL solve(int index, int sx, int sy)
	{
		if (index >= P)
			return sy == 0 ? 1 : 0;

		LL &val = dp[index][sx];

		if (val != -1)
			return val;

		LL result = 0;
		
		if (sy > 0)
			result += solve(index + 1, sx + 1, sy - 1) * sy;

		if (sx > M)
			result += solve(index + 1, sx, sy) * (sx - M);
		val = (result % 1000000007);
		return val;
	}

public:
	int numPlaylists(int N, int M, int P)
	{
		memSet(dp, -1);
		this->N = N;
		this->M = M;
		this->P = P;

		return solve(0, 0, N);
	}
};

void TEST(int N, int M, int P, int expected)
{
	clock_t start, end;
	double cpu_time_used;
    
	start = clock();
	NoRepeatPlaylist noRepeatPlaylist;
	int result = noRepeatPlaylist.numPlaylists(N, M, P);
	assert( expected == result );
    
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
	TEST(1, 0, 3, 1);
	TEST(1, 1, 3, 0);
	TEST(2, 0, 3, 6);
	TEST(4, 0, 4, 24);
	TEST(2, 1, 4, 2);
	TEST(50, 5, 100, 222288991);
	TEST(47, 47, 47, 846397273);
	TEST(47, 46, 47, 846397273 );
	TEST(4, 1, 4, 24);
	TEST(	82, 61, 100,443647325		);
	TEST(	92, 3, 100, 635215935		);
	TEST(	50, 50, 50, 318608048		);
	TEST(49, 7, 100,		437821697	);
	TEST(5, 5, 5,		120		);
	TEST(	88, 5, 100,		638621416		);
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

	cout << "success";
	getchar();
	return 0;
}
