class Solution {
public:
    unordered_map<int, int> shortestPath(int n, vector<vector<int>>& edges, int src) {
        
        unordered_map<int, vector<pair<int, int>>> adj;

        for (auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int wt = edge[2];
            adj[u].push_back({v, wt});
        }

        priority_queue<
            pair<int, int>, 
            vector<pair<int, int>>, 
            greater<pair<int, int>>> pq;

        pq.push({0, src});

        unordered_map<int, int> shortest;

        while (!pq.empty()) {
            auto [w1, n1] = pq.top();
            pq.pop();

            if (shortest.find(n1) != shortest.end()) {
                continue;
            }

            shortest[n1] = w1;

            if (adj.find(n1) != adj.end()) {
                for (auto& [n2, w2] : adj[n1]) {
                    if (shortest.find(n2) == shortest.end()) {
                        pq.push({w1 + w2, n2});
                    }
                }
            }
        }

        for (int i = 0; i < n; i++) {
            if (shortest.find(i) == shortest.end()) {
                shortest[i] = -1;
            }
        }

        return shortest;
    }
};
