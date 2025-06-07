#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <queue>

// Symbol Cast Algorithm Suite for EtherOS
// Inputs are 3D objects with ordering numbers and category colors.
// Complexity: O(n) = S(n) + cT(n) treating time as a spatial dimension.
// Referencing an object updates its position; copying leaves it in place.

using namespace std;

class Arrays_And_Hashing {
public:
    // Constructors & Assignment
    Arrays_And_Hashing() {}
    ~Arrays_And_Hashing() {}
    Arrays_And_Hashing(const Arrays_And_Hashing& other) = default;
    Arrays_And_Hashing(Arrays_And_Hashing&& other) noexcept = default;
    Arrays_And_Hashing& operator=(const Arrays_And_Hashing& other) = default;
    Arrays_And_Hashing& operator=(Arrays_And_Hashing&& other) noexcept = default;

    // 1. Contains Duplicates
    bool has_duplicate(vector<int>& nums) {
        unordered_set<int> seen;
        for (int num : nums) {
            if (seen.count(num)) return true;
            seen.insert(num);
        }
        return false;
    }

    // 2. Valid Anagram
    bool isAnagram(string s, string t) {
        if (s.length() != t.length()) return false;
        unordered_map<char, int> count;
        for (char c : s) count[c]++;
        for (char c : t) {
            if (--count[c] < 0) return false;
        }
        return true;
    }

    // 3. Two Sum
    vector<int> two_sum(vector<int>& nums, int target) {
        unordered_map<int, int> map;
        for (int i = 0; i < nums.size(); i++) {
            int diff = target - nums[i];
            if (map.count(diff)) return {map[diff], i};
            map[nums[i]] = i;
        }
        return {};
    }

    // 4. Group Anagrams
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> map;
        for (string s : strs) {
            string key = s;
            sort(key.begin(), key.end());
            map[key].push_back(s);
        }
        vector<vector<string>> res;
        for (auto& [_, group] : map) {
            res.push_back(group);
        }
        return res;
    }

    // 5. Top K Frequent Elements
    vector<int> topKFrequent(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        for (int num : nums) freq[num]++;
        priority_queue<pair<int, int>> pq;
        for (auto& [num, count] : freq) {
            pq.push({count, num});
        }
        vector<int> res;
        while (k--) {
            res.push_back(pq.top().second);
            pq.pop();
        }
        return res;
    }

    // 6. Encode & Decode Strings
    string encode(vector<string>& strs) {
        string encoded = "";
        for (string& s : strs) {
            encoded += to_string(s.size()) + "#" + s;
        }
        return encoded;
    }

    vector<string> decode(string s) {
        vector<string> res;
        int i = 0;
        while (i < s.size()) {
            int j = i;
            while (s[j] != '#') j++;
            int len = stoi(s.substr(i, j - i));
            res.push_back(s.substr(j + 1, len));
            i = j + 1 + len;
        }
        return res;
    }

    // 7. Product of Array Except Self
    vector<int> productExceptSelf(vector<int>& nums) {
        int n = nums.size();
        vector<int> res(n, 1);

        int left = 1;
        for (int i = 0; i < n; i++) {
            res[i] = left;
            left *= nums[i];
        }

        int right = 1;
        for (int i = n - 1; i >= 0; i--) {
            res[i] *= right;
            right *= nums[i];
        }

        return res;
    }

    // 8. Valid Sudoku
    bool isValidSudoku(vector<vector<char>>& board) {
        unordered_set<string> seen;

        for (int r = 0; r < 9; r++) {
            for (int c = 0; c < 9; c++) {
                char val = board[r][c];
                if (val == '.') continue;
                string rowKey = string(1, val) + " in row " + to_string(r);
                string colKey = string(1, val) + " in col " + to_string(c);
                string boxKey = string(1, val) + " in box " + to_string(r/3) + "-" + to_string(c/3);
                if (seen.count(rowKey) || seen.count(colKey) || seen.count(boxKey)) return false;
                seen.insert(rowKey);
                seen.insert(colKey);
                seen.insert(boxKey);
            }
        }
        return true;
    }

    // 9. Longest Consecutive Sequence
    int longestConsecutive(vector<int>& nums) {
        unordered_set<int> numSet(nums.begin(), nums.end());
        int maxLen = 0;

        for (int num : nums) {
            if (!numSet.count(num - 1)) {
                int currentNum = num;
                int streak = 1;

                while (numSet.count(currentNum + 1)) {
                    currentNum++;
                    streak++;
                }

                maxLen = max(maxLen, streak);
            }
        }

        return maxLen;
    }

private:
    // internal helpers if needed later
};