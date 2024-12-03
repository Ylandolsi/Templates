
struct BinaryTrie {
 
    struct Node {
        array<int, 2> child;
        int cnt;
 
        Node() {
            cnt = 0;
            child[0] = -1;
            child[1] = -1;
        }
    };
 
    vector<Node> t;
 
    BinaryTrie() {
        t.emplace_back();
        add(0); // a[i] xor nothing = a[i]
    };
 
    void create_children(int i) {
        if (t[i].child[0] > -1) return;
 
        for (int idx = 0; idx < 2; idx++) {
            t[i].child[idx] = t.size();
            t.emplace_back();
            // mouch lezem nasn3ou 2 childs mta 1 0 najmou nas3ou eli meshinlou kahaw  
            // ama maykalkch khater l khedm lkol al variable count !! 
        }
    }
 
    void add(int x) {
        int idx = 0;
 
        for (int bit = 30; bit >= 0; bit--) {
            create_children(idx);
            int visit = (x & (1 << bit)) > 0;
            idx = t[idx].child[visit];
            t[idx].cnt++;
        }
    }
    // idx should be 1 i guess !
    void remove(int x, int bit , int idx = 0 ) { // REMOVE BITS OF INTEGER x FROM TRIE
        t[idx].cnt--;
        int visit = (x & (1 << bit)) > 0;
        create_children(idx);
        if (t[t[idx].child[visit]].cnt > 0) // OCCURENCE OF THE NEXT 
            remove( x, bit - 1 , t[idx].child[visit] );
    }
 
    int Max_xor(int x) { // max U xor X       // we can do the same for max_and 
        int idx = 0;
        int res = 0;
        for (int bit = 30 ; bit >= 0; bit--) {
            int visit = ((x & (1 << bit)) > 0) ^ 1;
 
            create_children(idx);
 
            if (t[t[idx].child[visit]].cnt > 0) {
                res |= (1 << bit);
                idx = t[idx].child[visit];
            } else {
                idx = t[idx].child[visit ^ 1];
            }
        }
 
        return res;
    }
};