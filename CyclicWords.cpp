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
/* https://www.topcoder.com/stat?c=problem_statement&pm=7694 */

class CyclicWords
{
public:
	int differentCW(vector<string> words);
};

int CyclicWords::differentCW(vector<string> words)
{
	int len = words.size();
	vector<int> flag(len);

	for (int i = 0; i < len; ++i)
	{
		words[i] += words[i];
	}

	int max = 0;
	for (int i = 0; i < len; ++i)
	{
		if (!flag[i])
		{
			string t1 = words[i].substr(0, words[i].length()/2);
			int maxTemp = 0;
			for (int j = 0; j < len; ++j)
			{
				string t2 = words[j].substr(0, words[j].length()/2);
				if (i != j && t1.length() == t2.length())
				{
					int index = words[j].find(t1);

					if (index > -1)
					{
						flag[j] = 1;
						++maxTemp;
					}
				}
			}
			flag[i] = 1;
			++max;
		}
	}

	return max;
}

void TEST(vector<string> words, int expected)
{
	clock_t start, end;
	double cpu_time_used;

	start = clock();
	CyclicWords cyclicWords;

	int result = cyclicWords.differentCW(words);
	
	assert( result == expected );

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
	string str[] = { "picture", "turepic", "icturep", "word", "ordw" };

	TEST(convert(str, 5), 2);
}

void Test2()
{
	string str[] = {"aaaa", "aaa", "aa", "aaaa", "aaaaa"};

	TEST(convert(str, 5), 4);
}

void Test3()
{
	string str[] = { "ast", "ats", "tas", "tsa", "sat", "sta", "ttt" };

	TEST(convert(str, 7), 3);
}

void Test4()
{
	string str[] = {"ab", "na", "ba", "nb", "bna"};

	TEST(convert(str, 5), 4);
}

void Test5()
{
	string str[] = {"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxxxyzz",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxxxzyz",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxxxzzy",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxxyxzz", 
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxxyzxz",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxxyzzx",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxxzxyz",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxxzxzy",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxxzyxz",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxxzyzx",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxxzzxy",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxxzzyx",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxyxxzz",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxyxzxz",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxyxzzx",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxyzxxz",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxyzxzx",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxyzzxx",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxzxxyz",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxzxxzy",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxzxyxz",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxzxyzx",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxzxzxy",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxzxzyx",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxzyxxz",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxzyxzx",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxzyzxx", 
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxzzxxy", 
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxzzxyx",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxxzzyxx", 
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxyxxxzz",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxyxxzxz",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxyxxzzx",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxyxzxxz",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxyxzxzx",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxyxzzxx",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxyzxxxz", 
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxyzxxzx", 
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxyzxzxx",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxyzzxxx", 
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxzxxxyz", 
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxzxxxzy", 
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxzxxyxz",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxzxxyzx",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxzxxzxy",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxzxxzyx",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxzxyxxz",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxzxyxzx",
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxzxyzxx", 
		"aaabbcdddeeegghiijkkmmmnopqqrrrrssstuuvvwwxxzxzxxy"};

	TEST(convert(str, sizeof(str)/sizeof(str[0])), 50);
}

void Test6()
{
	string str[] = {"nfztpnejgfzofczqvlayustoxudheieqdljmqwdcwkumqjjkam", "fztpnejgfzofczqvlayustoxudheieqdljmqwdcwkumqjjkamn", "ztpnejgfzofczqvlayustoxudheieqdljmqwdcwkumqjjkamnf", "tpnejgfzofczqvlayustoxudheieqdljmqwdcwkumqjjkamnfz", "pnejgfzofczqvlayustoxudheieqdljmqwdcwkumqjjkamnfzt", "nejgfzofczqvlayustoxudheieqdljmqwdcwkumqjjkamnfztp", "ejgfzofczqvlayustoxudheieqdljmqwdcwkumqjjkamnfztpn", "jgfzofczqvlayustoxudheieqdljmqwdcwkumqjjkamnfztpne", "gfzofczqvlayustoxudheieqdljmqwdcwkumqjjkamnfztpnej", "fzofczqvlayustoxudheieqdljmqwdcwkumqjjkamnfztpnejg", "zofczqvlayustoxudheieqdljmqwdcwkumqjjkamnfztpnejgf", "ofczqvlayustoxudheieqdljmqwdcwkumqjjkamnfztpnejgfz", "fczqvlayustoxudheieqdljmqwdcwkumqjjkamnfztpnejgfzo", "czqvlayustoxudheieqdljmqwdcwkumqjjkamnfztpnejgfzof", "zqvlayustoxudheieqdljmqwdcwkumqjjkamnfztpnejgfzofc", "qvlayustoxudheieqdljmqwdcwkumqjjkamnfztpnejgfzofcz", "vlayustoxudheieqdljmqwdcwkumqjjkamnfztpnejgfzofczq", "layustoxudheieqdljmqwdcwkumqjjkamnfztpnejgfzofczqv", "ayustoxudheieqdljmqwdcwkumqjjkamnfztpnejgfzofczqvl", "yustoxudheieqdljmqwdcwkumqjjkamnfztpnejgfzofczqvla", "ustoxudheieqdljmqwdcwkumqjjkamnfztpnejgfzofczqvlay", "stoxudheieqdljmqwdcwkumqjjkamnfztpnejgfzofczqvlayu", "toxudheieqdljmqwdcwkumqjjkamnfztpnejgfzofczqvlayus", "oxudheieqdljmqwdcwkumqjjkamnfztpnejgfzofczqvlayust", "xudheieqdljmqwdcwkumqjjkamnfztpnejgfzofczqvlayusto", "udheieqdljmqwdcwkumqjjkamnfztpnejgfzofczqvlayustox", "dheieqdljmqwdcwkumqjjkamnfztpnejgfzofczqvlayustoxu", "heieqdljmqwdcwkumqjjkamnfztpnejgfzofczqvlayustoxud", "eieqdljmqwdcwkumqjjkamnfztpnejgfzofczqvlayustoxudh", "ieqdljmqwdcwkumqjjkamnfztpnejgfzofczqvlayustoxudhe", "eqdljmqwdcwkumqjjkamnfztpnejgfzofczqvlayustoxudhei", "qdljmqwdcwkumqjjkamnfztpnejgfzofczqvlayustoxudheie", "dljmqwdcwkumqjjkamnfztpnejgfzofczqvlayustoxudheieq", "ljmqwdcwkumqjjkamnfztpnejgfzofczqvlayustoxudheieqd", "jmqwdcwkumqjjkamnfztpnejgfzofczqvlayustoxudheieqdl", "mqwdcwkumqjjkamnfztpnejgfzofczqvlayustoxudheieqdlj", "qwdcwkumqjjkamnfztpnejgfzofczqvlayustoxudheieqdljm", "wdcwkumqjjkamnfztpnejgfzofczqvlayustoxudheieqdljmq", "dcwkumqjjkamnfztpnejgfzofczqvlayustoxudheieqdljmqw", "cwkumqjjkamnfztpnejgfzofczqvlayustoxudheieqdljmqwd", "wkumqjjkamnfztpnejgfzofczqvlayustoxudheieqdljmqwdc", "kumqjjkamnfztpnejgfzofczqvlayustoxudheieqdljmqwdcw", "umqjjkamnfztpnejgfzofczqvlayustoxudheieqdljmqwdcwk", "mqjjkamnfztpnejgfzofczqvlayustoxudheieqdljmqwdcwku", "qjjkamnfztpnejgfzofczqvlayustoxudheieqdljmqwdcwkum", "jjkamnfztpnejgfzofczqvlayustoxudheieqdljmqwdcwkumq", "jkamnfztpnejgfzofczqvlayustoxudheieqdljmqwdcwkumqj", "kamnfztpnejgfzofczqvlayustoxudheieqdljmqwdcwkumqjj", "amnfztpnejgfzofczqvlayustoxudheieqdljmqwdcwkumqjjk", "mnfztpnejgfzofczqvlayustoxudheieqdljmqwdcwkumqjjka"};

	TEST(convert(str, sizeof(str)/sizeof(str[0])), 1);
}

void Test7()
{
	string str[] = {"wszojxenmqrbidckuawcgfbtagosozdygtdxkggbjayhznjspk", "ebsasnaoyihcqkjdkftdcgojxgzwxsyugpdnjozzgbagmktwrb", "bsasnaoyihcqkjdkftdcgojxgzwxsyugpdnjozzgbagmktwrbe", "smptrokfkguobsgogazntweiygxczgkzdjddjsbybnhqcxawja", "mptrokfkguobsgogazntweiygxczgkzdjddjsbybnhqcxawjas", "ptrokfkguobsgogazntweiygxczgkzdjddjsbybnhqcxawjasm", "sogkgczefjaxnnabkydotzmhadbcbsywoigdxgpktwusrjjgqz", "ogkgczefjaxnnabkydotzmhadbcbsywoigdxgpktwusrjjgqzs", "gkgczefjaxnnabkydotzmhadbcbsywoigdxgpktwusrjjgqzso", "jnbfxtgcxdnogkazssiygkwgyhjbwbrcsodagmetkaouqzdpjz", "nbfxtgcxdnogkazssiygkwgyhjbwbrcsodagmetkaouqzdpjzj", "bfxtgcxdnogkazssiygkwgyhjbwbrcsodagmetkaouqzdpjzjn", "pmrsezqsobjxbnghgywbjjyfgddxzccsdkawnoktgotaziuagk", "mrsezqsobjxbnghgywbjjyfgddxzccsdkawnoktgotaziuagkp", "rsezqsobjxbnghgywbjjyfgddxzccsdkawnoktgotaziuagkpm", "gsssawophytodegijkxzkaqnbjxjbrugbzgtngayokmcwzcdfd", "sssawophytodegijkxzkaqnbjxjbrugbzgtngayokmcwzcdfdg", "ssawophytodegijkxzkaqnbjxjbrugbzgtngayokmcwzcdfdgs", "jwgwpjxkjcsiqnobtadzbsgxsbggnoatkzyyohkgdcfrzmedau", "wgwpjxkjcsiqnobtadzbsgxsbggnoatkzyyohkgdcfrzmedauj", "gwpjxkjcsiqnobtadzbsgxsbggnoatkzyyohkgdcfrzmedaujw", "ojepyrswwgsjktbaaqiohxkunzjcdbdtxczmbsggoanfgzgkdy", "jepyrswwgsjktbaaqiohxkunzjcdbdtxczmbsggoanfgzgkdyo", "epyrswwgsjktbaaqiohxkunzjcdbdtxczmbsggoanfgzgkdyoj", "nsdigajsyjzkbegggydzockawogxquzkradbcnbxoswtmhfptj", "sdigajsyjzkbegggydzockawogxquzkradbcnbxoswtmhfptjn", "digajsyjzkbegggydzockawogxquzkradbcnbxoswtmhfptjns", "dstasgbxjaygkhgdsijgcwydnpctxjrofgzkbwonoquzzkameb", "stasgbxjaygkhgdsijgcwydnpctxjrofgzkbwonoquzzkamebd", "tasgbxjaygkhgdsijgcwydnpctxjrofgzkbwonoquzzkamebds", "yewgtdjsbzngaodkntxmsyaxqzkuzwpcofsdcjhkgjiogbabrg", "ewgtdjsbzngaodkntxmsyaxqzkuzwpcofsdcjhkgjiogbabrgy", "wgtdjsbzngaodkntxmsyaxqzkuzwpcofsdcjhkgjiogbabrgye", "ozxfhxjsberqccoddtypwmgagtayzagskjouniwksgzbdngjkb", "zxfhxjsberqccoddtypwmgagtayzagskjouniwksgzbdngjkbo", "xfhxjsberqccoddtypwmgagtayzagskjouniwksgzbdngjkboz", "kgxdadnpszrdewyomgjtfwsynjccgakshxtakgqjzbbugzoobi", "gxdadnpszrdewyomgjtfwsynjccgakshxtakgqjzbbugzoobik", "xdadnpszrdewyomgjtfwsynjccgakshxtakgqjzbbugzoobikg", "hoijjkfkscaggyboduzasxdtnwodygjnzgbxctzbmrqwpsakge", "oijjkfkscaggyboduzasxdtnwodygjnzgbxctzbmrqwpsakgeh", "ijjkfkscaggyboduzasxdtnwodygjnzgbxctzbmrqwpsakgeho"};

	TEST(convert(str, sizeof(str)/sizeof(str[0])), 15);
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
