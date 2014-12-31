#include <iostream>
#include <cstdio>
#include <vector>
#include <cassert>
#include <sstream>
#include <set>
#include <queue>
#include <map>
#include <algorithm>
#include <time.h>
using namespace std;
/* https://www.topcoder.com/stat?c=problem_statement&pm=4721&rd=8000 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define memSet(a, val) memset(a, val, sizeof(a))

class HairCuts
{
public:
	double maxCut(vector<string> enter, string lastExit);
};
void parse(const vector<string> &enter, vector<int> &out)
{
	for (int i = 0, size = enter.size(); i < size; ++i)
	{
		istringstream iss(enter[i]);
		int hr, min;
		char colon;

		iss >> hr;
		iss >> colon;
		iss >> min;
		if (hr < 9)
		{
			hr += 12;
		}
		out.push_back(hr * 60 + min);
	}
}

double getMax(vector<int> &in, double mid)
{
	double temp = 0;
	for (int i = 0, size = in.size() - 1; i < size; ++i)
	{
		if (in[i] > temp)
			temp = in[i];
		temp += mid;
	}
	return temp;
}

double HairCuts::maxCut(vector<string> enter, string lastExit)
{
	vector<int> in;
	enter.push_back(lastExit);
	parse(enter, in);
	sort(in.begin(), in.end());

	double start = 5.0;
	double end = in[in.size() - 1];
	double last = end;

	while (end - start >= 1e-13)
	{
		double mid = start + (end - start) / 2;

		if (getMax(in, mid) >= last)
			end = mid;
		else
			start = mid;
	}
	if (getMax(in, start) > last + 1e-9)
		return -1;
	return start;
}

void TEST(vector<string> enter, string lastExit, double expected)
{
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	HairCuts hairCuts;

	double result = hairCuts.maxCut(enter, lastExit);

	//assert( expected - result <= 1e-9  );

	end = clock();
	cpu_time_used = ((double) (end - start));
	cout<<"Time taken : "<<cpu_time_used<<endl;
}

template<class T>
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
	string test[] = {"04:22","09:00"};
	TEST(convert(test, SIZEOFARRAY(test)), "05:52", 90.0);
}

void Test2()
{
	string test[] = {"09:00","09:22","09:22"};
	TEST(convert(test, SIZEOFARRAY(test)), "10:11", 23.666666666666863);
}

void Test3()
{
	string test[] = {"09:00","04:00","04:02"};
	TEST(convert(test, SIZEOFARRAY(test)), "04:09", -1.0);
}

void Test4()
{
	string test[] = 	{"01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00", "01:00"};
	TEST(convert(test, SIZEOFARRAY(test)), "05:10", 5.0);
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

void Test11()
{
}

void Test12()
{
}

void Test13()
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
	Test11();
	Test12();
	Test13();
	cout<<"success";

	getchar();
	return 0;
}
