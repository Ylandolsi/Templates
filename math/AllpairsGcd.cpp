const int mod = 1e9 + 7, N = 1e6 + 1;

ll phi[N + 1], ans[N + 1];

void pre() {
    for (int i = 1; i <= N; i++) phi[i] = i;
    for (int i = 2; i <= N; i++)
        if (phi[i] == i)
            for (int j = i; j <= N; j += i) phi[j] -= phi[j] / i;
    for (int i = 1; i <= N; i++)
        for (int j = 2 * i; j <= N; j += i) ans[j] += i * phi[j / i];
    for (int i = 1; i <= N; i++) ans[i] += ans[i - 1];
}

void solve(int n) { cout << ans[n] << el; }
ans[i] = gcd ( 1 , 2) , gcd ( 1 , 3 ) , gcd ( 1 , i )
        + gcd ( 2 , 3 ,) + ... + gcd (2 , i )
        + ... 
        + gcd ( i -1 , i ) ;