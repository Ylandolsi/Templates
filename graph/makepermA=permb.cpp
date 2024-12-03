/* n - nbr of cycles in directed graph
https://codeforces.com/contest/1768/submission/282627258
 */

void solve(){
    cin >> n;
    dsu.init(n);
    a = vi(n+1) , b= vi(n+1) ; iota(b.begin() +1 , b.end() , 1LL ); 
    for (int i = 1; i <= n; i++)
        cin >> a[i] , pos[b[i]] = i , used[i] = 0 ;
    for (int i = 1; i <= n; i++)
        if (!used[i])
            dsu.unite(i,pos[a[i]]);
    cycle =  dsu.connected_grps ;
    cout <<  n - cycle ; 
}