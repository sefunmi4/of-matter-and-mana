#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Two_Pointers {
public:
    // Constructors & assignment
    Two_Pointers() {}
    ~Two_Pointers() {}
    Two_Pointers(const Two_Pointers& other) = default;
    Two_Pointers(Two_Pointers&& other) noexcept = default;
    Two_Pointers& operator=(const Two_Pointers& other) = default;
    Two_Pointers& operator=(Two_Pointers&& other) noexcept = default;

    // 1. Valid Palindrome
    // Ignores non-alphanumeric characters and is case-insensitive.
    bool isPalindrome(string s) {
        int l = 0, r = s.length() - 1;
        while (l < r) {
            while (l < r && !isAlphaNum(s[l])) l++;
            while (r > l && !isAlphaNum(s[r])) r--;
            if (tolower(s[l]) != tolower(s[r])) return false;
            l++; r--;
        }
        return true;
    }

    // Helper to check if character is alphanumeric
    bool isAlphaNum(char c) {
        return (c >= 'A' && c <= 'Z') || 
               (c >= 'a' && c <= 'z') || 
               (c >= '0' && c <= '9');
    }

    // 2. Two Sum II (sorted input array)
    // Return 1-indexed pair of indices whose values add up to target.
    vector<int> twoSum(vector<int>& numbers, int target) {
        int l = 0, r = numbers.size() - 1;
        while (l < r) {
            int sum = numbers[l] + numbers[r];
            if (sum < target) l++;
            else if (sum > target) r--;
            else return {l + 1, r + 1};
        }
        return {};
    }

    // 3. 3Sum
    // Return all unique triplets that sum to zero.
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        vector<vector<int>> res;

        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > 0) break;
            if (i > 0 && nums[i] == nums[i - 1]) continue;

            int l = i + 1, r = nums.size() - 1;
            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];
                if (sum < 0) l++;
                else if (sum > 0) r--;
                else {
                    res.push_back({nums[i], nums[l], nums[r]});
                    l++; r--;
                    while (l < r && nums[l] == nums[l - 1]) l++;
                }
            }
        }
        return res;
    }

    // 4. Container With Most Water
    // Return the max area that can be formed by any two heights.
    int maxArea(vector<int>& heights) {
        int l = 0, r = heights.size() - 1;
        int res = 0;

        while (l < r) {
            int area = min(heights[l], heights[r]) * (r - l);
            res = max(res, area);
            if (heights[l] <= heights[r]) l++;
            else r--;
        }
        return res;
    }

    // 5. Trapping Rain Water
    // Return the total volume of water that can be trapped.
    int trap(vector<int>& height) {
        if (height.empty()) return 0;

        int l = 0, r = height.size() - 1;
        int leftMax = height[l], rightMax = height[r];
        int res = 0;

        while (l < r) {
            if (leftMax < rightMax) {
                l++;
                leftMax = max(leftMax, height[l]);
                res += leftMax - height[l];
            } else {
                r--;
                rightMax = max(rightMax, height[r]);
                res += rightMax - height[r];
            }
        }
        return res;
    }

private:
    // Internal helpers can be added here if needed in future.
};