// stores all possible subset sums in the interval [l, r]
auto get_subset_sums = [&](int l, int r) -> vector<int> {
        int len = r - l + 1;
        vector<int> res;

        // loop through all subsets
        for (int i = 0; i < (1 << len); i++) {
                int sum = 0;
                for (int j = 0; j < len; j++) {
                        if (i & (1 << j)) { sum += a[l + j]; }
                }
                res.push_back(sum);
        }

        return res;
};

vector<ints> left = get_subset_sums(0, n / 2 - 1);
vector<int> right = get_subset_sums(n / 2, n - 1);
sort(left.begin(), left.end());
sort(right.begin(), right.end());

int ans = 0;
for (int i : left) {
        auto low_iterator = lower_bound(right.begin(), right.end(), x - i);
        auto high_iterator = upper_bound(right.begin(), right.end(), x - i);
        ans += high_iterator - low_iterator;
}
