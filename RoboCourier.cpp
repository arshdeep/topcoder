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
/* https://www.topcoder.com/stat?c=problem_statement&pm=1749&rd=4555 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define memSet(a, val) memset(a, val, sizeof(a))

struct Node
{
	int x, y, time, accelrate, dir;

	Node(int a = 0, int b = 0, int c = 0, int d = 0, int e = 0) : x(a), y(b), time(c), accelrate(d), dir(e) {}
	bool operator<(const Node &rhs) const
	{
		if (this->time == rhs.time) return this->accelrate < rhs.accelrate;
		return this->time > rhs.time;
	}
};

bool edge[1000][1000][6];
bool done[1000][1000][6];
const int dx[6]={0,1,1,0,-1,-1};
const int dy[6]={1,1,0,-1,-1,0};

class RoboCourier
{
	int startX, startY, endX, endY;
	void buildGraph(const vector<string> &path);
public:
	int timeToDeliver(vector<string> path);
};

void RoboCourier::buildGraph(const vector<string> &path)
{
	int dir = 0;
	endX = startX;
	endY = startY;

	for (int i = 0, size = path.size(); i < size; ++i)
	{
		string str = path[i];
		for (int j = 0, len = str.length(); j < len; ++j)
		{
			switch(str[j])
			{
				case 'L':
					dir = (dir + 5) % 6; break;
				case 'R':
					dir = (dir + 1) % 6; break;
				case 'F':
				{
					edge[endX][endY][dir] = true;
					endX += dx[dir];
					endY += dy[dir];
					edge[endX][endY][(dir + 3) % 6] = true;
				}
				break;
			}
		}
	}
}
int RoboCourier::timeToDeliver(vector<string> path)
{
	startX = 500;
	startY = 500;
	memSet(edge, 0);
	memSet(done, 0);
	buildGraph(path);
	priority_queue<Node> pq;
	pq.push(Node(startX, startY));

	while(!pq.empty())
	{
		Node top = pq.top();
		pq.pop();

		if (top.x == endX && top.y == endY)
			return top.time;
		else if (done[top.x][top.y][top.dir])
			continue;

		done[top.x][top.y][top.dir] = true;

		for (int d = 0; d < 6; ++d)
		{
			if (!edge[top.x][top.y][d])
				continue;
			int time = 0;

			if (d == top.dir)
			{
				time = top.accelrate > 1 ? 2 : 4;
				pq.push(Node(top.x + dx[d], top.y + dy[d], top.time + time, top.accelrate + 1, d));
			}
			else {
				time = std::min((d + 6 - top.dir) % 6, (top.dir + 6 - d) % 6);
				pq.push(Node(top.x + dx[d], top.y + dy[d], top.time + time* 3 + 4, 1, d));
			}
		}
	}
	return 0;
}

void TEST(vector<string> path, int expected)
{
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	RoboCourier roboCourier;

	int result = roboCourier.timeToDeliver(path);

	assert( result == expected );

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
	string test[] = { "FRRFLLFLLFRRFLF" };
	TEST(convert(test, SIZEOFARRAY(test)), 15);
}

void Test2()
{
	string test[] = { "RFLLF" };
	TEST(convert(test, SIZEOFARRAY(test)), 17);
}

void Test3()
{
	string test[] = { "FLFRRFRFRRFLLFRRF" };
	TEST(convert(test, SIZEOFARRAY(test)), 0);
}

void Test4()
{
	string test[] = { "FFFFFFFFFRRFFFFFFRRFFFFF",
  "FLLFFFFFFLLFFFFFFRRFFFF" };
	TEST(convert(test, SIZEOFARRAY(test)), 44);
}

void Test5()
{
	string test[] = { "RFLLFLFLFRFRRFFFRFFRFFRRFLFFRLRRFFLFFLFLLFRFLFLRFF",
  "RFFLFLFFRFFLLFLLFRFRFLRLFLRRFLRFLFFLFFFLFLFFRLFRLF",
  "LLFLFLRLRRFLFLFRLFRF" };
	TEST(convert(test, SIZEOFARRAY(test)), 24);
}

void Test6()
{
	string test[] = { "LLFLFRLRRLRFFLRRRRFFFLRFFRRRLLFLFLLRLRFFLFRRFFFLFL",
  "RLFFRRLRLRRFFFLLLRFRLLRFFLFRLFRRFRRRFRLRLRLFFLLFLF",
  "FRFLRFRRLLLRFFRRRLRFLFRRFLFFRLFLFLFRLLLLFRLLRFLLLF",
  "FFLFRFRRFLLFFLLLFFRLLFLRRFRLFFFRRFFFLLRFFLRFRRRLLR",
  "FFFRRLLFLLRLFRRLRLLFFFLFLRFFRLRLLFLRLFFLLFFLLFFFRR",
  "LRFRRFLRRLRRLRFFFLLLLRRLRFFLFRFFRLLRFLFRRFLFLFFLFR",
  "RFRRLRRFLFFFLLRFLFRRFRFLRLRLLLLFLFFFLFRLLRFRLFRLFR",
  "LLFLFRLFFFFFFFRRLRLRLLRFLRLRRRRRRRRLFLFLFLRFLFRLFF",
  "RLFRRLLRRRRFFFRRRLLLLRRLFFLLLLLRFFFFRFRRLRRRFFFLLF",
  "FFFFLRRLRFLLRRLRLRFRRRRLFLLRFLRRFFFRFRLFFRLLFFRRLL" };
	TEST(convert(test, SIZEOFARRAY(test)), 169);
}

void Test7()
{
	string test[] = 	{"FLFRRLLFLLRLLRLLLRFRRLLLRRLLRLLLFLLRLRRLLRFLLFLLLR", "RRFFLLFLRFFRLLLRRLLRFLFLFRRFLLRRLLFLLFRRFRLRFLRLFR", "RFFLFFRRFFLLFFFRLFFRRFRLLFLLRRFFRLFRFRLLFLLRFLLRLF", "RRRLRLLFRFRRLLLLLFRFRLLRFLFLFFRFRRLLRFFLLRLRLRFLRL", "RFFRFLLLRLRRLFFRFLLFFRLRRLRLRLLLLFLLLLLFLRRFLRFRLL", "FFLFRLRRRLLFLFLLRLLRLLRLRFLLRLFRFRFRFLFLLRRLLLLFFF", "LRFLRFLLFLLRLFFLFFLLLRLLRLLRFRLRLRLLFFRRLFFLLFLRLL", "FLLRLRRLLFFLLFLLLRLRFRFFRRLRFRLLRRLRFRFRRLLFLRLLLL", "LFFLRLRLLRRFFRLLRFFLLFLRRRFLFLFLLRLFFLLRFLFLLLRLFF", "LLFRLLFLFFRLFFLLFLRRLLFLRFFFRLLFFRLFRFRLLFFFLLRLRL"};
	TEST(convert(test, SIZEOFARRAY(test)), 145);
}

void Test8()
{
	string test[] =	{"FLRLRFLRLRFLFLRFFFFLRFLFFFLRFFRLFRLRFLRLRRFRLRFRRF", "LRFFFRRFFLFLFLFRLLFFFLFFLFLLFLFFLFFFRFFFFLRLRLFLRF", "LFRLFLFFLFLRRFLRFRLFRLLFLRFLFLRFFFLRFLFRLFLRRFFLRL", "LRFFLLFLRLRLLFFFRFFRLFRFRLRLFFFRLRFLFLFLFRLRRFLRRF", "FLFFLFLFRLRLRLFRFFLLFLFLRFFRRFLRFFLRLRLRFRLFLFLFLR", "LFLRRFLLFLFLFLFFLLFFFLFFRFRLRFLFRFRLFLRFFLFRRFFFLL", "RFFFLRLFFRLFRFLRLFRFLFRFLFRRLFFLFRLRLLFRLFLFFFLFFR", "LRLLFFRFRFRLRLRFFRLFFLLFFFLRFFRFLFRFLRLRLRLFLFLFLF", "LLFLFRFLLFFLFFLRLFRRFLRLRLRFFRLFFLRFLFFRFLFLFLFFLR", "FFFLLFRFRLLFFFLRLFLRLFRLRRFLRFLRFFRFRFLFLLRFLFLRFL"};
	TEST(convert(test, SIZEOFARRAY(test)), 169);
}

void Test9()
{
	string test[] =	{"FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF"};
	TEST(convert(test, SIZEOFARRAY(test)), 1004);
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
