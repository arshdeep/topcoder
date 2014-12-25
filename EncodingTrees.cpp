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
/* https://www.topcoder.com/stat?c=problem_statement&pm=4700&rd=7995 */
#define SIZEOFSTRINGARRAY(s) sizeof(s)/sizeof(s[0])

class EncodingTrees
{
private:
	string code(vector<long> &dp, int N, int index, char start);
public:
	string getCode(int N, int index);
};

string EncodingTrees::code(vector<long> &dp, int n, int index, char start)
{
	if (n == 0)
		return "";

	size_t idx = 0;
	while (index > dp[idx] * dp[n - idx - 1])
	{
		index -= dp[idx] * dp[n - idx - 1];
		++idx;
	}
	int k = (int)dp[n - idx - 1];
	int i = (index - 1) / k + 1;
	int j = (index - 1) % k + 1;

	return (char)(start + idx) + code(dp, idx, i, start) + code(dp, n - idx - 1, j, start + idx + 1);
}

string EncodingTrees::getCode(int N, int index)
{
	vector<long> dp(N + 1);
	dp[0] = 1;

	for (size_t i = 1; i <= N; ++i)
	{
		for (size_t j = 0; j < i; ++j)
		{
			dp[i] += dp[j] * dp[i - j - 1];
		}
	}

	if (index > dp[N])
		return "";

	return code(dp, N, index, 'a');
}

void TEST(int N, int index, string expected)
{
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    EncodingTrees encodingTrees;
    
    string result = encodingTrees.getCode(N, index);
    
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
    TEST(4, 9, "cbad");
	TEST(15, 14023, "abcdeohgfniljkm");
	TEST(11, 111, "abcdekhfgji");
	TEST(19, 2000000000, "");
	TEST(19, 1000000000, "nmjgafbcdeihklosrpq");
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
    cout<<"success";
    
    getchar();
    return 0;
}
