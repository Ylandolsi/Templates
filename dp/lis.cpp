template<class I> vi lis(const vector<I>& S) {
	if (S.empty()) return {};
	vi prev((int)S.size());
    typedef pair<I, int> p;
	vector<p> res;
	for (int i = 0; i<S.size() ; i++ ) {
		// change 0 -> i for longest non-decreasing subsequence
		auto it = lower_bound(all(res), p{S[i], 0});
		if (it == res.end()) res.emplace_back(), it = res.end()-1;
		*it = {S[i], i};
		prev[i] = it == res.begin() ? 0 : (it-1)->second;
	}
	int L = (int)res.size(), cur = res.back().second;
	vi ans(L);
	while (L--) ans[L] = cur, cur = prev[cur];
	return ans;
    // return indicies 
    // vi a = {1 , 10 , 2 , 5 , 99 , 3  , 5 }; 
    // ans = [0 , 2 , 5 , 6 ] first element at index 0 , second element is at index 2 .. and so on 
}