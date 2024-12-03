// O(V + E)
// only in directed graph ! 
 

// Function to return list containing vertices in
// Topological order.
vector<int> topologicalSort(vector<vector<int> >& adj,
                            int V)
{
    // Vector to store indegree of each vertex
    vector<int> indegree(V);
    for (int i = 0; i < V; i++) {
        for (auto it : adj[i]) {
            indegree[it]++;
        }
    }

    // Queue to store vertices with indegree 0
    queue<int> q;
    for (int i = 0; i < V; i++) {
        if (indegree[i] == 0) {
            q.push(i);
        }
    }
    vector<int> result;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        result.push_back(node);

        // Decrease indegree of adjacent vertices as the
        // current node is in topological order
        for (auto it : adj[node]) {
            indegree[it]--;

            // If indegree becomes 0, push it to the queue
            if (indegree[it] == 0)
                q.push(it);
        }
    }

    // Check for cycle
    if (result.size() != V) {
        cout << "Graph contains cycle!" << endl;
        return {};
    }

    return result;
}




// topo dfs
deque<int> res;
//or , vector<int>res;
void topsort(int node) {
    if (visite[node])
        return;
    visite[node] = true;
    act[node] = true;
    for (int ch : graph[node]) {
            if (act[ch]) cycle = false;
            topsort(ch);
    }
    act[node] = false;
    res.push_front(node);
    // res.pushback(node);
}
// if used pushback ! reverse(all(res));