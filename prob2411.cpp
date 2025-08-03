#include <vector>
#include <iostream>

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

int getCountToMaxOr(vector<int>& nums, int index, int maxOrValue)
{
    int cumulativeOr = nums[index];
    int pos = index;

    // comma operator execs left side, then execs right side and returns right side
    while (cumulativeOr |= nums[++pos], cumulativeOr < maxOrValue) ;

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
            if (hasUniqueBits(nums[index], maxOrVec[index + 1]))
            {
                if (nums[index] > maxOrVec[index + 1])
                {
                    maxOrVec[index] = nums[index];
                    smallestSubVec[index] = 1;
                }
                else
                {
                    maxOrVec[index] = maxOrVec[index + 1] | nums[index];
                    smallestSubVec[index] = smallestSubVec[index + 1] + 1;
                }
            }
            else
            {
                maxOrVec[index] = maxOrVec[index + 1];
                if (nums[index] == maxOrVec[index + 1])
                {
                    smallestSubVec[index] = 1;
                }
                else
                {
                    if (0 == nums[index])
                    {
                        smallestSubVec[index] = smallestSubVec[index + 1] + 1;
                    }
                    else
                    {
                        // This is the complicated case, must iterate to see how
                        // many ORs it takes to get the smallest subarray creating max
                        smallestSubVec[index] = getCountToMaxOr(nums, index, maxOrVec[index + 1]);
                    }
                }
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

    auto result = sol.smallestSubarrays(test2);

    printVec(result);
}
