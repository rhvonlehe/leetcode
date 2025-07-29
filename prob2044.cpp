#include <vector>
#include <map>
#include <cmath>
#include <iostream>

// this is calling our for recursion:
// 1: add current to a tuple
// 2: add tuple including all combinations of current and immediate right neighbor

// So the basic function is:
//

using namespace std;
// This becomes a binning problem?

void printVec(vector<int>& vec)
{
    for (auto item : vec)
    {
        cout << item << " ";
    }

    cout << endl;
}

auto calcBitwiseOr(vector<int>& nums, vector<int>& indices)
{
    int ret{};

    for (auto index : indices)
    {
        if (0 == ret) ret = nums[index];
        else
        {
            ret = ret | nums[index];
        }
    }

    cout << "bitwise OR: " << ret << endl;
    return ret;
}

auto getAllIndexSets(vector<int>& nums)
{
    vector<vector<int>> ret;
    vector<int> maskCombo;
    const size_t vecsize = nums.size();

    size_t comboCnt = pow(2, vecsize);

    for (int mask = 1; mask < comboCnt; ++mask)
    {
        maskCombo.clear();

        for (int bitpos = 0; bitpos < vecsize; ++bitpos)
        {
            if ((1 << bitpos) & mask)
            {
                maskCombo.push_back(bitpos);
            }
        }

        printVec(maskCombo);
        ret.push_back(maskCombo);
    }

    return ret;
}

class Solution {
public:
    int countMaxOrSubsets(vector<int>& nums) {
        maxOr = 0;
        auto allIndexSets = getAllIndexSets(nums);

        for (auto& set : allIndexSets)
        {
            auto currentOr = calcBitwiseOr(nums, set);
            count[currentOr]++;

            if (currentOr > maxOr)
            {
                maxOr = currentOr;
            }
        }

        return count[maxOr];
    }

private:
    int             maxOr;
    map<int, int>   count;
};



int main()
{
    Solution sol;

    vector<int> test1 { 2, 2, 2 };
    auto ans = sol.countMaxOrSubsets(test1);
    cout << "test1 ans: " << ans << endl;

    vector<int> test2 { 3, 2, 1, 5 };
    ans = sol.countMaxOrSubsets(test2);
    cout << "test2 ans: " << ans << endl;


    // test stuff
    // vector<int> test { 1,3,5,7 };
    // auto ret = getAllIndexSets(test);


}
