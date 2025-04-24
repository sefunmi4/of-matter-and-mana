#include <vector>
#include <string>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Backtracking {
public:
    Backtracking() {}
    ~Backtracking() {}
    Backtracking(const Backtracking& other) = default;
    Backtracking(Backtracking&& other) noexcept = default;
    Backtracking& operator=(const Backtracking& other) = default;
    Backtracking& operator=(Backtracking&& other) noexcept = default;

    // 1. subsets
    // Given an array nums of unique integers, return all possible subsets of nums.
    // The solution set must not contain duplicate subsets. You may return the solution in any order.
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> res = {{}};
        
        for (int num : nums) {
            int size = res.size();
            for (int i = 0; i < size; i++) {
                vector<int> subset = res[i];
                subset.push_back(num);
                res.push_back(subset);
            }
        }

        return res;
    }

    // 2. combination sum:
    // You are given an array of distinct integers nums and a target integer target. Your task is to return a list of all unique combinations of nums where the chosen numbers sum to target.
    // The same number may be chosen from nums an unlimited number of times. Two combinations are the same if the frequency of each of the chosen numbers is the same, otherwise they are different.
    // You may return the combinations in any order and the order of the numbers in each combination can be in any order.
    class Solution {
    public:
        vector<vector<int>> res;
        vector<vector<int>> combinationSum(vector<int>& nums, int target) {
            sort(nums.begin(), nums.end());
            dfs(0, {}, 0, nums, target);
            return res;
        }

        void dfs(int i, vector<int> cur, int total, vector<int>& nums, int target) {
            if (total == target) {
                res.push_back(cur);
                return;
            }
            
            for (int j = i; j < nums.size(); j++) {
                if (total + nums[j] > target) {
                    return;
                }
                cur.push_back(nums[j]);
                dfs(j, cur, total + nums[j], nums, target);
                cur.pop_back();
            }
        }
    };

    // 3. permutations:
    // Given an array nums of unique integers, return all the possible permutations. You may return the answer in any order.
    class Solution {
        vector<vector<int>> res;
    public:
        vector<vector<int>> permute(vector<int>& nums) {
            backtrack(nums, 0);
            return res;
        }

        void backtrack(vector<int>& nums, int idx) {
            if (idx == nums.size()) {
                res.push_back(nums);
                return;
            }
            for (int i = idx; i < nums.size(); i++) {
                swap(nums[idx], nums[i]);
                backtrack(nums, idx + 1);
                swap(nums[idx], nums[i]);
            }
        }
    };

    // 4. subsets 2 - duplicates:
    // subsets 2 - duplicates:
    // You are given an array nums of integers, which may contain duplicates. Return all possible subsets.
    // The solution must not contain duplicate subsets. You may return the solution in any order.
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res = {{}};
        int prevIdx = 0;
        int idx = 0;

        for (int i = 0; i < nums.size(); i++) {
            idx = (i >= 1 && nums[i] == nums[i - 1]) ? prevIdx : 0;
            prevIdx = res.size();
            for (int j = idx; j < prevIdx; j++) {
                std::vector<int> tmp = res[j];
                tmp.push_back(nums[i]);
                res.push_back(tmp);
            }
        }

        return res;
    }

    // 5. combination sum 2 - duplicates:
    // You are given an array of integers candidates, which may contain duplicates, and a target integer target. Your task is to return a list of all unique combinations of candidates where the chosen numbers sum to target.
    // Each element from candidates may be chosen at most once within a combination. The solution set must not contain duplicate combinations.
    // You may return the combinations in any order and the order of the numbers in each combination can be in any order.
    class Solution {
    public:
        vector<vector<int>> res;
        vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
            res.clear();
            sort(candidates.begin(), candidates.end());
            dfs(0, {}, 0, candidates, target);
            return res;
        }

    private:
        void dfs(int idx, vector<int> path, int cur, vector<int>& candidates, int target) {
            if (cur == target) {
                res.push_back(path);
                return;
            }
            for (int i = idx; i < candidates.size(); i++) {
                if (i > idx && candidates[i] == candidates[i - 1]) {
                    continue;
                }
                if (cur + candidates[i] > target) {
                    break;
                }

                path.push_back(candidates[i]);
                dfs(i + 1, path, cur + candidates[i], candidates, target);
                path.pop_back();
            }
        }
    };

    // 6. word search:
    // Given a 2-D grid of characters board and a string word, return true if the word is present in the grid, otherwise return false.
    // For the word to be present it must be possible to form it with a path in the board with horizontally or vertically neighboring cells. The same cell may not be used more than once in a word.
    class Solution {
    public:
        int ROWS, COLS;

        bool exist(vector<vector<char>>& board, string word) {
            ROWS = board.size();
            COLS = board[0].size();

            for (int r = 0; r < ROWS; r++) {
                for (int c = 0; c < COLS; c++) {
                    if (dfs(board, word, r, c, 0)) {
                        return true;
                    }
                }
            }
            return false;
        }

        bool dfs(vector<vector<char>>& board, string word, int r, int c, int i) {
            if (i == word.size()) {
                return true;
            }
            if (r < 0 || c < 0 || r >= ROWS || c >= COLS || 
                board[r][c] != word[i] || board[r][c] == '#') {
                return false;
            }

            board[r][c] = '#';
            bool res = dfs(board, word, r + 1, c, i + 1) ||
                    dfs(board, word, r - 1, c, i + 1) ||
                    dfs(board, word, r, c + 1, i + 1) ||
                    dfs(board, word, r, c - 1, i + 1);
            board[r][c] = word[i];
            return res;
        }
    };

    // 7. palilndrome partining:
    // Given a string s, split s into substrings where every substring is a palindrome. Return all possible lists of palindromic substrings.
    // You may return the solution in any order.
    class Solution {
        vector<vector<bool>> dp;
    public:
        vector<vector<string>> partition(string s) {
            int n = s.length();
            dp.resize(n, vector<bool>(n));
            for (int l = 1; l <= n; l++) {
                for (int i = 0; i <= n - l; i++) {
                    dp[i][i + l - 1] = (s[i] == s[i + l - 1] && 
                                        (i + 1 > (i + l - 2) || 
                                        dp[i + 1][i + l - 2]));
                }
            }

            vector<vector<string>> res;
            vector<string> part;
            dfs(0, s, part, res);
            return res;
        }

    private:
        void dfs(int i, const string& s, vector<string>& part, vector<vector<string>>& res) {
            if (i >= s.length()) {
                res.push_back(part);
                return;
            }
            for (int j = i; j < s.length(); j++) {
                if (dp[i][j]) {
                    part.push_back(s.substr(i, j - i + 1));
                    dfs(j + 1, s, part, res);
                    part.pop_back();
                }
            }
        }
    };

    // 8. combinations of a phone number:
    // You are given a string digits made up of digits from 2 through 9 inclusive.

    // Each digit (not including 1) is mapped to a set of characters as shown below:

    // A digit could represent any one of the characters it maps to.

    // Return all possible letter combinations that digits could represent. You may return the answer in any order.
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        
        vector<string> res = {""};
        vector<string> digitToChar = {
            "", "", "abc", "def", "ghi", "jkl",
            "mno", "qprs", "tuv", "wxyz"
        };

        for (char digit : digits) {
            vector<string> tmp;
            for (string &curStr : res) {
                for (char c : digitToChar[digit - '0']) {
                    tmp.push_back(curStr + c);
                }
            }
            res = tmp;
        }
        return res;
    }

    // 9. n Queens:
    // The n-queens puzzle is the problem of placing n queens on an n x n chessboard so that no two queens can attack each other.
    // A queen in a chessboard can attack horizontally, vertically, and diagonally.
    // Given an integer n, return all distinct solutions to the n-queens puzzle.
    // Each solution contains a unique board layout where the queen pieces are placed. 'Q' indicates a queen and '.' indicates an empty space.
    // You may return the answer in any order.
    class Solution {
    public:
        unordered_set<int> col;
        unordered_set<int> posDiag;
        unordered_set<int> negDiag;
        vector<vector<string>> res;

        vector<vector<string>> solveNQueens(int n) {
            vector<string> board(n, string(n, '.'));

            backtrack(0, n, board);
            return res;
        }

    private:
        void backtrack(int r, int n, vector<string>& board) {
            if (r == n) {
                res.push_back(board);
                return;
            }

            for (int c = 0; c < n; c++) {
                if (col.count(c) || posDiag.count(r + c) || 
                    negDiag.count(r - c)) {
                    continue;
                }

                col.insert(c);
                posDiag.insert(r + c);
                negDiag.insert(r - c);
                board[r][c] = 'Q';

                backtrack(r + 1, n, board);

                col.erase(c);
                posDiag.erase(r + c);
                negDiag.erase(r - c);
                board[r][c] = '.';
            }
        }
    };
private:
    // No internal members yet
};