class Solution {
public:
    unordered_map<int, int> shortestPath(int n, vector<vector<int>>& edges, int src) {
        
        unordered_map<int, vector<pair<int, int>>> adj;
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            adj[u].push_back({v, w});
        }

        priority_queue<
        pair<int, int>, 
        vector<pair<int, int>>, 
        greater<pair<int, int>>> minHeap;
        
        minHeap.push({0, src});

        unordered_map<int, int> shortest;

        while (!minHeap.empty()) {
            auto [w1, n1] = minHeap.top();
            minHeap.pop();

            if (shortest.find(n1) != shortest.end()) {
                continue;
            }

            shortest[n1] = w1;

            if (adj.find(n1) != adj.end()) {
                for (const auto& [n2, w2] : adj[n1]) {
                    if (shortest.find(n2) == shortest.end()) {
                        minHeap.push({w1 + w2, n2});
                    }
                }
            }
        }

        // 3. Fill in unreachable nodes with -1 as required
        for (int i = 0; i < n; i++) {
            if (shortest.find(i) == shortest.end()) {
                shortest[i] = -1;
            }
        }

        return shortest;
    }
};
