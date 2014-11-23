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

struct Trie
{
	int words;
	int prefixes;
	Trie *edges[26];
};

class Dict
{
private:
	Trie *trie;

	void cutLeftmostCharacter(string &str)
	{
		str.erase(str.begin());
	}
public:
	void initialize(Trie *vertex);
	void addWord(Trie *vertex, string word);
	int countPrefixes(Trie *vertex, string prefix);
	int countWords(Trie *vertex, string word);
	int countWords(Trie *vertex, string word, int missingLetters);
};

void Dict::initialize(Trie *vertex)
{
	vertex->words = 0;
	vertex->prefixes = 0;

	for (int i = 0; i < 26; ++i)
	{
		vertex->edges[i] = NULL;
	}
}

void Dict::addWord(Trie *vertex, string word)
{
	if (word.length() == 0)
        vertex->words = vertex->words + 1;
    else
	{
        vertex->prefixes = vertex->prefixes + 1;
        int k = word[0] - 'a';
        if(vertex->edges[k] == NULL)
		{
            vertex->edges[k] = new Trie();
            initialize(vertex->edges[k]);
		}
        cutLeftmostCharacter(word);
        addWord(vertex->edges[k], word);
	}
}

int Dict::countWords(Trie *vertex, string word)
{
	if (word.length() == 0)
		return vertex->words;
	else
	{
		int k = word[0] - 'a';

		if (vertex->edges[k] == NULL)
			return 0;
		else
		{
			cutLeftmostCharacter(word);
			return countWords(vertex->edges[k], word);
		}
	}
}

int Dict::countPrefixes(Trie *vertex, string prefix)
{
	if (prefix.length() == 0)
		return vertex->prefixes;
	else
	{
		int k = prefix[0] - 'a';

		if (vertex->edges[k] == NULL)
			return 0;
		else
		{
			cutLeftmostCharacter(prefix);
			return countPrefixes(vertex->edges[k], prefix);
		}
	}
}

int Dict::countWords(Trie *vertex, string word, int missingLetters)
{
	if (word.length() == 0)
		return vertex->words;
	else
	{
		int k = word[0] - 'a';
		if (vertex->edges[k] == NULL && missingLetters == 0)
		{
			return 0;
		}
		else if (vertex->edges[k] == NULL)
		{
			//Here we cut a character but we don't go lower in the tree
			cutLeftmostCharacter(word);
			return countWords(vertex, word, missingLetters - 1);
		}
		else
		{
			//We are adding the two possibilities: the first
			//character has been deleted plus the first character is present
			int r = countWords(vertex, word, missingLetters - 1);
			cutLeftmostCharacter(word);
			r = r + countWords(vertex->edges[k], word, missingLetters);
			return r;
		}
	}
}

int main()
{
	Dict dict;
	Trie trie;

	dict.initialize(&trie);

	dict.addWord(&trie, "tree");
	dict.addWord(&trie, "trie");
	dict.addWord(&trie, "algo");
	dict.addWord(&trie, "assoc");
	dict.addWord(&trie, "all");
	dict.addWord(&trie, "also");


	cout<<dict.countWords(&trie, "tee");
	getchar();
	return 0;
}
