class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int,int>>> adj(n+1);
        for(auto &it: times) {
            adj[it[0]].push_back({it[1], it[2]});
        }

        vector<int> signal(n+1, 1e9);
        signal[k] = 0;

        // Min-heap: {cost, node}
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
        pq.push({0, k});

        while(!pq.empty()) {
            auto [cost, node] = pq.top(); pq.pop();

            if(cost > signal[node]) continue; // already found better path

            for(auto [adjnode, w] : adj[node]) {
                if(cost + w < signal[adjnode]) {
                    signal[adjnode] = cost + w;
                    pq.push({signal[adjnode], adjnode});
                }
            }
        }

        int ans = *max_element(signal.begin()+1, signal.end());
        return (ans == 1e9) ? -1 : ans;
    }
};
