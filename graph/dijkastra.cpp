struct info {
    int weight;
    int nd;
    bool operator<(const info& b) const  {
        // sorted increasing by weights cause it s priorty queue 
        return weight > b.weight;
    }
};

auto rundij = [&]( int current ) -> vector<int>{
        priority_queue<info> pq;

        vector<int> distTo(n) , vis(n);

        distTo[current] = 0;
        pq.push({0, current});

        while (!pq.empty())
        {
            auto [ node , dis ]  = pq.top();
            pq.pop();
            if ( vis[node])continue;
			vis[node] = 1;
            // whenever we visit it the first time 
            // its guranteed that s the shortest path ! 
			for (auto it : adj[node])
            {
                int v = it.first;
                int w = it.second;
                if (dis + w < distTo[v])
                {
                    distTo[v] = dis + w;
                    pq.push({dis + w, v});
                }
            }
        }
        return distTo;
    };