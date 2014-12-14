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
#include <queue>
using namespace std;
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
/* https://www.topcoder.com/stat?c=problem_statement&pm=2288&rd=4725 */
	
struct node
{
	size_t weapons;
	size_t shots;
	node (size_t w, size_t s) : weapons(w), shots(s) {}

	bool operator<(const node &rhs) const
	{
		return this->shots > rhs.shots;
	}
};

class KiloManX
{
	bool visited[32768];
	priority_queue<node> pq;
public:
	int leastShots(vector<string> damageChart, vector<int> bossHealth);
};

int KiloManX::leastShots(vector<string> damageChart, vector<int> bossHealth)
{
	memset(visited, 0, sizeof(visited));
	pq.push(node(0, 0));

	size_t maxWeapons = (1 << damageChart[0].length()) - 1;
	while (!pq.empty())
	{
		node top = pq.top();

		pq.pop();

		if ( visited[top.weapons] ) continue;
		if ( top.weapons == maxWeapons )
			return top.shots;

		visited[top.weapons] = true;

		for (size_t i = 0, size = damageChart.size(); i < size; ++i)
		{
			if ((top.weapons >> i) & 1) continue;
			int best = bossHealth[i];
			for (size_t j = 0; j < size; ++j)
			{
				if (i == j) continue;
				size_t damage = damageChart[j][i] - '0';
				if ( ((top.weapons >> j) & 1) && damage)
				{
					int hits = bossHealth[i] / damage;
					if ( bossHealth[i] % damage ) ++hits;
					best = std::min(best, hits);
				}
			}
			pq.push(node(top.weapons | (1 << i), top.shots + best)); 
		}
	}
	return -1;
}

void TEST(vector<string> damageChart, vector<int> bossHealth, int expected)
{
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	KiloManX kiloManX;

	int result = kiloManX.leastShots(damageChart, bossHealth);
	
	assert( result == expected );

	end = clock();
	cpu_time_used = ((double) (end - start));
	cout<<"Time taken : "<<cpu_time_used<<endl;
}

vector< vector<int> > convert(string *list, int n)
{
	vector< vector<int> > ret(n, vector<int> (n));

	for (int i = 0; i< n; ++i)
	{
		string str = list[i];

		for (int j = 0, len = str.length(); j < len; ++j) {
			istringstream iss(str.substr(j,1));

			iss >> ret[i][j];
		}
	}

	return ret;
}

template <class T>
vector<T> convertEx(T *list, int n)
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
	string damageChart[]= {"070","500","140"};
	int bossHealth[]= {150,150,150};

TEST(convertEx(damageChart, SIZEOFARRAY(damageChart)), 
	convertEx(bossHealth, SIZEOFARRAY(bossHealth)), 218);
}

void Test2()
{
	string damageChart[]= {"1542", "7935", "1139", "8882"};
	int bossHealth[]= {150,150,150,150};

TEST(convertEx(damageChart, SIZEOFARRAY(damageChart)), 
	convertEx(bossHealth, SIZEOFARRAY(bossHealth)), 205);
}

void Test3()
{
	string damageChart[]= {"07", "40"};
	int bossHealth[]= {150,10};

TEST(convertEx(damageChart, SIZEOFARRAY(damageChart)), 
	convertEx(bossHealth, SIZEOFARRAY(bossHealth)), 48);
}

void Test4()
{
	string damageChart[]= {"198573618294842",
 "159819849819205",
 "698849290010992",
 "000000000000000",
 "139581938009384",
 "158919111891911",
 "182731827381787",
 "135788359198718",
 "187587819218927",
 "185783759199192",
 "857819038188122",
 "897387187472737",
 "159938981818247",
 "128974182773177",
 "135885818282838"};
	int bossHealth[]= {157, 1984, 577, 3001, 2003, 2984, 5988, 190003,
9000, 102930, 5938, 1000000, 1000000, 5892, 38};

TEST(convertEx(damageChart, SIZEOFARRAY(damageChart)), 
	convertEx(bossHealth, SIZEOFARRAY(bossHealth)), 260445);
}

void Test5()
{
	string damageChart[]= {"02111111", "10711111", "11071111", "11104111",
 "41110111", "11111031", "11111107", "11111210"};
	int bossHealth[]= {28,28,28,28,28,28,28,28};

TEST(convertEx(damageChart, SIZEOFARRAY(damageChart)), 
	convertEx(bossHealth, SIZEOFARRAY(bossHealth)), 92);
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
