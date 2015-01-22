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
using namespace std;
/* http://community.topcoder.com/stat?c=problem_statement&pm=6095&rd=9917 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define REP(i,n) for(int i=0;i<(n);++i)
#define LOOP(i,v,n) for(i=v;i<(n);++i)
#define LL long long
#define memSet(m, v) memset(m, v, sizeof(m))

class FloorBoards
{
	int solve(int mask, const vector<string> &mat)
	{

	}
public:
	int howMany(vector<string> mat)
	{
		memSet(memo, -1);
		return solve(0, mat);
	}
};

void TEST(vector<string> mat, int expected)
{
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	FloorBoards floorBoards;
	int result = floorBoards.howMany(mat);

	assert(result == expected);

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
	string test[] = { "....."
		, "....."
		, "....."
		, "....."
		, "....." };
	TEST(convert(test, SIZEOFARRAY(test)), 5);
}

void Test2()
{
	string test[] = { "......."
		, ".#..##."
		, ".#....."
		, ".#####."
		, ".##..#."
		, "....###" };
	TEST(convert(test, SIZEOFARRAY(test)), 7);
}

void Test3()
{
	string test[] = { "####"
		, "####"
		, "####"
		, "####" };
	TEST(convert(test, SIZEOFARRAY(test)), 0);
}

void Test4()
{
	string test[] = { "...#.."
		, "##...."
		, "#.#..."
		, ".#...."
		, "..#..."
		, "..#..#" }
	;
	TEST(convert(test, SIZEOFARRAY(test)), 9);
}

void Test5()
{
	string test[] = { ".#...."
		, "..#..."
		, ".....#"
		, "..##.."
		, "......"
		, ".#..#." };
	TEST(convert(test, SIZEOFARRAY(test)), 9);
}

void Test6()
{
	string test[] = { "NNNNNNNNNNNNYYNNYN", "NNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNNYNNNN", "NNNNNNNNNNNNNNNYNN", "NNNNNNNNNNNNNNNNNN", "NNNNNNNNNNNNYNNNNN", "NNNNNNNNNNYYNNNNYN", "NNNNNNNNNYNNNYNNNN", "NNNNNNNNNNNNNNYYNN", "NNNNNNNYNNNNNYYNYN", "NNNNNNYNNNNNNYYNNN", "NNNNNNYNNNNNYNNNNN", "YNNNNYNNNNNYNNNNNN", "YNYNNNNYNYYNNNNNNN", "NNNNNNNNYYYNNNNNNN", "NNNYNNNNYNNNNNNNNN", "YNNNNNYNNYNNNNNNNN", "NNNNNNNNNNNNNNNNNN" };
	TEST(convert(test, SIZEOFARRAY(test)), 14);
}

void Test7()
{
	string test[] = { "NYYNYYYYYYNNNYYYYY", "YNYNYYYNNYNYYNYYYN", "YYNNYYYYNNYYYYNYNY", "NNNNYYYNYYYYYNYNYN", "YYYYNYYYYYYYYYYYYY", "YYYYYNYNYNYYYYNNNN", "YYYYYYNYYYYYYNYYNY", "YNYNYNYNYYYNYYNYYY", "YNNYYYYYNYNYYYYNYN", "YYNYYNYYYNYYYYYYYY", "NNYYYYYYNYNNYYYNNY", "NYYYYYYNYYNNYNYYNN", "NYYYYYYYYYYYNNYNYN", "YNYNYYNYYYYNNNYNNY", "YYNYYNYNYYYYYYNYNY", "YYYNYNYYNYNYNNYNNY", "YYNYYNNYYYNNYNNNNY", "YNYNYNYYNYYNNYYYYN" };
	TEST(convert(test, SIZEOFARRAY(test)), 18);
}

void Test8()
{
	string test[] = { "NYYYY", "YNNNN", "YNNNN", "YNNNN", "YNNNN" };
	TEST(convert(test, SIZEOFARRAY(test)), 2);
}

void Test9()
{
	string test[] = { "NYNNNNNNNNNNNNNNNY", "YNNNNNNNNNNNNNNNYN", "NNNYYYYYYYYYYYYYNN", "NNYNYYYYYYYYYYYYNN", "NNYYNYYYYYYYYYYYNN", "NNYYYNYYYYYYYYYYNN", "NNYYYYNYYYYYYYYYNN", "NNYYYYYNYYYYYYYYNN", "NNYYYYYYNYYYYYYYNN", "NNYYYYYYYNYYYYYYNN", "NNYYYYYYYYNYYYYYNN", "NNYYYYYYYYYNYYYYNN", "NNYYYYYYYYYYNYYYNN", "NNYYYYYYYYYYYNYYNN", "NNYYYYYYYYYYYYNYNN", "NNYYYYYYYYYYYYYNNN", "NYNNNNNNNNNNNNNNNN", "YNNNNNNNNNNNNNNNNN" };
	TEST(convert(test, SIZEOFARRAY(test)), 18);
}

void Test10()
{
	string test[] = { "NYNYNNNN", "YNYNNNNN", "NYNNNNNN", "YNNNYYNN", "NNNYNNYN", "NNNYNNNY", "NNNNYNNN", "NNNNNYNN" };
	TEST(convert(test, SIZEOFARRAY(test)), 8);
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
	return 0;
}
