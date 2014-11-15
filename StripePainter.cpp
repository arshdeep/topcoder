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
using namespace std;
/* StripePainter https://www.topcoder.com/stat?c=problem_statement&pm=1215&rd=4555 */

class StripePainter
{
private:
	std::unordered_map<string, int> memo;
public:
	int minStrokesRec(string stripes);
};

int StripePainter::minStrokesRec(string stripes)
{
	int len = stripes.length();

	if (len == 1) return 1;

	unordered_map<string, int>::iterator itr = memo.find(stripes);

	if (itr != memo.end())
		return itr->second;

	int min = INT_MAX;

	for (int k = 1; k < len; ++k)
	{
		string s1 = stripes.substr(0, k);
		string s2 = stripes.substr(k, len - k);
		int t1 = minStrokesRec(s1);
		int t2 = minStrokesRec(s2);

		if ( !memo.count(s1) )
			memo.insert( std::make_pair(s1, t1) );

		if ( !memo.count(s2) )
			memo.insert( std::make_pair(s2, t2) );

		int d =  stripes[0] == stripes[len - 1] ? 1 : 0;

		min = std::min(min, t1 + t2 - d);
	}

	return min;
}

void TEST( string stripes, int expected )
{
	clock_t start, end;
	double cpu_time_used;

	start = clock();

	StripePainter stripePainter;

	int result = stripePainter.minStrokesRec(stripes);

	end = clock();
	cpu_time_used = ((double) (end - start));
	cout<<"Time taken : "<<cpu_time_used<<endl;

	assert( result == expected );
}


void Test1()
{
	TEST( "RGBGR", 3);
}

void Test2()
{
	TEST( "RGBG", 3);
}

void Test3()
{
	TEST( "ABACADA", 4);
}

void Test4()
{
	TEST( "AABBCCDDCCBBAABBCCDD", 7);
}

void Test5()
{
	TEST( "BECBBDDEEBABDCADEAAEABCACBDBEECDEDEACACCBEDABEDADD", 26);
}

void Test6()
{
	TEST( "ABABABABABABABABABABABABABABABABABABABABABABABABAB", 26);
	TEST( "DEJJEDAIJHBFCEGHFEADCJAIIGKBF", 21);
	TEST( "ABACDBABDFDFJDFDFBCCABDBABABDBBCBCDBABCBJIEDF", 27);
	
}

int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();

	cout<<"success";

	getchar();
	return 0;
}
