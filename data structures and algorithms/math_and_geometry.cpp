
class Math_And_Geometry(){
    public:
        // constructor 
        Math_And_Geometry(){

        }

        // destructor
        ~Math_And_Geometry(){
            
        }

        // copy constructor 
        Math_And_Geometry(){
            
        }

        // move constructor

        
        // copy assignment 


        // move assignment


        // 1. rotate image
        // input: 2D Matrix
        // output: 2D Matrix
        // process: Matrix Mul or rotate from corners & shift idx once level complete shift T-B,L-R bound
        // notes: if its a rectangle will need to copy shape to account for length and width will assume is square
        void rotate(vector<vector<int>>& matrix) {
            // let n = size of matrix row
            int n = matrix.size();
            // make result vector to copy to
            vector<vector<int>> rotated(n, vector<int>(n));
    
            // for row in rows: for col in cols
            for (int row = 0; row < n; row++) {
                for (int col = 0; col < n; col++) {
                    // linear algebra translation - kernel index
                    // [ 0  1 ]
                    // [-1  0 ]
                    // [x'] = 0*x + 1*y =  y
                    // [y'] =  (n-1)+ -1*x + 0*y = (n-1)-x
                    rotated[col][n - 1 - row] = matrix[row][col];
                }
            }
    
            matrix = rotated;
        }

        // 2. spiral matrix
        // input: 2D Matrix
        // output: 2D Matrix
        // process: while L>=R & T>=B: L->R; T->B; shift T; if T<B or R<L:complete; R->L; shift R; B->T
        vector<int> spiral_order(vector<vector<int>>& matrix) {
            int m = matrix.size(), n = matrix[0].size();
            vector<int> res;
    
            // append all the elements in the given direction
            spiral_order_depth_fist_search(m, n, 0, -1, 0, 1, matrix, res);
            return res;
        }
    
        void spiral_order_dfs(
            int row, int col, 
            int r, int c, 
            int dr, int dc, 
            vector<vector<int>>& matrix, vector<int>& res
        ) {
            if (row == 0 || col == 0) return; //basecase
            
            // recurrent case
            for (int i = 0; i < col; i++) { 
                r += dr;
                c += dc;
                res.push_back(matrix[r][c]);
            }
    
            // sub-problem
            dfs(col, row - 1, r, c, dc, -dr, matrix, res);
        }

        
        // 3. set matrix zeros
        // input: 2D Matrix
        // output: 2D Matrix
        // process: track data in visted cells. from L->R and T->B: matrix[r][0]&[0][c] = matrix[r][c] if m==0
        &std::vector< std::vector <int> > set_matrix_zeros(&std::vector< std::vector <int> > matrix){
            
        }

        // 4. happy number
        // input: unsigned_int
        // output: bool
        // process: base(f_ptr = 1: return true; f_ptr = s_ptr: return false) recur(f_ptr-next-next, s_ptr-next)
        bool is_happy(int n) {
            unordered_set<int> visit;
    
            while (visit.find(n) == visit.end()) {
                visit.insert(n);
                n = sum_of_squares(n);
                if (n == 1) {
                    return true;
                }
            }
            return false;
        }
        int sum_of_squares(int n) {
            int output = 0;
    
            while (n > 0) {
                int digit = n % 10;
                digit = digit * digit;
                output += digit;
                n /= 10;
            }
            return output;
        }

        // 5. plus one - recurive
        // input: int sum , int carry
        // output: int result
        // process: sum ,carry= 1 + n[0];  while carry: carry= 1 if n[i]=9 else 0; sum,carry = sum+carry 
        &unsigned int plus_one(&unsigned int sum , &unsigned int carry){
            
        }

        // 6. pow(x,n)
        // input: bool
        // output: unsigned int
        // process: base(x=0:return 0; n=0:return 1) recurr(p= dfs(x*x) return x*p if n=odd else p )
        double myPow(double x, int n) {
            if (x == 0) {
                return 0;
            }
            if (n == 0) {
                return 1;
            }
            double res = 1;
            for (const auto& i = 0; i < abs(n); i++) {
                res *= x;
            }
            return n >= 0 ? res : 1 / res;
        }

        // 7. multiply Strings
        // input: 
        // output: 
        // process: (x+y)(a+b): p[i1+i2] += n1[i1]*n2[i2]; p[i1+i2+1] +=p[i1]//b;  p[i1+i2]%=b then reverse(p)
        string multiply(string& num1, string& num2) {
            if (num1 == "0" || num2 == "0") return "0";
            
            if (num1.size() < num2.size()) {
                return multiply(num2, num1);
            }
            
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
            int i = s.size() - 1, carry = 0;
            int digit = d - '0';
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
                i--;
                j--;
            }
            
            reverse(res.begin(), res.end());
            return res;
        }

        // 8. Detect squares 
        // input:
        // output:
        // process: for point p : for nodes as diag d: count += num_points[(p.x,d.y)]*num_points[(d.x,p.y)]
        unordered_map<long, int> detect_squares(vector<vector<int>>& points){
            unordered_map<long, int> ptsCount;
            vector<vector<int>> pts;

            for (const auto& point : points) {
                add_square(point, pts, ptsCount);
            }

            for (const auto& point : points) {
                squares_per_point = count_squares(point, pts, ptsCount);
            }

            return ptsCount;
        }

        long get_squares_key(const int& x, const int& y) {
            return (static_cast<long>(x) << 32) | static_cast<long>(y);
        }

        void add_square(const vector<int>& point, vector<vector<int>>& pts, unordered_map<long, int>& ptsCount) {
            long key = get_squares_key(point[0], point[1]);
            ptsCount[key]++; 
            pts.push_back(point); 
        }
                
        int count_squares(const vector<int>& point,const vector<vector<int>>& pts, unordered_map<long, int>& ptsCount) {
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


}