template<typename T>
struct Fenwick {
    int sz ; 
    //T data[N];
    vector<T> data;
    Fenwick(int n = 0) { sz = n ; build(n); }
    void build(int n) {
        // fill(bit, bit + sz + 1, 0);
         data.assign(n+1, T{});
    }
    // Sum on segment [0, r]:
    T sum(int r) const {
        assert(r < (int)data.size());
        T result = 0;
        for (; r >= 0; r = (r & (r+1)) - 1)
            result += data[r];
        return result;
    }
	/** Sets the value at index ind to val. */
    void set(int ind, T val) { inc(ind, val - data[ind]); }
    // Increase value on position `ind` by delta:
    void inc(int ind , T delta) {
        assert(p >= 0);
        for (; p < (int)data.size(); p = (p | (p+1)))
            data[p] += delta;
    }
    // Sum on segment [l, r]:
    T sum (int l, int r) const { return sum(r) - ( l  > 0 ?  sum(l-1) : 0 )  ; }
    
};