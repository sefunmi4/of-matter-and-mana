#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>
#include <cstdint>

// Symbol Cast Algorithm Suite for EtherOS
// Inputs are 3D objects with ordering numbers and category colors.
// Complexity: O(n) = S(n) + cT(n) treating time as a spatial dimension.
// Referencing an object updates its position; copying leaves it in place.

using namespace std;

class Bit_Manipulation {
public:
    // Default constructor
    Bit_Manipulation() {}

    // Destructor
    ~Bit_Manipulation() {}

    // Copy constructor
    Bit_Manipulation(const Bit_Manipulation& other) = default;

    // Move constructor
    Bit_Manipulation(Bit_Manipulation&& other) noexcept = default;

    // Copy assignment
    Bit_Manipulation& operator=(const Bit_Manipulation& other) = default;

    // Move assignment
    Bit_Manipulation& operator=(Bit_Manipulation&& other) noexcept = default;

    // 1. Single number
    int singleNumber(vector<int>& nums) {
        int result = 0;
        for (int num : nums) {
            result ^= num;  // XOR cancels out pairs
        }
        return result;
    }

    // 2. Number of 1 bits (Hamming weight)
    int number_of_one_bits(uint32_t n) {
        int count = 0;
        while (n) {
            n &= (n - 1);  // clears the least significant bit
            count++;
        }
        return count;
    }

    // 3. Counting bits
    vector<int> count_bits(int n) {
        vector<int> res(n + 1);
        for (int i = 1; i <= n; i++) {
            res[i] = res[i >> 1] + (i & 1);
        }
        return res;
    }

    // 4. Reverse bits
    uint32_t reverse_bits(uint32_t n) {
        uint32_t result = 0;
        for (int i = 0; i < 32; i++) {
            result <<= 1;
            result |= (n & 1);
            n >>= 1;
        }
        return result;
    }

    // 5. Missing number
    int missing_number(vector<int>& nums) {
        int xor_all = 0, xor_nums = 0;
        int n = nums.size();
        for (int i = 0; i <= n; i++) {
            xor_all ^= i;
        }
        for (int num : nums) {
            xor_nums ^= num;
        }
        return xor_all ^ xor_nums;
    }

    // 6. Sum of two integers without using '+' or '-'
    int getSum(int a, int b) {
        while (b != 0) {
            unsigned carry = (unsigned)(a & b) << 1;
            a = a ^ b;
            b = carry;
        }
        return a;
    }

    // 7. Reverse integer
    int reverse_integer(int x) {
        long res = 0;
        while (x != 0) {
            res = res * 10 + x % 10;
            x /= 10;
        }
        // Clamp to 32-bit int
        if (res > INT32_MAX || res < INT32_MIN) return 0;
        return (int)res;
    }

private:
    // Add internal helper functions here if needed
};