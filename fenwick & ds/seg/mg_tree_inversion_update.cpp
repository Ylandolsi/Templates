// https://codeforces.com/group/YTYmnVxV00/contest/520855/submission/259002875
// problem G && code&quener
template <class T, class C = less<T>>
using ordered_set = tree<T, null_type, C, rb_tree_tag, tree_order_statistics_node_update>; 
struct SegTree {
  public:
  int n;
  vector<ordered_set<pair<int, int>>> st;
    vi a ;
  SegTree(int _n, vi ar) : n(_n) {
    st.resize(4 * n);
    a = ar;
  }
 
  void build(int v, int l, int r) {
    if (l == r) {
      st[v].insert({a[l], l});
      return ;
    }
 
    int mid = l + (r - l) / 2;
    build(v * 2, l, mid);
    build(v * 2 + 1, mid + 1, r);
    for (auto ptr : st[v * 2]) {
      st[v].insert(ptr);
    }
    for (auto ptr : st[v * 2 + 1]) {
      st[v].insert(ptr);
    }
  }
 
  void update(int v, int l, int r, int pos, int nv) {
    if (l < r) {
        int mid = l + (r - l) / 2;
        if (pos <= mid) {
            update(v * 2, l, mid, pos, nv);
        } else {
            update(v * 2 + 1, mid + 1, r, pos, nv);
        }
    }
    int rank = st[v].order_of_key({a[pos], pos});//Number of elements that are less than v in t
    auto  ptr = st[v].find_by_order(rank); //
    st[v].erase(ptr);
    st[v].insert({nv, pos});
  }
 
  int get(int v, int l, int r, int low, int high, int pos, bool type) {
    if (l == low && r == high) {
      if (type) {
        // count element bigger than a[pos] to left  
        return (int) st[v].size() - st[v].order_of_key(make_pair(a[pos], 12345678));
      } else {
        // count elements smaller than  a[pos] to right 
        int x= st[v].order_of_key(make_pair(a[pos], -1));
        return x;
      }
    }
 
    int mid = l + (r - l) / 2;
    if (high <= mid) {
      return get(v * 2, l, mid, low, high, pos, type);
    } else if (low > mid) {
      return get(v * 2 + 1, mid + 1, r, low, high, pos, type);
    } else {
      return get(v * 2, l, mid, low, mid, pos, type) +
         get(v * 2 + 1, mid + 1, r, mid + 1, high, pos, type);
    }
  };
};


/*
or it can be done with treap !
https://pastebin.com/BijJZKyh
*/