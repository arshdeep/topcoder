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
/* http://community.topcoder.com/stat?c=problem_statement&pm=12155 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define REP(i,n) for(int i=0;i<(n);++i)
#define LOOP(i,v,n) for(i=v;i<(n);++i)
#define LL long long
#define memSet(m, v) memset(m, v, sizeof(m))

class CuttingBitString
{
	map<string, int> memo;
	bool check(string sub)
	{
		if (sub[0] == '0') return 0;
		long long num = 1;
		for (int idx = 1, len = sub.length(); idx < len; ++idx)
		{
			num <<= 1;
			if (sub[idx] == '1')
				num |= 1;
		}

		if (num > 5)
			while (num % 5 == 0)
				num /= 5;

		return num == 1 || num == 5;
	}
public:
	int getmin(string S)
	{
		map<string, int>::iterator itr =  memo.find(S);

		if (itr != memo.end())
			return itr->second;
		int res = INT_MAX;
		for (int idx = 0, len = S.length(); idx < len; ++idx)
		{
			int tmp = 0;
			if ( check(S.substr(0, idx + 1)) && ( (idx + 1) == len || S[idx + 1] == '1' ) )
			{
				string str = S.substr(idx + 1, len - idx - 1);
				int min = getmin(str);

				if (str.length() == 0)
					tmp = 1;
				else if (min != -1)
					tmp += min + 1;
			}

			if (tmp > 0)
				res = std::min(tmp, res);
		}
		res = res == INT_MAX ? -1 : res;
		memo.insert(make_pair(S, res));
		return res;
	}
};

void TEST(string s, int expected)
{
	clock_t start, end;
	double cpu_time_used;
    
	start = clock();
	CuttingBitString cuttingBitString;
	int result = cuttingBitString.getmin(s);
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
	TEST("101101101", 3 );
	TEST("1111101", 1 );
	TEST("00000", -1 );
	TEST("110011011", 3 );
	TEST("1000101011", -1 );
	TEST("111011100110101100101110111", 5 );
	TEST("11111011111101111111011111101111111111111101111111", 20 );
	TEST("101101101101101101101101101101101101101101101101", 16 );
	TEST("00010111001110100000101101001100010011111111100110", -1 );
	TEST("000001111101", -1 );
	TEST("1011111011011111011011111011011111011011111011111", 29 );
	TEST("111101000010011001010100000010111110011", 3 );
	TEST("101110011100011001110001111110110011100011111101", 7 );
	TEST("100010101100011100100011000001001000100111101", 1 );
	TEST("10111010010000111011011101", 1 );
	TEST("1101100011010111001001101011011100010111011110101", 1 );
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
