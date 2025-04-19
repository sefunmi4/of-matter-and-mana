
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
        &std::vector< std::vector <unsigned int> > rotate_image(&std::vector< std::vector <unsigned int> > matrix = std::null_ptr){
            unsigned int swap_item = 0;
            unsigned int l_bound = 0;
            unsigned int r_bound = matrix[0][0]->size()-1;
            unsigned int t_bound = 0;
            unsigned int b_bound = matrix[0]->size()-1;

            if (b_bound == r_bound) { // square or symetrically rotated poygon 
                //  while square exist (bound check)
                //      for col/corners 
                //          for number of corners/vectors 
                //              rotate corners into same shape and use temp S(1) storage
                //      move to next layer - make boundary smaller
            } else { // rectangle or non-symetrically rotated polygon
                //  while rectangle exist (bound check)
                //      for col length
                //          for number of corners/vectors 
                //              rotate corners into rotated copied shape (S(n*m) storage)
                //      move to next layer - make boundary smaller
            } 

            // TODO: since in-menory I'll need a helper function that can format tensor to given space domains space.

            return matrix_ptr;
        }

        // 2. spiral matrix
        // input: 2D Matrix
        // output: 2D Matrix
        // process: while L>=R & T>=B: L->R; T->B; shift T; if T<B or R<L:complete; R->L; shift R; B->T
        &std::vector< std::vector <int> > spiral_matrix(&std::vector< std::vector <int> > matrix){
            
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
        &bool happy_number(&unsigned int num){
            
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
        &bool pow(&unsigned int num){
            
        }

        // 7. multiply Strings
        // input: 
        // output: 
        // process: (x+y)(a+b): p[i1+i2] += n1[i1]*n2[i2]; p[i1+i2+1] +=p[i1]//b;  p[i1+i2]%=b then reverse(p)
        multiply_strings(){
            
        }

        // 8. Detect squares 
        // input:
        // output:
        // process: for point p : for nodes as diag d: count += num_points[(p.x,d.y)]*num_points[(d.x,p.y)]
        detect_squares(){
            
        }
    private:


}