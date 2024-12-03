/*
        - Count number of subsequence That xor values = X between L ,  R : 
                1) check if that Xor Value can be formed first 
                2) if can be formed 
                        ans = pow [R-L+1  - Xor basis size ]

*/


const int N = 1e6 + 10, LOG_K = 30;
 
int basis[LOG_K], sz;
 
void insertVector(int mask) {
	for (int i = LOG_K - 1; i >= 0; i--) {
		if ((mask & 1 << i) == 0) continue;
 
		if (!basis[i]) {
			basis[i] = mask;
			sz++;
 
			return;
		}
 
		mask ^= basis[i];
	}
}
 
bool checkXor(int mask) {
        for (int i = LOG_K - 1; i >= 0; i--) {
		if ((mask & 1 << i) == 0) continue;
 
		if (!basis[i]) {
 
			return false ;
		}
 
		mask ^= basis[i];
	}
	return true;
}
int query(int k) {
        //  print the 𝑘 'th smallest number from 𝑋
        // k = 0 smallest 
	int mask = 0;
 
	int tot = 1 << sz;
	for (int i = LOG_K - 1; i >= 0; i--)
		if (basis[i]) {
			int low = tot / 2;
                        // first condition ; 
                        // ken K > low maneha najam nokhou l ith bit w nwali greater than   "low" values ( khater mandhomch l bit set )

                        // second condition 
                        // else , malezmch nokhdh l ith bit, w kenou deja set amalou reset , khater malezmnich nkoun akbar men "low values "! 
			if ((low < k && (mask & 1 << i) == 0) ||
				(low >= k && (mask & 1 << i) > 0)) mask ^= basis[i];
 
			if (low < k) k -= low;
 
			tot /= 2;
		}
 
	return mask;
}

int getmax(){
        int ans = 0 ;
        for (int i = LOG_K - 1; i >= 0; i--) {
            if (!basis[i]) continue;

            if (ans & 1 << i) continue;

            ans ^= basis[i];
	    }
        return ans ; 
}



struct Node{
    	int basis[LOG],sz,lazy;
	bool islazy;
	Node(){
		lazy = -1;
		sz = 0;
		islazy = false;
		fill(basis,basis+LOG,0);
	}
	Node(int x){
		lazy = -1;
		sz = 0;
		islazy = false;
		fill(basis,basis+LOG,0);
		for(int i = LOG-1;i>=0;i--){
			if(x & (1<<i)){
				basis[i] = x;
				break;
			}
		}
	}
	void insert(int mask){
		for(int i = LOG-1;i>=0;i--){
		if(mask & (1<<i)){
			if(basis[i] == 0){
			basis[i] = mask;
			sz++;
			break;
			}
			mask ^= basis[i];
		}
		}
	}
	void pull (const Node &lt,const Node &rt){
		lazy = -1;
		sz = 0;
		islazy = false;
		fill(basis,basis+LOG,0);
		for(int i = 0;i<LOG;i++){
		if(lt.basis[i])
			insert(lt.basis[i]);
		if(rt.basis[i])
			insert(rt.basis[i]);
		}
	}
	void apply(int l , int r ){
		vector <int> tmp;
		for(int i = 0;i<LOG;i++){
		if(basis[i])
			tmp.push_back(basis[i] & lazy);
		}
		fill(basis,basis+LOG,0);
		sz = 0;
		for(auto it:tmp){
		insert(it);
		}
		islazy = false;
		lazy = -1;
	}
};

// https://codeforces.com/blog/loyalixa


