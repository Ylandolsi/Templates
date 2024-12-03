
const int mod = 1e9 + 7 ; 
template<int mod>
struct Mint {
    int e; 
    Mint(int e_ = 0) : e(e_) {
        e= (-mod <= e&& e< 2*mod) ? e: e% mod;
        if (e< 0) e+= mod;
        if (e>=mod ) e-= mod;
    }
    Mint operator+(const Mint& b) const {
        return Mint( e + b.e ) ;
    }

    Mint operator-(const Mint& b) const {
        return Mint( e - b.e );
    }

    Mint operator*(const Mint& b) const {
        return Mint(e * b.e);
    }
    
    Mint pow(int b) const {
        Mint res(1), a = e ;
        while (b) {
            if (b & 1) res = res * a;
            a = a * a ;
            b >>= 1;
        }
        return res;
    }
    Mint inv() const {return pow(mod-2);}
    Mint operator/(const Mint& b) const {
        return Mint(Mint(e) * b.inv());
    }
};
using mint=  Mint<mod>  ;
struct Binomial{
    int n; 
    vector<mint> facts, finvs, invs;
    Binomial(int _n): n(_n), facts(_n), finvs(_n), invs(_n){
        facts[0] = finvs[0] = 1;
        invs[1] = 1;
        for (int i = 2; i < n; i++) invs[i] =  invs[mod % i] * (-mod / i);
        for(int i = 1; i < n; i++){
            facts[i] = facts[i - 1] * i;
            finvs[i] = finvs[i - 1] * invs[i];
        }
    }
    inline mint fact(int n) { return facts[n]; }
    inline mint finv(int n) { return finvs[n]; }
    inline mint inv(int n) { return invs[n]; }
    inline mint ncr(int n, int k) { 
        if (  n < k or k < 0) return 0 ; 
        return facts[n] * finvs[k] * finvs[n-k]; 
    }
    inline mint perm(int n, int r) const {
        if (n < 0 || r < 0 || n < r) return 0;
        return facts[n] * finvs[n - r];
    }
    // returns nCr modulo mod where mod is a prime
    // Complexity: log(n)
    inline mint lucas(int n, int r) {
        if (r > n) return 0;
        if (n < mod) return ncr(n, r);
        return lucas(n / mod, r / mod) * lucas(n % mod, r % mod);
    }
    inline mint catalan ( int n ){
        if ( n <= 1 ) return 1 ;
        return ncr ( 2*n , n )* finvs[n+1]; 
    } 
    //  k is Size of array , n sum u want to distribute  
    mint stars_and_bars(int n, int k) {
        //The number of ways to put n identical objects into k labeled boxes is
        // x1 + x2 +x3 +x4 + ... + xk = n ( xi >= 0 )
        return ncr(n + k - 1, k -1 );
    }
    mint stars_and_bars_2(int n, int k){
        //The number of ways to have x1 + x2 + .. + xk = n , xi > 0 
        return ncr(n -1, k-1);
    }

    // k is size of array & n is prodcut 
    mint stars_and_bars_FOIS ( int n , int k ){
        // https://codeforces.com/contest/893/problem/E
        //  take every prime divisor i of x and distribute cnti
        // x1 * x2 * x3 * x4 *... * xk = n ! 
        // auto prm = primefactrize_sieve(n);
        // mint ans = 1 ;
        // for ( auto&[prime,occPrime]:prm){
            // ans = ans* stars_and_bars(occPrime, k )  ;
        // }
    }
    /*
        stars and bars with xi >= Z 
        x1 + x2 + x3 +..xk = n 
        xi' = xi - Z
        (x1'+Z) + ( x2' + Z ) + ... = n 
        x1' + x2' + .. xk' = n - z*k 


        stars and bars with xi >= a[i]
        x1 + x2 + x3 +..xk = n 
        xi' = xi - a[i]
        (x1'+a1) + ( x2' + a2 ) + ...+(xk' + ak ) = n 
        x1' + x2' + .. xk' = n -  a1 - a2 - .... - ak 


        then apply stars and bars ( x >=0 )
    */
    mint stirling2(int n, int k) // Number of ways to partition n elements into k non-empty sets
    {
        mint res = 0;
        for (int i = 0; i <= k; i++)
        {
            mint x = ncr(k, i) * ((mint)-1).pow( k - i)  * ((mint)-1).pow( n ) ;
            if ((k - i) & 1)
                res = (res - x) ;
            else
                res = (res + x) ;
        }
        return res * finvs[k] ;
    }
    mint bell(int n) // Number of ways to partition n elements into any number of non-empty sets
    {
        mint res = 0;
        for (int i = 0; i <= n; i++)
        {
            mint x = ncr(n, i) * bell(n - i);
            if (i & 1)
                res = res - x ;
            else
                res = res + x;
        }
        return res;
    }
    mint derangement(int n) // Number of permutations of n elements such that no element appears in its original position
    {
        mint res = 0;
        for (int i = 0; i <= n; i++)
        {
            mint x = ncr(n, i) * ((mint)-1).pow( n - i);
            if (i & 1)
                res = res - x;
            else
                res = res + x;
        }
        return res;
    }
};
// ncr ( n , k) == ncr ( n , n - k ) : its like choose subset of size K == choose the reste ! 
// npr ( n , k) = ncr ( n , k ) * k!  ( order matters ! )


// 1 2 2 4 , permuation with repition = 4!/2!
// /2! car exist occurence of 2 = 2 
const int N = 1e4  ; 
Binomial C(N); 


// if we need cnk % ( not prime !! )
            C.resize(maxn + 1, vector<mint>(maxn + 1));
            C[0][0] = 1 ; 
            for ( int n= 1 ; n<= maxn ; n++ ){
                C[n][0] = C[n][n] = 1 ; 
                for ( int k =1 ; k < n ; k++ ){
                    C[n][k] = C[n-1][k-1] + C[n-1][k]; 
                }
            }

// Catalan numbers up to C_9
// C_0 = 1
// C_1 = 1
// C_2 = 2
// C_3 = 5
// C_4 = 14
// C_5 = 42
// C_6 = 132
// C_7 = 429
// C_8 = 1430
// C_9 = 4862

// cataln (n) = *      for ( i = 0 ; i< n ;i++ ) sm+= c(i)*c(n-1-i)     for n >= 2  
//              *      1/(n+1) * choose  ( n , from (2n ))
const int MAX =  0 ;
int catalan[MAX];
void init() {
    catalan[0] = catalan[1] = 1;
    for (int i=2; i<=MAX -1 ; i++) {
        catalan[i] = 0;
        for (int j=0; j < i; j++) {
            catalan[i] += (catalan[j] * catalan[i-j-1]) % MOD;
            if (catalan[i] >= MOD) {
                catalan[i] -= MOD;
            }
        }
    }
}







// wtihout modulo inverse // we use modinverse only when mod is prime 
int binomcoef(int x, int r) {
        if (x < r || x < 0 || r < 0) 
                return 0;
        if (r == 0 || r == x) 
                return 1;
        int result = 1;
        for (int i = 1; i <= r; ++i) {
                result *= (x - i + 1);
                result /= i;
        }
        return result;
}