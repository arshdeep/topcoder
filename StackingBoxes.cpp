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

struct Box
{
	int w;
	int c;
	Box(int weight = 0, int capacity = 0) : w(weight), c(capacity) {}
	bool operator <(Box rhs)
	{
		return (this->w + this->c) < (rhs.w + rhs.c);
	}
};

class StackingBoxes
{
	vector<int> convertToList(const vector<string> &vect);
public:
	int highestStack(vector<string> &weight, vector<string> &canCarry);
};

vector<int> StackingBoxes::convertToList(const vector<string> &vect)
{
	vector<int> ret;

	for (size_t idx = 0, len = vect.size(); idx < len; ++idx)
	{
		string str = vect[idx];
		istringstream iss(str);
		while(!iss.eof())
		{
			int i = INT_MIN;

			iss >> i;

			if (i != INT_MIN)
				ret.push_back(i);
		}
	}

	return ret;
}
int StackingBoxes::highestStack(vector<string> &weight, vector<string> &canCarry)
{
	vector<int> wl = convertToList(weight);
	vector<int> cl = convertToList(canCarry);
	vector<int> dp(wl.size() + 1, INT_MAX);
	vector<Box> boxes(wl.size());

	dp[0] = 0;
	for (size_t idx = 0, len = wl.size(); idx < len; ++idx)
	{
		boxes[idx].c = cl[idx];
		boxes[idx].w = wl[idx];
	}
	std::sort(boxes.begin(), boxes.end());
	int max = 0;
	for (int i = 0, len = wl.size(); i < len; ++i)
	{
		for (int j = len; j >= 0; --j)
		{
			if (dp[j] != INT_MAX && boxes[i].c >= dp[j] && dp[j + 1] > dp[j] + boxes[i].w)
			{
				dp[j + 1] = dp[j] + boxes[i].w;
				max = std::max(max, j + 1);
			}
		}
	}
	return max;
}

void TEST(vector<string> weight, vector<string> canCarry, int expected)
{
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    StackingBoxes stackingBoxes;
    
	int result = stackingBoxes.highestStack(weight, canCarry);
    
	assert( result == expected );
    
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
	string weight[] = {"10 20 30"};
	string carry[] = {"11", "100 10"};

	TEST(convert(weight, SIZEOFSTRINGARRAY(weight)),
		convert(carry, SIZEOFSTRINGARRAY(carry)), 3);
}

void Test2()
{
	string weight[] = {"200 200 600 700 400"};
	string carry[] = {"1000 20 150 700 10"};

	TEST(convert(weight, SIZEOFSTRINGARRAY(weight)),
		convert(carry, SIZEOFSTRINGARRAY(carry)), 3);
}

void Test3()
{
	string weight[] = {"100 100", "1000 100"};
	string carry[] = {"90", "91 92 93"};

	TEST(convert(weight, SIZEOFSTRINGARRAY(weight)),
		convert(carry, SIZEOFSTRINGARRAY(carry)), 1);
}

void Test4()
{
	string weight[] = {"11 20 30"};
	string carry[] = {"11", "100 10"};

	TEST(convert(weight, SIZEOFSTRINGARRAY(weight)),
		convert(carry, SIZEOFSTRINGARRAY(carry)), 2);
}

void Test5()
{
	string weight[] ={"10", "20", "91"};
	string carry[] = {"11", "100 10"};

	TEST(convert(weight, SIZEOFSTRINGARRAY(weight)),
		convert(carry, SIZEOFSTRINGARRAY(carry)), 2);
}

void Test6()
{
	string weight[] ={"7976 11870 81678 7359 42058 87039 32212 61435", "83007 18385 68255 70360 63852 82093 48411 93386", "40587 99355 49112 26022 16971 53511 30129 65906", "11621 50556 85390 35823 18047 75405 31162 36324", "74045 69667 42392 52152 46576 84200 58435 27666", "10049 87759 36964 82507 79323 34948 26701"};
	string carry[] = {"72986 433139 179372 123127 366499 183472", "332646 189999 420411 468338 207420 235871", "32436 403795 201479 19223 400985 208481 62147", "321221 304760 322571 359298 324784 152131", "330901 290158 29967 159910 25855 215090 177147", "18087 237724 237882 8880 104930 221340 385316", "264583 380539 417645 203549 34585 402021", "266142 126165"};

	TEST(convert(weight, SIZEOFSTRINGARRAY(weight)),
		convert(carry, SIZEOFSTRINGARRAY(carry)), 19);
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
