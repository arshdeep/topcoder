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
/* AutoLoan http://community.topcoder.com/stat?c=problem_statement&pm=3970&rd=7993 */

double interestRate(double price, double monthlyPayment, int loanTerm)
{
	double max = 100;
	double min = 0;
	double monthlyPercentage;

	while (max - min > 1e-9)
	{
		double mid = min + (max - min) / 2;
		int term = loanTerm;
		double principal = price;
		monthlyPercentage = (mid/principal)*(double)100;

		for (int t = 0; t < term; ++t)
		{
			principal += (principal * monthlyPercentage)/(double)100;
			principal -= (double)monthlyPayment;
		}
		if (principal < 1e-9)
			min = mid;
		else
			max = mid;
	}

	return monthlyPercentage*(double)12;
}

int main(int argc, char *argv[])
{
	cout<<interestRate(6800, 100, 68)<<endl;
	cout<<interestRate(2000, 510, 4)<<endl;
	cout<<interestRate(15000, 364, 48)<<endl;
	getchar(); 
	return 0;
}
