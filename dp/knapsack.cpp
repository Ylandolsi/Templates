
// https://codeforces.com/contest/1856/submission/228874223
const int N = 1000001; // max sum we can get !
// tot max sum we can form ! ( sum of all elements of vector a)
template<int len = 1> int knapsack(int tot, vi &a){
    // tot = sm(a) + 1 !!!!!! +1 lezma !
    /* wee need all sum [0 , tot] 
    so we have to make this commented!
    if (tot <= 1) return 0;
    */
    if (len < tot) return knapsack<min(len * 2, N)>(tot, a);
    int mx = *max_element(a.begin(),a.end());

    bitset<len> dp; dp[0] = 1;
    map<int,int> freq; 
    for (auto &e : a) ++freq[e];
    for (auto &e : freq){
        // compressing it !
        int k = 1;
        while (k <= e.second){
            dp |= dp << (k * e.first);
            e.second -= k, k <<= 1;
        }
        if (e.second) dp |= dp << (e.first * e.second);
    }
    int ans = 0;
    for ( int i = 0 ; i < len ; i++ ) 
        if (dp[i]) // we can from sum = i ! 
            ans = max ( ans ,  i * (int)(tot - i - 1));
    return ans;
    // S = totalsum ( sum of all elements in a )
    // complexity  O( S * sqrt(S) / 32   ) 
}













struct custom_bitset {
    vector<uint64_t> bits;
    int64_t b, n;
 
    custom_bitset(int64_t _b = 0) {
        init(_b);
    }
 
    void init(int64_t _b) {
        b = _b;
        n = (b + 63) / 64;
        bits.assign(n, 0);
    }
 
    void clear() {
        b = n = 0;
        bits.clear();
    }
 
    void reset() {
        bits.assign(n, 0);
    }
 
    void _clean() {
        // Reset all bits after `b`.
        if (b != 64 * n)
            bits.back() &= (1LLU << (b - 64 * (n - 1))) - 1;
    }
 
    bool get(int64_t index) const {
        return bits[index / 64] >> (index % 64) & 1;
    }
 
    void set(int64_t index, bool value) {
        assert(0 <= index && index < b);
        bits[index / 64] &= ~(1LLU << (index % 64));
        bits[index / 64] |= uint64_t(value) << (index % 64);
    }
 
    // Simulates `bs |= bs << shift;`
    void or_shift(int64_t shift) {
        int64_t div = shift / 64, mod = shift % 64;
 
        if (mod == 0) {
            for (int64_t i = n - 1; i >= div; i--)
                bits[i] |= bits[i - div];
 
            return;
        }
 
        for (int64_t i = n - 1; i >= div + 1; i--)
            bits[i] |= bits[i - (div + 1)] >> (64 - mod) | bits[i - div] << mod;
 
        if (div < n)
            bits[div] |= bits[0] << mod;
 
        _clean();
    }
 
    // Simulates `bs |= bs >> shift;`
    void or_shift_down(int64_t shift) {
        int64_t div = shift / 64, mod = shift % 64;
 
        if (mod == 0) {
            for (int64_t i = div; i < n; i++)
                bits[i - div] |= bits[i];
 
            return;
        }
 
        for (int64_t i = 0; i < n - (div + 1); i++)
            bits[i] |= bits[i + (div + 1)] << (64 - mod) | bits[i + div] >> mod;
 
        if (div < n)
            bits[n - div - 1] |= bits[n - 1] >> mod;
 
        _clean();
    }
 
    int64_t find_first() const {
        for (int i = 0; i < n; i++)
            if (bits[i] != 0)
                return 64 * i + __builtin_ctzll(bits[i]);
 
        return -1;
    }
 
    custom_bitset& operator&=(const custom_bitset &other) {
        assert(b == other.b);
 
        for (int i = 0; i < n; i++)
            bits[i] &= other.bits[i];
 
        return *this;
    }
};
void compress (vector<long long> &v) {
	if (v.size() <= 100) {
		return;
	}
	map<int,int> cnt;
	for (int i: v) {
		cnt[i] += 1;
	}
	vector<pair<int,int>> vec;
	for (auto& p: cnt) {
		vec.emplace_back(p);
	}
	for (auto& p: vec) {
		cnt[p.first] = 0;
		int powr = 1;
		while (powr <= p.second) {
			cnt[powr * p.first] += 1;
			p.second -= powr;
			powr *= 2;
		}
		cnt[p.first * p.second] += p.second;
	}
	v.clear();
	for (auto& p: cnt) {
		while (p.second--) {
			v.push_back(p.first);
		}
	}
}

void solve( int t ){
    int n ; cin >> n ; 
    vi a (n);
    for ( auto &d : a) cin >> d ; 
    compress(a);

    int sm = accumulate(all(a) , 0LL ); 
    custom_bitset cb(sm+ 1);
    cb.set(0, 1);
    for (int i: a) {
        cb.or_shift(i);
    }
    int ans =  0;
    for (int i = sm; i >= 0; i--) {
        if (cb.get(i)) {
            // we can get sum = i
            ans += (i+1)/2;
        }
    }
    cout << ans ;
}