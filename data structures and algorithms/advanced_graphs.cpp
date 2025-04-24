#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <queue>

using namespace std;

class Advanced_Graphs {
public:
    // Constructors & Assignment
    Advanced_Graphs() {}
    ~Advanced_Graphs() {}
    Advanced_Graphs(const Advanced_Graphs& other) = default;
    Advanced_Graphs(Advanced_Graphs&& other) noexcept = default;
    Advanced_Graphs& operator=(const Advanced_Graphs& other) = default;
    Advanced_Graphs& operator=(Advanced_Graphs&& other) noexcept = default;

    // 1. reconstruct itinerary:
    // You are given a list of flight tickets tickets where tickets[i] = [from_i, to_i] represent the source airport and the destination airport.

    // Each from_i and to_i consists of three uppercase English letters.

    // Reconstruct the itinerary in order and return it.

    // All of the tickets belong to someone who originally departed from "JFK". Your objective is to reconstruct the flight path that this person took, assuming each ticket was used exactly once.

    // If there are multiple valid flight paths, return the lexicographically smallest one.

    // For example, the itinerary ["JFK", "SEA"] has a smaller lexical order than ["JFK", "SFO"].
    // You may assume all the tickets form at least one valid flight path.

    class Solution {
    public:
        vector<string> findItinerary(vector<vector<string>>& tickets) {
            unordered_map<string, deque<string>> adj;
            for (auto& ticket : tickets) {
                adj[ticket[0]].push_back(ticket[1]);
            }
            for (auto& [src, dests] : adj) {
                sort(dests.rbegin(), dests.rend());
            }
            
            vector<string> res;
            dfs("JFK", adj, res);
            reverse(res.begin(), res.end());
            return res;
        }

    private:
        void dfs(const string& src, unordered_map<string, 
                deque<string>>& adj, vector<string>& res) {
            while (!adj[src].empty()) {
                string dst = adj[src].back();
                adj[src].pop_back();
                dfs(dst, adj, res);
            }
            res.push_back(src);
        }
    };

    // 2. min cost to connect all points:
    // You are given a 2-D integer array points, where points[i] = [xi, yi]. Each points[i] represents a distinct point on a 2-D plane.

    // The cost of connecting two points [xi, yi] and [xj, yj] is the manhattan distance between the two points, i.e. |xi - xj| + |yi - yj|.

    // Return the minimum cost to connect all points together, such that there exists exactly one path between each pair of points.
    int minCostConnectPoints(vector<vector<int>>& points) {
        int n = points.size(), node = 0;
        vector<int> dist(n, 100000000);
        vector<bool> visit(n, false);
        int edges = 0, res = 0;

        while (edges < n - 1) {
            visit[node] = true;
            int nextNode = -1;
            for (int i = 0; i < n; i++) {
                if (visit[i]) continue;
                int curDist = abs(points[i][0] - points[node][0]) + 
                               abs(points[i][1] - points[node][1]);
                dist[i] = min(dist[i], curDist);
                if (nextNode == -1 || dist[i] < dist[nextNode]) {
                    nextNode = i;
                }
            }
            res += dist[nextNode];
            node = nextNode;
            edges++;
        }
        return res;
    }

    // 3. network delay time:
    // You are given a network of n directed nodes, labeled from 1 to n. You are also given times, a list of directed edges where times[i] = (ui, vi, ti).

    // ui is the source node (an integer from 1 to n)
    // vi is the target node (an integer from 1 to n)
    // ti is the time it takes for a signal to travel from the source to the target node (an integer greater than or equal to 0).
    // You are also given an integer k, representing the node that we will send a signal from.

    // Return the minimum time it takes for all of the n nodes to receive the signal. If it is impossible for all the nodes to receive the signal, return -1 instead.

    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        unordered_map<int, vector<pair<int, int>>> edges;
        for (const auto& time : times) {
            edges[time[0]].emplace_back(time[1], time[2]);
        }

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> minHeap;
        minHeap.push({0, k});

        set<int> visited;
        int t = 0;
        while (!minHeap.empty()) {
            auto curr = minHeap.top();
            minHeap.pop();
            int w1 = curr.first, n1 = curr.second;
            if (visited.count(n1)) {
                continue;
            }
            visited.insert(n1);
            t = w1;

            if (edges.count(n1)) {
                for (const auto& next : edges[n1]) {
                    int n2 = next.first, w2 = next.second;
                    if (!visited.count(n2)) {
                        minHeap.push({w1 + w2, n2});
                    }
                }
            }
        }

        return visited.size() == n ? t : -1;
    }

    // 4. swim in raising water:
    // You are given a square 2-D matrix of distinct integers grid where each integer grid[i][j] represents the elevation at position (i, j).

    // Rain starts to fall at time = 0, which causes the water level to rise. At time t, the water level across the entire grid is t.

    // You may swim either horizontally or vertically in the grid between two adjacent squares if the original elevation of both squares is less than or equal to the water level at time t.

    // Starting from the top left square (0, 0), return the minimum amount of time it will take until it is possible to reach the bottom right square (n - 1, n - 1).

    class DSU {
        vector<int> Parent, Size;
    public:
        DSU(int n) : Parent(n + 1), Size(n + 1, 1) {
            for (int i = 0; i <= n; i++) Parent[i] = i;
        }

        int find(int node) {
            if (Parent[node] != node)
                Parent[node] = find(Parent[node]);
            return Parent[node];
        }

        bool unionSets(int u, int v) {
            int pu = find(u), pv = find(v);
            if (pu == pv) return false;
            if (Size[pu] < Size[pv]) swap(pu, pv);
            Size[pu] += Size[pv];
            Parent[pv] = pu;
            return true;
        }

        bool connected(int u, int v) {
            return find(u) == find(v);
        }
    };

    class Solution {
    public:
        int swimInWater(vector<vector<int>>& grid) {
            int N = grid.size();
            DSU dsu(N * N);
            vector<tuple<int, int, int>> positions;
            for (int r = 0; r < N; r++)
                for (int c = 0; c < N; c++)
                    positions.emplace_back(grid[r][c], r, c);

            sort(positions.begin(), positions.end());
            vector<pair<int, int>> directions = {
                {0, 1}, {1, 0}, {0, -1}, {-1, 0}
            };

            for (auto& [t, r, c] : positions) {
                for (auto& [dr, dc] : directions) {
                    int nr = r + dr, nc = c + dc;
                    if (nr >= 0 && nr < N && nc >= 0 && 
                        nc < N && grid[nr][nc] <= t) {
                        dsu.unionSets(r * N + c, nr * N + nc);
                    }
                }
                if (dsu.connected(0, N * N - 1)) return t;
            }
            return N * N;
        }
    };

    // 5. alien dictionary:
    // There is a foreign language which uses the latin alphabet, but the order among letters is not "a", "b", "c" ... "z" as in English.

    // You receive a list of non-empty strings words from the dictionary, where the words are sorted lexicographically based on the rules of this new language.

    // Derive the order of letters in this language. If the order is invalid, return an empty string. If there are multiple valid order of letters, return any of them.

    // A string a is lexicographically smaller than a string b if either of the following is true:

    // The first letter where they differ is smaller in a than in b.
    // There is no index i such that a[i] != b[i] and a.length < b.length.
    string foreignDictionary(vector<string>& words) {
        unordered_map<char, unordered_set<char>> adj;
        unordered_map<char, int> indegree;
        for (string w : words) {
            for (char c : w) {
                adj[c] = unordered_set<char>();
                indegree[c] = 0;
            }
        }
        
        for (int i = 0; i < words.size() - 1; i++) {
            string w1 = words[i], w2 = words[i + 1];
            int minLen = min(w1.size(), w2.size());
            if (w1.size() > w2.size() && 
                w1.substr(0, minLen) == w2.substr(0, minLen)) {
                return "";
            }
            for (int j = 0; j < minLen; j++) {
                if (w1[j] != w2[j]) {
                    if (!adj[w1[j]].count(w2[j])) {
                        adj[w1[j]].insert(w2[j]);
                        indegree[w2[j]]++;
                    }
                    break;
                }
            }
        }
        
        queue<char> q;
        for (auto &[c, deg] : indegree) {
            if (deg == 0) {
                q.push(c);
            }
        }
        
        string res;
        while (!q.empty()) {
            char char_ = q.front();
            q.pop();
            res += char_;
            for (char neighbor : adj[char_]) {
                indegree[neighbor]--;
                if (indegree[neighbor] == 0) {
                    q.push(neighbor);
                }
            }
        }
        
        return res.size() == indegree.size() ? res : "";
    }

    // 6. cheapest flight within Kstops:
    // There are n airports, labeled from 0 to n - 1, which are connected by some flights. You are given an array flights where flights[i] = [from_i, to_i, price_i] represents a one-way flight from airport from_i to airport to_i with cost price_i. You may assume there are no duplicate flights and no flights from an airport to itself.
    // You are also given three integers src, dst, and k where:
    // src is the starting airport
    // dst is the destination airport
    // src != dst
    // k is the maximum number of stops you can make (not including src and dst)
    // Return the cheapest price from src to dst with at most k stops, or return -1 if it is impossible.
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<int> prices(n, INT_MAX);
        prices[src] = 0;
        vector<vector<pair<int, int>>> adj(n);
        for (const auto& flight : flights) {
            adj[flight[0]].emplace_back(flight[1], flight[2]);
        }

        queue<tuple<int, int, int>> q;
        q.push({0, src, 0});

        while (!q.empty()) {
            auto [cst, node, stops] = q.front();
            q.pop();
            if (stops > k) continue;

            for (const auto& neighbor : adj[node]) {
                int nei = neighbor.first, w = neighbor.second;
                int nextCost = cst + w;
                if (nextCost < prices[nei]) {
                    prices[nei] = nextCost;
                    q.push({nextCost, nei, stops + 1});
                }
            }
        }
        return prices[dst] == INT_MAX ? -1 : prices[dst];
    }

private:
    // internal helpers if needed later
};