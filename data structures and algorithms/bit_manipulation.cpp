
class Bit_Manipulation(){
    public:
        // constructor 
        Bit_Manipulation(){

        }

        // destructor
        ~Bit_Manipulation(){
            
        }

        // copy constructor 
        Bit_Manipulation(){
            
        }

        // move constructor
        
        // copy assignment 

        // move assignment

        // 1. single number	 
        // input: 
        // output:
        // process: use XOR gate as a filter and all the duplicates will cancel
        int singleNumber(vector<int>& nums) {
            //unordered hashset of visited
            unordered_set<int> seen;

            // for all num in nums
            for (int num : nums) {
                // check if in visited 
                // on even visits the number is removed 
                // on odd visits the number is added
                if (seen.count(num)) {
                    seen.erase(num);
                } else {
                    seen.insert(num);
                }
            }
            //only number left is odd and showed up 1, or 3, ... 2n-1 time in the list 
            return *seen.begin();
        }

        // 2. number of 1 bits	
        // input:
        // output:
        // process: while n > 0: n = (n-1) & n; count++; diffrent logic below
        int  number_of_one_bits(uint32_t n) {
            int res = 0;
            for (int i = 0; i < 32; i++) {
                if ((1 << i) & n) {
                    res++;
                }
            }
            return res;
        }

        // 3. counting bits
        // input: 
        // output: 
        // process: dp[i] = 1 + dp[i - offset] if offset * 2 = i: offset = i
        vector<int> count_bits(int n) {
            vector<int> res(n + 1);
            for (int num = 1; num <= n; num++) {
                for (int i = 0; i < 32; i++) { // could do (n -1) & n too or dp
                    if (num & (1 << i)) {
                        res[num]++;
                    }
                }x
            }
            return res;
        }

        // 4. reverse bits
        // input: 
        // output: 	
        // process: l, r swap and move to center or shift left n >> i; check if bit 1 and res & bit << (31-i)
        uint32_t reverse_bits(uint32_t n) {
            string binary = "";
            for (int i = 0; i < 32; i++) {
                if (n & (1 << i)) {
                    binary += '1';
                } else {
                    binary += '0';
                }
            }
            
            uint32_t res = 0;
            for (int i = 0; i < 32; i++) {
                if (binary[31 - i] == '1') { 
                    res |= (1 << i);
                }
            }
            
            return res;
        }

        // 5. missing number	
        // input: 
        // output: 	
        // process: approach1:(complete_n[...] xor n[...])  approach2:(sum(complete_n[...] )-sum(n[...]))
        int missing_number(vector<int>& nums) {
            int n = nums.size();
            sort(nums.begin(), nums.end());
            for (int i = 0; i < n; i++) {
                if (nums[i] != i) {
                    return i;
                }
            }
            return n;
        }

        // 6. sum of two integers	
        // input: 
        // output: 	
        // process: curr_sum=sum_operator(n1 xor n2); carry_bit = carry_operator(n1 & n2); different logic below
        int getSum(int a, int b) {
            return a + b;
        }

        // 7. reverse integer	
        // input: 
        // output: 	
        // process: swap left and right bit with force ON or OFF mask shifting the index till 1/2 bits length
        void reverse_integer(vector<vector<int>>& matrix) {
            int n = matrix.size();
            vector<vector<int>> rotated(n, vector<int>(n));
      
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    rotated[j][n - 1 - i] = matrix[i][j];
                }
            }
      
            matrix = rotated;
        }
        
    private:

}