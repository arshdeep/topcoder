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
using namespace std;
/*http://community.topcoder.com/stat?c=problem_statement&pm=6714&rd=9999 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define memSet(a, val) memset(a, val, sizeof(a))
class ConstructBST
{
	void rec(vector<int> tree, int root, int &bc, int &count);
public:
	long numInputs(vector<int> tree);
};
long bin[30][30];

void ConstructBST::rec(vector<int> tree, int root, int &bc, int &count)
{
	if (std::find(tree.begin(), tree.end(), root) == tree.end())
	{
		count = 0;
		bc = 1;
		return;
	}
	int lbc = 0, rbc = 0, lcount = 0, rcount = 0;

	rec(tree, root*2, lbc, lcount);
	rec(tree, root*2+1, rbc, rcount);
	bc = lbc * rbc * bin[lcount + rcount][rcount];
	count = lcount + rcount + 1;
}

long ConstructBST::numInputs(vector<int> tree)
{
	// first calculate binomial coefficient
	int size = tree.size();
	sort(tree.begin(), tree.end());
	memSet(bin, 0);

	bin[0][0] = 1;
	for (int i = 1; i <= size; ++i)
	{
		bin[i][0] = 1;
		for (int j = 1; j <= i; ++j)
		{
			bin[i][j] = bin[i - 1][j] + bin[i - 1][j - 1];
		}
	}

	int ret = 0;
	int count = 0;
	rec(tree, 1, ret, count);

	return ret;
}

void TEST(vector<int> tree, int expected)
{
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    ConstructBST constructBST;
    
	int result = constructBST.numInputs(tree);
    
	assert( result == expected );
    
    end = clock();
    cpu_time_used = ((double) (end - start));
    cout<<"Time taken : "<<cpu_time_used<<endl;
}

template<class T>
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
	int test[] = {1, 2, 5, 3, 4};

	TEST(convert(test, SIZEOFARRAY(test)), 8);
}

void Test2()
{
	int test[] = {2, 1};

	TEST(convert(test, SIZEOFARRAY(test)), 1);
}

void Test3()
{
	int test[] = {1, 2, 4, 6, 3};

	TEST(convert(test, SIZEOFARRAY(test)), 6);
}

void Test4()
{
	int test[] = {2, 4, 3, 62, 7, 15, 1, 31, 5, 14, 28, 57, 56, 114};

	TEST(convert(test, SIZEOFARRAY(test)), 96096);
}

void Test5()
{
	int test[] = {1, 2, 4, 9, 18, 37, 74, 148, 296, 592, 3, 7, 14, 29, 58, 117, 235, 471, 943, 1887, 3774, 7548, 15096, 30192, 60384, 120769};

	TEST(convert(test, SIZEOFARRAY(test)), 2042975);
}

void Test6()
{
	int test[] = 	{1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767, 65535, 131071, 131070};

	TEST(convert(test, SIZEOFARRAY(test)), 2);
}

void Test7()
{
	int test[] = 	{1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767, 65535, 131071, 262143, 524287, 1048575, 2097151, 4194303, 8388607, 16777215, 33554431, 67108863};

	TEST(convert(test, SIZEOFARRAY(test)), 1);
}

void Test8()
{
	int test[] = {1, 3, 7, 15, 31, 63, 127, 255, 511, 1023, 2047, 4095, 8191, 16383, 32767, 65535, 131071, 262143, 524287, 1048575, 2097151, 4194303, 8388607, 14, 2, 6};

	TEST(convert(test, SIZEOFARRAY(test)), 12075);
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
    cout<<"success";
    
    getchar();
    return 0;
}
