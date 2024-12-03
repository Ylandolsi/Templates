auto find_d = [&](int v) {
                vector<int> d(n, -1);
                queue<int> q;
                d[v] = 0;
                q.push(v);
                while (!q.empty()) {
                        int u = q.front();
                        q.pop();
                        for (int x : adj[u]) {
                                if (d[x] == -1) {
                                        d[x] = d[u] + 1;
                                        q.push(x);
                                }
                        }
                }
                return d;
        };