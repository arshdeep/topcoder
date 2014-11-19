//
//  topcoder.cpp
//  test
//
//  Created by asingh on 11/19/14.
//  Copyright (c) 2014 asingh. All rights reserved.
//

#include <iostream>
#include <vector>
#include <cassert>
using namespace std;
/* http://topcoder.bgcoder.com/print.php?id=393 */

#define SIZEOFINTARRAY(a) sizeof(a)/sizeof(int)

class FlowerGarden
{
public:
    vector<int> getOrdering(vector<int> height, vector<int> bloom, vector<int> wilt);
};

vector<int> FlowerGarden::getOrdering(vector<int> height, vector<int> bloom, vector<int> wilt)
{
    size_t len = height.size();
    vector<int> result;
    vector<int> used(len);
    
    for (size_t i = 0; i < len; ++i)
    {
        size_t maxIndex = -1;
        int maxHeight = -1;
        
        for (size_t j = 0; j < len; ++j) {
            if (!used[j])
            {
                bool found = true;
                for (size_t k = 0; k < len && found; ++k) {
                    if (!used[k])
                    {
                        bool isBlocking = (wilt[j] >= bloom[k] && bloom[j] <= wilt[k])
                        || (wilt[j] >= wilt[k] && bloom[j] <= wilt[k]);

                        if (height[j] > height[k] && isBlocking)
                        {
                            found = false;
                            break;
                        }
                    }
                }
                
                if (found && height[j] > maxHeight)
                {
                    maxIndex = j;
                    maxHeight = height[j];
                }
            }
        }
        
        if (maxIndex != -1)
        {
            used[maxIndex] = true;
            result.push_back(maxHeight);
        }
    }
    return result;
}

void TEST(vector<int> height, vector<int> bloom, vector<int> wilt, vector<int> expected)
{
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    
    FlowerGarden flowerGarden;
    
    vector<int> result = flowerGarden.getOrdering(height, bloom, wilt);
    
    end = clock();
    cpu_time_used = ((double) (end - start));
    cout<<"Time taken : "<<cpu_time_used<<endl;
    
    assert( result.size() == expected.size() &&
           std::equal(result.begin(), result.end(),
                      expected.begin()) );
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
    int height[] = {730,882,841,120,789};
    int bloom[] = {51,234,354,273,115};
    int wilt[] = {214, 319,363,331,251};
    int expected[] = {841, 730, 789, 120, 882};
    
    TEST( convert(height, sizeof(height)/sizeof(int)),
         convert(bloom, sizeof(bloom)/sizeof(int)),
         convert(wilt, sizeof(wilt)/sizeof(int)),
         convert(expected, sizeof(expected)/sizeof(int)) );
}

void Test2()
{
    int height[] = {5,4,3,2,1};
    int bloom[] = {1,1,1,1,1};
    int wilt[] = {365,365,365,365,365};
    int expected[] = {1,  2,  3,  4,  5};
    
    TEST( convert(height, sizeof(height)/sizeof(int)),
         convert(bloom, sizeof(bloom)/sizeof(int)),
         convert(wilt, sizeof(wilt)/sizeof(int)),
         convert(expected, sizeof(expected)/sizeof(int)) );
}

void Test3()
{
    int height[] = {5,4,3,2,1};
    int bloom[] = {1,5,10,15,20};
    int wilt[] = {4,9,14,19,24};
    int expected[] = {5,  4,  3,  2,  1};
    
    TEST( convert(height, sizeof(height)/sizeof(int)),
         convert(bloom, sizeof(bloom)/sizeof(int)),
         convert(wilt, sizeof(wilt)/sizeof(int)),
         convert(expected, sizeof(expected)/sizeof(int)) );
}

void Test4()
{
    int height[] = {5,4,3,2,1};
    int bloom[] = {1,5,10,15,20};
    int wilt[] = {5,10,15,20,25};
    int expected[] = {1,  2,  3,  4,  5 };
    
    TEST( convert(height, sizeof(height)/sizeof(int)),
         convert(bloom, sizeof(bloom)/sizeof(int)),
         convert(wilt, sizeof(wilt)/sizeof(int)),
         convert(expected, sizeof(expected)/sizeof(int)) );
}

void Test5()
{
    int height[] = {3,2,5,4};
    int bloom[] = {1,2,11,10};
    int wilt[] = {4,3,12,13};
    int expected[] = {4,  5,  2,  3 };
    
    TEST( convert(height, sizeof(height)/sizeof(int)),
         convert(bloom, sizeof(bloom)/sizeof(int)),
         convert(wilt, sizeof(wilt)/sizeof(int)),
         convert(expected, sizeof(expected)/sizeof(int)) );
}

void Test6()
{
    int height[] = {1,2,3,4,5,6};
    int bloom[] = {1,3,1,3,1,3};
    int wilt[] = {2,4,2,4,2,4};
    int expected[] = {2,  4,  6,  1,  3,  5};
    
    TEST( convert(height, sizeof(height)/sizeof(int)),
         convert(bloom, sizeof(bloom)/sizeof(int)),
         convert(wilt, sizeof(wilt)/sizeof(int)),
         convert(expected, sizeof(expected)/sizeof(int)) );
}

int main(int argc, const char * argv[]) {
    // insert code here...
    Test1();
    Test2();
    Test3();
    Test4();
    Test5();
    Test6();
    cout<<"success";
    return 0;
}
