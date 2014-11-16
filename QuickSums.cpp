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
/* QuickSums https://www.topcoder.com/stat?c=problem_statement&pm=2829&rd=5072 */

class QuickSums
{
private:
	int parseInt(string str);
	string normalizeIntString(string str);
public:
	int minSums(string numbers, int sum);
};

int QuickSums::parseInt(string str)
{
	istringstream ss(str);
	int ret;

	ss >> ret;

	return ret;
}

string QuickSums::normalizeIntString(string str)
{
	istringstream ss(str);
	__int64 ret;

	ss >> ret;
	stringstream ss2;
	
	ss2 << ret;
	return ss2.str();
}

#define MAXSUM 100
int QuickSums::minSums(string numbers, int sum)
{
	numbers = normalizeIntString(numbers);
	int len = numbers.length();
	int dp[10][10][101];

	for (int i = 0; i < len; ++i)
	{
		for (int j = 0; j < len; ++j)
		{
			for (int k = 0; k <= sum; ++k)
				dp[i][j][k] = INT_MAX;
		}
	}

	for (int idx = 0; idx < len; ++idx)
	{
		dp[idx][idx][parseInt(numbers.substr(idx, 1))] = 0;
	}

	for (int gap = 1; gap < len; ++gap)
	{
		for (int i = 0, j = gap; j < len; ++i, ++j)
		{
			int v = parseInt(numbers.substr(i, j - i + 1));
			if (v  > 0 && v < sum)
				dp[i][j][v] = 0;
			for (int k = i; k < j; ++k)
			{
				for (int s1 = 0; s1 < sum; ++s1)
				{
					for (int s2 = 0; s2 + s1 <= sum; ++s2)
					{
						if (dp[i][k][s1] < INT_MAX && dp[k + 1][j][s2] < INT_MAX)
							dp[i][j][s1 + s2] = std::min(dp[i][j][s1 + s2], dp[i][k][s1] + dp[k + 1][j][s2] + 1);
					}
				}
			}
		}
	}

	return dp[0][len-1][sum] < INT_MAX ? dp[0][len-1][sum] : -1;
}

void TEST(string numbers, int sum, int expected)
{
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	QuickSums quickSums;

	int result = quickSums.minSums( numbers, sum);
	
	assert( result == expected );

	end = clock();
	cpu_time_used = ((double) (end - start));
	cout<<"Time taken : "<<cpu_time_used<<endl;
}


void Test1()
{
	TEST("99999", 45, 4);
	TEST("382834", 100, 2);
	TEST("99999", 100, -1);
	TEST("9230560001", 71, 4);
	TEST("0123456789", 45, 8);
	TEST("0000000001", 1, 0);
	TEST("8833614925", 100, -1);
	TEST("1", 1, 0);
	TEST("1000000001", 2, 1);
	TEST("1000000001", 11, 1);
	TEST("0220120200", 63, 4);
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
