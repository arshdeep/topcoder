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
/* https://www.topcoder.com/stat?c=problem_statement&pm=6713&rd=9999 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define memSet(a, val) memset(a, val, sizeof(a))

struct node
{
	int i;
	char ch;

	node (int intVal = 0, int cha = 0) : i(intVal), ch(cha) {}
	bool operator<(const node &rhs) const
	{
		return this->i < rhs.i;
	}
	bool operator==(int rhs) const
	{
		return this->i == rhs || this->ch == rhs;
	}
};

class IncompleteBST
{
	vector<node> parseNodes(vector<string> list);
	bool isBST(const vector<node> &tree, int root, int min, int max) const;
public:
	string missingValues(vector<string> tree);
};

vector<node> IncompleteBST::parseNodes(vector<string> list)
{
	vector<node> ret;

	for (int i = 0, size = list.size(); i < size; ++i)
    {
        string node = list[i];
		istringstream iss(node);
		struct node nd;

		iss>>nd.ch;
		iss>>nd.i;
		ret.push_back(nd);
    }

    return ret;
}
bool IncompleteBST::isBST(const vector<node> &tree, int root, int min, int max) const
{
	vector<node>::const_iterator itr = std::find(tree.begin(), tree.end(), root);
	if (itr == tree.end())
	{
		return true;
	}

	if (itr->ch != '?' && (itr->ch < min || itr->ch > max))
		return false;

	return isBST(tree, itr->i*2, min, itr->ch == '?' ? max : itr->ch + 1) && isBST(tree, itr->i*2 + 1, itr->ch == '?' ? min : itr->ch + 1, max);
}

string getMissing(const vector<node> &tree)
{
	vector<node>::const_iterator itr = std::find(tree.begin(), tree.end(), '?');
	int v = itr->i;
	bool isLhs = true;
	if (v % 2 == 0)
	{
		isLhs = true;
	}
	else
	{
		isLhs = false;
	}
	string ret = "";
	if (v == 1)
	{
		vector<node>::const_iterator sitr = std::find(tree.begin(), tree.end(), itr->i*2);
		vector<node>::const_iterator eitr = std::find(tree.begin(), tree.end(), itr->i*2 + 1);
		for (char ch = (eitr != tree.end() ? eitr->ch - 1 : 'Z'), endChar = (sitr != tree.end() ? sitr->ch : 'A'); ch >= endChar; --ch)
		{
			string temp = ch + ret;
			temp.swap(ret);
		}
	}
	else if (isLhs)
	{
		ret = std::find(tree.begin(), tree.end(), itr->i/2)->ch;
		for (char ch = ret[0] - 1; ch >= 'A'; --ch)
		{
			if (std::find(tree.begin(), tree.end(), ch) != tree.end())
				break;
			string temp = ch + ret;
			temp.swap(ret);
		}
	}
	else
	{
		for (char ch = std::find(tree.begin(), tree.end(), itr->i/2)->ch + 1; ch <= 'Z'; ++ch)
		{
			ret += ch;
			if (std::find(tree.begin(), tree.end(), ch) != tree.end())
				break;
		}
	}
	return ret;
}
string IncompleteBST::missingValues(vector<string> tree)
{
	vector<node> nodeList = parseNodes(tree);
	sort(nodeList.begin(), nodeList.end());
	if (!isBST(nodeList, 1, INT_MIN, INT_MAX))
		return "";

	return getMissing(nodeList);
}

void TEST(vector<string> tree, string expected)
{
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	IncompleteBST incompleteBST;

	string result = incompleteBST.missingValues(tree);

	assert( result.compare(expected) == 0 );

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
	string test[] = {"A 1", "? 2"};

	TEST(convert(test, SIZEOFARRAY(test)), "A");
}

void Test2()
{
	string test[] = {"B 1", "? 2"};

	TEST(convert(test, SIZEOFARRAY(test)), "AB");
}

void Test3()
{
	string test[] = {"Z 1", "Y 2", "X 4", "W 8", "V 16", "U 32", "T 64", "S 128", "R 256", "Q 512", 
"P 1024", "O 2048", "N 4096", "M 8192", "L 16384", "K 32768", "J 65536", "? 131072"};

	TEST(convert(test, SIZEOFARRAY(test)), "ABCDEFGHIJ");
}

void Test4()
{
	string test[] = {"K 1", "K 2", "A 6", "? 12", "Y 3"};

	TEST(convert(test, SIZEOFARRAY(test)), "");
}

void Test5()
{
	string test[] = {"V 1", "? 3"};

	TEST(convert(test, SIZEOFARRAY(test)), "WXYZ");
}

void Test6()
{
	string test[] = {"V 1", "? 3"};

	TEST(convert(test, SIZEOFARRAY(test)), "WXYZ");
}

void Test7()
{
	string test[] = {"A 1", "A 2", "? 3"};

	TEST(convert(test, SIZEOFARRAY(test)), "BCDEFGHIJKLMNOPQRSTUVWXYZ");
}

void Test8()
{
	string test[] = {"H 2", "U 15", "S 14", "A 8", "N 3", "N 6", "K 5", "A 4", "R 28", "T 7", "? 9", "M 1"};

	TEST(convert(test, SIZEOFARRAY(test)), "BCDEFGH");
}

void Test9()
{
	string test[] = {"? 56", "H 2", "U 15", "S 14", "A 8", "N 3", "N 6", "M 1", "K 5", "A 4", "R 28", "T 7"};

	TEST(convert(test, SIZEOFARRAY(test)), "OPQR");
}

void Test10()
{
	string test[] = {"Z 1", "Y 2", "X 4", "W 8", "V 16", "U 32", "T 64", "S 128", "R 256", "Q 512", "P 1024", "O 2048", "N 4096", "M 8192", "L 16384", "K 32768", "J 65536", "? 65537"};

	TEST(convert(test, SIZEOFARRAY(test)), "L");
}

void Test11()
{
	string test[] = {"C 2", "? 1", "X 3"};

	TEST(convert(test, SIZEOFARRAY(test)), "CDEFGHIJKLMNOPQRSTUVW");
}

void Test12()
{
	string test[] = {"? 1", "Y 2", "X 4", "W 8", "V 16", "U 32", "T 64", "S 128", "R 256", "Q 512", "P 1024", "O 2048", "N 4096", "M 8192", "L 16384", "K 32768", "J 65536", "K 65537"};

	TEST(convert(test, SIZEOFARRAY(test)), "");
}

void Test13()
{
	string test[] = {"V 6", "A 2", "? 1", "H 5", "X 3", "J 21", "N 23", "K 11", "C 10", "A 4"};

	TEST(convert(test, SIZEOFARRAY(test)), "");
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
	Test11();
	Test12();
	Test13();
	cout<<"success";

	getchar();
	return 0;
}
