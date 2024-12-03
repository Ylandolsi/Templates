/*
Goldbach’s conjecture: Each even integer n > 2 can be represented as a
sum n = a+b so that both a and b are primes.
 
Twin prime conjecture: There is an infinite number of pairs of the form
{p, p+2}, where both p and p+2 are primes.
 
Legendre’s conjecture: There is always a prime between numbers pow(n , 2)
and pow(n+1 , 2), where n is any positive integer.
*/

// number of number that divides N from (1 , to  n ) 
// N % d == 0       = N/d 
// divides e & z ==> N/( e * z )       generaly used in inclusion excl 



// If a ≡ b (mod n) and c ≡ d (mod n),
// then: ac ≡ bd (mod n)
// then: a+c ≡ (b+d)%n  (mod n)

// sqrt(n) number that <= n that can be written as squre 

// lcm ( x , kx  ) =  kx  

// any number who have a divisor <= sqrt(n) && != 1 
// --> is not a prime a number ! 

// A^(c+d) = A^ c * A^d 


// gcd( A , B ) = minimum positive value such g = Ax + By
// gcd (A ,B ) = gcd ( A , B + x*A ) = gcd ( A%B , B ) 

// gcd ( A , B ) = k => gcd ( A/k , B/k) = 1 , cause K = all prime factors in coefcient commun 


/*
        The prefix gcd can only change 𝑂(𝑙𝑜𝑔(𝑚))
        times, because everytime the gcd changes, it has to reduce at least by a factor of 2

*/


// X = c1*a1 + c2 * a2 + c3*a3 + c4 * a4
// only if X % gcd ( a1 , a2 , a3 , a4 ) == 0 
// ci can be negative and zero also 


// when gcd ( p , a ) =  1 means p % a != 0
// a^(p-1) congurent 1    mod p
// => (a^(p-1) * a )    (congurent)  (a)    mod p 
// congurent ( maneha % p ) 

// !!
// a congurent 1 mod ( p ) =>  a - 1 = k * p  


// modular inverse X 
// a  . X congurent 1 mod n => X modular inverse 
// a . x - 1 = k * n    ==>    a.x - k*n = 1    and we use extendedgcd  

// useful use of sieve 
// intilize siv[i] = ay heja theb aleha for exmp siv[i] = i
// for ( int i = 2 ; i <= N ;i++ )
//      if ( siv[i] == i ) // means i is prime 
//      we will do some operations on multiples of that prime 
//             for ( int j = i ; j<= N ; j++  ) siv[j] -= siv[j]/i 
// siv[i]=> number of element <=i that are coprime with i = euleur phi 



//  a derangement is a permutation of the elements of a set
//  in which no element appears in its original position.
// The recursive formula is 𝐷(𝑛)=(𝐷(𝑛−1)+𝐷(𝑛−2))(𝑛−1)
const int mod = 1e9 + 7  ;




double my_log(int base, ll N){return (double)log(N)/log(base);}
bool isPowerOfTwo(ll n){ if (n <= 0) return false; return !(n & (n - 1)); }
bool is_prime(ll n) { if( n==1 || n==0 )return 0; else if( n==2 )return 1; else if(n%2==0)return 0;for(ll i=2;i*i<=n;i++){if(n%i==0)return 0;}return 1;}
// n is divisble by 2^k
bool isDivisibleByPowerOf2(int n, int k) {int powerOf2 = 1 << k;return (n & (powerOf2 - 1)) == 0;}


int mod_add(int a, int b , int MOD ) {a += b; if (a >= MOD) a -= MOD; return a;}
int mod_sub(int a, int b , int MOD ) { return mod_add(a, MOD - b,MOD); }


auto  lpow = [&] (int  base, int  exp) { // log2 
        int result = 1;
        while (exp > 0) {
                if (exp % 2 == 1) {
                        result *= result ;
                        result%= mod ;
                }
                base *= base ;
                base %= mod ;
                exp /= 2;
        }
        return result;
};


auto get_sqrt = [&](int x) { // x up to 2e18
		int l =  0, r = 2e9;
		while(l < r) {
			int mid  = (l + r + 1) / 2;
			if(mid * mid <= x) {
				l = mid;
			}
			else {
				r = mid - 1;
			}
		}
		return l;
	};
        

auto is_sq = [](long long x){
        long long sq = sqrtl(x + 0.5);
        for (long long i = max(1ll, sq - 2); i < sq + 3; ++i) {
                if (i * i == x) return true;
        }
        return false;
};

auto ArithmethicGap =[]( int debut , int terms , int gap   ){
        return (terms* (2LL * debut + (terms -1) * gap ))/2 ;
};

// 1^2 + 2^2 + 3 ^ 2 + ... + i^2 

auto CalQaur = [] ( int i ){
        return (i * (i+1) * (2*i +1 )) / 6 ; 
}
const int N = 1e5 ; 
/*
        primes up to N = sqrt(n)^(1/3) = n /ln(n)

        primes up to 
        1 to 10 = 4

        1 to 100 = 25

        1 to 1e3 = 168

        1 to 1e4 = 1,229

        1 to 1e5 =9,592

        1 to 1e6 = 78,492

        1 to 1e7 = 6,64,579

        1 to 1e8 = 5,761,455

        1 to 1e9 = 50 ,847, 534
*/
// give a , b it will return x ,y such  x*a + y*b = gcd 
int ext_gcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = ext_gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
// ext_gcd( 4 , 8 ,x , y )
// return gcd of ( 4 , 8 ) , x*4 + y*8 = gcd , and modify values of x ,y 
// ( x,y ) is a solution then ( (x + k *8/gcd) , (y - k*4 / gcd)
// (x,y ) solution means => ( x + (k*b/gcd)     , y - (k *a / gcd) ) also solution K can be any integer ! 


// given a ,b , c find x0 , y0 such x0*a + y0*b =c  ( c can be any integer )
bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
    g = ext_gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}


// gcd(a,m) should be 1
// solution of ax+my=1 as (ax)%m=(1)%m
bool modinvers(int a,int m,int &ai) {
    int x, y;
    int g = ext_gcd(a, m, x, y);
    if (g != 1) {
        return false;
    } else {
        // ai is the modular inverse of A 
        ai = (x % m + m) % m;
    }
    return true;
}
class NumberTheory {
public:
                bitset<N+1> is_prime; // up to 1e9 
                vector<int> primes , spd , numberofdivisors ;
                vector<vector<int>> listofdivisors ;
                vector<int>greatestdivisor;


                NumberTheory(int N ) {
                        /* all function up to +1e7
                        except sieve divisor it s limit = 1e5  khater tkhabi el elemtns */
                        is_prime.set();
                        //sieve_is_prime(N);
                        //sieve_smallest_prime(N);
                        //sieve_divisors(N);
                        //greatest_divisor(N);
                }

                template <typename T>
                T gcd(T a, T b) {
                        return (b == 0 ? a : gcd(b, a % b));
                }

                template <typename T>
                T lcm(T a, T b) {
                        return a * (b / gcd(a, b));
                }

                template <typename T>
                bool issquare(T w) {
                        T sq = round(sqrt(w));
                        return sq * sq == w;
                }
                // sieve is n log log (n)

                void sieve_is_prime(int M) {
                        is_prime.set();
                        is_prime[0] = is_prime[1] = false ; // 0 and 1 are not primes
                        int add = 1 ; 
                        // we ignored the values ( i *2 , i *3 , ... , i*(i-1) ) 
                        // bcz like u see they have another divisor !
                        // and its guranteed that they will covered but their smaller 
                        // divisors ! 

                        for (int i = 2; (long long ) i * i  <= M; i+= add , add = 2 ) {
                                if (is_prime[i]) {
                                        for (int j = (long long ) i * i; j <= M; j += i) {
                                                is_prime[j] = false;
                                        }
                                        primes.push_back(i);
                                }
                        }
                }
                void sieve_smallest_prime ( int M ){
                        // spd smallest prime divisor ! 
                        //https://codeforces.com/blog/entry/7262#:~:text=We%20use%20Eratosthenes%20sieve%20for,n))*log(n).
                        spd.resize( M +1 , 1 ) ; 
                        int n = M ; 
                        for ( int i = 2 ; i <= n ;i++ ){
                                if ( spd[i] == 1 ) {
                                        for ( int j = i ; j <= n ; j+= i  ){
                                                if ( spd[j] == 1 ) spd[j] = i ; 
                                        }
                                }
                        }
                }

                // no more than log2(n) prime divisors of some n up to 1e7 
                vector<int>primefactrize_sieve ( int x ){ // o(log2(n))
                        vector<int>ans ;
                        //vector<pair<int,int>>ans ;
                        while ( x > 1 ) {
                                int divisor = spd[x];
                                int cte = 0 ;
                                while ( x % divisor == 0 ){
                                        x /= divisor ;
                                        cte++ ; 
        
                                }
                                ans.push_back(divisor);
                                // ans.push_back({divisor , cte });
                        }
                        return ans ; 
                }
                
                vector<int>primefactrize_sieve_primes ( int x ){ // o(number of primes  < sqrt(x)
                        vector<pair<int,int>> primefactors;

                        int cte = 0 , cp = x ; 
                        // run primes  sieve up sqrt(x) !!!

                        for ( int i = 0 ; i  <= primes.size() ; i++ ){
                                cte = 0; 
                                while ( cp % i == 0 ){ cte++ ; cp/= i ; }    
                                if ( cte ) primefactors.pb({i,cte});
                        }
                        // if reste a number , 
                        // that a prime number > sqrt(x) we will push it there 
                        if ( cp > 1 ) primefactors.pb({cp,1});

                        return primefactors; 
                }

                
                vector<pair<int,int>> primeFactorize_normal(int p ) // sqrt(P) 
                {
                                vector<pair<int,int>> primefactors;

                                int cte = 0 , cp = p ; 
                                while ( cp % 2 == 0 ){cte++ ; cp/= 2 ; }    
                                if ( cte ) primefactors.pb({2,cte});

                                for ( int i = 3 ; i * i <= p ; i+=2 ){
                                                cte = 0; 
                                                while ( cp % i == 0 ){ cte++ ; cp/= i ; }    
                                                if ( cte ) primefactors.pb({i,cte});
                                }
                                if ( cp > 1 ) primefactors.pb({cp,1});

                                return primefactors;
                }

                
                void sieve_divisors ( int M ){
                        // maximum M can be is 1e5;
                        listofdivisors.resize(M+5);
                                for (int i = 1; i < M; i++)
                                        for (int j = i; j < M; j += i)
                                                        listofdivisors[j].pb(i);

                }

                void greatest_divisor ( int M ){
                        greatestdivisor.resize(M+2,1);
                                for ( int i = 1 ; i <= M ; i++ )
                                                for ( int j = i*2 ; j <= M ; j+= i ) 
                                                                greatestdivisor[j] = i ;
                                // for each number storing it s biggest divisor 
                }
                
                void countdivisors( int M ){
                        numberofdivisors.resize(M+3,0);
                        for ( int i = 1 ; i < M ; i++ )
                                        for ( int j = i ; j < M ; j+= i ) divv[j]++;
                        // for each multiple of i (= j )we increment divisors ( it s divisor = i ) 
                }

                

                template <typename T>
                T numDiv(T N) {
                        int PF_idx = 0, PF = primes[PF_idx];
                        T ans = 1;
                        while (N != 1 && (PF * 1ll * PF <= N)) {
                        int power = 0;
                        while (N % PF == 0) {
                                N /= PF;
                                power++;
                        }
                        ans *= (power + 1);
                        PF = primes[++PF_idx];
                        }
                        if (N != 1) ans *= 2;
                        return ans;
                }
                template <typename T>
                ll sumDiv(T N) {
                        int PF_idx = 0, PF = primes[PF_idx];
                        ll ans = 1;
                        while (N != 1 && (PF * 1ll * PF <= N)) {
                        int power = 0;
                        T po = PF;
                        while (N % PF == 0) {
                                N /= PF;
                                power++;
                                po *= PF;
                        }
                        ans *= ((po - 1) / (PF - 1));
                        PF = primes[++PF_idx];
                        }
                        if (N != 1) ans *= (N + 1);
                        return ans;
                }


 
                
                vector<int> generateDivisor_fromprime(int x) {
                        vector<pair<int, int>> f = primeFactorize_normal(x);
                        vector<int> dels;
                        int ret= 0 ; 

                        // gen complexity = O ( around log2(n ) * d(n) )
                        function<int(int, int)> gen = [&](int id, int p) {
                        if (id == f.size()) {
                                        dels.emplace_back(p);
                                        // if condition satisifed about that del ( divisor )
                                        if ( cond )return 1
                                        else return 0 ; 
                                }
                        else {
                                int mult = 1;
                                for (int i = 0; i <= f[id].second ; ++i) { // WE CAN PRECISE ( NOT USE MOREE THAN half prime coefficent )
                                        ret  += gen(id + 1, p * mult);
                                        mult *= f[id].first;
                                }
                        }
                        };
                        gen(0, 1);
                        return dels;
                }


};

// NumberTheory nt(N) ; 
auto cal = [&] ( int vl ) {return max ( 0LL , (vl+1)*(vl+1)/4 )  ;}; 
// vl + vl-2 + vl -4 + .. 1 ( vl is odd ! )

// if ( vl is even) vl + vl-2 + vl-4 +..+0         vl * ( vl+2 ) / 4 


// Return the number of odd numbers 
// in the range [L, R] 
int countOdd(int left , int right ){ 
    int vals  = (right  - left ) / 2;
    // if either right  or left  is odd 
    vals += right  % 2 != 0 || left  % 2 != 0;
    return vals ;
}


ll maxPowerOfTwo(ll n){ // akbar power of 2 asghar ou egal n 
        ll x=log2(n);
        return lpow(2,x);
}


















long long sqr(long long x) {
	return x * x;
}
 
bool is_square(long long n) {
	long long x = roundl(sqrtl(n)) - 2;
	if (x < 0) {
		x = 0;
	}
	while (sqr(x + 1) <= n) {
		++x;
	}
	return x * x == n;
}