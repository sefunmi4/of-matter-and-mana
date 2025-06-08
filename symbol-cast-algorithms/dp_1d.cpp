#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <numeric>  // for accumulate
#include <cstdint>

// Symbol Cast Algorithm Suite for EtherOS
// Inputs are 3D objects with ordering numbers and category colors.
// Complexity: O(n) = S(n) + cT(n) treating time as a spatial dimension.
// Referencing an object updates its position; copying leaves it in place.

using namespace std;

class DP_1D {
public:
    DP_1D() {}
    ~DP_1D() {}
    DP_1D(const DP_1D& other) = default;
    DP_1D(DP_1D&& other) noexcept = default;
    DP_1D& operator=(const DP_1D& other) = default;
    DP_1D& operator=(DP_1D&& other) noexcept = default;

    // 1. climbing stairs / num_ways_fibinacci_1D:
    // Given a linear sequence of n discrete positions, you may advance 1 or 2
    // units at a time. Count the unique sequences of moves required to reach
    // position n. This models movement through time as a 1D space.
    int climbStairs(int n) {
        int one = 1, two = 1;
        
        for (int i = 0; i < n - 1; i++) {
            int temp = one;
            one = one + two;
            two = temp;
        }
        
        return one;
    }

    // 2. min cost climbing stairs:
    // Given an array cost where cost[i] is the energy to move from position i,
    // you may advance 1 or 2 positions after paying that energy. Determine the
    // minimal total cost to go beyond the last index.
    int minCostClimbingStairs(vector<int>& cost) {
        for (int i = cost.size() - 3; i >= 0; i--) {
            cost[i] += min(cost[i + 1], cost[i + 2]);
        }
        return min(cost[0], cost[1]);
    }

    // 3. house robber:
    // Given a line of locations each holding a value, pick locations to
    // maximize the total without selecting two that are adjacent along the
    // line. This models optimal resource collection along a 1D path.
    int rob(vector<int>& nums) {
        int rob1 = 0, rob2 = 0;

        for (int num : nums) {
            int temp = max(num + rob1, rob2);
            rob1 = rob2;
            rob2 = temp;
        }
        return rob2;
    }

    // 4. house robber 2:
    // Similar to the linear case, but the locations form a closed loop. Choose
    // values to maximize the sum without taking two neighboring locations.

    class HouseRobber2Solution {
    public:
        int rob(vector<int>& nums) {
            vector<int> nums1(nums.begin() + 1, nums.end());
            vector<int> nums2(nums.begin(), nums.end() - 1);
            return max(nums[0],
                max(helper(nums1), helper(nums2)));
        }

    private:
        int helper(vector<int>& nums) {
            int rob1 = 0, rob2 = 0;
            for (int num : nums) {
                int newRob = max(rob1 + num, rob2);
                rob1 = rob2;
                rob2 = newRob;
            }
            return rob2;
        }
    };

    // 5. longest palandromic substring:
    // For a sequence of symbols, find the longest contiguous region that reads
    // identically forward and backward. Return any maximum-length region.

    class PalindromeSolution {
    public:
        vector<int> manacher(string& s) {
            string t = "#" + string(1, s[0]);
            for (int i = 1; i < s.size(); ++i)
                t += "#" + string(1, s[i]);
            t += "#";
            int n = t.size();
            vector<int> p(n, 0);
            int l = 0, r = 0;
            for (int i = 0; i < n; i++) {
                p[i] = (i < r) ? min(r - i, p[l + (r - i)]) : 0;
                while (i + p[i] + 1 < n && i - p[i] - 1 >= 0 &&
                    t[i + p[i] + 1] == t[i - p[i] - 1])
                    p[i]++;
                if (i + p[i] > r)
                    l = i - p[i], r = i + p[i];
            }
            return p;
        }
        
        string longestPalindrome(string s) {
            vector<int> p = manacher(s);
            int resLen = 0, center_idx = 0;
            for (int i = 0; i < p.size(); i++) {
                if (p[i] > resLen) {
                    resLen = p[i];
                    center_idx = i;
                }
            }
            int resIdx = (center_idx - resLen) / 2;
            return s.substr(resIdx, resLen);
        }
    };

    // 6. decode ways:
    // Digits map to letters using 1→A, 2→B, … 26→Z. Given a numeric string,
    // count how many valid letter sequences it can represent when grouping the
    // digits. Leading zeroes are not allowed in any group.
    int numDecodings(string s) {
        int dp = 0, dp2 = 0;
        int dp1 = 1;
        for (int i = s.size() - 1; i >= 0; i--) {
            if (s[i] == '0') {
                dp = 0;
            } else {
                dp = dp1;
                if (i + 1 < s.size() && (s[i] == '1' || 
                    s[i] == '2' && s[i + 1] < '7')) {
                    dp += dp2;
                }
            }
            dp2 = dp1;
            dp1 = dp;
            dp = 0;
        }
        return dp1;
    }

    // 7. coin change:
    // Given coin denominations and a target value, compute the minimal number
    // of coins required to exactly reach that value. Return -1 if it cannot be
    // reached using the available denominations.
    int coinChange(vector<int>& coins, int amount) {
        vector<int> dp(amount + 1, amount + 1);
        dp[0] = 0;
        for (int i = 1; i <= amount; i++) {
            for (int j = 0; j < coins.size(); j++) {
                if (coins[j] <= i) {
                    dp[i] = min(dp[i], dp[i - coins[j]] + 1);
                }
            }
        }
        return dp[amount] > amount ? -1 : dp[amount];
    } 

    // 8. maximum product subarray:
    // Find the contiguous segment of numbers whose product is maximized.
    // Assumes the result fits in a standard 32-bit integer type.

    int maxProduct(vector<int>& nums) {
        int n = nums.size(), res = nums[0];
        int prefix = 0, suffix = 0;

        for (int i = 0; i < n; i++) {
            prefix = nums[i] * (prefix == 0 ? 1 : prefix);
            suffix = nums[n - 1 - i] * (suffix == 0 ? 1 : suffix);
            res = max(res, max(prefix, suffix));
        }
        return res;
    }

    // 9. word break:
    // Determine if a string can be segmented into a sequence of allowed words.
    // Words may be reused any number of times.

    class TrieNode {
    public:
        unordered_map<char, TrieNode*> children;
        bool is_word = false;
    };

    class Trie {
    public:
        TrieNode* root;

        Trie() {
            root = new TrieNode();
        }

        void insert(string word) {
            TrieNode* node = root;
            for (char c : word) {
                if (!node->children.count(c)) {
                    node->children[c] = new TrieNode();
                }
                node = node->children[c];
            }
            node->is_word = true;
        }

        bool search(string& s, int i, int j) {
            TrieNode* node = root;
            for (int idx = i; idx <= j; ++idx) {
                if (!node->children.count(s[idx])) {
                    return false;
                }
                node = node->children[s[idx]];
            }
            return node->is_word;
        }
    };

    bool wordBreak(string s, vector<string>& wordDict) {
        Trie trie;
        for (string word : wordDict) {
            trie.insert(word);
        }

        int n = s.length();
        vector<bool> dp(n + 1, false);
        dp[n] = true;

        int maxLen = 0;
        for (string w : wordDict) {
            maxLen = max(maxLen, (int)w.size());
        }

        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < min(n, i + maxLen); ++j) {
                if (trie.search(s, i, j)) {
                    dp[i] = dp[j + 1];
                    if (dp[i]) break;
                }
            }
        }

        return dp[0];
    }

    // 10. longest increasing subsequence:
    // Compute the length of the longest sequence that strictly increases as you
    // move forward through the values, skipping elements as needed.
    int lengthOfLIS(vector<int>& nums) {
        vector<int> dp;
        dp.push_back(nums[0]);

        int LIS = 1;
        for (int i = 1; i < nums.size(); i++) {
            if (dp.back() < nums[i]) { 
                dp.push_back(nums[i]);
                LIS++;
                continue;
            }

            int idx = lower_bound(dp.begin(), 
                                  dp.end(), nums[i]) - dp.begin();
            dp[idx] = nums[i]; 
        }

        return LIS;
    }

    // 11. partition equal subset sum:
    // Determine if the values can be split into two groups with equal totals.
    class PartitionSolution {
    public:
        bool canPartition(vector<int>& nums) {
            if (sum(nums) % 2 != 0) {
                return false;
            }

            int target = sum(nums) / 2;
            vector<bool> dp(target + 1, false);

            dp[0] = true;
            for (int i = 0; i < nums.size(); i++) {
                for (int j = target; j >= nums[i]; j--) {
                    dp[j] = dp[j] || dp[j - nums[i]];
                }
            }
            
            return dp[target];
        }

    private:
        int sum(vector<int>& nums) {
            int total = 0;
            for (int num : nums) {
                total += num;
            }
            return total;
        }
    };

};