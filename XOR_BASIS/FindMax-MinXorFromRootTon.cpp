/*
        approach 
        push all cycles values  to xor basis 

        cycle values = from root 0 traverse till that cycle and back again 
        at root 0 

        push all of those to xor basis

        and take the max with them 

        with the path from root to node N

        val[i] = any xor path from root till I 

        if u want to maximize it 

        loop over all the basis and try to maximize it 

        because we can take any cycle and go back to root 0 , and then 
        go to node N   
         

*/

// https://codeforces.com/contest/845/submission/72271147
#include <bits/stdc++.h>

using namespace std;

typedef pair<int,int> pii;

#define f first
#define s second

const int maxn = 1e5+10;

int n, m, val[maxn], mark[maxn], base[maxn];

vector<pii> grafo[maxn], g[maxn];

vector<int> cycle;

void dfs(int u, int v){
    mark[u] = 1;
    val[u] = v;

    for(auto x : grafo[u]){
        if(mark[x.f]){
            cycle.push_back(val[u] ^ x.s ^ val[x.f]);
        }
        else{
            dfs(x.f, v ^ x.s);
        }
    }
}

void gauss(){
    for(auto x : cycle){
        for(int i=30; i>=0; i--){
            if((x>>i) & 1){
                if(!base[i]) base[i] = x;
                x ^= base[i];
            }
        }
    }
}

int solve(int v){
    for(int i=30; i>=0; i--){
        if((v>>i) & 1) v = min(v, v ^ base[i]);
    }
    return v;
}

int main(){
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    cin >> n >> m;

    for(int i=1; i<=m; i++){
        int u, v, w;

        cin >> u >> v >> w;

        grafo[u].push_back({v, w});
        grafo[v].push_back({u, w});
    }

    dfs(1, 0);

    gauss();

    cout << solve(val[n]) << endl;
}
