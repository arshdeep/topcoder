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
using namespace std;
/* http://community.topcoder.com/stat?c=problem_statement&pm=13634 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define REP(i,n) for(int i=0;i<(n);++i)
#define LOOP(i,v,n) for(i=v;i<(n);++i)
#define LL long long
#define memSet(m, v) memset(m, v, sizeof(m))

class BuildingTowersEasy
{
public:
	int maxHeight(int N, vector< int > &x, vector< int > &t)
	{
		int max = 0;
		for ( int i = 1; i <= N; ++i )
		{
			int ub = i - 1;
			for ( int j = 0, size = x.size(); j < size; ++j )
			{
				ub = std::min(ub, abs(i - x[j]) + t[j]);
			}
			max = std::max(max, ub);
		}
		return max;
	}
};

void TEST(int N, vector< int > x, vector< int > t, int expected)
{
	clock_t start, end;
	double cpu_time_used;
    
	start = clock();
	BuildingTowersEasy buildingTowersEasy;
	int result = buildingTowersEasy.maxHeight(N, x, t);
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
	int a[] = {3,8};
	int b[] = {1,1};
	TEST(10, convert(a, SIZEOFARRAY(a)), convert(b, SIZEOFARRAY(b)), 3 );
}

void Test2()
{
	int a[] = {4,7,13,15,18};
	int b[] = {3,8,1,17,16};
	TEST(20, convert(a, SIZEOFARRAY(a)), convert(b, SIZEOFARRAY(b)), 8 );
}

void Test3()
{
	int a[] = {32,35,55,60,61,88,91,97,128,151,181,186,192,196,198,237,259,268,291,314,341,367,389,390,391,428,435};
	int b[] = {81,221,172,641,25,953,330,141,123,440,692,394,200,649,78,726,50,810,501,4,216,407,2,172,0,29,14};
	TEST(447, convert(a, SIZEOFARRAY(a)), convert(b, SIZEOFARRAY(b)), 120 );
}

void Test4()
{
	int a[] = {8,1749,4550,5388,6752,7089,9737,14891,16671,16821,17691,19753,24589,
25348,30114,32213,34376,36467,37699,41490,44784,44893,57316,58275,58567,
61122,61489,63195,64776,65905,68788,69908,72853,78152,78784,82779,84488,
86277,88611,92793,93214,97583};
	int b[] = {16610,6,497,14,42892,31,79,1203,518,31147,597,7846,1396,8309,12,14,1148,
433,23693,13,1939,244,19,46,27,611,412,10,27023,19141,34,15667,588,10,229,
83,390,14,38441,16021,4,39386};
	TEST(97638, convert(a, SIZEOFARRAY(a)), convert(b, SIZEOFARRAY(b)), 6343 );
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
	getchar();
	cout << "success";
	return 0;
}
