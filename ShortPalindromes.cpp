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
#define SIZEOFSTRINGARRAY(s) sizeof(s)/sizeof(s[0])
/* http://community.topcoder.com/stat?c=problem_statement&pm=1861&rd=4630&rm=&cr=311502 */

class ShortPalindromes
{
	unordered_map<string, string> memo;
private :
	string &lexicographicalCmp(string &s1, string &s2)
	{
		if (s1.length() == s2.length())
		{
			return s1.compare(s2) < 0 ? s1 : s2;
		}
		else
		{
			return s1.length() > s2.length() ? s2 :  s1;
		}
	}
	bool isPlaindrome(const string &str);
public:
	string shortest(string base);
};

bool ShortPalindromes::isPlaindrome(const string &str)
{
	string cmp = str;

	std::reverse_copy(str.begin(), str.end(), cmp.begin());

	return cmp.compare(str) == 0;
}

string ShortPalindromes::shortest(string base)
{
	int strLen = base.length();

	if (isPlaindrome(base))
	{
		return base;
	}
	else if (base[0] == base[strLen - 1])
	{
		string str = base.substr(0, 1);
		return str + shortest(base.substr(1, strLen - 2)) + str;
	}
	else
	{
		string start = base.substr(0, 1);
		string end = base.substr(strLen - 1, 1);
		string sub1 = base.substr(1, strLen - 1);
		string sub2 = base.substr(0, strLen - 1);
		string r1;
		string r2;

		unordered_map<string, string>::iterator itr = memo.find(sub1);
		if (itr == memo.end())
		{
			r1 = shortest(sub1);
			memo.insert(make_pair(sub1, r1));
		}
		else
		{
			r1 = itr->second;
		}
		itr = memo.find(sub2);
		if (itr == memo.end())
		{
			r2 = shortest(sub2);
			memo.insert(make_pair(sub2, r2));
		}
		else
		{
			r2 = itr->second;
		}

		return lexicographicalCmp( start + r1 + start, end + r2 + end);
	}
}

void TEST(string base, string expected)
{
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	ShortPalindromes shortPalindromes;

	string result = shortPalindromes.shortest(base);
	
	assert( result.compare(expected) == 0 );

	end = clock();
	cpu_time_used = ((double) (end - start));
	cout<<"Time taken : "<<cpu_time_used<<endl;
}

vector<string> convert(string *list, int n)
{
	vector<string> ret;

	for (int i = 0; i< n; ++i)
	{
		ret.push_back(list[i]);
	}

	return ret;
}

void Test1()
{
	TEST("RACE", "ECARACE");
	TEST("TOPCODER", "REDTOCPCOTDER");
	TEST("Q", "Q");
	TEST("MADAMIMADAM", "MADAMIMADAM");
	TEST("ALRCAGOEUAOEURGCOEUOOIGFA", "AFLRCAGIOEOUAEOCEGRURGECOEAUOEOIGACRLFA");
	TEST("ABCDEFG", "ABCDEFGFEDCBA");
	TEST("GECABDF", "FDBACEGECABDF");
	TEST("GOOGLE", "ELGOOGLE");
	TEST("ABACADAFAGAFAHAJAKABA", "ABACKADJAHAFAGAFAHAJDAKCABA");
	TEST("MWRQIGJTGNKPBHKXQGIIECSF", "FMSCEIWRQIGJQTGNXKHBPBHKXNGTQJGIQRWIECSMF");
	TEST("HMDCDJKWHWMEDBKWJEKRFHLO", "OLHFMDCDRKEJWKBDEMWHWMEDBKWJEKRDCDMFHLO");

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

int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	Test7();
	cout<<"success";

	getchar();
	return 0;
}
