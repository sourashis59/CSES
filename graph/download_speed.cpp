#include<bits/stdc++.h>
using namespace std;

class Edge {
public:
    int to;
    long long weight;
    Edge(int to, long long weight): to(to), weight(weight) {}
};

class Graph {
    int n;
    vector<vector<Edge>> adj;
public:
    Graph(int n): n(n), adj(vector<vector<Edge>>(n)) {}
    int V() { return n; }
    vector<Edge> &get_edges(int u) { return adj[u]; }
    void add_edge(int from, int to, long long weight) { adj[from].push_back(Edge(to, weight)); }
};




//* checks if it's possible to reach from source to dest such that all edge weight in the path
//* are >= lower_bound
bool possible_to_reach(int source, int dest, long long lower_bound, vector<bool> &visited, Graph &graph) {
    visited[source] = true;
    if (source == dest) return true;
    for (const auto &e: graph.get_edges(source)) {
        if (!visited[e.to] && e.weight >= lower_bound 
            && possible_to_reach(e.to, dest, lower_bound, visited, graph))
            return true;
    }
    return false;
}

long long method1(Graph &graph) {
    /*
    Pseudo Intuition: (Binary Search)
        We know answer is in range [0, max edge weight]
        For each potential weight, check if there exists a path from source
        to destination such that all edge weights in that path >= potential weight  
    */
    long long low = 0, high = 0;
    for (int u = 0; u < graph.V(); ++u) {
        for (const auto &e: graph.get_edges(u))
            high = max(high, e.weight);
    }
    vector<bool> visited(graph.V());
    long long res = 0;
    while (low <= high) {
        long long mid = low + (high - low) / 2;
        visited.assign(visited.size(), false);
        if (possible_to_reach(0, graph.V() - 1, mid, visited, graph)) {
            res = mid;
            low = mid + 1; 
        } else {
            high = mid - 1;
        }
    }
    return res;
}


int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    int u, v;
    long long w;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v >> w;
        graph.add_edge(u - 1, v - 1, w);
    }
    cout << method1(graph);
    return 0;
}