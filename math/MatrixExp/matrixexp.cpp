/*
Requirement 
    * SPACE EFFICIENT DP      size of DPTABLE ( <200 generally )
        if u can build it forward generaly we can transform to matrix 

        forward means , for exp if we asked for ( k-th answer ) 
        we will start by 0-th answer and keep incremiting till reach K-th (important!)

        but when we will convert to matrix we will start from k-th till base case ( 0 ) 

  

    when we do it 
    - suppose we have Transition ( reccurence ) and Repeats K times ( k <= 1e18)
        we can first impliment it using DP then 
        speed it up using matrix exp 
        
        we know our base cases 

        we can move from f(n) to f(n+k)  by power it ^k     
*/

const int mod = 1e9 + 7 ; 
struct Matrix {
        int n, m;
        vector <vector <int>> mat;
        Matrix() {}
        Matrix(int _n, int _m) {
                n = _n, m = _m;
                mat = vector <vector <int>> (n, vector <int> (m));
        }
        Matrix(vector< vector<int> > v) { n = (int)v.size(); m = n ? (int)v[0].size() : 0; mat = v; }
        void print() {
                for(int i = 0; i < n; i++) 
                        for(int j = 0; j < m; j++) 
                                cout << mat[i][j ]<< " \n" [j == m-1]; 
        }
        inline Matrix operator * ( const Matrix & b ){
            int r1= m , c1 = n ; 
            int r2= b.m , c2 = b.n ; 
            Matrix res(c1 , r2 ); 
            for ( int i = 0 ; i < c1 ; i++ ){
                for  (int k = 0 ; k <r2 ; k++ ){
                    for ( int j = 0 ; j < r1 ; j++ ) {
                        // multiply and 
                        res.mat[i][k] +=(mat[i][j] * b.mat[j][k]) % mod; 
                        res.mat[i][k] %= mod ; 


                         // Dif merge 
                        // res.mat[i][k]  =  min ( res.mat[i][k] , mat[i][j] +  b.mat[j][k] )  ; 
                    }
                }
            }
            return res ; 
        }
        inline Matrix operator + (const Matrix &b) {
            assert(n == b.n && m == b.m);
            Matrix ans = Matrix(n, m);
            for(int i = 0; i < n; i++) 
                for(int j = 0; j < m; j++) 
                    ans.mat[i][j] = (mat[i][j] + b.mat[i][j]) % mod;
                    // if - subtraction   
                    // ans.mat[i][j] = (mat[i][j] - b.mat[i][j + mod ]) % mod;
                    
            return ans;
        } 
        inline Matrix operator ^ ( int e  ){
                assert( n == m ); 
                Matrix unit ( n ,n );  
                Matrix Rs = mat; 
                for ( int i = 0 ; i < n ; i++ )
                    unit.mat[i][i] = 1 ; 


                // for mins ! 
                // for ( int i = 0 ; i < n ; i++ )
                //     unit.mat[i][i] = 0 ; 
                
                while ( e ){
                    if ( e& 1 ) unit = unit * Rs   ;  
                    Rs = Rs * Rs   ; 
                    e >>= 1 ; // e/= 2 
                }
                return unit ; 
        }
};
/*



    how to get ans : 
            either Exp^(B) * ( Base cases ) 

            or Exp ^ (B)
                then loop and multiply by ur base cases case by case!
                remember ( dont think if coeficient = 0 , u dont need to multiply by base case )
                always multiply

    -------------------------------------
    Transform To Dp with prev and current 
    then easy to do Matrix expo !

    -- -----------------------------------------------
    always prefer the  build of matrix like this !

            prev dp[n-1] , prev dp[n-2] .... 
    ________
    dp[n]
    dp[n-1]


    ---------------------------


    after generating the the final matrix  
        * we will multiply by the base cases ( the first version of  prevdp !! ) 

        => we will apply to it the normal transition of our dp
            ( codes almost stays the same ! )
            https://codeforces.com/gym/102644/problem/D 

    
    -----------------------------------
    GOOD EXAMPLE COVERING ALL 
        
        * how to get ans with prevdp
        * transform dp into matirx
        * how to deal with constant and powers 
           for exp (i)^2 = (i-1)^2 + 2*i - 1 
           we will add a function g (i) = i^2 , g(i) = g(i-1) + 2 * i - 1 
    
        https://ideone.com/6Ya1iM
        https://codeforces.com/gym/102644/problem/G

    

    hints K up to 1e9 , n up to 200 , complexity  n ^ 3 * log(k)

    // we can speed up the n^3 by precaulcating it !  


    Tricks : 

      
        speed up The binary repsentation by Precalcualtion : 
                    divide it into Binary
                    https://codeforces.com/gym/102644/problem/I

        count at most K !! 
                
                * if we want to calcualte path with  At most K lenght : 
                    we will consider first Calculate exactly K , 
                        then Add a new fucntion reccurence that will calcualte the sum 
                        of fonction( K )

                * since always we represent F (n) = F(n-1) 
                sometimes we shift it by one F(n+1) = F(n) , bcz we need the value
                    of F(n) to be included in Reccurence that will sum all the functions

                this problem coverted the 2 tricks fo9 https://codeforces.com/gym/102644/problem/E
                        https://www.youtube.com/watch?v=HcEHmcQDQe0&list=PLc02D4EoVYQDgO3L6boSJjcKwahRa4iGY&index=2&pp=iAQB



*/