#include <vector>
#include <string>
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

    // 1. Binary Search (Recursive)
    // Return the index of the target in a sorted array, or -1 if not found.
    int binary_search(int l, int r, vector<int>& nums, int target) {
        if (l > r) return -1;
        int m = l + (r - l) / 2;
        if (nums[m] == target) return m;
        return (nums[m] < target)
            ? binary_search(m + 1, r, nums, target)
            : binary_search(l, m - 1, nums, target);
    }

    int search(vector<int>& nums, int target) {
        return binary_search(0, nums.size() - 1, nums, target);
    }

    // 2. Search a 2D Matrix (Flattened binary search)
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int rows = matrix.size(), cols = matrix[0].size();
        int l = 0, r = rows * cols - 1;

        while (l <= r) {
            int m = l + (r - l) / 2;
            int val = matrix[m / cols][m % cols];
            if (val == target) return true;
            else if (val < target) l = m + 1;
            else r = m - 1;
        }
        return false;
    }

    // 3. Koko Eating Bananas
    int minEatingSpeed(vector<int>& piles, int h) {
        int l = 1, r = *max_element(piles.begin(), piles.end());
        int res = r;

        while (l <= r) {
            int k = (l + r) / 2;
            long long totalHours = 0;

            for (int p : piles) {
                totalHours += ceil((double)p / k);
            }

            if (totalHours <= h) {
                res = k;
                r = k - 1;
            } else {
                l = k + 1;
            }
        }
        return res;
    }

    // 4. Find Minimum in Rotated Sorted Array
    int findMin(vector<int>& nums) {
        int l = 0, r = nums.size() - 1;
        while (l < r) {
            int m = l + (r - l) / 2;
            if (nums[m] < nums[r]) r = m;
            else l = m + 1;
        }
        return nums[l];
    }

    // 5. Time-Based Key-Value Store
    class TimeMap {
    public:
        unordered_map<string, map<int, string>> store;

        TimeMap() {}

        void set(string key, string value, int timestamp) {
            store[key][timestamp] = value;
        }

        string get(string key, int timestamp) {
            auto it = store[key].upper_bound(timestamp);
            if (it == store[key].begin()) return "";
            return prev(it)->second;
        }
    };

    // 6. Median of Two Sorted Arrays
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int>& A = nums1;
        vector<int>& B = nums2;

        if (A.size() > B.size()) swap(A, B);

        int total = A.size() + B.size();
        int half = (total + 1) / 2;

        int l = 0, r = A.size();
        while (l <= r) {
            int i = (l + r) / 2;
            int j = half - i;

            int Aleft = (i == 0) ? INT_MIN : A[i - 1];
            int Aright = (i == A.size()) ? INT_MAX : A[i];
            int Bleft = (j == 0) ? INT_MIN : B[j - 1];
            int Bright = (j == B.size()) ? INT_MAX : B[j];

            if (Aleft <= Bright && Bleft <= Aright) {
                if (total % 2 == 1) return max(Aleft, Bleft);
                return (max(Aleft, Bleft) + min(Aright, Bright)) / 2.0;
            } else if (Aleft > Bright) {
                r = i - 1;
            } else {
                l = i + 1;
            }
        }

        return -1.0; // unreachable
    }

private:
    // No internal data members
};