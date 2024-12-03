// https://github.com/Mtaylorr/Competitive-programming-Solutions/blob/main/Gym/2023-2024%20ICPC%2C%20Swiss%20Subregional/C.cpp
#define ll long long
#define db long double
#define pb push_back
typedef unsigned long long ul;
class Pollard {
   public:
    map<ul, int> cnt_primes;
    vector<ul> primes, divisors;
    ul modMul(ul a, ul b, const ul mod) {
        ll ret = a * b - mod * (ul)((db)a * b / mod);
        return ret + ((ret < 0) - (ret >= (ll)mod)) * mod;
    }
    ul modPow(ul a, ul b, const ul mod) {
        if (b == 0) return 1;
        ul res = modPow(a, b / 2, mod);
        res = modMul(res, res, mod);
        return b & 1 ? modMul(res, a, mod) : res;
    }

    bool Isprime (ul n) {  // not ll!
        if (n < 2 || n % 6 % 4 != 1) return n - 2 < 2;
        ul A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
           s = __builtin_ctzll(n - 1), d = n >> s;
        for (auto a : A) {  // ^ count trailing zeroes
            ul p = modPow(a, d, n), i = s;
            while (p != 1 && p != n - 1 && a % n && i--) p = modMul(p, p, n);
            if (p != n - 1 && i != s) return 0;
        }
        return 1;
    }
    ul pollard(ul n) {  // return some nontrivial factor of n
        auto EE = [n, this](ul x) { return modMul(x, x, n) + 1; };
        ul x = 0, y = 0, t = 30, prd = 2, i = 1, q;
        while (t++ % 40 ||
               __gcd(prd, n) == 1) {  /// speedup: don't take gcd every it
            if (x == y) x = ++i, y = EE(x);
            if ((q = modMul(prd, max(x, y) - min(x, y), n))) prd = q;
            x = EE(x), y = EE(EE(y));
        }
        return __gcd(prd, n);
    }
    // prime factors ! 
    void factor_rec(ul n, map<ul, int>& cnt) {
        if (n == 1) return;
        if (Isprime (n)) {
            ++cnt[n];
            return;
        }
        ul u = pollard(n);
        factor_rec(u, cnt), factor_rec(n / u, cnt);
    }
    // calcualte divisors from prime factors ! 
    void calcDivisorsRec(ul cur, int i) {
        if (i >= primes.size()) {
            divisors.pb(cur);
            return;
        }
        int r = cnt_primes[primes[i]];
        for (int j = 0; j <= r; j++) {
            calcDivisorsRec(cur, i + 1);
            cur = cur * primes[i];
        }
    }
    // and complextiy become ( o ( n^(1/4 ) to generate primes + d(n) to geenrate divisors )! 
    void calcDivisors(ul x) {
        cnt_primes.clear();
        primes.clear();
        divisors.clear();
        factor_rec(x, cnt_primes);
        for (auto& u : cnt_primes) {
            primes.pb(u.first);
        }
        calcDivisorsRec(1, 0);
    }
} pollard;