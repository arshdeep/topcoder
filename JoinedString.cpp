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
/* http://topcoder.bgcoder.com/print.php?id=1244 */
#define SIZEOFSTRINGARRAY(s) sizeof(s)/sizeof(s[0])
class JoinedString
{
public:
	string joinWords(vector<string> words);
};

string JoinedString::joinWords(vector<string> words)
{
	int len = words.size();
	vector<string> dp(len);

	//std::sort(words.begin(), words.end());
	dp[0] = words[0];
	for (int i = 0; i < len; ++i)
	{
		string s1 = dp[i];
		string result = "";
		for (int j = 0; j < len; ++j)
		{
			if (i != j)
			{
				string s2 = words[j];
				if (s1.find(s2) != string::npos) continue;

				int result = s1.compare(s2);

				if (result == -1)
					s1.swap(s2);
				else if (result == 0) continue;

				for (int k = 1, s1Size = s1.length(); k < s1Size; ++k)
				{
					string sub1 = s1.substr(s1.size() - k, k);

					for (int kk = j; kk < len; ++kk)
					{

					}
				}
			}
		}

	}

	return dp[len - 1];
}

void TEST(vector<string> words, string expected)
{
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	JoinedString joinedString;

	string result = joinedString.joinWords(words);
	
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
	string test[] = {"BAB", "ABA"};

	TEST(convert(test, SIZEOFSTRINGARRAY(test)), "ABAB");
}

void Test2()
{
	string test[] = {"ABABA", "AKAKA", "AKABAS", "ABAKA"};

	TEST(convert(test, SIZEOFSTRINGARRAY(test)), "ABABAKAKABAS");
}

void Test3()
{
	string test[] = {"AAA","BBB", "CCC", "ABC", "BCA", "CAB"};

	TEST(convert(test, SIZEOFSTRINGARRAY(test)), "AAABBBCABCCC");
}

void Test4()
{
	string test[] = {"OFG", "SDOFGJTILM", "KBWNF", "YAAPO", "AWX", "VSEAWX", "DOFGJTIL", "YAA"};

	TEST(convert(test, SIZEOFSTRINGARRAY(test)), "KBWNFSDOFGJTILMVSEAWXYAAPO");
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
