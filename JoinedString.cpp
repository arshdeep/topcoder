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
/* http://topcoder.bgcoder.com/print.php?id=1244 */
#define SIZEOFSTRINGARRAY(s) sizeof(s)/sizeof(s[0])
	string memo[12][1<<12];
	string common[12][12];

class JoinedString
{
	size_t len;
	string dp(int current, int mask);
public:
    string joinWords(vector<string> words);
};

string JoinedString::dp(int current, int mask)
{
	string &memoval = memo[current][mask];

	if (memoval != "") return memoval;
	if (!mask) return "";

	for (size_t i = 0, size = len; i < size; ++i)
	{
		if (mask & (1 << i))
		{
			string temp = common[current][i] + dp(i, mask ^ (1 << i));
			if (memoval == "" || (temp.length() < memoval.length() || temp.length() == memoval.length() && temp < memoval))
			{
				memoval = temp;
			}
		}
	}

	return memoval;
}
string JoinedString::joinWords(vector<string> wordsList)
{
    len = wordsList.size();
	vector<string> words;

	for (size_t i = 0; i < len; ++i)
    {
		bool ok = true;
		for (size_t j = 0; j < len; ++j)
		{
			common[i][j] = "";
			if (i != j)
			{
				string w1 = wordsList[i];
				string w2 = wordsList[j];
				if (w2.find(w1) != -1)
				{
					ok = false;
					break;
				}
			}
		}

		if (ok)
		{
			words.push_back(wordsList[i]);
		}
	}
	len = words.size();
	for (int i = 0; i < len; ++i)
    {
		for (int j = 0; j < 1<<len; ++j)
		{
			memo[i][j] = "";
		}
	}
	for (size_t i = 0; i < len; ++i)
    {
		for (size_t j = 0; j < len; ++j)
		{
			if (i != j)
			{
				common[i][j] = words[j];
				for (size_t t = 1, size = std::min(words[i], words[j]).length(); t < size; ++t)
				{
					string s1 = words[i].substr(t, words[i].length() - t);
					string s2 = words[j].substr(0, words[i].length() - t);

					if (s1.compare(s2) == 0)
					{
						common[i][j] = words[j].substr(s2.length(), words[j].length() - s2.length() + 1);
						break;
					}
				}
			}
		}
    }

    string best = "";

	for (size_t i = 0; i < len; ++i)
	{
		string temp = words[i] + dp(i, ((1 << len) - 1) ^ (1 << i));

		if (best == "" || (temp.length() < best.length() || temp.length() == best.length() && temp < best))
		{
			best = temp;
		}
	}

    return best;
}

void TEST(vector<string> words, string expected)
{
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    JoinedString joinedString;
    
    string result = joinedString.joinWords(words);
    
    assert( result.compare(expected) == 0 );
    
    end = clock();
    cpu_time_used = ((double) (end - start));
    cout<<"Time taken : "<<cpu_time_used<<endl;
}

vector<string> convert(string *list, int n)
{
    vector<string> ret;
    
    for (int i = 0; i< n; ++i)
    {
        ret.push_back(list[i]);
    }
    
    return ret;
}

void Test1()
{
    string test[] = {"BAB", "ABA"};
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), "ABAB");
}

void Test2()
{
    string test[] = {"ABABA", "AKAKA", "AKABAS", "ABAKA"};
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), "ABABAKAKABAS");
}

void Test3()
{
    string test[] = {"AAA","BBB", "CCC", "ABC", "BCA", "CAB"};
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), "AAABBBCABCCC");
}

void Test4()
{
    string test[] = {"OFG", "SDOFGJTILM", "KBWNF", "YAAPO", "AWX", "VSEAWX", "DOFGJTIL", "YAA"};
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), "KBWNFSDOFGJTILMVSEAWXYAAPO");
}

void Test5()
{
    string test[] = {"STRING", "RING"};
    
    TEST(convert(test, SIZEOFSTRINGARRAY(test)), "STRING");
}

void Test6()
{
    
}

void Test7()
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
    cout<<"success";
    
    getchar();
    return 0;
}
