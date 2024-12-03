vector<int> ADJ[N];
int colors[N];
auto is_bipartite =[&] (int ind) -> bool {
        colors[ind]=1; // bleu = 1;
        queue<int> q;
        q.push(ind);
        while(!q.empty()){
            int parent=q.front();
            q.pop();
            for ( auto child :ADJ[parent]){
                if (!colors[child]){
                    if (colors[parent] == 1)
                        colors[child] = 2; // parent bleu , child red
                    else
                        colors[child] = 1; // parent red , child bleu
                    q.push(child);
                }
                else if (  colors[child] == colors[parent])
                    return 0;
            }
        }
 
    return 1;
};