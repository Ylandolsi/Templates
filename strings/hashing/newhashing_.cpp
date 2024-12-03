// https://codeforces.com/contest/245/submission/277170913


mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int get_rand(int l, int r) {return uniform_int_distribution<int>(l, r)(rng);}

int BASE = get_rand(1252 , 279054253 ) + 161 ; 
const int MOD_X = 1000000181, MOD_Y = 998244353  ;

int add(int a, int b , int MOD ) { a += b;if (a >= MOD) a -= MOD;return a;}
int sub(int a, int b , int MOD ) { return add(a, MOD - b,MOD); }
int mul(int a, int b, int MOD) {return a * 1LL * b % MOD;} 
 
struct H {
  int x, y;
  H() = default;
  H(int _x): x(_x), y(_x) {}
  H(int _x, int _y): x(_x), y(_y) {}
  inline H operator+(const H& h) const { return H(add(x, h.x, MOD_X), add(y, h.y, MOD_Y)); }
  inline H operator-(const H& h) const { return H(sub(x, h.x, MOD_X), sub(y, h.y, MOD_Y)); }
  inline H operator*(const H& h) const { return H(mul(x, h.x, MOD_X), mul(y, h.y, MOD_Y)); }
  inline bool operator==(const H& h) const { return x == h.x && y == h.y; }
};
const int N = 2e6 ; 
vector<H> pw (N); 

void calc ( ){
    pw[0] = 1;
    for ( int i = 0 ;i < N ; i++ )  pw[i+1] = pw[i] * BASE;
}
struct HashInterval {
	vector<H> ha , harev;
    int n ; 
	HashInterval(string& str) : n(str.size()) {
        ha.resize(n+2);  harev = ha ; 
		for ( int i = 0 ; i < n; i++ )
			ha[i+1] = ha[i] * BASE + str[i] -'a' + 1,
        harev[n] = 0;
        for(int i = n - 1;i >= 0;--i)
            harev[i] = harev[i + 1] * BASE + str[i] - 'a' + 1 ;
	}
	int hashInterval(int a, int b) { 
		H ans =  ha[b+1] - (ha[a] * pw[b - a+1]);
        return (ans.x << 32LL) | ans.y ; 
	}
    int hashIntervalRev (int a, int b) {
        H ans =  harev[a] - (harev[b + 1] * pw[b-a+1]);
        return (ans.x << 32LL) | ans.y ; 
    };
    bool is_palindrome ( int i , int j ){
        return hashInterval(i,j) == hashIntervalRev(i,j) ; 
    }
    int getFullHash ( string &x) {
        H ans = 0  ; 
        for ( int i = 0 ; i < (int)x.size(); i++ )
			ans = ans * BASE +x[i] -'a' + 1 ;
        return (ans.x << 32LL) | ans.y ; 
    }

};

int merge(const H &h1, const H &h2 , int r2 , int l2 ) {
    H ans_merged =  h1 * pw[r2 - l2 + 1]  + h2;
    return (ans_merged.x << 32LL) | ans_merged.y ;  ;
}