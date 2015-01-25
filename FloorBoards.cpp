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
#include <stdlib.h>
using namespace std;
/* http://community.topcoder.com/stat?c=problem_statement&pm=8516&rd=11124 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define REP(i,n) for(int i=0;i<(n);++i)
#define LOOP(i,v,n) for(i=v;i<(n);++i)
#define LL long long
#define memSet(m, v) memset(m, v, sizeof(m))

int howFar[15][51];
//bool canpaint[51][1<<15];

class PaintingBoards
{
	int mBoardLen;
	int mPainters;

	bool canPaint(const vector<int> &boardLength, const vector<int> &painterSpeed, double time)
	{
		int k = 0;
		REP(i, mBoardLen)
		{
			REP(j, mPainters)
			{
				int dist = 0;
				double maxDist = time * painterSpeed[j];
				LOOP(k, i, mBoardLen)
				{
					dist += boardLength[k];
					if (maxDist < dist) break;
				}
				howFar[i][j] = k;
			}
		}
		vector< vector <int> > canpaint(mBoardLen + 1, vector<int>(1 << mPainters));
		canpaint[0][0] = true;
		REP(i, mBoardLen)
		{
			REP(j, (1 << mPainters))
			{
				if (!canpaint[i][j]) continue;

				REP(k, mPainters)
				{
					if ((j & (1 << k)) == 0)
					{
						canpaint[ howFar[i][k] ][j | (1 << k)] = true;
					}
				}
			}
		}
		int j = 0;
		REP(j, (1 << mPainters))
		{
			if (canpaint[mBoardLen][j])
				return true;
		}

		return false;
	}
public:
	double minimalTime(vector<int> boardLength, vector<int> painterSpeed)
	{
		memSet(howFar, 0);
		//memSet(canpaint, 0);

		mBoardLen = (int)boardLength.size();
		mPainters = (int)painterSpeed.size();
        
		double start = 0;
		double end = 50000;

		while (end - start > 1e-11)
		{
			double mid = start + (end - start) / 2;

			if (canPaint(boardLength, painterSpeed, mid))
				end = mid;
			else
				start = mid;
		}
		return end;
	}
};

void TEST(vector<int> boardLength, vector<int> painterSpeed, double expected)
{
	clock_t start, end;
	double cpu_time_used;
    
	start = clock();
	PaintingBoards paintingBoards;
	double result = paintingBoards.minimalTime(boardLength, painterSpeed);
    cout<<result<< " "<< expected<<endl;
	//assert(result - expected <= 1e-12);
    
	end = clock();
	cpu_time_used = ((double)(end - start));
	cout << "Time taken : " << cpu_time_used << endl;
}

template <class T>
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
	int boardLength[] = {5,3,2};
	int painterSpeed[] = {2,3,5};
	TEST(convert(boardLength, SIZEOFARRAY(boardLength)),
			convert(painterSpeed, SIZEOFARRAY(painterSpeed)), 1.0);
}

void Test2()
{
	int boardLength[] = {1,2,1,4,2,1,1};
	int painterSpeed[] = {1,2,3};
	TEST(convert(boardLength, SIZEOFARRAY(boardLength)),
			convert(painterSpeed, SIZEOFARRAY(painterSpeed)), 2.0);
}

void Test3()
{
	int boardLength[] = {3,3,20};
	int painterSpeed[] = {9,1};
	TEST(convert(boardLength, SIZEOFARRAY(boardLength)),
			convert(painterSpeed, SIZEOFARRAY(painterSpeed)), 2.888888888888889);
}

void Test4()
{
	int boardLength[] = {40, 46, 82, 89, 33, 46, 3, 50, 95,
		81, 69, 40, 94, 93, 90, 98, 17, 34,
		45, 18, 93, 28, 43, 38, 35};
	int painterSpeed[] = {49, 51, 35, 27, 48, 36, 54, 10};
	TEST(convert(boardLength, SIZEOFARRAY(boardLength)),
			convert(painterSpeed, SIZEOFARRAY(painterSpeed)), 4.686274509803922);
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
	getchar();
	cout << "success";
	return 0;
}
