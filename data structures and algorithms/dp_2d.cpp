#include <vector>
#include <string>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <cmath>

using namespace std;

class DP_2D {
public:
    DP_2D() {}
    ~DP_2D() {}
    DP_2D(const DP_2D& other) = default;
    DP_2D(DP_2D&& other) noexcept = default;
    DP_2D& operator=(const DP_2D& other) = default;
    DP_2D& operator=(DP_2D&& other) noexcept = default;

    // 1. unique paths:
    // There is an m x n grid where you are allowed to move either down or to the right at any point in time.s
    // Given the two integers m and n, return the number of possible unique paths that can be taken from the top-left corner of the grid (grid[0][0]) to the bottom-right corner (grid[m - 1][n - 1]).
    // You may assume the output will fit in a 32-bit integer.
    int uniquePaths(int m, int n) {
        vector<int> dp(n, 1);
        
        for (int i = m - 2; i >= 0; i--) {
            for (int j = n - 2; j >= 0; j--) {
                dp[j] += dp[j + 1];
            }
        }
        
        return dp[0];
    }

    // 2. longest common subsequence:
    // Given two strings text1 and text2, return the length of the longest common subsequence between the two strings if one exists, otherwise return 0.
    // A subsequence is a sequence that can be derived from the given sequence by deleting some or no elements without changing the relative order of the remaining characters.
    // For example, "cat" is a subsequence of "crabt".
    // A common subsequence of two strings is a subsequence that exists in both strings.
    int longestCommonSubsequence(string text1, string text2) {
        if (text1.size() < text2.size()) {
            swap(text1, text2);
        }

        vector<int> dp(text2.size() + 1, 0);

        for (int i = text1.size() - 1; i >= 0; --i) {
            int prev = 0;
            for (int j = text2.size() - 1; j >= 0; --j) {
                int temp = dp[j];
                if (text1[i] == text2[j]) {
                    dp[j] = 1 + prev;
                } else {
                    dp[j] = max(dp[j], dp[j + 1]);
                }
                prev = temp;
            }
        }

        return dp[0];
    }

    // 3.best time to buy and sell stock with cooldown:
    // You are given an integer array prices where prices[i] is the price of NeetCoin on the ith day.

    // You may buy and sell one NeetCoin multiple times with the following restrictions:

    // After you sell your NeetCoin, you cannot buy another one on the next day (i.e., there is a cooldown period of one day).
    // You may only own at most one NeetCoin at a time.
    // You may complete as many transactions as you like.

    // Return the maximum profit you can achieve.
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        int dp1_buy = 0, dp1_sell = 0;
        int dp2_buy = 0;

        for (int i = n - 1; i >= 0; --i) {
            int dp_buy = max(dp1_sell - prices[i], dp1_buy);
            int dp_sell = max(dp2_buy + prices[i], dp1_sell);
            dp2_buy = dp1_buy;
            dp1_buy = dp_buy;
            dp1_sell = dp_sell;
        }

        return dp1_buy;
    }

    // 4. coin change 2:
    // You are given an integer array coins representing coins of different denominations (e.g. 1 dollar, 5 dollars, etc) and an integer amount representing a target amount of money.
    // Return the number of distinct combinations that total up to amount. If it's impossible to make up the amount, return 0.
    // You may assume that you have an unlimited number of each coin and that each value in coins is unique.
    int change(int amount, vector<int>& coins) {
        vector<uint> dp(amount + 1, 0);
        dp[0] = 1;
        for (int i = coins.size() - 1; i >= 0; i--) {
            for (int a = 1; a <= amount; a++) {
                dp[a] = dp[a] + (coins[i] <= a ? dp[a - coins[i]] : 0);
            }
        }
        return dp[amount];
    }

    // 5. target sum:
    // You are given an array of integers nums and an integer target.
    // For each number in the array, you can choose to either add or subtract it to a total sum.
    // For example, if nums = [1, 2], one possible sum would be "+1-2=-1".
    // If nums=[1,1], there are two different ways to sum the input numbers to get a sum of 0: "+1-1" and "-1+1".
    // Return the number of different ways that you can build the expression such that the total sum equals target.
    int findTargetSumWays(vector<int>& nums, int target) {
        unordered_map<int, int> dp;
        dp[0] = 1;

        for (int num : nums) {
            unordered_map<int, int> nextDp;
            for (auto& entry : dp) {
                int total = entry.first;
                int count = entry.second;
                nextDp[total + num] += count;
                nextDp[total - num] += count;
            }
            dp = nextDp;
        }
        return dp[target];
    }

    // 6. interleaving string:
    // You are given three strings s1, s2, and s3. Return true if s3 is formed by interleaving s1 and s2 together or false otherwise.

    // Interleaving two strings s and t is done by dividing s and t into n and m substrings respectively, where the following conditions are met

    // |n - m| <= 1, i.e. the difference between the number of substrings of s and t is at most 1.
    // s = s1 + s2 + ... + sn
    // t = t1 + t2 + ... + tm
    // Interleaving s and t is s1 + t1 + s2 + t2 + ... or t1 + s1 + t2 + s2 + ...
    // You may assume that s1, s2 and s3 consist of lowercase English letters.
    bool isInterleave(string s1, string s2, string s3) {
        int m = s1.size(), n = s2.size();
        if (m + n != s3.size()) return false;
        if (n < m) {
            swap(s1, s2);
            swap(m, n);
        }

        vector<bool> dp(n + 1, false);
        dp[n] = true;
        for (int i = m; i >= 0; i--) {
            bool nextDp = true;
            for (int j = n - 1; j >= 0; j--) {
                bool res = false;
                if (i < m && s1[i] == s3[i + j] && dp[j]) {
                    res = true;
                }
                if (j < n && s2[j] == s3[i + j] && nextDp) {
                    res = true;
                }
                dp[j] = res;
                nextDp = dp[j];
            }
        }
        return dp[0];
    }

    // 7. longest increaseing path in a matrix:
    // You are given a 2-D grid of integers matrix, where each integer is greater than or equal to 0.
    // Return the length of the longest strictly increasing path within matrix.
    // From each cell within the path, you can move either horizontally or vertically. You may not move diagonally.
    class Solution {
    public:
        vector<vector<int>> directions = {{-1, 0}, {1, 0}, 
                                        {0, -1}, {0, 1}};
        vector<vector<int>> dp;

        int dfs(vector<vector<int>>& matrix, int r, int c, int prevVal) {
            int ROWS = matrix.size(), COLS = matrix[0].size();
            if (r < 0 || r >= ROWS || c < 0 || 
                c >= COLS || matrix[r][c] <= prevVal) {
                return 0;
            }
            if (dp[r][c] != -1) return dp[r][c];

            int res = 1;
            for (vector<int> d : directions) {
                res = max(res, 1 + dfs(matrix, r + d[0], 
                                c + d[1], matrix[r][c]));
            }
            dp[r][c] = res;
            return res;
        }

        int longestIncreasingPath(vector<vector<int>>& matrix) {
            int ROWS = matrix.size(), COLS = matrix[0].size();
            dp = vector<vector<int>>(ROWS, vector<int>(COLS, -1));
            int LIP = 0;

            for (int r = 0; r < ROWS; r++) {
                for (int c = 0; c < COLS; c++) {
                    LIP = max(LIP, dfs(matrix, r, c, INT_MIN));
                }
            }
            return LIP;
        }
    };

    // 8. distinct subsequences:
    // You are given two strings s and t, both consisting of english letters.
    // Return the number of distinct subsequences of s which are equal to t.
    int numDistinct(string s, string t) {
        int m = s.size(), n = t.size();
        vector<uint> dp(n + 1, 0);
        dp[n] = 1;

        for (int i = m - 1; i >= 0; i--) {
            int prev = 1;
            for (int j = n - 1; j >= 0; j--) {
                uint res = dp[j];
                if (s[i] == t[j]) {
                    res += prev;
                }

                prev = dp[j];
                dp[j] = res;
            }
        }

        return dp[0];
    }

    // 9. edit distance:
    // You are given two strings word1 and word2, each consisting of lowercase English letters.

    // You are allowed to perform three operations on word1 an unlimited number of times:

    // Insert a character at any position
    // Delete a character at any position
    // Replace a character at any position
    // Return the minimum number of operations to make word1 equal word2.
    int minDistance(string word1, string word2) {
        int m = word1.size(), n = word2.size();
        if (m < n) {
            swap(m, n);
            swap(word1, word2);
        }

        vector<int> dp(n + 1);
        for (int i = 0; i <= n; i++) dp[i] = n - i;

        for (int i = m - 1; i >= 0; i--) {
            int nextDp = dp[n];
            dp[n] = m - i;
            for (int j = n - 1; j >= 0; j--) {
                int temp = dp[j];
                if (word1[i] == word2[j]) {
                    dp[j] = nextDp;
                } else {
                    dp[j] = 1 + min({dp[j], dp[j + 1], nextDp});
                }
                nextDp = temp;
            }
        }
        return dp[0];
    }

    // 10. burst balloons:
    // You are given an array of integers nums of size n. The ith element represents a balloon with an integer value of nums[i]. You must burst all of the balloons.
    // If you burst the ith balloon, you will receive nums[i - 1] * nums[i] * nums[i + 1] coins. If i - 1 or i + 1 goes out of bounds of the array, then assume the out of bounds value is 1.
    // Return the maximum number of coins you can receive by bursting all of the balloons.
    int maxCoins(vector<int>& nums) {
        int n = nums.size();
        vector<int> newNums(n + 2, 1);
        for (int i = 0; i < n; i++) {
            newNums[i + 1] = nums[i];
        }

        vector<vector<int>> dp(n + 2, vector<int>(n + 2, 0));
        for (int l = n; l >= 1; l--) {
            for (int r = l; r <= n; r++) {
                for (int i = l; i <= r; i++) {
                    int coins = newNums[l - 1] * newNums[i] * newNums[r + 1];
                    coins += dp[l][i - 1] + dp[i + 1][r];
                    dp[l][r] = max(dp[l][r], coins);
                }
            }
        }

        return dp[1][n];
    }

    // 11. regular expression matching:
    // You are given an input string s consisting of lowercase english letters, and a pattern p consisting of lowercase english letters, as well as '.', and '*' characters.

    // Return true if the pattern matches the entire input string, otherwise return false.

    // '.' Matches any single character
    // '*' Matches zero or more of the preceding element.
    bool isMatch(string s, string p) {
        vector<bool> dp(p.length() + 1, false);
        dp[p.length()] = true;

        for (int i = s.length(); i >= 0; i--) {
            bool dp1 = dp[p.length()];
            dp[p.length()] = (i == s.length());

            for (int j = p.length() - 1; j >= 0; j--) {
                bool match = i < s.length() && 
                             (s[i] == p[j] || p[j] == '.');
                bool res = false;
                if (j + 1 < p.length() && p[j + 1] == '*') {
                    res = dp[j + 2];
                    if (match) {
                        res = res || dp[j];
                    }
                } else if (match) {
                    res = dp1;
                }
                dp1 = dp[j];
                dp[j] = res;
            }
        }

        return dp[0];
    }

private:
    // No private members
};