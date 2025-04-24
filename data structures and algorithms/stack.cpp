#include <vector>
#include <string>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Stack {
public:
    Stack() {}
    ~Stack() {}
    Stack(const Stack& other) = default;
    Stack(Stack&& other) noexcept = default;
    Stack& operator=(const Stack& other) = default;
    Stack& operator=(Stack&& other) noexcept = default;

    // 1. Valid Parentheses
    bool isValid(string s) {
        stack<char> stk;
        unordered_map<char, char> match = {{')','('}, {']','['}, {'}','{'}};
        for (char c : s) {
            if (match.count(c)) {
                if (stk.empty() || stk.top() != match[c]) return false;
                stk.pop();
            } else {
                stk.push(c);
            }
        }
        return stk.empty();
    }

    // 2. Min Stack
    class MinStack {
    private:
        stack<int> mainStack;
        stack<int> minStack;
    public:
        MinStack() {}

        void push(int val) {
            mainStack.push(val);
            if (minStack.empty() || val <= minStack.top()) {
                minStack.push(val);
            }
        }

        void pop() {
            if (mainStack.top() == minStack.top()) {
                minStack.pop();
            }
            mainStack.pop();
        }

        int top() {
            return mainStack.top();
        }

        int getMin() {
            return minStack.top();
        }
    };

    // 3. Evaluate Reverse Polish Notation
    int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        for (const string& token : tokens) {
            if (token == "+" || token == "-" || token == "*" || token == "/") {
                int b = stk.top(); stk.pop();
                int a = stk.top(); stk.pop();
                if (token == "+") stk.push(a + b);
                else if (token == "-") stk.push(a - b);
                else if (token == "*") stk.push(a * b);
                else if (token == "/") stk.push(a / b);
            } else {
                stk.push(stoi(token));
            }
        }
        return stk.top();
    }

    // 4. Generate Parentheses
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        generateParenthesisDFS("", 0, 0, n, res);
        return res;
    }

    void generateParenthesisDFS(string s, int open, int close, int n, vector<string>& res) {
        if (s.length() == 2 * n) {
            res.push_back(s);
            return;
        }
        if (open < n) generateParenthesisDFS(s + "(", open + 1, close, n, res);
        if (close < open) generateParenthesisDFS(s + ")", open, close + 1, n, res);
    }

    // 5. Daily Temperatures (Optimized using monotonic stack)
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> res(n, 0);
        stack<int> stk;

        for (int i = 0; i < n; ++i) {
            while (!stk.empty() && temperatures[i] > temperatures[stk.top()]) {
                int idx = stk.top(); stk.pop();
                res[idx] = i - idx;
            }
            stk.push(i);
        }
        return res;
    }

    // 6. Car Fleet
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        vector<pair<int, int>> car_data;
        for (int i = 0; i < position.size(); i++) {
            car_data.push_back({position[i], speed[i]});
        }
        sort(car_data.rbegin(), car_data.rend());

        vector<double> fleets;
        for (auto& [pos, spd] : car_data) {
            double time = (double)(target - pos) / spd;
            if (fleets.empty() || time > fleets.back()) {
                fleets.push_back(time);
            }
        }
        return fleets.size();
    }

    // 7. Largest Rectangle in Histogram
    int largestRectangleArea(vector<int>& heights) {
        stack<int> stk;
        heights.push_back(0); // Sentinel
        int maxArea = 0;

        for (int i = 0; i < heights.size(); ++i) {
            while (!stk.empty() && heights[i] < heights[stk.top()]) {
                int h = heights[stk.top()]; stk.pop();
                int w = stk.empty() ? i : i - stk.top() - 1;
                maxArea = max(maxArea, h * w);
            }
            stk.push(i);
        }
        return maxArea;
    }

private:
    // No internal members yet
};