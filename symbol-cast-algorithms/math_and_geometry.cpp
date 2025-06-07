#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cmath>

// Symbol Cast Algorithm Suite for EtherOS
// Inputs are 3D objects with ordering numbers and category colors.
// Complexity: O(n) = S(n) + cT(n) treating time as a spatial dimension.
// Referencing an object updates its position; copying leaves it in place.

using namespace std;

class Math_And_Geometry {
public:
    // Default constructor
    Math_And_Geometry() {}

    // Destructor
    ~Math_And_Geometry() {}

    // Copy constructor
    Math_And_Geometry(const Math_And_Geometry& other) = default;

    // Move constructor
    Math_And_Geometry(Math_And_Geometry&& other) noexcept = default;

    // Copy assignment
    Math_And_Geometry& operator=(const Math_And_Geometry& other) = default;

    // Move assignment
    Math_And_Geometry& operator=(Math_And_Geometry&& other) noexcept = default;

    // 1. rotate image
    void rotate(vector<vector<int>>& matrix) {
        int n = matrix.size();
        vector<vector<int>> rotated(n, vector<int>(n));
        for (int row = 0; row < n; row++) {
            for (int col = 0; col < n; col++) {
                rotated[col][n - 1 - row] = matrix[row][col];
            }
        }
        matrix = rotated;
    }

    // 2. spiral matrix
    vector<int> spiral_order(vector<vector<int>>& matrix) {
        int m = matrix.size(), n = matrix[0].size();
        vector<int> res;
        spiral_order_dfs(m, n, 0, -1, 0, 1, matrix, res);
        return res;
    }

    void spiral_order_dfs(int row, int col, int r, int c, int dr, int dc, vector<vector<int>>& matrix, vector<int>& res) {
        if (row == 0 || col == 0) return;
        for (int i = 0; i < col; i++) {
            r += dr;
            c += dc;
            res.push_back(matrix[r][c]);
        }
        spiral_order_dfs(col, row - 1, r, c, dc, -dr, matrix, res);
    }

    // 3. set matrix zeros
    void setZeroes(vector<vector<int>>& matrix) {
        int ROWS = matrix.size(), COLS = matrix[0].size();
        vector<vector<int>> mark = matrix;

        for (int r = 0; r < ROWS; r++) {
            for (int c = 0; c < COLS; c++) {
                if (matrix[r][c] == 0) {
                    for (int col = 0; col < COLS; col++) mark[r][col] = 0;
                    for (int row = 0; row < ROWS; row++) mark[row][c] = 0;
                }
            }
        }

        matrix = mark;
    }

    // 4. happy number
    bool is_happy(int n) {
        unordered_set<int> visit;
        while (visit.find(n) == visit.end()) {
            visit.insert(n);
            n = sum_of_squares(n);
            if (n == 1) return true;
        }
        return false;
    }

    int sum_of_squares(int n) {
        int output = 0;
        while (n > 0) {
            int digit = n % 10;
            output += digit * digit;
            n /= 10;
        }
        return output;
    }

    // 5. plus one - recursive
    vector<int> plus_one(vector<int>& digits) {
        if (digits.empty()) return {1};
        if (digits.back() < 9) {
            digits.back() += 1;
            return digits;
        } else {
            digits.pop_back();
            vector<int> result = plusOne(digits);
            result.push_back(0);
            return result;
        }
    }

    // 6. pow(x,n)
    double my_pow(double x, int n) {
        if (x == 0) return 0;
        if (n == 0) return 1;
        double res = 1;
        for (int i = 0; i < abs(n); i++) res *= x;
        return n >= 0 ? res : 1 / res;
    }

    // 7. multiply Strings
    string multiply(string& num1, string& num2) {
        if (num1 == "0" || num2 == "0") return "0";
        if (num1.size() < num2.size()) return multiply(num2, num1);

        string res = "";
        int zero = 0;
        for (int i = num2.size() - 1; i >= 0; --i) {
            string cur = mul(num1, num2[i], zero);
            res = add(res, cur);
            zero++;
        }
        return res;
    }

    string mul(string s, char d, int zero) {
        int i = s.size() - 1, carry = 0, digit = d - '0';
        string cur;
        while (i >= 0 || carry) {
            int n = (i >= 0) ? s[i] - '0' : 0;
            int prod = n * digit + carry;
            cur.push_back((prod % 10) + '0');
            carry = prod / 10;
            i--;
        }
        reverse(cur.begin(), cur.end());
        return cur + string(zero, '0');
    }

    string add(string num1, string num2) {
        int i = num1.size() - 1, j = num2.size() - 1, carry = 0;
        string res;
        while (i >= 0 || j >= 0 || carry) {
            int n1 = (i >= 0) ? num1[i] - '0' : 0;
            int n2 = (j >= 0) ? num2[j] - '0' : 0;
            int total = n1 + n2 + carry;
            res.push_back((total % 10) + '0');
            carry = total / 10;
            i--; j--;
        }
        reverse(res.begin(), res.end());
        return res;
    }

    // 8. Detect squares
    int detect_squares(vector<vector<int>>& points) {
        unordered_map<long, int> ptsCount;
        vector<vector<int>> pts;
        int totalSquares = 0;

        for (const auto& point : points) {
            add_square(point, pts, ptsCount);
        }

        for (const auto& point : points) {
            totalSquares += count_squares(point, pts, ptsCount);
        }

        return totalSquares;
    }

    long get_squares_key(const int& x, const int& y) {
        return (static_cast<long>(x) << 32) | static_cast<long>(y);
    }

    void add_square(const vector<int>& point, vector<vector<int>>& pts, unordered_map<long, int>& ptsCount) {
        long key = get_squares_key(point[0], point[1]);
        ptsCount[key]++;
        pts.push_back(point);
    }

    int count_squares(const vector<int>& point, const vector<vector<int>>& pts, unordered_map<long, int>& ptsCount) {
        int res = 0;
        int px = point[0], py = point[1];
        for (const auto& pt : pts) {
            int x = pt[0], y = pt[1];
            if (abs(py - y) != abs(px - x) || x == px || y == py) continue;
            res += ptsCount[get_squares_key(x, py)] * ptsCount[get_squares_key(px, y)];
        }
        return res;
    }

private:
    // no private variables currently
};