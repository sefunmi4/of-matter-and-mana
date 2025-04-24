#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <numeric>  // for accumulate
#include <cstdint>

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
    // You are given an integer n representing the number of steps to reach the top of a staircase. You can climb with either 1 or 2 steps at a time.
    // Return the number of distinct ways to climb to the top of the staircase.
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
    // You are given an array of integers cost where cost[i] is the cost of taking a step from the ith floor of a staircase. After paying the cost, you can step to either the (i + 1)th floor or the (i + 2)th floor.
    // You may choose to start at the index 0 or the index 1 floor.
    // Return the minimum cost to reach the top of the staircase, i.e. just past the last index in cost.
    int minCostClimbingStairs(vector<int>& cost) {
        for (int i = cost.size() - 3; i >= 0; i--) {
            cost[i] += min(cost[i + 1], cost[i + 2]);
        }
        return min(cost[0], cost[1]);
    }

    // 3. house robber:
    // You are given an integer array nums where nums[i] represents the amount of money the ith house has. The houses are arranged in a straight line, i.e. the ith house is the neighbor of the (i-1)th and (i+1)th house.
    // You are planning to rob money from the houses, but you cannot rob two adjacent houses because the security system will automatically alert the police if two adjacent houses were both broken into.
    // Return the maximum amount of money you can rob without alerting the police.
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
    // You are given an integer array nums where nums[i] represents the amount of money the ith house has. The houses are arranged in a circle, i.e. the first house and the last house are neighbors.

    // You are planning to rob money from the houses, but you cannot rob two adjacent houses because the security system will automatically alert the police if two adjacent houses were both broken into.

    // Return the maximum amount of money you can rob without alerting the police.

    class Solution {
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
    // Given a string s, return the longest substring of s that is a palindrome.

    // A palindrome is a string that reads the same forward and backward.

    // If there are multiple palindromic substrings that have the same length, return any one of them.

    class Solution {
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

    // 6.decode ways:
    // A string consisting of uppercase english characters can be encoded to a number using the following mapping:

    // 'A' -> "1"
    // 'B' -> "2"
    // ...
    // 'Z' -> "26"
    // To decode a message, digits must be grouped and then mapped back into letters using the reverse of the mapping above. There may be multiple ways to decode a message. For example, "1012" can be mapped into:

    // "JAB" with the grouping (10 1 2)
    // "JL" with the grouping (10 12)
    // The grouping (1 01 2) is invalid because 01 cannot be mapped into a letter since it contains a leading zero.

    // Given a string s containing only digits, return the number of ways to decode it. You can assume that the answer fits in a 32-bit integer.
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
    // You are given an integer array coins representing coins of different denominations (e.g. 1 dollar, 5 dollars, etc) and an integer amount representing a target amount of money.

    // Return the fewest number of coins that you need to make up the exact target amount. If it is impossible to make up the amount, return -1.

    // You may assume that you have an unlimited number of each coin.
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
    // Given an integer array nums, find a subarray that has the largest product within the array and return it.

    // A subarray is a contiguous non-empty sequence of elements within an array.

    // You can assume the output will fit into a 32-bit integer.

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
    // Given a string s and a dictionary of strings wordDict, return true if s can be segmented into a space-separated sequence of dictionary words.

    // You are allowed to reuse words in the dictionary an unlimited number of times. You may assume all dictionary words are unique.

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
    // Given an integer array nums, return the length of the longest strictly increasing subsequence.

    // A subsequence is a sequence that can be derived from the given sequence by deleting some or no elements without changing the relative order of the remaining characters.

    // For example, "cat" is a subsequence of "crabt".
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
    // You are given an array of positive integers nums.
    // Return true if you can partition the array into two subsets, subset1 and subset2 where sum(subset1) == sum(subset2). Otherwise, return false.
    class Solution {
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
private:

};