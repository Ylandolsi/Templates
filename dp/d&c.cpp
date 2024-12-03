#include <iostream>
 
using namespace std;
 
#define int long long
 
const int MXN = 3001, INF = 1e17;
int psum[MXN], dp[MXN][MXN];
 
void dnc(int i, int l, int r, int optl, int optr) {
    if (l > r) return;
 
    int mid = (l + r) / 2;
 
    pair<int, int> best = {INF, l};
 
    for (int j = optl; j < min(mid, optr + 1); j++) {
        int sum = psum[mid] - psum[j];
        best = min(best, make_pair(sum * sum + dp[i - 1][j], j));
        // best = min(best, make_pair(cost() + dp[i - 1][j], j));
    }
 
    dp[i][mid] = best.first;
 
    int opt = best.second;
    dnc(i, l, mid - 1, optl, opt);
    dnc(i, mid + 1, r, opt, optr);
}
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    int N, K;
    cin >> N >> K;
 
    for (int i = 1; i <= N; i++) {
        cin >> psum[i];
        psum[i] += psum[i - 1];
    }
 
    for (int j = 0; j <= N; j++)
        dp[0][j] = INF;
 
    dp[0][0] = 0;
 
    for (int i = 1; i <= K; i++)
        dnc(i, 1, N, 0, N - 1);
 
    cout << dp[K][N];
}


//  * Status: tested on http://codeforces.com/contest/321/problem/E
