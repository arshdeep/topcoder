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
/* http://community.topcoder.com/stat?c=problem_statement&pm=11781 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define REP(i,n) for(int i=0;i<(n);++i)
#define LOOP(i,v,n) for(i=v;i<(n);++i)
#define LL uint64_t
#define memSet(m, v) memset(m, v, sizeof(m))

int dp[60][60];
class CasketOfStar
{
	int solve(vector<int> weight, int a, int b)
	{
		if (b == a + 1) return 0;
		int &val = dp[a][b];

		if (val != -1)
			return val;

		for (int i = a + 1; i < b; ++i)
		{
			val = std::max(val, weight[a] * weight[b] + solve(weight, a, i) + solve(weight, i, b));
		}

		return val;
	}
public:
	int maxEnergy(vector<int> weight)
	{
		memSet(dp, -1);
		return solve(weight, 0, weight.size() - 1);
	}
};

void TEST(vector<int> weight, int expected)
{
	clock_t start, end;
	double cpu_time_used;
    
	start = clock();
	CasketOfStar casketOfStar;
	int result = casketOfStar.maxEnergy(weight);
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
	int test[] = {1,2,3,4};
	TEST(convert(test, SIZEOFARRAY(test)), 12 );
}

void Test2()
{
	int test[] = {100,2,1,3,100};
	TEST(convert(test, SIZEOFARRAY(test)), 10400 );

}

void Test3()
{
	int test[] = {2,2,7,6,90,5,9};
	TEST(convert(test, SIZEOFARRAY(test)), 1818 );

}

void Test4()
{
	int test[] = {1,2,3,4};
	TEST(convert(test, SIZEOFARRAY(test)), 12 );
}

void Test5()
{
	int test[] = {477,744,474,777,447,747,777,474};
	TEST(convert(test, SIZEOFARRAY(test)), 2937051 );
}

void Test6()
{
	int test[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
	TEST(convert(test, SIZEOFARRAY(test)), 13 );
}

void Test7()
{
	int test[] = {95, 221, 734, 362, 713, 352, 341, 520, 280, 260, 314, 479, 355};
	TEST(convert(test, SIZEOFARRAY(test)), 2870087 );
}

void Test8()
{
	int test[] = {379, 483, 521, 400, 506, 587, 486, 248, 390, 311, 440, 465, 405, 441, 375, 533, 452, 277, 475, 460, 572, 557, 489, 259, 486, 445, 497, 447, 283, 289, 503, 400, 559, 372};
	TEST(convert(test, SIZEOFARRAY(test)), 8269952 );
}

void Test9()
{
	int test[] = 	{457, 470, 453, 455, 452, 464, 450, 449, 449, 458, 448, 467, 466, 451, 469, 450, 451, 466, 459, 451, 466, 461, 452, 460, 457, 465, 453, 470, 464, 453, 468, 448, 462, 451, 455, 465, 448, 463, 448, 449, 468, 458, 463, 463, 459, 451, 451, 448, 448, 462};
	TEST(convert(test, SIZEOFARRAY(test)), 10358879 );
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
