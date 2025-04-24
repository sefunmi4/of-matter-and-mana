#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

class Stack{
public:
    // Default constructor
    Stack() {}

    // Destructor
    ~Stack() {}

    // Copy constructor
    Stack(const Stack& other) = default;

    // Move constructor
    Stack(Stack&& other) noexcept = default;

    // Copy assignment
    Stack& operator=(const Stack& other) = default;

    // Move assignment
    Stack& operator=(Stack&& other) noexcept = default;

    // 1. valid_parentheses:
    // You are given a string s consisting of the following characters: '(', ')', '{', '}', '[' and ']'.
    // The input string s is valid if and only if:
    // Every open bracket is closed by the same type of close bracket.
    // Open brackets are closed in the correct order.
    // Every close bracket has a corresponding open bracket of the same type.
    // Return true if s is a valid string, and false otherwise.
    // stack.append(item) if open_[ else (pop if close_item match) else invalid
    // I want to use this solution: stack.append(item) if open_[ else (pop if close_item match) else invalid
    bool isValid(string s) {
        while (true) {
            size_t pos = string::npos;
            if ((pos = s.find("()")) != string::npos) {
                s.erase(pos, 2);
                continue;
            }
            if ((pos = s.find("{}")) != string::npos) {
                s.erase(pos, 2);
                continue;
            }
            if ((pos = s.find("[]")) != string::npos) {
                s.erase(pos, 2);
                continue;
            }
            break;
        }
        return s.empty();
    }

    // 2. min stack:
    // Design a stack class that supports the push, pop, top, and getMin operations.

    // MinStack() initializes the stack object.
    // void push(int val) pushes the element val onto the stack.
    // void pop() removes the element on the top of the stack.
    // int top() gets the top element of the stack.
    // int getMin() retrieves the minimum element in the stack.
    // Each function should run in O(1) time.
    class MinStack {
    public:
        stack<int> stk;
        MinStack() {
            
        }
        
        void push(int val) {
            stk.push(val);
        }
        
        void pop() {
            stk.pop();
        }
        
        int top() {
            return stk.top();
        }
        
        int getMin() {
            stack<int> tmp;
            int mini = stk.top();
            while (stk.size()) {
                mini = min(mini, stk.top());
                tmp.push(stk.top());
                stk.pop();
            }

            while (tmp.size()) {
                stk.push(tmp.top());
                tmp.pop();
            }

            return mini;
        }
    };

    // 3. evaluate reverse polish notation:
    // You are given an array of strings tokens that represents a valid arithmetic expression in Reverse Polish Notation.
    // Return the integer that represents the evaluation of the expression.
    // The operands may be integers or the results of other operations.
    // The operators include '+', '-', '*', and '/'.
    // Assume that division between integers always truncates toward zero.
    int evalRPN(vector<string>& tokens) {
        while (tokens.size() > 1) {
            for (int i = 0; i < tokens.size(); i++) {
                if (tokens[i] == "+" 
                    || tokens[i] == "-" 
                    || tokens[i] == "*" 
                    || tokens[i] == "/") 
                {
                    int a = stoi(tokens[i - 2]);
                    int b = stoi(tokens[i - 1]);
                    int result = 0;
                    if (tokens[i] == "+") result = a + b;
                    else if (tokens[i] == "-") result = a - b;
                    else if (tokens[i] == "*") result = a * b;
                    else if (tokens[i] == "/") result = a / b;
                    
                    tokens.erase(tokens.begin() + i - 2, tokens.begin() + i + 1);
                    tokens.insert(tokens.begin() + i - 2, to_string(result));
                    break;
                }
            }
        }
        return stoi(tokens[0]);
    }

    // 4. generate parantheses:
    // You are given an integer n. Return all well-formed parentheses strings that you can generate with n pairs of parentheses.
    class Solution {
    public:
        bool valid(const string& s) {
            int open = 0;
            for (char c : s) {
                open += (c == '(') ? 1 : -1;
                if (open < 0) return false;
            }
            return open == 0;
        }

        void dfs(string s, vector<string>& res, int n) {
            if (s.length() == 2 * n) {
                if (valid(s)) res.push_back(s);
                return;
            }
            dfs(s + '(', res, n);
            dfs(s + ')', res, n);
        }

        vector<string> generateParenthesis(int n) {
            vector<string> res;
            dfs("", res, n);
            return res;
        }
    };

    // 5. daily temperatures:
    // You are given an array of integers temperatures where temperatures[i] represents the daily temperatures on the ith day.
    // Return an array result where result[i] is the number of days after the ith day before a warmer temperature appears on a future day. If there is no day in the future where a warmer temperature will appear for the ith day, set result[i] to 0 instead.
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = temperatures.size();
        vector<int> res(n);

        for (int i = 0; i < n; i++) {
            int count = 1;
            int j = i + 1;
            while (j < n) {
                if (temperatures[j] > temperatures[i]) {
                    break;
                }
                j++;
                count++;
            }
            count = (j == n) ? 0 : count;
            res[i] = count;
        }
        return res;
    }

    // 6. car fleet:
    // There are n cars traveling to the same destination on a one-lane highway.
    // You are given two arrays of integers position and speed, both of length n.
    // position[i] is the position of the ith car (in miles)
    // speed[i] is the speed of the ith car (in miles per hour)
    // The destination is at position target miles.
    // A car can not pass another car ahead of it. It can only catch up to another car and then drive at the same speed as the car ahead of it.
    // A car fleet is a non-empty set of cars driving at the same position and same speed. A single car is also considered a car fleet.
    // If a car catches up to a car fleet the moment the fleet reaches the destination, then the car is considered to be part of the fleet.
    // Return the number of different car fleets that will arrive at the destination.
    int carFleet(int target, vector<int>& position, vector<int>& speed) {
        vector<pair<int, int>> pair;
        for (int i = 0; i < position.size(); i++) {
            pair.push_back({position[i], speed[i]});
        }
        sort(pair.rbegin(), pair.rend());
        vector<double> stack;
        for (auto& p : pair) {
            stack.push_back((double)(target - p.first) / p.second);
            if (stack.size() >= 2 && 
                stack.back() <= stack[stack.size() - 2]) 
            {
                stack.pop_back();
            }
        }
        return stack.size();
    }

    // largest rectangle in histogram:
    // You are given an array of integers heights where heights[i] represents the height of a bar. The width of each bar is 1.
    // Return the area of the largest rectangle that can be formed among the bars.
    // Note: This chart is known as a histogram.
    int largestRectangleArea(vector<int>& heights) {
        int n = heights.size();
        int maxArea = 0;

        for (int i = 0; i < n; i++) {
            int height = heights[i];

            int rightMost = i + 1;
            while (rightMost < n && heights[rightMost] >= height) {
                rightMost++;
            }

            int leftMost = i;
            while (leftMost >= 0 && heights[leftMost] >= height) {
                leftMost--;
            }

            rightMost--;
            leftMost++;
            maxArea = max(maxArea, height * (rightMost - leftMost + 1));
        }
        return maxArea;
    }

private:
    // no private variables currently
};