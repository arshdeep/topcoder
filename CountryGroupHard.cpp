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
/* http://community.topcoder.com/stat?c=problem_statement&pm=13688 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define REP(i,n) for(int i=0;i<(n);++i)
#define LOOP(i,v,n) for(i=v;i<(n);++i)
#define LL long long
#define memSet(m, v) memset(m, v, sizeof(m))

class CountryGroupHard
{
public:
	string solve(vector<int> a)
	{
		int len = a.size();
		vector<int> dp(len + 1);
		dp[0] = 1;
		for (int i = 0; i < len; ++i)
		{
			if (dp[i] == 0) continue;

			for (int j = 1; j <= len - i; ++j)
			{
				int flag = true;
				for (int k = 0; k < j; ++k)
				{
					if ( a[i + k] != 0 && a[i + k] != j )
					{
						flag = false;
						break;
					}
				}

				if ( flag )
				{
					dp[i + j] += dp[i];
				}
			}
		}
		if ( dp[len] == 1 ) return "Sufficient";

		return "Insufficient";
	}
};

void TEST(vector<int> a, string expected)
{
	clock_t start, end;
	double cpu_time_used;
    
	start = clock();
	CountryGroupHard countryGroupHard;
	string result = countryGroupHard.solve(a);
	assert( expected.compare(result) == 0 );
    
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
	int a[] = {0,3,0,0,3,0};
	TEST(convert(a, SIZEOFARRAY(a)), "Sufficient");
}

void Test2()
{
	int a[] = {0,0,3,3,0,0};
	TEST(convert(a, SIZEOFARRAY(a)), "Insufficient");
}

void Test3()
{
	int a[] = {0,2,3,0,0};
	TEST(convert(a, SIZEOFARRAY(a)), "Sufficient");
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
	getchar();
	cout << "success";
	return 0;
}
