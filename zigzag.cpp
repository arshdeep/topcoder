#include <climits>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <numeric>
using namespace std;

int longestZigZag(int* sequence, int size)
{
	vector<int> len(size + 1);
	vector<int> sign(size + 1);
	len[1] = 1;

	for (int i = 1; i < size; ++i)
	{
		int diff = sequence[i] - sequence[i - 1];

		sign[i]  = diff == 0 ? sign[i-1] : diff > 0;

		for (int j = i - 1; j > 0; --j)
		{
			if (sign[i] != sign[j] && len[i] < len[j] + 1)
				len[i] = len[j] + 1;
			else if (sign[i] == sign[j] && len[i] < len[j])
				len[i] = len[j];
		}
	}
	return len[size-1] + 1;
}

int main(int argc, char *argv[])
{
	int sequence[] = { 374, 40, 854, 203, 203, 156, 362, 279, 812, 955, 
600, 947, 978, 46, 100, 953, 670, 862, 568, 188, 
67, 669, 810, 704, 52, 861, 49, 640, 370, 908, 
477, 245, 413, 109, 659, 401, 483, 308, 609, 120, 
249, 22, 176, 279, 23, 22, 617, 462, 459, 244 };
	//{1, 17, 5, 10, 13, 15, 10, 5, 16, 8};
		//{ 1, 7, 4, 9, 2, 5 };// { 70, 55, 13, 2, 99, 2, 80, 80, 80, 80, 100, 19, 7, 5, 5, 5, 1000, 32, 32 };
	
	int size = sizeof(sequence) / sizeof(sequence[0]);

	cout<<longestZigZag(sequence, size)<<endl;

	getchar(); 
   return 0;
}