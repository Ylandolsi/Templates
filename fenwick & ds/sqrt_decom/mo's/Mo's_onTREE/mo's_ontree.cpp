
// https://www.youtube.com/watch?v=1Zduxi_CFx0
template < typename T = int , typename graphType = int , bool VAL_ON_EDGE = false >
class MoTree {
public:
    struct Query {
        int l, r, k, lca, queryIdx;
        int64_t ord;

        Query(vector < T >& S, vector < T >& E, int L = 0, int R = 0, int QueryIdx = 0, int LCA = 0, int HilbertPow = 0) {
            if (S[L] > S[R])
                swap(L, R);
            if (LCA == L) // if in the same subtree we traverse from s[l] to s[r]
            // if valuse on edge we will invremret start by 1 khater mich teb3a !
                l = S[L] + VAL_ON_EDGE, r = S[R], lca = -1, queryIdx = QueryIdx;
            else // if not , traverse from end[l] to start[r] without 
                // and add lca if they are not in same subtree && values on nodes! 
                l = E[L], r = S[R], lca = LCA, queryIdx = QueryIdx;
            // calcOrder(HilbertPow);
        }

/*         void calcOrder(int hilbert_pow) {
            ord = MoTree::hilbertOrder(l, r, hilbert_pow, 0);
        } */

/*         bool operator < (const Query& rhs) const {
            return ord < rhs.ord;
        } */

        bool operator <(Query b) const{
            if(l / SqrtN != b.l / SqrtN)
                return l / SqrtN < b.l / SqrtN;
            return l / SqrtN % 2 ? r < b.r : r > b.r;
        }
    };

    MoTree(int N, int M, const vector < vector < graphType > >& G, const vector < T >& V = {}, int root = 1) 
        : curr_l(1), curr_r(0), n(N), m(M), SqrtN(n / sqrt(m) + 1), timer(1), ans(0), answers(M), val(V), adj(G) {
        LOG = calcLog(N);
        // helbertPow = calcHilbertPow(2 * N + 1);
        nodeFreq = S = E = dep = vector < int > (n + 5);
        FT = vector < int > (2 * n + 5);
        anc = vector < vector < int > > (n + 5, vector < int > (LOG));
        if(val.empty()) val = vector < T > (n + 5);

        dfs(root, adj);
    }

/*     static inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
        if (pow == 0) return 0;
        int hpow = 1 << (pow - 1);
        int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
        seg = (seg + rotate) & 3;
        const int rotateDelta[4] = {3, 0, 0, 1};
        int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
        int nrot = (rotate + rotateDelta[seg]) & 3;
        int64_t subSquareSize = int64_t(1) << (2 * pow - 2);
        int64_t ordd = seg * subSquareSize;
        int64_t add = hilbertOrder(nx, ny, pow - 1, nrot);
        ordd += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
        return ordd;
    } */

    void getData() {
        for (int i = 0, u, v; i < m && cin >> u >> v; i++)
            queries.emplace_back(S, E, u, v, i, getLCA(u, v), helbertPow);
            // queries.emplace_back(S, E, u, v, i, getLCA(u, v), helbertPow);
        process();
    }

    void process() {
        sort(queries.begin(), queries.end());

        // start with the first query
        curr_l = queries[0].l, curr_r = queries[0].l - 1;
        // queries[i].l & r are now with values of flated tree ! rod belek 
        for (auto& q : queries) {
            setRange(q);

            // if lca is -1 then the two nodes are in the same subtree
            // we only add lca if the values on node && [u , v ] not in the same sutbree !
            if (~q.lca && !VAL_ON_EDGE) 
                add(q.lca);
            
            answers[q.queryIdx] = ans;
            
            if (~q.lca && !VAL_ON_EDGE) 
                remove(q.lca);
        }
    }

    vector < T > getAnswers() const {
        return answers;
    }

private:
    int curr_l, curr_r, n, m, SqrtN, timer, LOG, helbertPow;
    T ans;
    vector < T > answers, val;
    vector < int > dep, S, E, FT, nodeFreq;
    vector < vector < int > > anc;
    vector < Query > queries;
    const vector < vector < graphType > >& adj;
    
    void dfs(int u, const vector < vector < pair < int, int > > >& adj, int p = -1) {
        S[u] = timer;
        FT[timer++] = u;
        for (auto& [v, w] : adj[u]) {
            if (v == p) continue;
            dep[v] = dep[u] + 1, anc[v][0] = u ; 
            val[v] = w; // store the value of the edge in the child 
            for (int bit = 1; bit < LOG; bit++)
                anc[v][bit] = anc[anc[v][bit - 1]][bit - 1];
            dfs(v, adj, u);
        }
        E[u] = timer;
        FT[timer++] = u;
    }

    void dfs(int u, const vector < vector < int > >& adj, int p = -1) {
        S[u] = timer;
        FT[timer++] = u;
        for (auto& v : adj[u]) {
            if (v == p) continue;
            dep[v] = dep[u] + 1;
            anc[v][0] = u;
            for (int bit = 1; bit < LOG; bit++)
                anc[v][bit] = anc[anc[v][bit - 1]][bit - 1];
            dfs(v, adj, u);
        }
        E[u] = timer;
        FT[timer++] = u;
    }

    int kthAncestor(int u, int k) const {
        if (dep[u] < k)
            return -1;
        for (int bit = LOG - 1; bit >= 0; bit--)
            if (k & (1 << bit))
                u = anc[u][bit];
        return u;
    }

    int getLCA(int u, int v) const {
        if (dep[u] < dep[v])
            swap(u, v);
        u = kthAncestor(u, dep[u] - dep[v]);
        if (u == v)
            return u;
        for (int bit = LOG - 1; bit >= 0; bit--)
            if (anc[u][bit] != anc[v][bit])
                u = anc[u][bit], v = anc[v][bit];
        return anc[u][0];
    }

    void setRange(Query& q) {
        while (curr_l > q.l) operation(--curr_l);
        while (curr_r < q.r) operation(++curr_r);
        while (curr_l < q.l) operation(curr_l++);
        while (curr_r > q.r) operation(curr_r--);
    }

    inline void add(int u){
        
    }

    inline void remove(int u){

    }

    inline void operation(int idx) {
        // if values added twice remove it ! 
        int u = FT[idx];
        nodeFreq[u] ^= 1;
        if (nodeFreq[u] == 1) {
            // add u to the path
            add(u);
        } else {
            // remove u from the path
            remove(u);
        }
    }

    int calcLog(int max_n) const {
        int log = 0;
        while ((1 << log) <= max_n) log++;
        return log;
    }

    int calcHilbertPow(int max_n) const {
        int pow = 0;
        while ((1 << pow) < max_n) pow++;
        return pow;
    }
};