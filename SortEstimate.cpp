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
/* sortEstimate http://community.topcoder.com/stat?c=problem_statement&pm=3561&rd=6519 */

double howMany(int c, int time)
{
	double a = double(time) / c;
	double Min = 1e-10, Max = time + 1;

	while (Max-Min > (1+1e-10)) {
		double Mid = (Min + Max) / 2, v=Mid * log(Mid) / log(2.0);

		if(v>a)Max=Mid; else Min=Mid;
	}
	return (Min+Max)/2; 
}

int main(int argc, char *argv[])
{
	cout<<howMany(1, 2000000000)<<endl;
	cout<<howMany(37, 12392342)<<endl;

	getchar(); 
	return 0;
}
