#include <vector>
#include <string>
#include <stack>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

// Symbol Cast Algorithm Suite for EtherOS
// Inputs are 3D objects with ordering numbers and category colors.
// Complexity: O(n) = S(n) + cT(n) treating time as a spatial dimension.
// Referencing an object updates its position; copying leaves it in place.

using namespace std;

class Backtracking {
public:
    Backtracking() {}
    ~Backtracking() {}
    Backtracking(const Backtracking& other) = default;
    Backtracking(Backtracking&& other) noexcept = default;
    Backtracking& operator=(const Backtracking& other) = default;
    Backtracking& operator=(Backtracking&& other) noexcept = default;

    // 1. number of islands:
    // Given a 2D grid grid where '1' represents land and '0' represents water, count and return the number of islands.
    // An island is formed by connecting adjacent lands horizontally or vertically and is surrounded by water. You may assume water is surrounding the grid (i.e., all the edges are water).
    class Solution {
        int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    public:
        int numIslands(vector<vector<char>>& grid) {
            int ROWS = grid.size(), COLS = grid[0].size();
            int islands = 0;

            for (int r = 0; r < ROWS; r++) {
                for (int c = 0; c < COLS; c++) {
                    if (grid[r][c] == '1') {
                        dfs(grid, r, c);
                        islands++;
                    }
                }
            }
            
            return islands;
        }
        
        void dfs(vector<vector<char>>& grid, int r, int c) {
            if (r < 0 || c < 0 || r >= grid.size() || 
                c >= grid[0].size() || grid[r][c] == '0') {
                return;
            }
            
            grid[r][c] = '0';
            for (int i = 0; i < 4; i++) {
                dfs(grid, r + directions[i][0], c + directions[i][1]);
            }
        }
    };

    // 2. max area of island:
    // You are given a matrix grid where grid[i] is either a 0 (representing water) or 1 (representing land).
    // An island is defined as a group of 1's connected horizontally or vertically. You may assume all four edges of the grid are surrounded by water.
    // The area of an island is defined as the number of cells within the island.
    // Return the maximum area of an island in grid. If no island exists, return 0.

    class Solution {
        int directions[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    public:
        int maxAreaOfIsland(vector<vector<int>>& grid) {
            int ROWS = grid.size(), COLS = grid[0].size();
            int area = 0;

            for (int r = 0; r < ROWS; r++) {
                for (int c = 0; c < COLS; c++) {
                    if (grid[r][c] == 1) {
                        area = max(area, dfs(grid, r, c));
                    }
                }
            }
            
            return area;
        }
        
        int dfs(vector<vector<int>>& grid, int r, int c) {
            if (r < 0 || c < 0 || r >= grid.size() || 
                c >= grid[0].size() || grid[r][c] == 0) {
                return 0;
            }
            
            grid[r][c] = 0;
            int res = 1;
            for (int i = 0; i < 4; i++) {
                res += dfs(grid, r + directions[i][0], 
                                c + directions[i][1]);
            }
            return res;
        }
    };

    // 3. clone graphs:
    // Given a node in a connected undirected graph, return a deep copy of the graph.

    // Each node in the graph contains an integer value and a list of its neighbors.

    // class Node {
    // public int val;
    // public List neighbors;
    // }
    // The graph is shown in the test cases as an adjacency list. An adjacency list is a mapping of nodes to lists, used to represent a finite graph. Each list describes the set of neighbors of a node in the graph.

    // For simplicity, nodes values are numbered from 1 to n, where n is the total number of nodes in the graph. The index of each node within the adjacency list is the same as the node's value (1-indexed).

    // The input node will always be the first node in the graph and have 1 as the value.

    // /*
    // // Definition for a Node.
    // class Node {
    // public:
    //     int val;
    //     vector<Node*> neighbors;
    //     Node() {
    //         val = 0;
    //         neighbors = vector<Node*>();
    //     }
    //     Node(int _val) {
    //         val = _val;
    //         neighbors = vector<Node*>();
    //     }
    //     Node(int _val, vector<Node*> _neighbors) {
    //         val = _val;
    //         neighbors = _neighbors;
    //     }
    // };
    // */

    class Solution {
    public:
        Node* cloneGraph(Node* node) {
            map<Node*, Node*> oldToNew;
            return dfs(node, oldToNew);
        }

        Node* dfs(Node* node, map<Node*, Node*>& oldToNew) {
            if (node == nullptr) {
                return nullptr;
            }

            if (oldToNew.count(node)) {
                return oldToNew[node];
            }

            Node* copy = new Node(node->val);
            oldToNew[node] = copy;

            for (Node* nei : node->neighbors) {
                copy->neighbors.push_back(dfs(nei, oldToNew));
            }

            return copy;
        }
    };

    // 4. walls and gates:
    // Islands and Treasure
    // You are given a m×n 2D grid initialized with these three possible values:
    // -1 - A water cell that can not be traversed.
    // 0 - A treasure chest.
    // INF - A land cell that can be traversed. We use the integer 2^31 - 1 = 2147483647 to represent INF.
    // Fill each land cell with the distance to its nearest treasure chest. If a land cell cannot reach a treasure chest than the value should remain INF.
    // Assume the grid can only be traversed up, down, left, or right.
    // Modify the grid in-place.
    void islandsAndTreasure(vector<vector<int>>& grid) {
        int m = grid.size();
        int n = grid[0].size();
        
        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 0) {
                    q.push({i, j});
                }
            }
        }
        
        vector<vector<int>> dirs = {{-1, 0}, {1, 0}, 
                                    {0, -1}, {0, 1}};
        while (!q.empty()) {
            int row = q.front().first;
            int col = q.front().second;
            q.pop();
            
            for (int i = 0; i < 4; i++) {
                int r = row + dirs[i][0];
                int c = col + dirs[i][1];
                
                if (r < 0 || r >= m || c < 0 || 
                    c >= n || grid[r][c] != INT_MAX) {
                    continue;
                }
                
                grid[r][c] = grid[row][col] + 1;
                q.push({r, c});
            }
        }
    }

    // 5.rotting oranges:
    // You are given a 2-D matrix grid. Each cell can have one of three possible values:

    // 0 representing an empty cell
    // 1 representing a fresh fruit
    // 2 representing a rotten fruit
    // Every minute, if a fresh fruit is horizontally or vertically adjacent to a rotten fruit, then the fresh fruit also becomes rotten.

    // Return the minimum number of minutes that must elapse until there are zero fresh fruits remaining. If this state is impossible within the grid, return -1.
    int orangesRotting(vector<vector<int>>& grid) {
        queue<pair<int, int>> q;
        int fresh = 0;
        int time = 0;

        for (int r = 0; r < grid.size(); r++) {
            for (int c = 0; c < grid[0].size(); c++) {
                if (grid[r][c] == 1) {
                    fresh++;
                }
                if (grid[r][c] == 2) {
                    q.push({r, c});
                }
            }
        }

        vector<pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
        while (fresh > 0 && !q.empty()) {
            int length = q.size();
            for (int i = 0; i < length; i++) {
                auto curr = q.front();
                q.pop();
                int r = curr.first;
                int c = curr.second;

                for (const auto& dir : directions) {
                    int row = r + dir.first;
                    int col = c + dir.second;
                    if (row >= 0 && row < grid.size() && 
                        col >= 0 && col < grid[0].size() &&
                        grid[row][col] == 1) {
                        grid[row][col] = 2;
                        q.push({row, col});
                        fresh--;
                    }
                }
            }
            time++;
        }
        return fresh == 0 ? time : -1;
    }

    // 6. pacific atlantic water flow:
    // You are given a rectangular island heights where heights[r][c] represents the height above sea level of the cell at coordinate (r, c).
    // The islands borders the Pacific Ocean from the top and left sides, and borders the Atlantic Ocean from the bottom and right sides.
    // Water can flow in four directions (up, down, left, or right) from a cell to a neighboring cell with height equal or lower. Water can also flow into the ocean from cells adjacent to the ocean.
    // Find all cells where water can flow from that cell to both the Pacific and Atlantic oceans. Return it as a 2D list where each element is a list [r, c] representing the row and column of the cell. You may return the answer in any order.

    class Solution {
        vector<pair<int, int>> directions = {{1, 0}, {-1, 0}, 
                                            {0, 1}, {0, -1}};
    public:
        vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
            int ROWS = heights.size(), COLS = heights[0].size();
            vector<vector<bool>> pac(ROWS, vector<bool>(COLS, false));
            vector<vector<bool>> atl(ROWS, vector<bool>(COLS, false));

            for (int c = 0; c < COLS; ++c) {
                dfs(0, c, pac, heights);
                dfs(ROWS - 1, c, atl, heights);
            }
            for (int r = 0; r < ROWS; ++r) {
                dfs(r, 0, pac, heights);
                dfs(r, COLS - 1, atl, heights);
            }

            vector<vector<int>> res;
            for (int r = 0; r < ROWS; ++r) {
                for (int c = 0; c < COLS; ++c) {
                    if (pac[r][c] && atl[r][c]) {
                        res.push_back({r, c});
                    }
                }
            }
            return res;
        }

    private:
        void dfs(int r, int c, vector<vector<bool>>& ocean, vector<vector<int>>& heights) {
            ocean[r][c] = true;
            for (auto [dr, dc] : directions) {
                int nr = r + dr, nc = c + dc;
                if (nr >= 0 && nr < heights.size() && 
                    nc >= 0 && nc < heights[0].size() && 
                    !ocean[nr][nc] && heights[nr][nc] >= heights[r][c]) {
                    dfs(nr, nc, ocean, heights);
                }
            }
        }
    };


    // 7. surrounded regions:
    You are given a 2-D matrix board containing 'X' and 'O' characters.

    If a continous, four-directionally connected group of 'O's is surrounded by 'X's, it is considered to be surrounded.

    Change all surrounded regions of 'O's to 'X's and do so in-place by modifying the input board.

    class DSU {
        vector<int> Parent, Size;

    public:
        DSU(int n) {
            Parent.resize(n + 1);
            Size.resize(n + 1);
            for (int i = 0; i <= n; i++) {
                Parent[i] = i;
                Size[i] = 1;
            }
        }

        int find(int node) {
            if (Parent[node] != node) {
                Parent[node] = find(Parent[node]);
            }
            return Parent[node];
        }

        bool unionNodes(int u, int v) {
            int pu = find(u), pv = find(v);
            if (pu == pv) return false;
            if (Size[pu] >= Size[pv]) {
                Size[pu] += Size[pv];
                Parent[pv] = pu;
            } else {
                Size[pv] += Size[pu];
                Parent[pu] = pv;
            }
            return true;
        }

        bool connected(int u, int v) {
            return find(u) == find(v);
        }
    };

    // 8. course schedule:
    // You are given an array prerequisites where prerequisites[i] = [a, b] indicates that you must take course b first if you want to take course a.
    // The pair [0, 1], indicates that must take course 1 before taking course 0.
    // There are a total of numCourses courses you are required to take, labeled from 0 to numCourses - 1.
    // Return true if it is possible to finish all courses, otherwise return false.
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<int> indegree(numCourses, 0);
        vector<vector<int>> adj(numCourses);
        
        for (auto& pre : prerequisites) {
            indegree[pre[1]]++;
            adj[pre[0]].push_back(pre[1]);
        }

        queue<int> q;
        for (int i = 0; i < numCourses; ++i) {
            if (indegree[i] == 0) {
                q.push(i);
            }
        }

        int finish = 0;
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            finish++;
            for (int nei : adj[node]) {
                indegree[nei]--;
                if (indegree[nei] == 0) {
                    q.push(nei);
                }
            }
        }

        return finish == numCourses;
    }

    // 9. course schedule 2:
    // You are given an array prerequisites where prerequisites[i] = [a, b] indicates that you must take course b first if you want to take course a.
    // For example, the pair [0, 1], indicates that to take course 0 you have to first take course 1.
    // There are a total of numCourses courses you are required to take, labeled from 0 to numCourses - 1.
    // Return a valid ordering of courses you can take to finish all courses. If there are many valid answers, return any of them. If it's not possible to finish all courses, return an empty array.

    class Solution {
        vector<int> output;
        vector<int> indegree;
        vector<vector<int>> adj;
        
        void dfs(int node) {
            output.push_back(node);
            indegree[node]--;
            for (int nei : adj[node]) {
                indegree[nei]--;
                if (indegree[nei] == 0) {
                    dfs(nei);
                }
            }
        }

    public:
        vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
            adj = vector<vector<int>>(numCourses);
            indegree = vector<int>(numCourses, 0);
            for (auto& pre : prerequisites) {
                indegree[pre[0]]++;
                adj[pre[1]].push_back(pre[0]);
            }

            for (int i = 0; i < numCourses; i++) {
                if (indegree[i] == 0) {
                    dfs(i);
                }
            }

            if (output.size() != numCourses) return {};
            return output;
        }
    };

    // 10. graph valid tree:
    // Given n nodes labeled from 0 to n - 1 and a list of undirected edges (each edge is a pair of nodes), write a function to check whether these edges make up a valid tree.
    class DSU {
        vector<int> Parent, Size;
        int comps;
    public:
        DSU(int n) {
            comps = n;
            Parent.resize(n + 1);
            Size.resize(n + 1);
            for (int i = 0; i <= n; i++) {
                Parent[i] = i;
                Size[i] = 1;
            }
        }

        int find(int node) {
            if (Parent[node] != node) {
                Parent[node] = find(Parent[node]);
            }
            return Parent[node];
        }

        bool unionNodes(int u, int v) {
            int pu = find(u), pv = find(v);
            if (pu == pv) return false;
            if (Size[pu] < Size[pv]) {
                swap(pu, pv);
            }
            comps--;
            Size[pu] += Size[pv];
            Parent[pv] = pu;
            return true;
        }

        int components() {
            return comps;
        }
    };

    bool validTree(int n, vector<vector<int>>& edges) {
        if (edges.size() > n - 1) {
            return false;
        }

        DSU dsu(n);
        for (auto& edge : edges) {
            if (!dsu.unionNodes(edge[0], edge[1])) {
                return false;
            }
        }
        return dsu.components() == 1;
    }

    // 11. number of connected components - undir graph:
    // There is an undirected graph with n nodes. There is also an edges array, where edges[i] = [a, b] means that there is an edge between node a and node b in the graph.

    // The nodes are numbered from 0 to n - 1.

    // Return the total number of connected components in that graph.

    class DSU {
    public:
        vector<int> parent;
        vector<int> rank;

        DSU(int n) {
            parent.resize(n);
            rank.resize(n, 1);
            for (int i = 0; i < n; i++) {
                parent[i] = i;
            }
        }

        int find(int node) {
            int cur = node;
            while (cur != parent[cur]) {
                parent[cur] = parent[parent[cur]];
                cur = parent[cur];
            }
            return cur;
        }

        bool unionSets(int u, int v) {
            int pu = find(u);
            int pv = find(v);
            if (pu == pv) {
                return false;
            }
            if (rank[pv] > rank[pu]) {
                swap(pu, pv);
            }
            parent[pv] = pu;
            rank[pu] += rank[pv];
            return true;
        }
    };

    class Solution {
    public:
        int countComponents(int n, vector<vector<int>>& edges) {
            DSU dsu(n);
            int res = n;
            for (auto& edge : edges) {
                if (dsu.unionSets(edge[0], edge[1])) {
                    res--;
                }
            }
            return res;
        }
    };


    // 12. redundant connection:
    // You are given a connected undirected graph with n nodes labeled from 1 to n. Initially, it contained no cycles and consisted of n-1 edges.

    // We have now added one additional edge to the graph. The edge has two different vertices chosen from 1 to n, and was not an edge that previously existed in the graph.

    // The graph is represented as an array edges of length n where edges[i] = [ai, bi] represents an edge between nodes ai and bi in the graph.

    // Return an edge that can be removed so that the graph is still a connected non-cyclical graph. If there are multiple answers, return the edge that appears last in the input edges.

    class Solution {
    public:
        vector<int> findRedundantConnection(vector<vector<int>>& edges) {
            int n = edges.size();
            vector<int> par(n + 1), rank(n + 1, 1);
            for (int i = 0; i <= n; ++i)
                par[i] = i;

            for (const auto& edge : edges) {
                if (!Union(par, rank, edge[0], edge[1]))
                    return vector<int>{ edge[0], edge[1] };
            }
            return {};
        }

    private:
        int Find(vector<int>& par, int n) {
            int p = par[n];
            while (p != par[p]) {
                par[p] = par[par[p]];
                p = par[p];
            }
            return p;
        }

        bool Union(vector<int>& par, vector<int>& rank, int n1, int n2) {
            int p1 = Find(par, n1);
            int p2 = Find(par, n2);

            if (p1 == p2)
                return false;
            if (rank[p1] > rank[p2]) {
                par[p2] = p1;
                rank[p1] += rank[p2];
            } else {
                par[p1] = p2;
                rank[p2] += rank[p1];
            }
            return true;
        }
    };

    // 13. word ladder:
    // You are given two words, beginWord and endWord, and also a list of words wordList. All of the given words are of the same length, consisting of lowercase English letters, and are all distinct.

    // Your goal is to transform beginWord into endWord by following the rules:

    // You may transform beginWord to any word within wordList, provided that at exactly one position the words have a different character, and the rest of the positions have the same characters.
    // You may repeat the previous step with the new word that you obtain, and you may do this as many times as needed.
    // Return the minimum number of words within the transformation sequence needed to obtain the endWord, or 0 if no such sequence exists.

    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        if (endWord.empty() || find(wordList.begin(), wordList.end(), endWord) == wordList.end()) {
            return 0;
        }

        unordered_map<string, vector<string>> nei;
        wordList.push_back(beginWord);
        for (const string& word : wordList) {
            for (int j = 0; j < word.size(); ++j) {
                string pattern = word.substr(0, j) + "*" + word.substr(j + 1);
                nei[pattern].push_back(word);
            }
        }

        unordered_set<string> visit{beginWord};
        queue<string> q;
        q.push(beginWord);
        int res = 1;
        while (!q.empty()) {
            int size = q.size();
            for (int i = 0; i < size; ++i) {
                string word = q.front();
                q.pop();
                if (word == endWord) {
                    return res;
                }
                for (int j = 0; j < word.size(); ++j) {
                    string pattern = word.substr(0, j) + "*" + word.substr(j + 1);
                    for (const string& neiWord : nei[pattern]) {
                        if (visit.find(neiWord) == visit.end()) {
                            visit.insert(neiWord);
                            q.push(neiWord);
                        }
                    }
                }
            }
            ++res;
        }
        return 0;
    }
private:
    // No internal members yet
};