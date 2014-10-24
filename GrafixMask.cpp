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
/*grafixMask : http://community.topcoder.com/stat?c=problem_statement&pm=2998&rd=5857 */
#define HEIGHT 400
#define WIDTH 600

struct Point
{
	int x;
	int y;
	Point(int left, int top) : x(left), y(top) {}
};

struct Rectangle
{
    Rectangle(const Point& _ul, const Point& _br)
        : ul(_ul), br(_br)
    {}

    Point ul;
    Point br;
};

typedef stack<Point> DfsSearch;
typedef queue<Point> BfsSearch;
typedef vector<Rectangle> Rectangles;

int doFill(vector<vector<int>> &grafixMask, int left, int top, int right, int bottom)
{
	DfsSearch dfs;

	dfs.push(Point(left, top));
	int count = 0;
	while (!dfs.empty())
	{
		Point cp = dfs.top();

		dfs.pop();

		if ((cp.x < 0 || cp.x >= WIDTH)
			|| (cp.y < 0 || cp.y >= HEIGHT)
			|| grafixMask[cp.x][cp.y]) {
				continue;
		}

		++count;
		grafixMask[cp.x][cp.y] = 1;
		dfs.push(Point(cp.x + 1, cp.y));
		dfs.push(Point(cp.x - 1, cp.y));
		dfs.push(Point(cp.x, cp.y + 1));
		dfs.push(Point(cp.x, cp.y - 1));
	}

	return count;
}
void maskRect(vector<vector<int>> &grafixMask, Rectangle rect)
{
	int top = rect.ul.y;
	int left = rect.ul.x;
	int bottom = rect.br.y;
	int right = rect.br.x;

	for (int idx = left; idx <= right; ++idx)
	{
		for (int idy = top; idy <= bottom; ++idy)
		{
			grafixMask[idx][idy] = 1;
		}
	}
}

vector<int> sortedAreas(Rectangles& rectangles)
{
	vector<vector<int>> grafixMask(WIDTH, vector<int>(HEIGHT));
	vector<int> minAreas;
	
	for (size_t idx = 0, rectCount = rectangles.size(); idx< rectCount; ++idx)
	{
		maskRect(grafixMask, rectangles[idx]);
	}

	for (int idx = 0; idx < WIDTH; ++idx)
	{
		for (int idy = 0; idy < HEIGHT; ++idy)
		{
			if (grafixMask[idx][idy] == 0)
			{
				minAreas.push_back(doFill(grafixMask, idx, idy, WIDTH, HEIGHT));
			}
		}
	}

	std::sort(minAreas.begin(), minAreas.end());
	return minAreas;
}

void convert(const vector<string>& strRectangles,
	Rectangles& rectangles) {
	int upper; int left;
	int bottom; int right;

	for (size_t idx = 0; idx < strRectangles.size(); ++ idx)
	{
		istringstream iss(strRectangles[idx]);
		if ( (iss >> upper) && (iss >> left) && (iss >> bottom) && (iss >> right) )
		{
			rectangles.push_back( Rectangle(Point(left, upper),
											Point(right, bottom)) );
		}
	}
}

int main(int argc, char *argv[])
{
	vector<string> strRectangles;
	//test case {"0 292 399 307"}

	/*strRectangles.push_back("48 192 351 207");
	strRectangles.push_back("48 392 351 407");
	strRectangles.push_back("120 52 135 547");
	strRectangles.push_back("260 52 275 547");*/
	//Test case 2
	/*strRectangles.push_back("0 192 399 207");
    strRectangles.push_back("0 392 399 407");
    strRectangles.push_back("120 0 135 599");
    strRectangles.push_back("260 0 275 599");*/
	// TEST case 3
	strRectangles.push_back("0 20 399 20");
    strRectangles.push_back("0 44 399 44");
    strRectangles.push_back("0 68 399 68");
    strRectangles.push_back("0 92 399 92");
    strRectangles.push_back("0 116 399 116");
    strRectangles.push_back("0 140 399 140");
    strRectangles.push_back("0 164 399 164");
    strRectangles.push_back("0 188 399 188");
    strRectangles.push_back("0 212 399 212");
    strRectangles.push_back("0 236 399 236");
    strRectangles.push_back("0 260 399 260");
    strRectangles.push_back("0 284 399 284");
    strRectangles.push_back("0 308 399 308");
    strRectangles.push_back("0 332 399 332");
    strRectangles.push_back("0 356 399 356");
    strRectangles.push_back("0 380 399 380");
    strRectangles.push_back("0 404 399 404");
    strRectangles.push_back("0 428 399 428");
    strRectangles.push_back("0 452 399 452");
    strRectangles.push_back("0 476 399 476");
    strRectangles.push_back("0 500 399 500");
    strRectangles.push_back("0 524 399 524");
    strRectangles.push_back("0 548 399 548");
    strRectangles.push_back("0 572 399 572");
    strRectangles.push_back("0 596 399 596");
    strRectangles.push_back("5 0 5 599");
    strRectangles.push_back("21 0 21 599");
    strRectangles.push_back("37 0 37 599");
    strRectangles.push_back("53 0 53 599");
    strRectangles.push_back("69 0 69 599");
    strRectangles.push_back("85 0 85 599");
    strRectangles.push_back("101 0 101 599");
    strRectangles.push_back("117 0 117 599");
    strRectangles.push_back("133 0 133 599");
    strRectangles.push_back("149 0 149 599");
    strRectangles.push_back("165 0 165 599");
    strRectangles.push_back("181 0 181 599");
    strRectangles.push_back("197 0 197 599");
    strRectangles.push_back("213 0 213 599");
    strRectangles.push_back("229 0 229 599");
    strRectangles.push_back("245 0 245 599");
    strRectangles.push_back("261 0 261 599");
    strRectangles.push_back("277 0 277 599");
    strRectangles.push_back("293 0 293 599");
    strRectangles.push_back("309 0 309 599");
    strRectangles.push_back("325 0 325 599");
    strRectangles.push_back("341 0 341 599");
    strRectangles.push_back("357 0 357 599");
    strRectangles.push_back("373 0 373 599");
    strRectangles.push_back("389 0 389 599");

	Rectangles intRectangles;
	convert(strRectangles, intRectangles);

	vector<int> minAreas = sortedAreas(intRectangles);

	for (size_t idx = 0; idx < minAreas.size(); ++ idx)
	{
		cout<<minAreas[idx]<<" ";
	}

	getchar(); 
	return 0;
}
