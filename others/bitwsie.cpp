/* --------------Builtin Bit Functions-------------- */
// 1) __builtin_clz(x) -> returns the number of zeros at the beginning in the bit representaton of x.
// 2) __builtin_ctz(x) -> returns the number of zeros at the end in the bit representaton of x.
// 3) __builtin_popcount(x) -> returns the number of ones in the bit representaton of x.
//    __builtin_popcountll for ll 
// 4) __builtin_parity(x) -> returns the parity of the number of ones in the bit representaton of x.

//1. it generate every possible subset of a set , ex:- 1001  :- 0000,0001,1001,1000
int ss=0;
do{
	//process subset ss of x
}while(ss=(ss-x)&x);

//2. remove last bit of a number
 n=n&(n-1); //ex:- 101100 -> 101000

 //3. get the lowest bit
a) i&-i
b) i&~(i-1)
	
//4. add
a + b − (a xor b) = 2 × (a and b)
a + b ≥ a xor b

template<class T> int getbit(T s, int i) { return (s >> 1) & 1; }
template<class T> T onbit(T s, int i) { return s | (T(1) << i); }
template<class T> T offbit(T s, int i) { return s & (~(T(1) << i)); }
template<class T> int cntbit(T s) { return __builtin_popcount(s); }

#define FOR_subset(t, s) for (ll t = (s); t >= 0; t = (t == 0 ? -1 : (t - 1) & (s)))

#define  ibits(x) 32 - __builtin_clz(x) // 32 - bts(x) if int 
#define  lbits(x) 64 -  __builtin_clzll(x) // 64 - bts(x) if ll 
// msb(x) = 31 - __builtin_clz(x) int      .. msb(x) ll 63 - __builtin_clzll(x)  

ll binToDec(string s) { return bitset<64>(s).to_ullong(); }
string decToBin(ll a) { return bitset<64>(a).to_string(); }


int bitflip(int num , int index ){
    return num ^ ( 1 <<  index ); 
}
bool isKthBitSet(int n, int k){
  return ((n & (1 << k)) ? 1 : 0);
}
ll Setbit(ll n,int i){
    return n|(1<<i);
}
ll unsetbit ( ll n , int i ){
    return n & ~(1<<i);
}
ll flipbit ( int num , int ind){
    num &= ~( 1 << j ) ; 
    return num ; 
}
// tne7i l bit ! A &= ∼(1 << j)
int countBits(int number) {
    if (number <= 0) {
        return 0;
    }
    int bits = (int)(log2(number)) + 1;
    return bits;
}
int inverse ( int a ){
    return   a ^ ( (1 << countBits(a) )-1 )  ;
}

bool isPowerOfTwo(int n){
    if ( n ==0 ) return 0;
    return !( n & (n-1) );// return 1000000 & 0111111 == 0 
}

vector<ll> decimalToBinary(ll number){
    //10 will become -> 00000000000001010
    vector<ll> binary;
    while(number){
        binary.push_back(number % 2);
        number /= 2;
    }
    // 18 number of bits total 
    ll left = 18 - binary.size();
    while(left--) binary.push_back(0);
    reverse(binary.begin(), binary.end());
    return binary;
}
 


int countbits_with_kth_bit_set_up_to_N ( int k , int N ) {
    int x = (1LL<<k)*2LL ;
    int groups = N/x;
    int reminder = N%x;
    int ans = 0 ; 
    ans += ( groups  * ( 1LL<<k) ); // each group andou 1 << k possibilites 
    /*
        0001
        0010
        0011
        0100
        0101
        0110
        0111
        1000
        1001
        1010
        1011
        1100
        1101
        

        if we consider k = 2 ,
        groups = 1 
        reminder = 2 ;
        for each group andna 4 = ( 1 << 2) possibilites al ymin 00 / 01 / 10 / 11   
        
        w reminder = 2 
        f cas hedhy andna 2 choix kahaw manajmouch nekhtrou 
        houma 00 w 01 
        khw 
    */
    ans+= max ( 0LL , (reminder - (1LL << k) + 1 ) );
    
    return ans % mod  ;   
}
long long cte( int k , long long n )
{
    // cte k-th bit from [0 ,n ] 
    // k[ 0 , 1 , 2 , .... ] k = 0 = 2^0 

	n = n +1 ; 
    long long res = (n >> (k + 1)) << k;
    if ((n >> k) & 1)
        res += n & ((1ll << k) - 1);
    return res;
}


auto calc_and_from_left_to_right  =[=] ( int left , int right) {
    // https://youtu.be/-qrpJykY2gE
        int shiftcount = 0;
        while(left != right and left > 0) {
            shiftcount++;
            left = left >> 1; 
            right = right >> 1;
            // nokdou enheiw lin nalkaw zoz bit sets al ymiin
        }
        return int64_t(left << shiftcount);
        /*
            leeft = 111001
                    111010
                    .
                    .....
                    111110

            right = 111111
            donc ken l 3bit lwala bech yetnahew khater baed chiwaliw kad kad 
            donc answer  = 111000
        

        ---
        l = 10010101000
        r=  11111111000
        ---> ans = 1000000000
        */
};


auto calc_and_from_left_to_right  =[=] ( int left , int right) {
    // https://youtu.be/gLZZyvXTRLk
        while ( right > left ) right &= (right-1); // remove awel bit set al ymiin
        return right;
    // exp right = 1100 , left = 1010 
    /* chnokdou enehiw bit par bit mel right lin twali kad l left */
};


template <typename T, typename V> T rangeBitwiseAnd(T left, V right) {
    T res = 0;
    int cnt = 0; for(; left >= (1ll<<cnt); cnt++){}
    if(1ll<<cnt <= right) return 0;
    if(left==right) return left;
    
    res += 1ll<<(--cnt);
    left -= 1ll<<(cnt); right -= 1ll<<cnt;
    return res + rangeBitwiseAnd(left, right);
}
 
template<typename T> T MSB(T n) {T ans = -1;while(n) n /=2, ans++;return ans;}
template<typename T> T rangeBitwiseOr(T l, T r) {
    ll res = 0;
    ll u = MSB(l), v = MSB(r);
    while(u == v && u >= 0 && v >= 0) {
        ll val = (1ll<<u);
        l-=val, r-=val;
        res += val;
        u = MSB(l), v = MSB(l);
    }
    u = max(MSB(l), MSB(r));
    res += (1ll<<(u+1))-1;
    return res;
}
 
template<typename T> T XOR1(T n) {
    ll md = n % 4;
    if(!md) return n;
    else if(md==1) return 1;
    else if(md==2) return n+1;
    return 0;
}
template<typename T> T rangeBitwiseXor(T l, T r) {return XOR1(r)^XOR1(l-1);}