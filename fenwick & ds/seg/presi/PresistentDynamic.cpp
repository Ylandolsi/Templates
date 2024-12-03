// https://ideone.com/xcNps8 example used on tree ! , roots[i] = merge ( roots[par],  ...  ); https://www.spoj.com/problems/COT/



// clasic : roots[i] sorte all thelement that are in array indicies [0 , i ]

// we can sort thee array and make roots[i] store all the elements that <= i 



const int MAXND = N * 40; // N * log  heja ki kek !
struct node {
    int val ;
    int occ ; 
    int lchild;
    int rchild ;
    node (){
        val =  0 , occ = 0 , lchild = -1 , rchild = -1 ; 
    } 
    node  (int v , int oc , int lch , int rch ) {
        val = v , occ = oc , lchild = lch , rchild = rch ; 
    }
    
};
template <typename NODE>
class PresistentDynamic {
   public:
    NODE vals[MAXND],   defautl_value = NODE();
    int ndcnt = 0;

    void init() { ndcnt = 0; }

    int addnode() {
        vals[ndcnt] = NODE(); 
        return ndcnt++;
    }
    int left(int u) { return u == -1? u :  vals[u].lchild; }
    int right(int u) { return u == -1 ? u : vals[u].rchild ;  };

    // T mrg(T u, T v) { return u + v; }

    int getval(int nd) {
        if (nd != -1) {
            return vals[nd].val;
        }
        return 0; // CHANGE IT IF NECESSARY 
    }

    void pull_up(int& nd) {
        vals[nd].val = getval(left(nd)) ^ getval(right(nd));
    }
    void apply(int old_idx, int new_idx,   int  v  ) {
        vals[new_idx].val =  v ^ getval(old_idx)   ; 
    }



    template <typename... M>
    int modify(int cur, int p, int l, int r, bool inplace, const M&... v) {
        if (l == r) {
            int idx = cur; // inplace = 0 means create a new segtree ! ( modify (root[i-1] , a[i] , BOUNDARYL , BOUNDARYRs, 0 (inplace) , add value ! ))
            // what does that mean inplace = 0 , tched ekher segment tree amaltha w tamaleha copy w tasnfa3 valeur jdid 
            // if u want to acces segment tree from [1 , i] , current = root[i] !
            
            //             else modify already existent seg tree 
            if (cur == -1 || !inplace) {
                idx = addnode();
            }
            apply(cur, idx, v...);
            return idx;
        }
        int idx = cur;
        if (cur == -1 || !inplace) {
            idx = addnode();
        }
        int md = l + (r - l) / 2;
        if (p <= md) {
            vals[idx].lchild = modify(left(cur), p, l, md, inplace, v...);
            vals[idx].rchild = right(cur);
        } else {
            vals[idx].lchild = left(cur);
            vals[idx].rchild = modify(right(cur), p, md + 1, r, inplace, v...);
        }
        pull_up(idx);
        return idx;
    }
        // query on values >= qs && values  <= qe
    NODE get(int cur, int qs, int qe, int l, int r) { // l , r always fixed ! ( boundaries of our seg tree !!!)
        if (cur == -1) {
            return defautl_value;
        }
        if (qs <= l && qe >= r) {
            return getval(cur);
        }
        int md = l + (r - l) / 2;
        if (qe <= md) {
            return get(left(cur), qs, qe, l, md);
        } else if (qs > md) {
            return get(right(cur), qs, qe, md + 1, r);
        } else {
            return mrg(get(left(cur), qs, qe, l, md),
                       get(right(cur), qs, qe, md + 1, r));
        }
    }

    NODE getkth(int lnd, int rnd, int k, int l, int r) {// l , r always fixed ! ( boundaries of our seg tree !!!)
        if (l == r) {
            return l;
        }
        int lsum = getval(left(rnd)) - getval(left(lnd)); // check goibng to left nodes before ( if answer dosent exist there)
                                                        // go to right node ! 
        int md = l + (r - l) / 2;
        if (lsum >= k) {
            return getkth(left(lnd), left(rnd), k, l, md);
        }
        return getkth(right(lnd), right(rnd), k - lsum, md + 1, r);
    }

    NODE getkthInPathTree(int ndu, int ndv, int ndlc, int vallc, int k, int l,
                       int r) {
        if (l == r) {
            return l;
        }
        int md = l + (r - l) / 2;
        int lsum = getval(left(ndu)) + getval(left(ndv)) -
                   2 * getval(left(ndlc)) + (vallc <= md);

        if (lsum >= k) {
            return getkth(left(ndu), left(ndv), left(ndlc), vallc, k, l, md);
        }
        return getkth(right(ndu), right(ndv), right(ndlc), vallc, k - lsum, md + 1,
                      r);
    }
    NODE getMex(int lnd, int rnd, int l, int r) {
        if (l == r) {
            return l;
        }
        int lsum = getval(left(rnd)) - getval(left(lnd));
        int md = l + (r - l) / 2;
        if (lsum != (md - l + 1)) {
            return getkth(left(lnd), left(rnd), l, md);
        }
        return getkth(right(lnd), right(rnd), md + 1, r);
    }
    NODE getMexInverse(int lnd, int rnd, int l, int r) {
        if (l == r) {
            return l;
        }
        int rsum = getval(right(rnd)) - getval(right(lnd));
        int md = l + (r - l) / 2;
        if (rsum == (r - md)) {
            return getkth(left(lnd), left(rnd), l, md);
        }
        return getkth(right(lnd), right(rnd), md + 1, r);
    }




     int firstDiff(int nl, int nr, int qs, int qe, int l, int r) {
        if (qs > r || qe < l) return -1;
        if (qs <= l && qe >= r) {
            if (/*not condition */) {
                return -1;
            }
        }
        if (l == r) {
            return l;
        }
        int md = l + (r - l) / 2;
        int x = firstDiff(lch[nl], lch[nr], qs, qe, l, md);
        if (x == -1) {
            return firstDiff(rch[nl], rch[nr], qs, qe, md + 1, r);
        }
        return x;
    }
};

// dont u ever use left < 0 , if u need negative values shift all of them to positve !


// PresistentDynamic<node> sg;
// sg.init();
// root[0] = addnode();
// for ( int i = 1 ; i <= n ; i++ ){
//         roots[i] = modify(root[i-1] , curentval = a[i] , boundaryL , boundaryR  , inplace = 0 ,      val to add ) 

// }
// acess seg tre of values from [1 , i ]

// sg.get ( roots[i] , Left , Right ,  boundaryL , boundaryR)
// [left , Right ] values u want to query on in this interval

// !! dont forget [left , right ] represents values not indicies !!! 









// https://github.com/Mtaylorr/Competitive-programming-Solutions/blob/main/DS/Segment%20Tree/dynamic%20persistent%20segment%20tree/Template.cpp
// https://codeforces.com/group/YTYmnVxV00/contest/568776/my# example (F league of coders )

// https://codeforces.com/problemset/problem/1771/F mtaylor solution 