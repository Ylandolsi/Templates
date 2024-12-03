// O(N)
const int N = 2e7 + 1;
vector<int> spf;
void build() {
    spf.resize( N +1 , 1) ; 
    for ( int i = 2 ; i <= N ;i++ ){
            if ( spf[i] == 1 ) {
                    for ( int j = i ; j <=N ; j+= i  ){
                            if ( spf[j] == 1 ) spf[j] = i ; 
                    }
            }
    }
}
 
// O(d(n^p))
vector<int> gen_divisors(const vector<array<int, 2>>& pfs) {
    vector<int> divs{1};
 
    auto recd = [&](int x, int i, auto&& recd) -> void {
        if (i >= (int) pfs.size()) return;
        recd(x, i + 1, recd);
        for (int j = 0; j < pfs[i][1]; j++) {
            x *= pfs[i][0];
            divs.push_back(x);
            recd(x, i + 1, recd);
        }
    };
    recd(1, 0, recd);
 
    // sort(divs.begin(), divs.end());
    return divs;
}
 
// O(log(n) + d(n^p))
// n up to 2e7 !! ;
// log n to generate prime factors 
vector<int> divisors(int n, int p = 1) {
    if (spf.empty()) build();
    if (n == 1) return {1};
 
	// generate prime facto in log(n) with sieve ! if ( n < 2e7 ) 
    vector<array<int, 2>> pfs{{spf[n], p}};
    n /= spf[n];
    while (n != 1) {
        if (pfs.back()[0] == spf[n])
            pfs.back()[1] += p;
        else
            pfs.push_back({spf[n], p});
        n /= spf[n];
    }
 
    return gen_divisors(pfs);
}
 
// O(log(n))
int prime_factors(int n) {
    if (n == 1) return 0;
 
    int sz = 1, prev = spf[n];
    n /= spf[n];
    while (n != 1) {
        if (prev != spf[n])
            prev = spf[n], sz++;
        n /= spf[n];
    }
 
    return sz;
}