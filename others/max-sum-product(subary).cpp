int maxProductSubArray(vector<int> &arr) {
    int n = arr.size(); //size of array.
    // idea is if we have even numbers we will delete in and get 2 subparts ( prefix and suufix )
    int pre = 1, suff = 1;
    int ans = __LONG_LONG_MIN__;
    for (int i = 0; i < n; i++) {
        if (pre == 0) pre = 1LL;
        if (suff == 0) suff = 1LL;
        pre *= arr[i];
        suff *= arr[n - i - 1];
        ans = max(ans, max(pre, suff));
    }
    return ans;
}


int subarraymax (vector<int>& vect) {
    int final_answer = vect[0];
    int current_answer = vect[0];

    for (int i = 1; i < vect.size(); ++i) {
        current_answer = max(vect[i], current_answer + vect[i]);
        final_answer = max(final_answer, current_answer);
    }
    return final_answer ;
}