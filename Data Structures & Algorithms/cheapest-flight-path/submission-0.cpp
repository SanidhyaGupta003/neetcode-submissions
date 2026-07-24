class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        
        // 1. Build adjacency list: node -> list of {neighbor, price}
        vector<pair<int, int>> adj[n];
        for (auto &it : flights) {
            adj[it[0]].push_back({it[1], it[2]});
        }

        // 2. Queue stores {stops, {node, cost}}
        queue<pair<int, pair<int, int>>> q;
        q.push({0, {src, 0}});

        vector<int> dist(n, INT_MAX);
        dist[src] = 0;

        while (!q.empty()) {
            auto it = q.front();
            q.pop();

            int stops = it.first;
            int node = it.second.first;
            int cost = it.second.second;

            // If stops exceed k, do not expand further
            if (stops > k) continue;

            for (auto neighbour : adj[node]) {
                int adjNode = neighbour.first;
                int edgeWt = neighbour.second;

                // Relax edge if a cheaper path to adjNode is found within allowed stops
                if (cost + edgeWt < dist[adjNode] && stops <= k) {
                    dist[adjNode] = cost + edgeWt;
                    q.push({stops + 1, {adjNode, cost + edgeWt}});
                }
            }
        }

        return dist[dst] == INT_MAX ? -1 : dist[dst];
    }
};
