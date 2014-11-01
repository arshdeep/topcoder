#include <climits>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;
/* nthElement https://www.topcoder.com/stat?c=problem_statement&pm=4823&rd=8074 */

int nthElement(vector<int> lowerBound, vector<int> upperBound, int n)
{
	int lo = INT_MIN;
	int hi = INT_MAX;
	int itr = 0;
	while (lo < hi)
	{
		++itr;
		long count = 0;
		int x = (hi + lo + 1) /2;

		for (int i = 0, size = lowerBound.size(); i < size; ++i)
		{
			if (x >= lowerBound[i] && x <= upperBound[i])
			{
				count += (long)x - lowerBound[i];
			}
			else if (x > lowerBound[i] && x > upperBound[i])
			{
				count += upperBound[i] - lowerBound[i];
			} 
		}

		if (count <= n)
			lo = x;
		else
			hi = x - 1;
	}
	cout<<"Iterations :"<<itr<<endl;
	return lo;
}

int main(int argc, char *argv[])
{
	vector<int> lowerBound;
	vector<int> hBound;

	lowerBound.push_back(1);
	lowerBound.push_back(2);

	hBound.push_back(3);
	hBound.push_back(7);

	cout<<nthElement(lowerBound, hBound, 4)<<endl;

	lowerBound.clear();
	hBound.clear();
	lowerBound.push_back(1);
	lowerBound.push_back(3);

	hBound.push_back(4);
	hBound.push_back(5);

	cout<<nthElement(lowerBound, hBound, 3)<<endl;

	lowerBound.clear();
	hBound.clear();
	lowerBound.push_back(-1500000000);

	hBound.push_back(1500000000);

	cout<<nthElement(lowerBound, hBound, 1500000091)<<endl;

	getchar(); 
   return 0;
}