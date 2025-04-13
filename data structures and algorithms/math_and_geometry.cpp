
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
        // input:
        // output:
        // process: Matrix Mul or rotate from corners & shift idx once level complete shift T-B,L-R bound

        // 2. spiral matrix
        // input:
        // output:
        // process: while L>=R & T>=B: L->R; T->B; shift T; if T<B or R<L:complete; R->L; shift R; B->T

        // 3. set matrix zeros
        // input:
        // output:
        // process: track data in visted cells. from L->R and T->B: matrix[r][0]&[0][c] = matrix[r][c] if m==0

        // 4. happy number
        // input:
        // output:
        // process: base(f_ptr = 1: return true; f_ptr = s_ptr: return false) recur(f_ptr-next-next, s_ptr-next)

        // 5. plus one
        // input:
        // output:
        // process: sum ,carry= 1 + n[0];  while carry: carry= 1 if n[i]=9 else 0; sum,carry = sum+carry 

        // 6. pow(x,n)
        // input:
        // output:
        // process: base(x=0:return 0; n=0:return 1) recurr(p= dfs(x*x) return x*p if n=odd else p )

        // 7. multiply Strings
        // input:
        // output:
        // process: (x+y)(a+b): p[i1+i2] += n1[i1]*n2[i2]; p[i1+i2+1] +=p[i1]//b;  p[i1+i2]%=b then reverse(p)

        // 8. Detect squares 
        // input:
        // output:
        // process: for point p : for nodes as diag d: count += num_points[(p.x,d.y)]*num_points[(d.x,p.y)]

    private:


}