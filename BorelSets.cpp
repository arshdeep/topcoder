#include <climits>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <unordered_set>
#include <map>
 #include <time.h>
using namespace std;
/* BorelSets http://community.topcoder.com/stat?c=problem_statement&pm=2322&rd=5003 */
/* solution : http://community.topcoder.com/tc?module=Static&d1=match_editorials&d2=tccc04_qual_4
 http://apps.topcoder.com/forums/;jsessionid=E24D4398F8A31C949256E997D88A5654?module=Thread&threadID=242932&messageID=242931&mc=4&view=tree#242931 */ 

int createField(string field)
{
	int ret = 0;

	if (field.length() > 0)
	{
		istringstream iss(field);

		while ( !iss.eof() )
		{
			int num = 0;

			iss >> num;
			ret |= 1 << (num - 1);
		}
	}

	return ret;
}

int howMany(int size, vector<string> subsets)
{
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	unordered_set<int> sets;
	queue<int> bfs;

	for (vector<string>::iterator itr = subsets.begin(), endItr = subsets.end();
			itr != endItr; ++itr) {
		int set = createField(*itr);

		bfs.push(set);
		sets.insert(set);
	}

	while ( !bfs.empty() )
	{
		int front = bfs.front();
		int tmp = (1 << size) - 1;
		int cmp = (~front) & tmp;

		if (sets.find(cmp) == sets.end())
		{
			sets.insert(cmp);
			bfs.push(cmp);
		}

		for (unordered_set<int>::iterator itr = sets.begin(), endItr = sets.end();
				itr != endItr; ++itr) {
			int unionSet = *itr | front;

			if (sets.find(unionSet) == sets.end())
			{
				sets.insert(unionSet);
				bfs.push(unionSet);
			}
		}
		bfs.pop();
	}

	end = clock();
	cpu_time_used = ((double) (end - start));
	cout<<"Time:"<<cpu_time_used<<endl;

	return sets.size();
}

int main(int argc, char *argv[])
{
	vector<string> subsets;

	subsets.push_back("1 2");
	subsets.push_back("");

	cout<<howMany(4, subsets)<<endl;

	subsets.clear();

	subsets.push_back("");
	subsets.push_back("1");
	subsets.push_back("2");
	subsets.push_back("3");
	subsets.push_back("4");
	subsets.push_back("5");
	subsets.push_back("6");
	subsets.push_back("7");
	subsets.push_back("8");
	subsets.push_back("9");
	subsets.push_back("10");
	cout<<howMany(10, subsets)<<endl;

	subsets.clear();

	subsets.push_back("");
	subsets.push_back("1 1 2");
	subsets.push_back("1 1 2 2 1 1");
	subsets.push_back("2 1 1");

	cout<<howMany(5, subsets)<<endl;

	getchar(); 
	return 0;
}