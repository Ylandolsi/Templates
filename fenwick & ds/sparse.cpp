template<typename T, class CMP = function<T(const T &, const T &)>>
class SparseTable {
public:
    int n{};
    vector<vector<T>> sp;
    CMP func;
 
    void build(const vector<int> &a, const CMP &f) {
        func = f;
        n = static_cast<int>(a.size());
        int max_log = 32 - __builtin_clz(n);
        sp.resize(max_log);
        sp[0].resize(n+1);
        sp[0] = a;
        /*
            or we can make it vector<vector<pair<int,int>> sp ; 
            for ( int i = 0 ; i < n ; i++ ){
                sp[0][i] = {a[i], i}; 
            }
        */
        for (int j = 1; j < max_log; ++j) {
            sp[j].resize(n - (1 << j) + 1);
            for (int i = 0; i <= n - (1 << j); ++i) {
                sp[j][i] = func(sp[j - 1][i], sp[j - 1][i + (1 << (j - 1))]);
            }
        }
    }
 
    T query(int l, int r) const { // [ l, r ]
        int lg = 32 - __builtin_clz(r - l + 1) - 1;
        return func(sp[lg][l], sp[lg][r - (1 << lg) + 1]);
    }
};
inline int f1(int a, int b) { return max(a, b);};
inline int f2(int a, int b) { return min(a, b);};
// SparseTable<int> sp;
