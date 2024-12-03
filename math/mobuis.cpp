// https://codeforces.com/blog/entry/53925

// https://codeforces.com/contest/2037/problem/G
// problem i solved with mobuis (!=1 ) && inclusion exclusion 
 

 
// i de 1 to n  ( i == 1 )     // can be also i != 1 if we use inverse of mobuis !
//- ---->   somme d | i mobuis(d) == somme de 1 to n [d|i ]  * mobuis(d)

// can used to calcualte sum of gcd ( ai ,aj ) 
// can used to calcualte how many   gcd ( ai ,aj )  = 1 

// [x == 1 ]
for (int i = 1; i <= N; i++) mu[i] = 1;
// [x != 1 ] for (int i = 1; i <= N; i++) mu[i] = -1;
for (int i = 2; i <= N; i++)
        if (isprime[i] == 0) {
                for (int j = i; j <= N; j += i) {
                        isprime[j] = 1;
                        if (j % (i * i) == 0) mu[j] = 0;
                        else mu[j] *= -1;
                }
        }

map<int, int> mob; // declared global ! ss

int mobius(int n)
{
    if (n == 1) return 1;
    int nn = n;
    if (mob.find(n) != mob.end())return mob[n];
    int p = 0;
 
    // Handling 2 separately
    if (n%2 == 0)
    {
        n = n/2;
        p++;
 
        // If 2^2 also divides N
        if (n % 2 == 0){
            mob[nn] = 0;
            return 0;
        }
    }
 
    // Check for all other prime factors
    for (int i = 3; i <= sqrt(n); i = i+2)
    {
        // If i divides n
        if (n%i == 0)
        {
            n = n/i;
            p++;
 
            // If i^2 also divides N
            if (n % i == 0) {
                mob[nn] = 0;
                return 0;
            }
               
        }
    }

    if (n != 1)p++;
 
    int ans =  (p % 2 == 0)? 1 : -1;
    mob[nn] = ans;
    return ans;
}






//  sum of gcd ( ai ,aj ) 

int ans[N + 1], cnt1[N + 1], cnt[N + 1], a[N + 1];

void solve() {
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        cnt1[x]++;
        a[i] = x;
    }

    for (int i = 1; i <= N; i++)
        for (int j = i; j <= N; j += i) cnt[i] += cnt1[j];
        // cnt[i] = mutlioles of  (i) from[ i , n] that present in array ! 
    ll res = 0;
    for (int d = N; d >= 1; d--) {
        ans[d] = cnt[d] * (cnt[d] - 1) / 2;
        for (int j = 2 * d; j <= N; j += d) ans[d] -= ans[j];
        res += ans[d] * d;
        // to gcd = d     , a[i] ,a [j] must not be divisble  by d*2 ; d*3 .... multiples of (d):
    }
    ll bf = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            bf += gcd(a[i], a[j]);

    cout << res << " " << bf << "\n";
}