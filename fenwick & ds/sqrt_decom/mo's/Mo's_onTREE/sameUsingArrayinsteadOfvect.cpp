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
            //calcOrder(HilbertPow);
        }

        //void calcOrder(int hilbert_pow) {
          //  ord = MoTree::hilbertOrder(l, r, hilbert_pow, 0);
        //}

        // bool operator < (const Query& rhs) const {
        //     return ord < rhs.ord;
        // }
        bool operator < (const Query& rhs) const {
            if ( l/SQ != rhs.l /SQ ){
                return l/SQ < rhs.l/SQ; 
            }
            if ( (l/SQ) & 1 ){
                return r > rhs.r;
            } 
            else {
                r < rhs.r ; 
            }
        }
    };

    MoTree(  int root = 1) 
        : curr_l(1), curr_r(0), timer(1), ans(0)  {
        dfs(root);
        // helbertPow = calcHilbertPow(2 * n + 1); 
    }

    // static inline int64_t hilbertOrder(int x, int y, int pow, int rotate) {
    //     if (pow == 0) return 0;
    //     int hpow = 1 << (pow - 1);
    //     int seg = (x < hpow) ? ((y < hpow) ? 0 : 3) : ((y < hpow) ? 1 : 2);
    //     seg = (seg + rotate) & 3;
    //     const int rotateDelta[4] = {3, 0, 0, 1};
    //     int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
    //     int nrot = (rotate + rotateDelta[seg]) & 3;
    //     int64_t subSquareSize = int64_t(1) << (2 * pow - 2);
    //     int64_t ordd = seg * subSquareSize;
    //     int64_t add = hilbertOrder(nx, ny, pow - 1, nrot);
    //     ordd += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
    //     return ordd;
    // }

    void getData() {
        for (int i = 0, u, v; i < m && cin >> u >> v; i++)
        {
            queries.emplace_back(u, v, i, getLCA(u, v), helbertPow);
            debug ( u , v  , i ); 
        }
        process();
    }

    void process() {
        sort(queries.begin(), queries.end());

        // start with the first query
        curr_l = queries[0].l, curr_r = queries[0].l - 1;
        debug( queries.size()); 
        for (auto& q : queries) {
            setRange(q);

            // if lca is -1 then the two nodes are in the same subtree
            if (~q.lca && !VAL_ON_EDGE) 
                add(q.lca);
            paa anse=  mn.query( 0 , N - 1   ) ;
            int ansp = -1 ;
            int mustbe = ( count_nodes ) / 2  + 1  ; 
            debug (q.l , q.r ,count_nodes,  mustbe , anse.first  , anse.second ); 
            if ( anse.first >= mustbe ){
                ansp = anse.second ; 
            }

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
        debug ( u , N , compressed[1] ) ;
        int comp = compressed[u] ; 
        mn.upd(comp , 1 ) ;

    }

    inline void remove(int u){
        count_nodes--;
        int comp = compressed[u] ; 
        mn.upd(comp , -1 ) ;
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

    int calcHilbertPow(int max_n) const {
        int pow = 0;
        while ((1 << pow) < max_n) pow++;
        return pow;
    }
};
