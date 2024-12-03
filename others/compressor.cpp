https://codeforces.com/contest/1915/submission/239420133

struct Compressor {
    vector<int> values;
    int n;
    void init() {
        values.clear();
        n = 0;
    }
    void add(int x) { values.push_back(x); }
    void run() {
        sort(all(values));
        values.resize(unique(all(values)) - values.begin());
        n = values.size();
    }
    int compress(int x) { return lower_bound(all(values), x) - values.begin(); }
    int greatestSmallerThanOrEqual(int x) {
        return (upper_bound(all(values), x) - values.begin()) - 1;
    }
    int greaterThanOrEqual(int x) {
        return (lower_bound(all(values), x) - values.begin());
    }
    int decompress(int p) { return values[p]; }
} compressor;



template <typename T>
vector<T> uniqued(vector<T> v) {
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    return v;
}


template <typename T>
vector<int> compressed_index(vector<T> v) {
    const int n = v.size();
    const vector<T> c = uniqued(v);
    vector<int> res(n);
    for (int i = 0; i < n; ++i) {
        res[i] = lower_bound(c.begin(), c.end(), v[i]) - c.begin();
    }
    return res;
}

// { value, count }
template <typename T>
pair<vector<T>, vector<int>> compressed_pair(vector<T> v) {
    size_t n = v.size();
    sort(v.begin(), v.end());
    vector<T> cnt, val;
    cnt.reserve(n);
    val.reserve(n);
    int now_cnt = 1;
    for (size_t i = 1; i < n; ++i) {
        if (v[i - 1] != v[i]) {
            cnt.push_back(now_cnt);
            val.push_back(v[i - 1]);
            now_cnt = 1;
        } else
            ++now_cnt;
    }
    cnt.push_back(now_cnt);
    val.push_back(v.back());

    return {val, cnt};
}