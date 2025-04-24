#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <numeric>  // for accumulate
#include <cstdint>

using namespace std;

class Greedy {
public:
    Greedy() {}
    ~Greedy() {}
    Greedy(const Greedy& other) = default;
    Greedy(Greedy&& other) noexcept = default;
    Greedy& operator=(const Greedy& other) = default;
    Greedy& operator=(Greedy&& other) noexcept = default;

    // 1. Maximum Subarray (Divide and Conquer)
    int maxSubArray(vector<int>& nums) {
        return maxSubArrayHelper(nums, 0, nums.size() - 1);
    }

    // 2. Jump Game I
    bool canJump(vector<int>& nums) {
        int goal = nums.size() - 1;
        for (int i = nums.size() - 2; i >= 0; i--) {
            if (i + nums[i] >= goal) goal = i;
        }
        return goal == 0;
    }

    // 3. Jump Game II
    int jump(vector<int>& nums) {
        int res = 0, l = 0, r = 0;
        while (r < nums.size() - 1) {
            int farthest = 0;
            for (int i = l; i <= r; i++) {
                farthest = max(farthest, i + nums[i]);
            }
            l = r + 1;
            r = farthest;
            res++;
        }
        return res;
    }

    // 4. Gas Station
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        if (accumulate(gas.begin(), gas.end(), 0) < accumulate(cost.begin(), cost.end(), 0)) {
            return -1;
        }

        int total = 0, start = 0;
        for (int i = 0; i < gas.size(); i++) {
            total += gas[i] - cost[i];
            if (total < 0) {
                total = 0;
                start = i + 1;
            }
        }
        return start;
    }

    // 5. Hand of Straights
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        if (hand.size() % groupSize != 0) return false;

        unordered_map<int, int> count;
        for (int num : hand) count[num]++;

        sort(hand.begin(), hand.end());
        for (int num : hand) {
            if (count[num] == 0) continue;

            for (int i = 0; i < groupSize; i++) {
                if (count[num + i] == 0) return false;
                count[num + i]--;
            }
        }
        return true;
    }

    // 6. Merge Triplets to Form Target Triplet
    bool mergeTriplets(vector<vector<int>>& triplets, vector<int>& target) {
        bool x = false, y = false, z = false;
        for (const auto& t : triplets) {
            if (t[0] <= target[0] && t[1] <= target[1] && t[2] <= target[2]) {
                if (t[0] == target[0]) x = true;
                if (t[1] == target[1]) y = true;
                if (t[2] == target[2]) z = true;
            }
        }
        return x && y && z;
    }

    // 7. Partition Labels
    vector<int> partitionLabels(string s) {
        unordered_map<char, int> last;
        for (int i = 0; i < s.size(); i++) {
            last[s[i]] = i;
        }

        vector<int> res;
        int size = 0, end = 0;
        for (int i = 0; i < s.size(); i++) {
            size++;
            end = max(end, last[s[i]]);
            if (i == end) {
                res.push_back(size);
                size = 0;
            }
        }
        return res;
    }

    // 8. Valid Parenthesis String
    bool checkValidString(string s) {
        int minOpen = 0, maxOpen = 0;
        for (char c : s) {
            if (c == '(') {
                minOpen++;
                maxOpen++;
            } else if (c == ')') {
                minOpen--;
                maxOpen--;
            } else {
                minOpen--;
                maxOpen++;
            }

            if (maxOpen < 0) return false;
            if (minOpen < 0) minOpen = 0;
        }
        return minOpen == 0;
    }

private:
    // Helper: Maximum Subarray Divide and Conquer
    int maxSubArrayHelper(vector<int>& nums, int l, int r) {
        if (l > r) return INT_MIN;
        int m = l + (r - l) / 2;

        int leftSum = 0, curSum = 0;
        for (int i = m - 1; i >= l; i--) {
            curSum += nums[i];
            leftSum = max(leftSum, curSum);
        }

        int rightSum = 0; curSum = 0;
        for (int i = m + 1; i <= r; i++) {
            curSum += nums[i];
            rightSum = max(rightSum, curSum);
        }

        int crossSum = leftSum + nums[m] + rightSum;
        int leftMax = maxSubArrayHelper(nums, l, m - 1);
        int rightMax = maxSubArrayHelper(nums, m + 1, r);

        return max({leftMax, rightMax, crossSum});
    }
};