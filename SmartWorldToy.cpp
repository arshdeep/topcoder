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
using namespace std;

struct Word
{
	string word;
	int level;
	Word(const string &wordStr, const int nodeLevel) : word(wordStr), level(nodeLevel)
	{
	}
};

typedef set<string> Dictionary;
typedef queue<Word> DfsSearch;
enum Dir
{
	kUp = 0,
	kDown
};

string switchLetter(const string &word, const int index, Dir dir)
{
	string str = word;
	char c = str[index];

	if (dir == kUp)
	{
		if (c == 'z')
			c = 'a';
		else
			c += 1;
	}
	else
	{
		if (c == 'a')
			c = 'z';
		else
			c -= 1;
	}

	str[index] = c;

	return str;
}

int minSteps(const string &start, const string &end, const Dictionary &forbiddenWords)
{
	Dictionary exploredNodes(forbiddenWords);
	DfsSearch dfsSearch;

	dfsSearch.push(Word(start, 0));

	while (!dfsSearch.empty())
	{
		Word curWord = dfsSearch.front();

		if (curWord.word.compare(end) == 0)
		{
			return curWord.level;
		}

		exploredNodes.insert(curWord.word);
		string str = curWord.word;
		for (size_t idx = 0, wordLen = curWord.word.length(); idx < wordLen; ++idx)
		{
			string nextWordUp = switchLetter(str, idx, kUp);
			string nextWordDown = switchLetter(str, idx, kDown);

			if (!exploredNodes.count(nextWordUp))
			{
				dfsSearch.push(Word(nextWordUp, curWord.level + 1));
			}

			if (!exploredNodes.count(nextWordDown))
			{
				dfsSearch.push(Word(nextWordDown, curWord.level + 1));
			}
		}
		dfsSearch.pop();
	}
	return -1;
}

int main(int argc, char *argv[])
{
	/*vector<string> forbiddenSequence;
    forbiddenSequence.push_back("a a a z");
    forbiddenSequence.push_back("a a z a");
    forbiddenSequence.push_back("a z a a");
    forbiddenSequence.push_back("z a a a");
    forbiddenSequence.push_back("a z z z");
    forbiddenSequence.push_back("z a z z");
    forbiddenSequence.push_back("z z a z");
    forbiddenSequence.push_back("z z z a");
	*/
	Dictionary forbiddenDictionary;

	forbiddenDictionary.insert("aaaz");
	forbiddenDictionary.insert("aaza");
	forbiddenDictionary.insert("azaa");
	forbiddenDictionary.insert("zaaa");
	forbiddenDictionary.insert("azzz");
	forbiddenDictionary.insert("zazz");
	forbiddenDictionary.insert("zzaz");
	forbiddenDictionary.insert("zzza");

	cout<<minSteps("aaaa", "zzzz", forbiddenDictionary);
	getchar(); 
   return 0;
}
