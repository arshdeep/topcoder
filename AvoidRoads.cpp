#include <iostream>
#include <cstdio>
#include <vector>
#include <cassert>
#include <sstream>
#include <set>

using namespace std;
/* AvoidRoads http://topcoder.bgcoder.com/print.php?id=382 */

class AvoidRoads
{
private:
	set< pair< pair< int, int >, pair< int, int > > > bad;
	vector<string> avoidRoads;
	int height;
	int width;

	void tokenize()
	{
		for (vector<string>::const_iterator itr = avoidRoads.begin(), endItr = avoidRoads.end();
				itr != endItr; ++itr) {
			istringstream iss(*itr);
			int lx, ly, rx, ry;

			if (iss >> lx, iss >> ly, iss >> rx, iss >> ry)
			{
				bad.insert( make_pair( make_pair(lx, ly), make_pair(rx, ry) ) );
				bad.insert( make_pair( make_pair(rx, ry), make_pair(lx, ly) ) );
			}
		}
	}

public:
	AvoidRoads(int x, int y, vector<string> &avoidRoadsVect)
	{
		height = y;
		width = x;
		avoidRoads = avoidRoadsVect;
	}

	__int64 numWays()
	{
		vector< vector<__int64> > result(width + 1, vector<__int64>(height + 1));
		result[0][0] = 1;
		tokenize();

		for (int i = 0; i <= width; ++i)
		{
			for (int j = 0; j <= height; ++j)
			{
				if (i > 0 && !bad.count( make_pair( make_pair(i - 1, j), make_pair(i, j) ) ) )
				{
					result[i][j] += result[i - 1][j];
				}
				if (j > 0 && !bad.count( make_pair( make_pair(i, j - 1), make_pair(i, j) ) ) )
				{
					result[i][j] += result[i][j - 1];
				}
			}
		}

		return result[width][height];
	}
};

__int64 TEST(int x, int y, vector<string> &avoidRoads, __int64 expected)
{
	AvoidRoads avoid(x, y, avoidRoads);
	__int64 res = avoid.numWays();

	assert(res == expected);

	return res;
}

vector<string> convert(string *list, int size)
{
	vector<string> vect;

	for (int idx = 0; idx < size; ++idx)
	{
		vect.push_back(list[idx]);
	}

	return vect;
}
int main()
{
    vector<string> avoidRoads;

    avoidRoads.push_back("");
    cout << TEST(1, 1, avoidRoads, 2)<<endl;

    avoidRoads.clear();
    avoidRoads.push_back("0 0 1 0");
    avoidRoads.push_back("1 2 2 2");
    avoidRoads.push_back("1 1 2 1");

    cout << TEST(2, 2, avoidRoads, 0)<<endl;
    avoidRoads.clear();
    avoidRoads.push_back("0 0 0 1");
    avoidRoads.push_back("6 6 5 6");
 
	cout << TEST(6, 6, avoidRoads, 252)<<endl;

    avoidRoads.clear();
	avoidRoads.push_back("");
	cout << TEST(35, 31, avoidRoads, 6406484391866534976)<<endl;
    avoidRoads.clear();
    avoidRoads.push_back("0 2 0 3");
    avoidRoads.push_back("1 2 1 3");
    avoidRoads.push_back("2 2 2 3");
    avoidRoads.push_back("3 2 3 3");
    avoidRoads.push_back("4 2 4 3");
    avoidRoads.push_back("5 2 5 3");
    avoidRoads.push_back("6 2 6 3");
    avoidRoads.push_back("7 2 7 3");

    avoidRoads.push_back("8 2 8 3");
    avoidRoads.push_back("9 2 9 3");
    cout << TEST(10, 100, avoidRoads, 66)<<endl;

	string bad[] = {"0 2 0 3", "1 2 1 3", "2 2 2 3", "3 2 3 3", "4 2 4 3", "5 2 5 3", "6 2 6 3", "7 2 7 3", "8 2 8 3", "9 2 9 3"};

	cout << TEST(20, 100, convert(bad,10), 2602994845445631)<<endl;

	string bad2[] = {"16 19 16 18", "11 7 11 6", "7 17 7 16", "20 8 20 7", "18 16 18 17",
		"8 21 8 22", "17 8 17 9", "9 21 8 21", "10 4 10 3", "1 20 1 21", "18 13 18 14", "13 18 13 17",
		"20 11 20 12", "20 7 20 8", "24 0 24 1", "5 23 4 23", "5 2 5 1", "13 17 13 16", "17 8 17 7", "13 23 14 23",
		"1 15 2 15", "3 12 3 11", "22 1 23 1", "7 24 6 24", "5 8 6 8", "17 1 18 1", "18 6 19 6", "19 12 18 12", "21 17 21 18",
		"17 10 17 9", "10 2 10 1", "4 7 3 7", "11 22 11 21", "20 22 20 23", "10 9 10 8",
		"1 3 1 4", "4 10 4 9", "14 8 15 8", "14 21 14 20", "12 20 12 21", "10 18 9 18", "13 16 13 17", "24 5 24 4",
		"17 15 17 16", "8 7 7 7", "1 9 0 9", "5 14 5 15", "10 5 11 5", "1 2 2 2", "1 15 1 16"};

	cout << TEST(24, 24, convert(bad2, 50), 5402543193164)<<endl;

	string bad3[] =  {"1 3 0 3", "0 4 0 3", "6 1 7 1", "4 7 4 8", "2 6 3 6",
		"0 6 0 7", "9 3 10 3", "2 4 2 3", "2 3 2 4", "7 6 7 7", "6 3 6 4", "8 7 8 8", 
		"1 4 1 5", "0 2 1 2", "4 3 5 3", "2 9 2 10", "1 1 1 2", "9 5 8 5", "2 7 2 8", "6 0 7 0", "6 8 7 8",
		"2 2 2 1", "2 9 1 9", "5 8 5 9", "1 6 2 6", "9 4 8 4", "4 1 3 1", "7 5 8 5", "5 0 5 1", "3 6 2 6", "7 9 8 9", "6 8 7 8", "4 2 4 3",
		"5 0 4 0", "7 2 7 3", "4 4 5 4", "8 9 7 9", "5 3 6 3", "3 7 3 6", "0 8 1 8", 
		"7 5 7 6", "9 3 10 3", "9 6 10 6", "1 9 1 10", "7 3 8 3", "4 6 4 7", "3 6 4 6", "3 1 3 0", "6 1 6 0", "8 3 7 3"};

	cout << TEST(19, 100, convert(bad3, 50), 1166309411843295530)<<endl;

    getchar();
    return 0;
}
