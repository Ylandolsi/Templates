// https://codeforces.com/contest/2002/submission/275771493
struct LCA {
    int n, l , timer = -1 ; 
    vector <vector<int>> p, adj;
    vector<int> h , in , out ;
    void init(int n_) {
        n = n_ ; 
        l = 0;
        while((1 << l) <= n) l++;
        p.assign(n + 1, vi(l));
        adj.resize(n + 1);
        h.resize(n + 1);
        in.resize(n+1),  out.resize(n+1); 
    }
    void add_edge(int u, int v) { adj[u].push_back(v); adj[v].push_back(u); }
    void dfs(int node, int par) {
        h[node] = h[par] + 1;
        p[node][0] = par;
        in[node] = ++timer ; 
        for(int i = 1; i < l; i++) {
            p[node][i] = p[p[node][i - 1]][i - 1];
        }
        for(auto u : adj[node]) {
            if(u != par) {
                dfs(u, node);
            }
        }
        out[node] = timer ; 
    }
    int go_up(int node, int d) {
        for(int i = 0; i < l; i++)
            if((d >> i) & 1)
                node = p[node][i];
        return node;
    }
    int lca(int u, int v) {
        if(h[u] < h[v]) swap(u, v);
        u = go_up(u, h[u] - h[v]);
        if(u == v) return u;
        for(int i = l - 1; i >= 0; i--) {
            if(p[u][i] != p[v][i]) {
                u = p[u][i];
                v = p[v][i];
            }
        }
        return p[u][0];
    }
    int dist(int u, int v) {
        return h[u] + h[v] - 2 * h[lca(u, v)];
    }
    bool isAncester(int u, int v) {
        return in[u] <= in[v] && in[v] <= out[u];
    }
};


