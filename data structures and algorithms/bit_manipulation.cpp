
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

        // 2. number of 1 bits	
        // input:
        // output:
        // process: while n > 0: n = (n-1) & n; count++;

        // counting bits
        // input: 
        // output: 
        // process: dp[i] = 1 + dp[i - offset] if offset * 2 = i: offset = i

        // reverse bits
        // input: 
        // output: 	
        // process: l, r swap and move to center or shift left n >> i; check if bit 1 and res & bit << (31-i)

        // missing number	
        // input: 
        // output: 	
        // process: approach1:(complete_n[...] xor n[...])  approach2:(sum(complete_n[...] )-sum(n[...]))

        // sum of two integers	
        // input: 
        // output: 	
        // process: curr_sum=sum_operator(n1 xor n2); carry_bit = carry_operator(n1 & n2);

        // reverse integer	
        // input: 
        // output: 	
        // process: swap left and right bit with force ON or OFF mask shifting the index till 1/2 bits length
         
    private:


}