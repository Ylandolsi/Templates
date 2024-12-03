// https://github.com/mrsac7/CSES-Solutions/blob/master/src/2081%20-%20Fixed-Length%20Paths%20II.cpp

int dfs(int s, int p) {
    dp[s] = 1;
    in[nd] = ++timer ; 
    prof[nd] = prof[pr] + 1 ;
    nodes[in[nd]] = nd ;
    for (auto i: adj[s]) {
        if (i != p && !mark[i]) {
            dp[s] += dfs(i, s);
        }
    }
    out[nd] = timer ; 
    return dp[s];
}
 
 
int GetCentroid(int s, int p, int n) {
    for (auto i: adj[s]) {
        if (i != p && !mark[i] && dp[i] > n/2) {
            return GetCentroid(i, s, n);
        }
    }
    return s;
}
 
 
void dfs3(int s, int p, int d, int flag) {
    if (d > k2) return;
    // bech baed tamal intilize lel segment tree wala arrays eli tkhabi fih ! 
    maxDepth = max(maxDepth, d);
    if (flag) update(d, 1);
    else ans += query(max(0LL, k1-d), k2-d);
    for (auto i: adj[s]) {
        if (i != p && !mark[i])
            dfs3(i, s, d+1, flag);
    }
}

 
void solve(int s) {
    dfs(s, 0);
    int ct = GetCentroid(s, 0, dp[s]);
    mark[ct] = 1;
    maxDepth = 0;
    for (auto i: adj[ct]) {
        if (!mark[i]) {
            // if flag == 0 update 
            // else query paths ! 
            dfs3(i, ct, 1, 0);
            dfs3(i, ct, 1, 1);
            // or we can to query paths ! 
            for ( int i = in[ch] ; i <= out[ch] ;i++ ){
                int nodehere = nodes[i];
                // query here 
            }
        }
    }
    for (int i = 1; i <= maxDepth; i++) 
        update(i, -query(i, i));
    for (auto i: adj[ct]) if (!mark[i]) {
        solve(i);
    }
}


solve(1); // root at 1 first !