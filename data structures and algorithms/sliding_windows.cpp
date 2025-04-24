#include <vector>
#include <string>
#include <deque>
#include <stack>
#include <unordered_map>
#include <map>
#include <algorithm>
#include <cmath>
#include <climits>

using namespace std;

class Binary_Search {
public:
    Binary_Search() {}
    ~Binary_Search() {}
    Binary_Search(const Binary_Search& other) = default;
    Binary_Search(Binary_Search&& other) noexcept = default;
    Binary_Search& operator=(const Binary_Search& other) = default;
    Binary_Search& operator=(Binary_Search&& other) noexcept = default;

    // 1. Best Time to Buy and Sell Stock
    int maxProfit(vector<int>& prices) {
        int maxProfit = 0;
        int minBuy = prices[0];

        for (int price : prices) {
            maxProfit = max(maxProfit, price - minBuy);
            minBuy = min(minBuy, price);
        }
        return maxProfit;
    }

    // 2. Longest Substring Without Repeating Characters
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> seen;
        int l = 0, maxLen = 0;

        for (int r = 0; r < s.length(); r++) {
            if (seen.count(s[r])) {
                l = max(seen[s[r]] + 1, l);
            }
            seen[s[r]] = r;
            maxLen = max(maxLen, r - l + 1);
        }
        return maxLen;
    }

    // 3. Permutation in String
    bool checkInclusion(string s1, string s2) {
        if (s1.length() > s2.length()) return false;

        vector<int> s1Count(26, 0), s2Count(26, 0);
        for (int i = 0; i < s1.length(); i++) {
            s1Count[s1[i] - 'a']++;
            s2Count[s2[i] - 'a']++;
        }

        int matches = 0;
        for (int i = 0; i < 26; i++) {
            if (s1Count[i] == s2Count[i]) matches++;
        }

        int l = 0;
        for (int r = s1.length(); r < s2.length(); r++) {
            if (matches == 26) return true;

            int inIdx = s2[r] - 'a';
            s2Count[inIdx]++;
            if (s2Count[inIdx] == s1Count[inIdx]) matches++;
            else if (s2Count[inIdx] == s1Count[inIdx] + 1) matches--;

            int outIdx = s2[l] - 'a';
            s2Count[outIdx]--;
            if (s2Count[outIdx] == s1Count[outIdx]) matches++;
            else if (s2Count[outIdx] == s1Count[outIdx] - 1) matches--;

            l++;
        }
        return matches == 26;
    }

    // 4. Longest Repeating Character Replacement
    int characterReplacement(string s, int k) {
        unordered_map<char, int> count;
        int l = 0, maxFreq = 0, res = 0;

        for (int r = 0; r < s.length(); r++) {
            count[s[r]]++;
            maxFreq = max(maxFreq, count[s[r]]);

            while ((r - l + 1) - maxFreq > k) {
                count[s[l]]--;
                l++;
            }

            res = max(res, r - l + 1);
        }
        return res;
    }

    // 5. Minimum Window Substring
    string minWindow(string s, string t) {
        if (t.empty()) return "";

        unordered_map<char, int> need, window;
        for (char c : t) need[c]++;

        int have = 0, needSize = need.size();
        int l = 0, resLen = INT_MAX;
        pair<int, int> res = {-1, -1};

        for (int r = 0; r < s.length(); r++) {
            char c = s[r];
            window[c]++;

            if (need.count(c) && window[c] == need[c]) {
                have++;
            }

            while (have == needSize) {
                if ((r - l + 1) < resLen) {
                    res = {l, r};
                    resLen = r - l + 1;
                }

                window[s[l]]--;
                if (need.count(s[l]) && window[s[l]] < need[s[l]]) {
                    have--;
                }
                l++;
            }
        }

        return resLen == INT_MAX ? "" : s.substr(res.first, resLen);
    }

    // 6. Sliding Window Maximum
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        deque<int> dq;
        vector<int> res;
        int l = 0;

        for (int r = 0; r < nums.size(); r++) {
            while (!dq.empty() && nums[dq.back()] < nums[r]) {
                dq.pop_back();
            }
            dq.push_back(r);

            if (l > dq.front()) {
                dq.pop_front();
            }

            if (r + 1 >= k) {
                res.push_back(nums[dq.front()]);
                l++;
            }
        }

        return res;
    }

private:
    // No internal data members
};