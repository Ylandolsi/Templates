https://marisaoj.com/submission/325136
const int N = 1e5 + 5 ; 
int answers[N];  // answer for queries !
int n , m;  // m query 
vector <int>adj[N]; 
int compressed[N] , colors[N]; // colros values of nodes ! 
int nodeFreq[N] , S[N] , E[N] , dep[N]; // frqof node , start , end , depth ! 
const int SQ = 300 , LOG = 17 ;
int anc[N][LOG]; 
int FlatTree[2*N +1 ] ; 


template < typename T = int , typename graphType = int , bool VAL_ON_EDGE = false >
class MoTree {
public:
    struct Query {
        int l, r, k, lca, queryIdx;
        int64_t ord;

        Query( int L = 0, int R = 0, int QueryIdx = 0, int LCA = 0, int HilbertPow = 0) {
            if (S[L] > S[R])
                swap(L, R);
            if (LCA == L)
                l = S[L] + VAL_ON_EDGE, r = S[R], lca = -1, queryIdx = QueryIdx;
            else
                l = E[L], r = S[R], lca = LCA, queryIdx = QueryIdx;
        }

        bool operator < (const Query& rhs) const {
            if ( l/SQ != rhs.l /SQ ) return l/SQ < rhs.l/SQ; 
            
            if ( (l/SQ) & 1 ) return r > rhs.r;
            
            else  r < rhs.r ; 
            
        }
    };

    MoTree(  int root = 1) 
        : curr_l(1), curr_r(0), timer(1), ans(0)  {
        dfs(root);
    }


    void getData() {
        for (int i = 0, u, v; i < m && cin >> u >> v; i++)
        {
            queries.emplace_back(u, v, i, getLCA(u, v), helbertPow);
        }
        process();
    }

    void process() {
        sort(queries.begin(), queries.end());

        // start with the first query
        curr_l = queries[0].l, curr_r = queries[0].l - 1;
        for (auto& q : queries) {
            setRange(q);


            // GET ANS : 


            // if lca is -1 then the two nodes are in the same subtree
            if (~q.lca && !VAL_ON_EDGE) 
                add(q.lca);

            
            int ansp = sg.query(0,N) ;

            answers[q.queryIdx] = ansp;
        
            if (~q.lca && !VAL_ON_EDGE) 
                remove(q.lca);
        }
    }



private:
    int curr_l, curr_r, timer, helbertPow;
    int count_nodes = 0 , dom = 0 ; 
    T ans;
    vector < Query > queries;
    


    void dfs(int u, int p = -1) {
        S[u] = timer;
        FlatTree[timer++] = u;
        for (auto& v : adj[u]) {
            if (v == p) continue;
            dep[v] = dep[u] + 1;
            anc[v][0] = u;
            for (int bit = 1; bit < LOG; bit++)
                anc[v][bit] = anc[anc[v][bit - 1]][bit - 1];
            dfs(v,  u);
        }
        E[u] = timer;
        FlatTree[timer++] = u;
    }
    /*
    weighted graph 
        void dfs(int u,  int p = -1) {
            S[u] = timer;
            FlatTree[timer++] = u;
            for (auto& [v, w] : adj[u]) {
                if (v == p) continue;
                dep[v] = dep[u] + 1, anc[v][0] = u, colors[v] = w;
                for (int bit = 1; bit < LOG; bit++)
                    anc[v][bit] = anc[anc[v][bit - 1]][bit - 1];
                dfs(v, u);
            }
            E[u] = timer;
            FlatTree[timer++] = u;
        }

    */
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
        count_nodes++ ;
        int comp = compressed[u] ; 
        sg.upd(comp , 1 ) ;

    }

    inline void remove(int u){
        count_nodes--;
        int comp = compressed[u] ; 
        sg.upd(comp , -1 ) ;
    }

    inline void operation(int idx) {
        int u = FlatTree[idx];
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
};
