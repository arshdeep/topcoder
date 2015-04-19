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
#include <stdlib.h>
#include <regex>
using namespace std;
/* http://community.topcoder.com/stat?c=problem_statement&pm=13193 */
#define SIZEOFARRAY(s) sizeof(s)/sizeof(s[0])
#define REP(i,n) for(int i=0;i<(n);++i)
#define LOOP(i,v,n) for(i=v;i<(n);++i)
#define LL long long
#define memSet(m, v) memset(m, v, sizeof(m))

int minDist[50][50];
int roads[50][50];
// O(n^4)
class BuildingRoutes
{
public:
	int build(vector<string> dist, int T)
	{
		memSet(minDist, INT_MAX);
		memSet(roads, 0);
		int n = n = dist.size();

		// Floyd warshall
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				minDist[i][j] = dist[i][j] - '0';
			}
		}

		for (int k = 0; k < n; ++k)
		{
			for (int i = 0; i < n; ++i)
			{
				for (int j = 0; j < n; ++j)
				{
					minDist[i][j] = std::min(minDist[i][j], minDist[i][k] + minDist[k][j]);
				}
			}
		}

		// check if x,y can be used in a,b cities.

		for (int a = 0; a < n; ++a)
		{
			for (int b = 0; b < n; ++b)
			{
				for (int i = 0; i < n; ++i)
				{
					for (int j = 0; j < n; ++j)
					{
						if (a != b && i != j)
						{
							if (minDist[a][b] == minDist[a][i] + (dist[i][j] - '0') + minDist[j][b])
								++roads[i][j];
						}
					}
				}
			}
		}

		int res = 0;
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				if (roads[i][j] >= T)
					res += dist[i][j] - '0';
			}
		}

		return res;
	}
};

void TEST(vector<string> dist, int T, int expected)
{
	clock_t start, end;
	double cpu_time_used;
    
	start = clock();
	BuildingRoutes buildingRoutes;
	int result = buildingRoutes.build(dist, T);
	assert( expected == result );
    
	end = clock();
	cpu_time_used = ((double)(end - start));
	cout << "Time taken : " << cpu_time_used << endl;
}

template <class T>
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
	string a[] = {"011",
 "101",
 "110"};

	TEST(convert(a, SIZEOFARRAY(a)), 1, 6 );
}

void Test2()
{
	string a[] = {"033",
 "309",
 "390"};

	TEST(convert(a, SIZEOFARRAY(a)), 1, 12 );
}

void Test3()
{
	string a[] = {"0123",
 "1023",
 "1203",
 "1230"};

	TEST(convert(a, SIZEOFARRAY(a)), 2, 5 );
}

void Test4()
{
	string a[] = {"05789654",
 "10347583",
 "65085479",
 "55602398",
 "76590934",
 "57939045",
 "12345608",
 "68647640"};

	TEST(convert(a, SIZEOFARRAY(a)), 3, 40);
}

void Test5()
{
	string a[] = {"09859241839387868941176158769631317592843734", "70348326627483485536712565561678647431612168", "69027432329479135474133499627734472797994592", "98408824687537769833468387913795649342136536", "57170745219243792938726113829391935321624356", "12775042961447639692577889623397251379473293", "38144304945331299399756117188298887759349961", "21686880957213485225548534595929472689632124", "96331824025549221359364719193427269656436895", "94491989902468695397395659758833781191968636", "89946622920366556657329565238426276527212653", "16271785154037556899579358958289551464213329", "86642525334405988376922971772784227255167742", "77249986143370123854337384826637938675613458", "74696735512548099345726164512736984973126833", "38126639723247808414249336125157874912264324", "61328684421752850415677992162547616759484681", "72374529969364686093641835781129551446996342", "74112941253639439807312725139731872873284793", "52765293163463786920451858768498142658617641", "54284284467594153615016228537239616579875151", "37337291135748997631608337788954787544377447", "79332325728588626762750751955723215561389439", "26477573111848197427297039818786423724221124", "53815594884699222364621603953971591429222398", "46621261437371215124618290881634625565189316", "31831348719281957661156417011633125115742624", "96359845439565442447618574504888559451117472", "46584758145597375268567725650711149875941971", "16176233956548188326195611937015858876757447", "29715488665692362548122241687606377923533783", "39411544655916194772639956827790131139841684", "51796925539914923195988283563436063129597662", "24194427453311366781269864522144507585511856", "73827163294797373114953798146733750367171651", "12866841166558648155713578198327467086872457", "18359875748973464517688242642473226209974663", "31614247796813463381562552511945588820243199", "45146238449535982339841127662276893571027657", "33288836393493569117484844993696288222105437", "75253989244769231856312212248959839584870595", "55116227163665364587871175968117895247354097", "11783125451292518348744624564544158833179601", "48531696978316632986228282876544669934276720"};

	TEST(convert(a, SIZEOFARRAY(a)), 3, 659);
}

void Test6()
{
}

void Test7()
{
}

void Test8()
{
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
	getchar();
	cout << "success";
	return 0;
}
