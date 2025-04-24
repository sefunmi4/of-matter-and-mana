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

private:
    // no private variables currently
};