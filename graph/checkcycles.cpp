// find cycle in undirected && directed both graph !
// or maybe directed only jsp confirm that ! 

vector<char> used(n, 0);
        vector<int> cyc;
        vector<int> par(n);
        function<bool(int, int)> dfs = [&](int v, int p) {
                par[v] = p;
                used[v] = 1;
                for (int x : adj[v]) {
                        if (x == p) {
                                continue;
                        }
                        if (used[x] == 2) {
                                continue;
                        }
                        if (used[x]) {
                                for (int y = v; y != x; y = par[y]) {
                                        cyc.push_back(y);
                                }
                                cyc.push_back(x);
                                return true;
                        }
                        if (dfs(x, v)) {
                                return true;
                        }
                }
                used[v] = 2;
                return false;
        };
dfs(0, 0);





// undirect graph check cycle 
bool isCyclicUtil(int v,  int parent) {
    // Mark the current node as visited
    visited[v] = true;

    // Recur for all the vertices
    // adjacent to this vertex
    for (int i : adj[v]) {
        // If an adjacent vertex is not visited,
        // then recur for that adjacent
        if (!visited[i]) {
            if (isCyclicUtil(i, v))
                return true;
        }
        // If an adjacent vertex is visited and
        // is not parent of current vertex,
        // then there exists a cycle in the graph.
        else if (i != parent)
            return true;
    }
    return false;
}

// Returns true if the graph contains
// a cycle, else false.
bool isCyclic(int V, vector<vector<int>>& adj) {
    bool* visited = new bool[V]{false};

    for (int u = 0; u < V; u++) {
        if (!visited[u])
            if (isCyclicUtil(u, -1))
                return true;
    }
    return false;
}






/* find cycle in directed graph*/

	bool dfsCheck(int node, vector<int> adj[], int vis[], int pathVis[]) {
		vis[node] = 1;
		pathVis[node] = 1;

		// traverse for adjacent nodes
		for (auto it : adj[node]) {
			// when the node is not visited
			if (!vis[it]) {
				if (dfsCheck(it, adj, vis, pathVis) == true)
					return true;
			}
			// if the node has been previously visited
			// but it has to be visited on the same path
			else if (pathVis[it]) {
				return true;
			}
		}

		pathVis[node] = 0;
		return false;
	}

	// Function to detect cycle in a directed graph.
	bool isCyclic(int V, vector<int> adj[]) {
		int vis[V] = {0};
		int pathVis[V] = {0};

		for (int i = 0; i < V; i++) {
			if (!vis[i]) {
				if (dfsCheck(i, adj, vis, pathVis) == true) return true;
			}
		}
		return false;
	}







