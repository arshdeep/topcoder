#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <time.h>
#include <cassert>
using namespace std;
/* https://www.topcoder.com/stat?c=problem_statement&pm=7921 */
/* https://www.topcoder.com/tc?module=Static&d1=tutorials&d2=disjointDataStructure */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define memSet(a, val) memset(a, val, sizeof(a))
using namespace std;

#ifdef PRIM 
int weight[50][50];
string idMap[50][50];
bool visited[50];
int mst[50][50];

struct Road
{
	size_t cost, parent, vertex;

	Road(size_t _vertex, size_t _parent, size_t cst) : vertex(_vertex), parent(_parent), cost(cst) {}
	bool operator<(const Road &rhs) const
	{
		if (this->cost != rhs.cost) return this->cost > rhs.cost;
		return idMap[this->vertex][this->parent] > idMap[rhs.vertex][rhs.parent];
		return false;
	}
};


class RoadReconstruction
{
	map<string, int> mapping;
	int roadCount;
	int cityID(string city);
	void parseInput(const vector<string> &roads);

public:
	RoadReconstruction()
	{
		roadCount = 0;
		memSet(idMap, 0);
		memSet(weight, -1);
		memSet(visited, 0);
	}

	string selectReconstruction(const vector<string> &roads);
};

int RoadReconstruction::cityID(string city)
{
	map<string, int>::iterator itr = mapping.find(city);
	if (itr != mapping.end()) return itr->second;

	mapping.insert(make_pair(city, roadCount++));

	return roadCount - 1;
}

void RoadReconstruction::parseInput(const vector<string> &roads)
{
	for (size_t i = 0, size = roads.size(); i < size; ++i)
	{
		istringstream iss(roads[i]);
		string id, road1, road2;
		size_t cost = 0;

		iss >> id;
		iss >> road1;
		iss >> road2;
		if (!iss.eof())
			iss >> cost;
		int city1 = cityID(road1);
		int city2 = cityID(road2);

		if (weight[city1][city2] > cost || weight[city1][city2] == -1 || (weight[city1][city2] == cost && idMap[city1][city2] > id))
		{
			weight[city1][city2] = weight[city2][city1] = cost;
			idMap[city1][city2] = idMap[city2][city1] = id;
		}
	}
}

int dfs(int order, int vertex)
{
	int ret = 1;
	visited[vertex] = true;

	for (int i = 0; i < order; ++i)
	{
		if (!visited[i] && weight[vertex][i] != -1)
		{
			ret += dfs(order, i);
		}
	}

	return ret;
}

void primMST(int order)
{
	memSet(visited, 0);
	memSet(mst, -1);
	priority_queue<Road> pq;

	pq.push(Road(0, 0, 0));

	while(!pq.empty())
	{
		Road top = pq.top();
		pq.pop();
		if (visited[top.vertex]) continue;
		visited[top.vertex] = true;
		mst[top.vertex][top.parent] = mst[top.parent][top.vertex] = top.cost;

		for (int i = 0; i < order; ++i)
		{
			int &w = weight[top.vertex][i];
			if (w != -1)
				pq.push(Road(i, top.vertex, w));
		}
	}
}

string RoadReconstruction::selectReconstruction(const vector<string> &roads)
{
	parseInput(roads);

	if (dfs(roadCount, 0) != roadCount) return "IMPOSSIBLE";

	primMST(roadCount);
	vector<string> retList;
	for (int i = 0; i < roadCount; ++i)
	{
		for (int j = i; j < roadCount; ++j)
		{
			if (mst[i][j] > 0)
			{
				retList.push_back(idMap[i][j]);
			}
		}
	}
	sort(retList.begin(), retList.end());
	string ret = "";
	for (int i = 0; i < retList.size(); ++i)
	{
		if (ret.length() == 0)
		{
			ret = retList[i];
		}
		else
		{
			ret += " ";
			ret += retList[i];
		}
	}
	return ret;
}
#else
#define ALL(a) a.begin(), a.end()
#define REP(size) for (int i = 0; i < (int)size; ++i)
class RoadReconstruction
{
	int rank[51];
	int parent[51];
	vector<pair<int, int>> ok;
	vector< pair< int, pair<string, pair<int, int>> > > edges;
	map<string, int> mapping;
	int roadCount;
	int cityID(string city);
	void parseInput(const vector<string> &roads);
	string kruskalMST();
	void unionSet(int a, int b);
	int findSet(int x);
public:
	RoadReconstruction()
	{
		roadCount = 0;
		memSet(rank, 0);
	}

	string selectReconstruction(const vector<string> &roads);
};

int RoadReconstruction::cityID(string city)
{
	map<string, int>::iterator itr = mapping.find(city);
	if (itr != mapping.end()) return itr->second;

	mapping.insert(make_pair(city, roadCount++));

	return roadCount - 1;
}

void RoadReconstruction::parseInput(const vector<string> &roads)
{
	for (size_t i = 0, size = roads.size(); i < size; ++i)
	{
		istringstream iss(roads[i]);
		string id, road1, road2;
		size_t cost = 0;

		iss >> id;
		iss >> road1;
		iss >> road2;
		if (!iss.eof())
			iss >> cost;
		int city1 = cityID(road1);
		int city2 = cityID(road2);

		if (cost == 0)
		{
			ok.push_back(make_pair(city1, city2));
		}
		else
		{
			edges.push_back(make_pair(cost, make_pair(id, make_pair(city1, city2) ) ) );
		}
	}
}

void RoadReconstruction::unionSet(int a, int b)
{
	int min = std::min(a, b);
	int max = std::max(a, b);

	rank[max] += rank[min];
	rank[min] = 1;
	parent[min] = parent[max];
}

int RoadReconstruction::findSet(int x)
{
	if (parent[x] != x)
		parent[x] = findSet(parent[x]);
	return parent[x];
}

string RoadReconstruction::kruskalMST()
{
	int mergedSets = 0;
	REP(ok.size())
	{
		pair<int, int> city = ok[i];
		int set1 = findSet(city.first);
		int set2 = findSet(city.second);
		if (set1 != set2)
		{
			unionSet(set1, set2);
			++mergedSets;
		}
	}
	vector<string> result;
	REP(edges.size())
	{
		if (mergedSets == roadCount - 1)
			break;
		pair<int, int> city = edges[i].second.second;
		int set1 = findSet(city.first);
		int set2 = findSet(city.second);
		if (set1 != set2)
		{
			unionSet(set1, set2);
			++mergedSets;
			result.push_back(edges[i].second.first);
		}
	}
	if (mergedSets == roadCount - 1)
	{
		sort(ALL(result));
		string ret = "";
		REP(result.size())
		{
			if (ret.length() == 0)
			{
				ret = result[i];
			}
			else
			{
				ret += " ";
				ret += result[i];
			}
		}

		return ret;
	}
	else
		return "IMPOSSIBLE";
}

string RoadReconstruction::selectReconstruction(const vector<string> &roads)
{
	parseInput(roads);
	REP(roadCount)
	{
		parent[i] = i;
	}

	sort(ALL(edges));

	return kruskalMST();
}
#endif

void TEST(vector<string> roads, string expected)
{
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	RoadReconstruction roadReconstruction;

	string result = roadReconstruction.selectReconstruction(roads);
	assert( expected.compare(result) == 0);

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
	string test[] = {"M1 Moscow Kiev 1", "M2 Minsk Kiev", "M3 Minsk Warsaw"};
	TEST(convert(test, SIZEOFARRAY(test)), "M1");
}

void Test2()
{
	string test[] = {"M1 Moscow StPetersburg 1", "M2 Moscow Saratov 2", "S0 Saratov StPetersburg"};
	TEST(convert(test, SIZEOFARRAY(test)), "M1");
}

void Test3()
{
	string test[] = {"R1 NY Washington", "M1 Moscow StPetersburg 1000"};
	TEST(convert(test, SIZEOFARRAY(test)), "IMPOSSIBLE");
}

void Test4()
{
	string test[] = {"B1 Bratislava Havka"};
	TEST(convert(test, SIZEOFARRAY(test)), "");
}

void Test5()
{
	string test[] = {"O1 Beetown Fearnot 6","N7 Fearnot Hornytown","M8 Hornytown Belcher 10",
 "L5 Belcher Fearnot 8","C7 Fearnot Beetown 4","K7 Quiggleville Beetown 12",
 "H4 Beetown DryFork 6","Z0 Hornytown Belcher 1","O5 Belcher Quiggleville 10",
 "U7 Quiggleville Fearnot 2","A8 Fearnot Quiggleville 8","T6 Beetown DryFork 17",
 "E8 Quiggleville DryFork 8","Y4 DryFork Quiggleville 4","Q8 Hornytown DryFork 2",
 "J9 Quiggleville DryFork 19","M4 DryFork Quiggleville 7","T1 DryFork Fearnot 9",
 "G4 Fearnot DryFork 6","V9 Hornytown Beetown 5","O6 Quiggleville Beetown 4",
 "L8 Beetown Roachtown 5","D5 Belcher DryFork 8","W5 Belcher DryFork 1"};
	TEST(convert(test, SIZEOFARRAY(test)), "C7 L8 U7 W5 Z0");

}

void Test6()
{
	string test[] =	{"U5 Ogle Belcher 4", "P5 Okay Ogle 9", "X0 Belcher Fearnot 4", "R5 Okay Odd 2", "H0 Belcher Fearnot", "P1 Beetown Frankenstein 5", "N3 Ogle Odd 2", "N8 Fearnot Ogle 1", "R3 Belcher Ogle", "R1 Odd Okay 3", "V8 Fearnot Okay 2", "B8 Belcher Fearnot 9", "T1 Belcher Ogle"};
	TEST(convert(test, SIZEOFARRAY(test)), "IMPOSSIBLE");
}

void Test7()
{
	string test[] ={"H8 Beetown Ogle 7", "I8 Okay Odd 3", "U3 Okay Ogle 3", "A9 Fearnot Odd 1", "K1 Beetown Odd 3", "O8 Okay Beetown 1", "N4 Beetown Okay 1", "Q7 Fearnot Ogle 4", "N1 Beetown Okay 8", "J0 Ogle Okay 8", "Q3 Beetown Ogle 3", "X3 Belcher Fearnot"};
	TEST(convert(test, SIZEOFARRAY(test)), "A9 I8 N4 Q3");
}

void Test8()
{
	string test[] ={"F4 Odd Frankenstein 8", "T9 Okay Odd 7", "N9 Panic Beetown", "J1 Belcher Ogle 8", "G0 Ogle Belcher 10", "R4 Belcher Beetown 6", "L4 Belcher Footville 8", "I6 Panic Ogle 3", "O8 Odd Peculiar 10", "V4 Ogle Belcher 10", "V7 Fearnot Peculiar 4", "U7 Beetown Fearnot 10", "S0 Belcher Frankenstein 1", "L7 Belcher Ogle 3", "Z6 Ogle Belcher 10", "G5 Peculiar Beetown 6", "L1 Beetown Footville 8", "J2 Peculiar Panic 3", "U5 Peculiar Odd 7", "W5 Odd Beetown 6", "C4 Frankenstein Peculiar 3", "F5 Beetown Footville 3", "O3 Okay Ogle 10", "W0 Okay Panic 1", "G8 Okay Odd 5", "H9 Belcher Ogle 7", "O0 Fearnot Frankenstein 2", "M9 Odd Belcher 5", "D1 Belcher Beetown 5", "A7 Frankenstein Belcher 8"};
	TEST(convert(test, SIZEOFARRAY(test)), "C4 F5 G8 I6 J2 O0 S0 W0");
}

void Test9()
{
	string test[] ={"A1 Panic Ogle", "K9 Footville Frankenstein 10", "V3 Odd Okay", "W3 Okay Peculiar 1", "T2 Panic Fearnot", "C4 Okay Beetown 7", "E6 Belcher Panic", "Y4 Okay Belcher 3", "R9 Ogle Frankenstein 10", "J2 Panic Beetown 1", "D5 Footville Panic 3", "A4 Footville Panic 5", "Y1 Fearnot Odd 4", "T8 Footville Frankenstein 9", "U5 Footville Okay 7", "N1 Odd Footville 10", "G5 Okay Odd 4", "X3 Frankenstein Okay", "H5 Okay Frankenstein 8", "H3 Belcher Okay 6", "Q0 Odd Peculiar 4", "X7 Frankenstein Belcher 1", "W0 Okay Ogle 3", "C2 Beetown Ogle 5", "F2 Belcher Footville 9", "D7 Footville Frankenstein 9", "G1 Peculiar Frankenstein 3", "C6 Peculiar Ogle 4", "F4 Okay Frankenstein 8", "U0 Ogle Frankenstein 9", "F6 Ogle Footville 9", "X1 Ogle Okay 1", "O4 Footville Panic 5", "K6 Fearnot Ogle 1", "K7 Frankenstein Okay 2", "B2 Footville Fearnot 7", "S7 Ogle Footville 10", "E7 Fearnot Peculiar 9", "R1 Belcher Beetown 10", "L4 Okay Belcher 4"};
	TEST(convert(test, SIZEOFARRAY(test)), "D5 J2 W3 X1");
}

void Test10()
{
	string test[] ={"S2 Odd Beetown 10", "U3 Fearnot Frankenstein 9", "U0 Frankenstein Fearnot 9", "D5 Belcher Odd 5", "B3 Footville Beetown 7", "O4 Beetown Okay 6", "P1 Panic Fearnot 6", "N3 Frankenstein Odd 1", "O8 Odd Beetown 2", "R2 Panic Okay 1", "Q8 Odd Beetown 6", "Y7 Footville Frankenstein 3", "U8 Odd Belcher 5", "M9 Blueballs Panic 10", "W4 Porkey Belcher 6", "H2 Ogle Gaylordsville 4", "V8 Footville Gaylordsville 5", "D8 Gaylordsville Odd 7", "Q9 Beetown Fearnot 4", "N8 Ogle Gaylordsville 11", "G3 Ogle Blueballs 5", "B1 Ogle Porkey 1", "J7 Frankenstein Panic 5", "I0 Fearnot Okay 5", "S3 Blueballs Peculiar 9", "P3 Beetown Porkey 8", "D9 Blueballs Footville 4", "Y1 Beetown Peculiar 3", "W5 Footville Frankenstein 3", "V3 Panic Footville 3", "P4 Okay Beetown 4", "K2 Odd Porkey 8", "R4 Fearnot Okay 11", "O3 Beetown Footville 3", "A7 Frankenstein Porkey 2", "C3 Porkey Panic 7", "M5 Gaylordsville Peculiar 3", "L0 Fearnot Odd 9", "S4 Porkey Belcher 11", "E0 Frankenstein Fearnot 3", "T1 Gaylordsville Beetown 9", "Y0 Ogle Odd 8", "B0 Beetown Odd 6", "Z7 Frankenstein Odd 10", "I7 Gaylordsville Belcher 3", "E1 Frankenstein Panic 8", "Z3 Belcher Porkey 2", "L1 Footville Odd 9", "F2 Ogle Blueballs 4", "Q7 Beetown Porkey 1"};
	TEST(convert(test, SIZEOFARRAY(test)), "A7 B1 D9 E0 I7 M5 N3 O3 Q7 R2 V3 Z3");
}

void Test11()
{
	string test[] ={"O1 Beetown Fearnot 6", "N7 Fearnot Hornytown", "M8 Hornytown Belcher 10", "L5 Belcher Fearnot 8", "C7 Fearnot Beetown 4", "K7 Quiggleville Beetown 12", "H4 Beetown DryFork 6", "Z0 Hornytown Belcher 1", "O5 Belcher Quiggleville 10", "U7 Quiggleville Fearnot 2", "A8 Fearnot Quiggleville 8", "T6 Beetown DryFork 17", "E8 Quiggleville DryFork 8", "Y4 DryFork Quiggleville 4", "Q8 Hornytown DryFork 2", "J9 Quiggleville DryFork 19", "M4 DryFork Quiggleville 7", "T1 DryFork Fearnot 9", "G4 Fearnot DryFork 6", "V9 Hornytown Beetown 5", "O6 Quiggleville Beetown 4", "L8 Beetown Roachtown 5", "D5 Belcher DryFork 8", "W5 Belcher DryFork 1"};
	TEST(convert(test, SIZEOFARRAY(test)), "C7 L8 U7 W5 Z0");
}

void Test12()
{
	string test[] =	{"A0 A B 11", "B0 B C 1"};
	TEST(convert(test, SIZEOFARRAY(test)), "A0 B0");
}

void Test13()
{
	string test[] =	{"P0 Romance Porkey 7", "J7 Fearnot Porkey 43", "Q5 Chestnut Boring 22", "N2 Buddha Panic 55", "D0 Romance Porkey 1", "I7 Panic Chestnut", "N5 Gaylordsville Fearnot 79", "Y6 Beetown Peculiar 2", "W3 Romance Buddha 38", "E4 Footville Okay 9", "G0 Quiggleville Gaylordsville 91", "N1 Gaylordsville Chestnut 5", "H5 Roachtown Boring 21", "O3 Ogle Blueballs 98", "U7 Ogle Chestnut 100", "R2 Boring Porkey 52", "E7 Odd Gaylordsville 50", "F8 Belcher Okay 42", "H2 Quiggleville Roachtown 35", "L8 Buddha Roachtown 14", "B3 Fearnot Chestnut 68", "T0 Footville Roachtown", "H4 Chestnut Odd 30", "M0 Romance Panic", "J5 Panic Odd 27", "K7 Roachtown Blueballs", "I1 Porkey Buddha 47", "V1 Boring Okay 82", "V2 Peculiar Roachtown 71", "U9 Buddha Peculiar 73", "X6 Footville Peculiar", "O2 Beetown Quiggleville 34", "K0 Belcher Peculiar 23", "Z0 Belcher Roachtown 59", "X1 Gaylordsville Buddha", "Z6 Panic Boring 25", "V5 Footville Quiggleville 95", "O0 Odd Blueballs", "X9 Porkey Fearnot 11", "J9 Peculiar Footville 35", "F9 Chestnut Porkey 61", "I0 Peculiar Boring 79", "K8 Ogle Belcher 56", "P6 Frankenstein Chestnut 43", "R6 Odd Peculiar 13", "B1 Buddha Hooker 36", "Y1 Buddha Okay 44", "C0 Belcher Peculiar 95"};
	TEST(convert(test, SIZEOFARRAY(test)), "B1 D0 E4 H5 K0 K8 L8 N1 O2 P6 X9 Y6");
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
