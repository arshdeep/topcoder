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
/* BadNeighbors https://www.topcoder.com/stat?c=problem_statement&pm=2402&rd=5009 */

int maxDonationsEx(int* donations, int n)
{
	vector<int> dp(n);

	int max = INT_MIN;
	dp[0] = donations[0];
	dp[1] = donations[1];
	dp[2] = donations[0] + donations[2];

	for (int i = 3; i < n; ++i)
	{
		dp[i] = std::max(dp[i - 3], dp[i - 2]) + donations[i];
		max = std::max(dp[i], max);
	}
	return max;
}

int maxDonations(int* donations, int n)
{
	if (n == 2)
		return std::max(donations[0], donations[1]);
	int max = INT_MIN;
	
	max = maxDonationsEx(donations, n - 1);
	max = std::max(max, maxDonationsEx(donations + 1, n - 1));
	return max;
}

int main(int argc, char *argv[])
{
	int donations[] = { 10, 3, 2, 5, 7, 8 };

	cout<<maxDonations(donations, sizeof(donations)/sizeof(int))<<endl;

	int donations2[] = { 7, 7, 7, 7, 7, 7, 7 };

	cout<<maxDonations(donations2, sizeof(donations2)/sizeof(int))<<endl;

	int donations3[] = { 1, 2, 3, 4, 5, 1, 2, 3, 4, 5 };

	cout<<maxDonations(donations3, sizeof(donations3)/sizeof(int))<<endl;

	int donations4[] = { 94, 40, 49, 65, 21, 21, 106, 80, 92, 81, 679, 4, 61,  
		  6, 237, 12, 72, 74, 29, 95, 265, 35, 47, 1, 61, 397,
		  52, 72, 37, 51, 1, 81, 45, 435, 7, 36, 57, 86, 81, 72 };

	cout<<maxDonations(donations4, sizeof(donations4)/sizeof(int))<<endl;
	getchar(); 
	return 0;
}