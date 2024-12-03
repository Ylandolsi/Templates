https://github.com/mitkonikov/competitive/blob/main/Segment%20Trees/D_-_All_Assign_Point_Add.cpp
https://www.youtube.com/watch?v=PBd85U_C9uk



const ll inf = 1e9;
struct Node {
	// r not included !
	Node *l = 0, *r = 0;
	ll lo, hi, mset = inf, madd = 0, val = -inf;

    void merge() {
        val = max(l->val, r->val);
    }
    
	void push() {
		if (!l) {
			ll mid = lo + (hi - lo) / 2;
			l = new Node(lo, mid);
            r = new Node(mid, hi);
		}
		if (mset != inf)
			l->set(lo,hi,mset), r->set(lo,hi,mset), mset = inf;
		else if (madd)
			l->add(lo,hi,madd), r->add(lo,hi,madd), madd = 0;
	}

    // Constructors
	Node(ll lo,ll hi):lo(lo),hi(hi){} // Large llerval of -inf
	Node(vector<ll>& v, ll lo, ll hi) : lo(lo), hi(hi) {
		if (lo + 1 < hi) {
			ll mid = lo + (hi - lo)/2;
			l = new Node(v, lo, mid);
            r = new Node(v, mid, hi);
			merge();
		}
		else val = v[lo];
	}

	ll query(ll L, ll R) {
		if (R <= lo || hi <= L) return -inf;
		if (L <= lo && hi <= R) return val;
		push();
		return max(l->query(L, R), r->query(L, R));
	}
	void set(ll L, ll R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
            mset = val = x, madd = 0;
            return;
        }
        push();
        l->set(L, R, x);
        r->set(L, R, x);
        merge();
	}
	void add(ll L, ll R, ll x) {
		if (R <= lo || hi <= L) return;
		if (L <= lo && hi <= R) {
			if (mset != inf) mset += x;
			else madd += x;
			val += x;
		} else {
			push();
            l->add(L, R, x);
            r->add(L, R, x);
			merge();
		}
	}
};


