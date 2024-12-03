
// https://codeforces.com/blog/entry/126043?#comment-1119139
struct fwtree {
	// up to 1e9
	// maybe up to 1e18 also i dont know !

	// its a multiset , each element can be found multiples times !
	// but we are suppossing  it s a  set !
    static constexpr i64 N = 1 << 30;
    map<i64, int> t;
    void modify(i64 p) {
		// mark the element P !
        for (; p < N; p |= p + 1) {
            t[p] += 1;
        }
    }
    i64 get(i64 p) {
        i64 res = 0;
        for (; p >= 0; p = (p & (p + 1)) - 1) {
            res += t[p];
        }
        return res;
    }
    i64 get_kth(i64 k) {
		// gives u K-element not found 
		// 0 is included ,  fenwick is empty (get_kth(1) => 0 ) 
        i64 res = -1;
        for (int i = 30; i >= 0; --i) {
            if (k > (1 << i) - t[res + (1 << i)]) {
                k -= (1 << i) - t[res + (1 << i)];
                res += 1 << i;
            }
        }
        return res + 1;
    }
    i64 get_last(i64 l, i64 r) {
		// gives u biggest integer not found in fenwick tree
		// in the given range   [l , r ]
		// suppose fenwick tree have [3]
		// get_las(1,3) since 3 is found it will return 2
		// 2 = biggest interger not found in fenwick tree
		// and  1<= 2 <=3
        i64 ll = get(l - 1), rr = get(r);
        if (rr - ll == r - l + 1) {
            return -1; // not found !
        }
        return get_kth(r + 1 - rr);
    }
	/*
	how your fenwick tree is finding the kth non existing number ?
	
		It's similar to binary search. 
		what we want is the maximum index i s.t.
		the # numbers before i (inclusive) is smaller than k. 
		than i + 1 would be the kth number. If size of N = 1000: 
		initialize res = -1. you first try 512 if # numbers before 511 (== # of numbers between [0, 511])
		 is less than k, you add 512 to res and subtract (== # of numbers between [0, 511]) from k.
		  than you try 256, 128, 64, ... , 1.
	*/
};