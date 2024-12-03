// gcd ( A , B ) = k => gcd ( A/k , B/k) = 1 


// euleu phi ( d ) = """count""" number that <= d that gcd ( d, i ) = 1 

// we can use it to calcualte the """sum""" of i such gcd ( d , i ) == 1, i <= d ;
//  Ans = d/2 * phi(d)      ( d should be > 1 ) 

// number of integer(i) that gcd ( i , n ) = d ( d = divisor of n  && i <=n )
// means gcd ( i/ d , n /d ) = 1 
// = phi ( n / d ) ;


// Σ φ(d) = n  (sum over all divisors d of n)
--
// for ( auto &d : divisors[n] ) ans+= euleur phi ( d)
// ans = n 


// a^n % m =  a^(n % phi(m) ) % m    ( gcd ( m ,a  ) = 1 )





// phi ( prime ) = prime -1  
// phi ( prime ^ k ) = prime ^k - prime ^(k-1) 
// phi( a * b ) = phi(a) * phi(b) * gcd ( a, b )/phi(gcd(a,b)) 
// phi( a *b ) = phi(a) * phi(b) if gcd ( a ,b )= 1  




// Application :
// a^(phi(n)) % n = 1     // ( gcd ( a , n ) = 1 )
// a^(k*phi(n)) % n = 1 


// modivnerse of a = a^(phi(n) - 1 )

// -----------
// caluclate large powers :
// for example  a^(b^c) % n 
// b  , c , a <= 1e9  && gcd ( a , n) = 1 
// b^c = q.phi(n)  +r 

// a^( q.phi(n) + r ) = a^(q.phi(n)) % n * a^r % n = 1 * a^r = a^r % n 

// ==> a^(b^c) = a^(  (b^c) % phi(n) ) % n 

// n = b^c ==== generalisation ( for a big N )

// a^n % m =  a^(n % phi(m) ) % m    ( gcd ( m ,a  ) = 1 )



// Another application  greatttt applciation
// https://codeforces.com/blog/entry/122677?#comment-1088190
// Since:
// Σ φ(d) = n  (sum over all divisors d of n)

// Therefore:
// Σ φ(d) = gcd(a_i, a_j)  (sum over all divisors d of gcd(a_i, a_j))

// Explanation:
// d | gcd(a_i, a_j)  =>  d divides gcd(a_i, a_j)
// Hence, d divides both a_i and a_j.

// Rewriting:
// Σ φ(d) where d | gcd(a_i, a_j)
// = gcd(a_i, a_j)


int phi(int n) {
    int result = n;
    // we can make it more optimal 
    // store all prime factors with sieve then loop 
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0)
                n /= i;
            result -= result / i;
        }
    }
    if (n > 1)
        result -= result / n;
    return result;
}
template <typename T>
T EulerPhi(T N) {
    int PF_idx = 0, PF = primes[PF_idx];
    T ans = N;
    while (N != 1 && (PF * 1ll * PF <= N)) {
        if (N % PF == 0) ans -= ans / PF;
        while (N % PF == 0) N /= PF;
        PF = primes[++PF_idx];
    }
    if (N != 1) ans -= ans / N;
    return ans;
}

using ull = unsigned long lobng ; 
ull f[N + 1];
void phi_1_to_n(int n) {
    // phi ""count""" of x from[1 , i] such gcd ( x,i ) = 1 
    // f  ""sum"" of x from[1 , i] such gcd ( x,i ) = 1 
    // i > 1 
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; i++)
        phi[i] = i , f[i] = i; 

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i , 
                f[j] = phi[j]; 
        }
    }
    for (int i = 2; i <= N; i++) f[i] *= i, f[i] /= 2;


}