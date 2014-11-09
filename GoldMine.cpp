#include <iostream>
#include <cstdio>
#include <vector>
#include <cassert>
#include <sstream>
#include <set>
#include <algorithm>
#include <time.h>
using namespace std;
/* GoldMine http://community.topcoder.com/stat?c=problem_statement&pm=1957&rd=4650 */

#define INTARRAYSIZE(a) sizeof(a)/sizeof(int)
#define UNDERCOST 60
#define OVERCOST 50
#define OVERDEDUCTCOST 20
#define EQUALCOST 50
#define MAXWORKERALLOWED 6

class GoldMine
{
private:
	int getProfit(vector<int> mine, int workers);
public:
	vector<int> getAllocation(vector< vector<int> > &mines, int miners);
};

int GoldMine::getProfit(vector<int> mine, int workers)
{
	int profit = 0;

	for ( int ore = 0, size = mine.size();
		ore < size; ++ore )
	{
		int p = mine[ore];

		if (p > 0) 
		{
			if ( ore == 0 )
			{
				profit -= ((double)p/100) * workers * OVERDEDUCTCOST;
			}
			else if ( ore > workers )
			{
				profit += ((double)p/100) * workers * UNDERCOST;
			}
			else if ( ore <= workers )
			{
				profit += ((double)p/100) * ( ore * OVERCOST - (( workers - ore ) * OVERDEDUCTCOST ));
			}
		}
	}

	return profit;
}

vector<int> GoldMine::getAllocation( vector< vector<int> > &mines, int miners )
{
	int size = mines.size();
	vector<int> result(size);
	vector<int> lastProfit(size);

	for ( int miner = 0; miner < miners; ++miner )
	{
		int ub = -1;
		int profit = INT_MIN;
		int maxProfit = 0;
		for (int idx = 0; idx < size; ++idx)
		{
			if (result[idx] < MAXWORKERALLOWED)
			{
				int temp = getProfit(mines[idx], result[idx] + 1);

				if ( temp - lastProfit[idx] > profit)
				{
					profit = temp - lastProfit[idx];
					ub = idx;
					maxProfit = temp;
				}
			}
		}

		if (ub > -1)
		{
			lastProfit[ub] = maxProfit;
			result[ub] += 1;
		}
	}
	return result;
}

void TEST( vector< vector<int> > &mines, int miners, vector<int> &expected )
{
	clock_t start, end;
	double cpu_time_used;

	start = clock();

	GoldMine goldMine;

	vector<int> result = goldMine.getAllocation(mines, miners);

	end = clock();
	cpu_time_used = ((double) (end - start));
	cout<<"Time taken : "<<cpu_time_used<<endl;

	assert( result.size() == expected.size() &&
			std::equal(result.begin(), result.end(),
			expected.begin()) );
}

vector<int> convert(int *list, int size)
{
	vector<int> vect;

	for (int idx = 0; idx < size; ++idx)
	{
		vect.push_back(list[idx]);
	}

	return vect;
}

vector<int> convert(string list)
{
	vector<int> vect;
	istringstream iss(list);

	while(!iss.eof())
	{
		int p;
		string d;
		iss >> p;
		iss >> d;
		vect.push_back(p);
	}

	return vect;
}

vector< vector<int> > convert(string *list, int size)
{
	vector< vector<int> > vect;

	for (int idx = 0; idx < size; ++idx)
	{
		vect.push_back(convert(list[idx]));
	}

	return vect;
}

void Test1()
{
	string mines[] = { "000, 030, 030, 040, 000, 000, 000",
		"020, 020, 020, 010, 010, 010, 010" };
	int result[] = { 2,  2 };
	TEST( convert(mines, 2), 4, convert(result, INTARRAYSIZE(result)) );
}

void Test2()
{
	string mines[] = { "100, 000, 000, 000, 000, 000, 000",
  "100, 000, 000, 000, 000, 000, 000",
  "100, 000, 000, 000, 000, 000, 000",
  "100, 000, 000, 000, 000, 000, 000",
  "100, 000, 000, 000, 000, 000, 000" };
	int result[] = { 6,  2,  0,  0,  0 };
	TEST( convert(mines, 5), 8, convert(result, INTARRAYSIZE(result)) );
}

void Test3()
{
	string mines[] = { "050, 000, 000, 000, 000, 050, 000",
  "050, 000, 000, 000, 000, 050, 000",
  "050, 000, 000, 000, 000, 050, 000",
  "050, 000, 000, 000, 000, 050, 000",
  "050, 000, 000, 000, 000, 050, 000",
  "050, 000, 000, 000, 000, 050, 000",
  "050, 000, 000, 000, 000, 050, 000",
  "050, 000, 000, 000, 000, 050, 000",
  "050, 000, 000, 000, 000, 050, 000",
  "050, 000, 000, 000, 000, 050, 000" };
	int result[] = { 4,  4,  4,  4,  4,  4,  4,  2,  0,  0 };
	TEST( convert(mines, 10), 30, convert(result, INTARRAYSIZE(result)) );
}

void Test4()
{
	string mines[] = { "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004",
  "026, 012, 005, 013, 038, 002, 004" };
	int result[] = { 2,  2,  2,  2,  2,  2,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1 };
	TEST( convert(mines, 50), 56, convert(result, INTARRAYSIZE(result)) );
}

void Test5()
{
	string mines[] = { "100, 000, 000, 000, 000, 000, 000",
  "090, 010, 000, 000, 000, 000, 000",
  "080, 020, 000, 000, 000, 000, 000",
  "075, 025, 000, 000, 000, 000, 000",
  "050, 050, 000, 000, 000, 000, 000",
  "025, 075, 000, 000, 000, 000, 000",
  "020, 080, 000, 000, 000, 000, 000",
  "010, 090, 000, 000, 000, 000, 000",
  "000, 100, 000, 000, 000, 000, 000",
  "000, 090, 010, 000, 000, 000, 000",
  "000, 080, 020, 000, 000, 000, 000",
  "000, 075, 025, 000, 000, 000, 000",
  "000, 050, 050, 000, 000, 000, 000",
  "000, 025, 075, 000, 000, 000, 000",
  "000, 020, 080, 000, 000, 000, 000",
  "000, 010, 090, 000, 000, 000, 000",
  "000, 000, 100, 000, 000, 000, 000",
  "000, 000, 090, 010, 000, 000, 000",
  "000, 000, 080, 020, 000, 000, 000",
  "000, 000, 075, 025, 000, 000, 000",
  "000, 000, 050, 050, 000, 000, 000",
  "000, 000, 025, 075, 000, 000, 000",
  "000, 000, 020, 080, 000, 000, 000",
  "000, 000, 010, 090, 000, 000, 000",
  "000, 000, 000, 100, 000, 000, 000",
  "000, 000, 000, 100, 000, 000, 000",
  "000, 000, 000, 090, 010, 000, 000",
  "000, 000, 000, 080, 020, 000, 000",
  "000, 000, 000, 075, 025, 000, 000",
  "000, 000, 000, 050, 050, 000, 000",
  "000, 000, 000, 025, 075, 000, 000",
  "000, 000, 000, 020, 080, 000, 000",
  "000, 000, 000, 010, 090, 000, 000",
  "000, 000, 000, 000, 100, 000, 000",
  "000, 000, 000, 000, 090, 010, 000",
  "000, 000, 000, 000, 080, 020, 000",
  "000, 000, 000, 000, 075, 025, 000",
  "000, 000, 000, 000, 050, 050, 000",
  "000, 000, 000, 000, 025, 075, 000",
  "000, 000, 000, 000, 020, 080, 000",
  "000, 000, 000, 000, 010, 090, 000",
  "000, 000, 000, 000, 000, 100, 000",
  "000, 000, 000, 000, 000, 090, 010",
  "000, 000, 000, 000, 000, 080, 020",
  "000, 000, 000, 000, 000, 075, 025",
  "000, 000, 000, 000, 000, 050, 050",
  "000, 000, 000, 000, 000, 025, 075",
  "000, 000, 000, 000, 000, 020, 080",
  "000, 000, 000, 000, 000, 010, 090",
  "000, 000, 000, 000, 000, 000, 100" };
	int result[] = { 0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,  2,  2,  2,  2,  2,  3,  3,  3,  3,  3,  3,  3,  3,  3,  4,  4,  4,  4,  4,  4,  4,  4,  4,  5,  5,  5,  5,  5,  5,  5,  5,  5,  5,  6,  6 };
	TEST( convert(mines, 50), 150, convert(result, INTARRAYSIZE(result)) );
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

	getchar();
	return 0;
}
