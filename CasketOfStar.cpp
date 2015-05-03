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

class CasketOfStar
{
	int sizeVect;
	map<LL, int> memo;
	int leadingZero(LL flag, int start)
	{
		for (int i = start; i >= 0; --i)
		{
			if ( (flag & ((LL)1 << i)) == 0 )
				return i;
		}
	}

	int trailZero(uint64_t flag, int start)
	{
		for (int i = start; i < sizeVect; ++i)
		{
			if ( (flag & ((LL)1 << i)) == 0 )
				return i;
		}
	}
	int solve(vector<int> weight, LL flag)
	{
		map<LL, int>::iterator itr = memo.find(flag);

		if ( itr != memo.end() )
			return itr->second;

		int res = INT_MIN;
		for (int i = 1, size = sizeVect - 1; i < size; ++i)
		{
			int energy = 0;
			if ( (flag & ((LL)1 << i)) == 0 ) {
				energy = weight[ leadingZero(flag, i - 1) ] * weight[ trailZero(flag, i + 1) ];
				energy += solve(weight, flag | ((LL)1 << i));
			}
			res = std::max(energy, res);
		}
		memo.insert( make_pair(flag, res) );
		return res;
	}
public:
	int maxEnergy(vector<int> weight)
	{
		sizeVect = weight.size();
		return solve(weight, 0);
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
