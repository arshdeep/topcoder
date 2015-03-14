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
/* https://www.topcoder.com/stat?c=problem_statement&pm=2912&rd=5849 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define REP(i,n) for(int i=0;i<(n);++i)
#define LOOP(i,v,n) for(i=v;i<(n);++i)
#define LL long long
#define memSet(m, v) memset(m, v, sizeof(m))

class UnLinker
{
public:
	string clean(string cyberline)
	{
		std::regex hyphen("((http://)?www[.]|http://)[a-zA-Z0-9.]+[.](com|org|edu|info|tv)");
		string rep("OMIT");
		string result( regex_replace(cyberline, hyphen, rep) );

		int index = -4;
		char idx = '1';
		while ((index = result.find("OMIT", index + 4)) != -1)
		{
			result.insert(index + 4, "x");
			result[index + 4] = idx++;
		}

		return result;
	}
};

void TEST(string cb, string expected)
{
	clock_t start, end;
	double cpu_time_used;
    
	start = clock();
	UnLinker unLinker;
	string result = unLinker.clean(cb);
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
	TEST("espihttp://www.tv.org.superwww.cali.comaladocious", "espiOMIT1aladocious");
}

void Test2()
{
	TEST("check www.foo.com 4 www.foo.com www.scoopz.com", "check OMIT1 4 OMIT2 OMIT3");
}

void Test3()
{
	TEST("check www.foo.com 4 www.foo.comwww.scoopz.com", "check OMIT1 4 OMIT2");
}

void Test4()
{
	TEST("check www.foo.com 4 www.foo.comhttp://scoopz.com", "check OMIT1 4 OMIT2OMIT3");
}

void Test5()
{
	TEST("http://411.com goodz 4 www.733t.com, 2http://..com", "OMIT1 goodz 4 OMIT2, 2OMIT3");
}

void Test6()
{
	TEST("http.//say.org,www.jeeves.x.info,www.comhttp://.tv", "http.//say.org,OMIT1,www.comhttp://.tv");
}

void Test7()
{
	TEST("http.//say.org,www.jeeves.x.info,www.comhttp://.tv", "http.//say.org,OMIT1,www.comhttp://.tv");
}

void Test8()
{
	TEST("Zu7yiI4 .eduuj.o.orgww.www.ht.edwww.orgpll.xx6uL3O", "Zu7yiI4 .eduuj.o.orgww.OMIT1pll.xx6uL3O");
}

void Test9()
{
	TEST("/wu.eduwww.edu://bY8dehttp://p://.tv.infowww.OM, J", "/wu.eduwww.edu://bY8dehttp://p://.tv.infowww.OM, J");
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
