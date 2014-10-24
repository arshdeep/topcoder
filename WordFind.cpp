#include <climits>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
#include <set>
#include <queue>
#include <iterator>
#include <sstream>
#include <cassert>
#include <stack>
using namespace std;

/*WordFind : http://community.topcoder.com/stat?c=problem_statement&pm=3972&rd=6521 */

struct Point
{
	int x;
	int y;
	Point() : x(-1), y(-1) {}
	Point(int left, int top) : x(left), y(top) {}
};

struct SearchState
{
	int compareIndex;
	struct Point startPoint;
	struct Point comparePoint;
	SearchState(int c, Point p, Point cp) : compareIndex(c), startPoint(p), comparePoint(cp) {}
};

typedef queue<SearchState> BfsSearch;

Point findWord(const vector<vector<char>> &charGrid, const string &searchStr)
{
	BfsSearch bfs;
	int gridSize = charGrid.size();
	int col = charGrid[0].size();
	vector<vector<vector<int>>> visitState(searchStr.length(), vector<vector<int>>(gridSize, vector<int>(col)) );

	bfs.push( SearchState(0, Point(-1,-1), Point(0,0)) );

	while (bfs.size())
	{
		SearchState state = bfs.front();

		bfs.pop();
		if (state.comparePoint.x < gridSize && state.comparePoint.y < col
			&& !visitState[state.compareIndex][state.comparePoint.x][state.comparePoint.y])
		{
			visitState[state.compareIndex][state.comparePoint.x][state.comparePoint.y] = 1;
			if (charGrid[state.comparePoint.x][state.comparePoint.y] == searchStr[state.compareIndex])
			{
				if (state.compareIndex == searchStr.length() - 1)
				{
					return state.startPoint;
				}
				else if (state.compareIndex == 0)
				{
					state.startPoint.x = state.comparePoint.x;
					state.startPoint.y = state.comparePoint.y;
				}
				int cmpIndex = state.compareIndex + 1;

				bfs.push( SearchState(cmpIndex, Point(state.startPoint.x, state.startPoint.y),
						Point(state.comparePoint.x + 1, state.comparePoint.y)) ) ;
				bfs.push( SearchState(cmpIndex, Point(state.startPoint.x, state.startPoint.y),
						Point(state.comparePoint.x, state.comparePoint.y + 1)) ) ;
				bfs.push( SearchState(cmpIndex, Point(state.startPoint.x, state.startPoint.y),
						Point(state.comparePoint.x + 1, state.comparePoint.y + 1)) ) ;
			}
			else
			{
				bfs.push( SearchState(0, Point(-1, -1),
						Point(state.comparePoint.x + 1, state.comparePoint.y)) ) ;
				bfs.push( SearchState(0, Point(-1, -1),
						Point(state.comparePoint.x, state.comparePoint.y + 1)) ) ;
				bfs.push( SearchState(0, Point(-1, -1),
						Point(state.comparePoint.x + 1, state.comparePoint.y + 1)) ) ;
			}
		}
	}

	return Point();
}

vector<Point> findWords(const vector<string> &grid, const vector<string> &wordList)
{
	int strLen = grid[0].length();
	vector<vector<char>> charGrid(grid.size() , vector<char>(strLen));
	vector<Point> points;

	for (size_t idx = 0, gridSize = grid.size(); idx < gridSize; ++idx)
	{
		string str = grid[idx];

		for (size_t sidx = 0, len = str.length(); sidx < len; ++sidx)
		{
			charGrid[idx][sidx] = str[sidx];
		}
	}

	for (size_t idx = 0, wordListSize = wordList.size(); idx < wordListSize; ++idx)
	{
		points.push_back(findWord(charGrid, wordList[idx]));
	}

	return points;
}

int main(int argc, char *argv[])
{
	vector<string> grid;
	vector<string> wordList;

	//grid.push_back("TEST");
	//grid.push_back("GOAT");
	//grid.push_back("BOAT");

	//wordList.push_back("BOAT");
	//wordList.push_back("GOAT");
	//wordList.push_back("TEST");

	//grid.push_back("SXXXXX");
	//grid.push_back("XQXMXX");
	//grid.push_back("XXXAXX");
	//grid.push_back("XXXSWX");
	//grid.push_back("XXXLQO");
	//grid.push_back("XXXLXL");

	//wordList.push_back("SQL");
	//wordList.push_back("RAM");

	grid.push_back("EASYTOFINDEAGSRVHOTCJYG");
	grid.push_back("FLVENKDHCESOXXXXFAGJKEO");
	grid.push_back("YHEDYNAIRQGIZECGXQLKDBI");
	grid.push_back("DEIJFKABAQSIHSNDLOMYJIN");
	grid.push_back("CKXINIMMNGRNSNRGIWQLWOG");
	grid.push_back("VOFQDROQGCWDKOUYRAFUCDO");
	grid.push_back("PFLXWTYKOITSURQJGEGSPGG");

	wordList.push_back("EASYTOFIND");
	wordList.push_back("DIAG");
	wordList.push_back("GOING");
	wordList.push_back("THISISTOOLONGTOFITINTHISPUZZLE");

	/*vector<Point> vect = */findWords(grid, wordList);
	getchar(); 
	return 0;
}
