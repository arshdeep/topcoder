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
#include <math.h>
using namespace std;
/* https://www.topcoder.com/stat?c=problem_statement&pm=2427&rd=4765 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define memSet(a, val) memset(a, val, sizeof(a))

class Mortgage
{
	bool canPay(double loan, double pay, double term, double roi);
public:
	int monthlyPayment(int loan, int interest, int term);
};

bool Mortgage::canPay(double loan, double pay, double term, double roi)
{
	for (int mon = 1; mon <= 12*term; ++mon)
	{
		loan -= pay;
		if (loan <= 0) return true;
			loan  = ceil(loan* (1 + roi/1200));
	}
	return false;
}

int Mortgage::monthlyPayment(int loan, int interest, int term)
{
	double roi = ((double)interest / 10.0);
	int s = 0, e = loan;

	while (s < e)
	{
		int mid = s + (e - s) / 2;

		if (canPay(loan, mid, term, roi))
			e = mid;
		else
			s = mid + 1;
	}
	return s;
}
void TEST(int loan, int interest, int term, int expected)
{
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	Mortgage mortgage;

	int result = mortgage.monthlyPayment(loan, interest, term);
	assert( expected == result);

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
	TEST(1000, 50, 1, 86);
	TEST(2000000000, 6000, 1, 671844808);
	TEST(1000000, 1000000, 1000, 988143);
	TEST(1000000,129,30, 10868);
	TEST(1999999999, 1000000, 1, 1976284585);
	TEST(1939524178, 2486, 309, 332849450);
	TEST(1463035902, 147540, 281, 1352991833);
	TEST(1999999999, 1000000, 1, 1976284585);

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
