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
/* https://www.topcoder.com/stat?c=problem_statement&pm=2396&rd=4755 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define REP(i,n) for(int i=0;i<(n);++i)
#define LOOP(i,v,n) for(i=v;i<(n);++i)
#define LL long long
#define memSet(m, v) memset(m, v, sizeof(m))

class Cyberline
{
public:
	string lastCyberword(string cyberline)
	{
		std::regex hyphen("-");
		string rep("");
		string r1( regex_replace(cyberline, hyphen, rep) );
		regex e2("[^a-zA-Z0-9@]");
		string space = " ";
		string result( std::regex_replace (r1, e2, space) );

		istringstream iss( result );
		string ret;

		while ( !iss.eof() )
		{
			iss >> ret;
		}

		return ret;
	}
};

void TEST(string cb, string expected)
{
	clock_t start, end;
	double cpu_time_used;
    
	start = clock();
	Cyberline cyberline;
	string result = cyberline.lastCyberword(cb);
 //   cout<<result<< " "<< expected<<endl;
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
	TEST("Zowie: This is a line of##cyber-poetry## !", "cyberpoetry");
}

void Test2()
{
	TEST("2-b|!2-b -- ?", "2b");
}

void Test3()
{
	TEST("if then{}; elseif schmelshif();", "schmelshif");
}

void Test4()
{
	TEST("~y?", "y");
}

void Test5()
{
	TEST("@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@", "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@");
}

void Test6()
{
	TEST("@-----------------------------------------------", "@");
}

void Test7()
{
	TEST(" c at t y p in g ", "g");
}

void Test8()
{
	TEST("@$%#$#)%(#&$){$@!}", "@");
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
