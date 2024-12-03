vector<int> arr(n);
vector<int> stk;
vector<int> used(n);
auto rec = [&](auto rec, int n, int i)
{
    if (n == i)
    {
        for (int t : stk) cout << t << " ";
        cout << endl;
        return;
    }
    for (int j = 0; j < n; j++)
    {
        if (!used[j])
        {
            used[j] = 1;
            stk.push_back(arr[j]);
            rec(rec, n, i + 1);
            used[j] = 0;
            stk.pop_back();
        }
    }
};
rec(rec, n, 0);