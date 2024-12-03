

// If a ≡ b (mod n) and c ≡ d (mod n),
// then: ac ≡ bd (mod n)
int makemod( int v){
    v = (-mod <= v && v < 2*mod) ? v : v % mod;
    if (v < 0) v += mod;
    if (v >=mod ) v -= mod;
    return v ; 
}  
void add(int  & a, int b,int Mod = mod) { a =   makemod ( makemod(a) + makemod(b) ) ; } 
void mult(int & a, int b,int Mod = mod) { a = makemod(  makemod(a) * makemod(b) ) ; }
void sub ( int  & a , int b , int Mod = mod ){   a = makemod (   makemod(a) -  makemod(b) )  ; }
void divide(int & a , int b,int Mod = mod) {  a = makemod ( makemod(a)  *  makemod( modinv(b) ) )   ; }
int binpow(int a, int k, int res = 1,int Mod = mod) {
    while (k) {
        if (k % 2) res = (res * a) % Mod;
        a = (a * a) % Mod;
        k /= 2;
    }
    return res;
}

int modinv(int a,int Mod = mod) { return binpow(a, Mod - 2); }

// mod of big integer represented in a string 
int str_mod(string s, int mod) {
    int res = 0;
    for (int i = 0; i < s.length(); i++) { res = (res * 10 + s[i] - '0') % mod; }
    return res;
}


// If a ≡ b (mod n) and c ≡ d (mod n),
// then: ac ≡ bd (mod n)
const int MOD = 1e9 + 7 ; 
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
        return Mint(e * b.inv());
    }
};
using mint=  Mint<MOD>  ;