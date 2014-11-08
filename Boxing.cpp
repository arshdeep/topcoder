#include <iostream>
#include <cstdio>
#include <vector>
#include <cassert>
#include <sstream>
#include <set>
#include <algorithm>
#include <time.h>
using namespace std;
/* Boxing http://topcoder.bgcoder.com/print.php?id=661 */

class Boxing
{
public:
	int maxCredit( vector<int> a, vector< int > b, vector<int> c, vector<int> d, vector<int> e );
};

int Boxing::maxCredit( vector<int> a, vector< int > b, vector<int> c, vector<int> d, vector<int> e )
{
	const int MAX = 180000;
	int curMax = 0;
	int count = 0;

	while (1)
	{
		int judges[5];

		vector<int>::const_iterator itr1 = std::lower_bound(a.begin(), a.end(), curMax);
		judges[0] = itr1 != a.end() ? *itr1 : MAX;

		vector<int>::const_iterator itr2 = std::lower_bound(b.begin(), b.end(), curMax);
		judges[1] = itr2 != b.end() ? *itr2 : MAX;

		vector<int>::const_iterator itr3 = std::lower_bound(c.begin(), c.end(), curMax);
		judges[2] = itr3 != c.end() ? *itr3 : MAX;

		vector<int>::const_iterator itr4 = std::lower_bound(d.begin(), d.end(), curMax);
		judges[3] = itr4 != d.end() ? *itr4 : MAX;

		vector<int>::const_iterator itr5 = std::lower_bound(e.begin(), e.end(), curMax);
		judges[4] = itr5 != e.end() ? *itr5 : MAX;

		std::sort(judges, judges + 5);

		if (judges[2] >= MAX)
			break;

		if (judges[2] - judges[0] <= 1000)
		{
			++count;
			curMax = judges[2] + 1;
		}
		else
		{
			++curMax;
		}
	}
	return count;
}

int TEST( vector<int> a, vector< int > b, vector<int> c, vector<int> d, vector<int> e, int expected )
{
	clock_t start, end;
	double cpu_time_used;

	start = clock();

	Boxing boxing;
	int ret = boxing.maxCredit( a, b, c, d, e );

	end = clock();
	cpu_time_used = ((double) (end - start));
	cout<<"Time taken : "<<cpu_time_used<<endl;

	assert( ret == expected );

	return ret;
}

vector<int> convert(int *list, int size)
{
	vector<int> vect;

	for (int idx = 0; idx < size; ++idx)
	{
		vect.push_back(list[idx]);
	}

	return vect;
}

void Test1()
{
	int g1[] = {1,2,3,4,5,6};
	int g2[] = {1,2,3,4,5,6,7};
	int g3[] = {1,2,3,4,5,6};
	int g4[] = {0,1,2};
	int g5[] = {1,2,3,4,5,6,7,8};

	cout<<TEST( convert(g1, sizeof(g1)/sizeof(int)),
		convert(g2, sizeof(g2)/sizeof(int)),
		convert(g3, sizeof(g3)/sizeof(int)),
		convert(g4, sizeof(g4)/sizeof(int)),
		convert(g5, sizeof(g5)/sizeof(int)), 6 )<<endl;
}

void Test2()
{
	int g1[] = {100,200,300,1200,6000};
	//int g2[] = { NULL };
	int g3[] = {900,902,1200,4000,5000,6001};
	int g4[] = {0,2000,6002};
	int g5[] = {1,2,3,4,5,6,7,8};

	cout<<TEST( convert(g1, sizeof(g1)/sizeof(int)),
		convert(NULL, 0),
		convert(g3, sizeof(g3)/sizeof(int)),
		convert(g4, sizeof(g4)/sizeof(int)),
		convert(g5, sizeof(g5)/sizeof(int)), 3 )<<endl;
}

void Test3()
{
	int g1[] = {5000,6500};
	int g2[] = {6000};
	int g3[] = {6500};
	int g4[] = {6000};
	int g5[] = {0,5800,6000};

	cout<<TEST( convert(g1, sizeof(g1)/sizeof(int)),
		convert(g2, sizeof(g2)/sizeof(int)),
		convert(g3, sizeof(g3)/sizeof(int)),
		convert(g4, sizeof(g4)/sizeof(int)),
		convert(g5, sizeof(g5)/sizeof(int)), 1 )<<endl;
}

void Test4()
{
	int g1[] = {180000};
	int g2[] =  {1, 2, 3, 4, 5, 6, 179000, 179500, 179800};
	int g3[] =  {5, 10, 1000, 10000};
	int g4[] = {5, 10, 1000, 10000};
	int g5[] = {6, 9000};

	cout<<TEST( convert(g1, sizeof(g1)/sizeof(int)),
		convert(g2, sizeof(g2)/sizeof(int)),
		convert(g3, sizeof(g3)/sizeof(int)),
		convert(g4, sizeof(g4)/sizeof(int)),
		convert(g5, sizeof(g5)/sizeof(int)), 3 )<<endl;
}

void Test5()
{
	int g1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50};
	int g2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50};
	int g3[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50};
	int g4[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50};
	int g5[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50};

	cout<<TEST( convert(g1, sizeof(g1)/sizeof(int)),
		convert(g2, sizeof(g2)/sizeof(int)),
		convert(g3, sizeof(g3)/sizeof(int)),
		convert(g4, sizeof(g4)/sizeof(int)),
		convert(g5, sizeof(g5)/sizeof(int)), 50 )<<endl;
}

void Test6()
{
	int g1[] = {0, 4244, 8627, 9903, 31479, 40959, 44573, 45119, 45998, 46078, 47150, 47833, 49210, 50070, 56274, 56982, 58247, 59485, 77334, 81949, 91133, 98080, 102696, 105045, 105079, 111421, 113613, 118602, 124653, 134545, 136564, 137813, 138060, 141547, 151108, 151348, 156210, 166236, 174986, 177342, 177710};
	int g2[] = {0, 2430, 7853, 13088, 21832, 24275, 30409, 36233, 49393, 51785, 54662, 55725, 56628, 60462, 63882, 66856, 67212, 74681, 74957, 87425, 89567, 97859, 97958, 105136, 106213, 107656, 108554, 111029, 113202, 119091, 119684, 124691, 126694, 132821, 144116, 146492, 147893, 151953, 155306, 164568, 164748};
	int g3[] = {0, 6842, 13439, 13936, 16259, 24061, 24247, 24852, 35161, 40211, 41246, 43182, 46628, 46750, 56598, 60779, 62036, 62447, 65024, 70049, 74411, 78506, 79298, 80462, 80797, 83909, 89970, 99032, 103158, 116140, 118861, 121203, 121884, 133335, 145983, 150611, 154531, 160319, 166847, 176077, 176980};
	int g4[] = {0, 4278, 4521, 14703, 15142, 15530, 19172, 19265, 21880, 25585, 26615, 28314, 31481, 31977, 33593, 37475, 39154, 49434, 60148, 63581, 68149, 68737, 73341, 73367, 84830, 84848, 89726, 91857, 94920, 109318, 110430, 112129, 115111, 119117, 122739, 126402, 147254, 149053, 151834, 168627, 174675};
	int g5[] = {0, 2148, 4367, 10640, 18035, 18487, 21629, 26109, 31283, 40380, 40730, 52166, 59667, 60313, 64014, 66510, 68348, 68609, 71314, 75624, 88972, 96476, 98137, 98788, 106141, 109176, 114246, 117649, 126005, 127893, 128583, 131962, 132113, 134437, 140498, 144765, 150567, 151156, 151584, 161092, 179359};

	cout<<TEST( convert(g1, sizeof(g1)/sizeof(int)),
		convert(g2, sizeof(g2)/sizeof(int)),
		convert(g3, sizeof(g3)/sizeof(int)),
		convert(g4, sizeof(g4)/sizeof(int)),
		convert(g5, sizeof(g5)/sizeof(int)), 18 )<<endl;
}

int main()
{
	Test1();
	Test2();
	Test3();
	Test4();
	Test5();
	Test6();
	getchar();
    return 0;
}
