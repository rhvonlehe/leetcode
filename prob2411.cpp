#include <vector>
#include <iostream>
#include <tuple>

using namespace std;

void printVec(vector<int>& vec)
{
    for (auto item : vec)
    {
        cout << item << " ";
    }

    cout << endl;
}


int hasUniqueBits(int left, int right)
{
    int xorResult = left ^ right;

    int finalResult = left & xorResult;

    return finalResult;
}

int getCountToMaxOr(vector<int>& nums, vector<int>& maxOrVec, int index)
{
    int cumulativeOr = nums[index];
    int count = 1;

    cumulativeOr |= nums[index + 1];

    if (cumulativeOr > maxOrVec[index + 1])
    {
        maxOrVec[index] = cumulativeOr;
        count++;
    }

    return (pos - index) + 1;
}

class Solution {
public:
    vector<int> smallestSubarrays(vector<int>& nums) {
        vector<int> maxOrVec(nums.size());
        vector<int> smallestSubVec(nums.size());
        int rightmostIndex = nums.size() - 1;

        // Fill out the known rightmost values
        maxOrVec[rightmostIndex] = nums[rightmostIndex];
        smallestSubVec[rightmostIndex] = 1;

        // iterate over the vector from right to left: TODO is there a way to use a transform?
        for (int index = rightmostIndex - 1; index >= 0; --index)
        {
            if (0 == nums[index])
            {
                maxOrVec[index] = maxOrVec[index + 1];
                smallestSubVec[index] = smallestSubVec[index + 1] + 1;
            }
            else
            {
                smallestSubVec[index] = getCountToMaxOr(nums, maxOrVec, index);
            }
        }

        return smallestSubVec;
    }
};


int main(void)
{
    Solution sol;
    vector<int> test1 { 1, 0, 2, 1, 3 };
    vector<int> test2 { 8, 10, 8 };
    vector<int> test3 {4,0,5,6,3,2};

    auto result = sol.smallestSubarrays(test3);

    printVec(result);
}
