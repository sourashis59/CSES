#include<bits/stdc++.h>
using namespace std;

/*
* Pseudo Intuition:
* ________________________________________
* Find the component graph (containing all the SCCs)
* For each SCC, find the total score of all nodes in it.
* Then we know Component Grph (or, Kernel Grpah) is DAG
* Use DP to check for each node SCC u, if we start from u, what is the max amount of points we can collect !!!!!!!!!!!!!!!!!!!!!!!!!!!
*/
 
 

class Graph {
    int n;
    vector<vector<int>> adj;
public:
    Graph(int n): n(n), adj(vector<vector<int>>(n)) {}
    
    // Move constructor
    Graph(Graph &&other) noexcept : n(other.n), adj(move(other.adj)) {
        // After moving, leave the source object in a valid state
        other.n = 0;
    }

    // Move assignment operator
    Graph& operator=(Graph &&other) noexcept {
        if (this != &other) {
            n = other.n;
            adj = move(other.adj);
            other.n = 0;
        }
        return *this;
    }
    
    int V() { return n; }
    vector<int> &get_edges(int u) { return adj[u]; }
    void add_edge(int from, int to) { adj[from].push_back(to); }
 
    Graph get_transpose_graph() {
        Graph transpose(n);
        transpose.n = this->n;
        transpose.adj = vector<vector<int>>(n);
        for (int u = 0; u < n; ++u) { for (int v: adj[u]) { transpose.add_edge(v, u); }}
        return transpose;
    }
};
 

void dfs(int u, vector<bool> &visited, Graph &graph, vector<int> &nodes_in_desc_order_of_finish_time) {
    visited[u] = true;
    for (int v: graph.get_edges(u)) { if (!visited[v]) dfs(v, visited, graph, nodes_in_desc_order_of_finish_time); }
    nodes_in_desc_order_of_finish_time.push_back(u);
}
 
void dfs_assign_scc_id(int u, int curr_scc_id, vector<bool> &visited, Graph &graph, vector<int> &scc_id) {
    visited[u] = true;
    scc_id[u] = curr_scc_id;
    for (int v: graph.get_edges(u)) { if (!visited[v]) dfs_assign_scc_id(v, curr_scc_id, visited, graph, scc_id); }
}
 
//* returns: scc_id[u] = SCC ID (in range 0 to k-1) of u 
pair<int, vector<int>> get_all_scc(Graph &graph) {
    vector<bool> visited(graph.V(), false);
    vector<int> nodes_in_desc_order_of_finish_time;
    nodes_in_desc_order_of_finish_time.reserve(graph.V());
    for (int u = 0; u < graph.V(); ++u) {
        if (visited[u]) continue;
        dfs(u, visited, graph, nodes_in_desc_order_of_finish_time);
    }
    reverse(nodes_in_desc_order_of_finish_time.begin(), nodes_in_desc_order_of_finish_time.end());
 
    vector<int> scc_id(graph.V(), -1);
    Graph transpose_graph = graph.get_transpose_graph();
    visited.assign(visited.size(), false);
    int increasing_scc_id = 0;
    for (int u: nodes_in_desc_order_of_finish_time) {
        if (visited[u]) continue;
        dfs_assign_scc_id(u, increasing_scc_id, visited, transpose_graph, scc_id);
        ++increasing_scc_id;
    }
    return {increasing_scc_id, scc_id};
}


//* given a DAG {graph}, check if we start from node {u} how much max coin we can collect 
//* in the path from u to some terminal node
long long mp(int u, Graph &graph, vector<long long> &points, vector<long long> &memo) {
    long long res = 0;
    if (memo[u] != -1) return memo[u];
    for (int v: graph.get_edges(u)) res = max(res, mp(v, graph, points, memo));
    res += points[u];
    return memo[u] = res;    
}

long long help(Graph &graph, const vector<int> &points) {
    pair<int, vector<int>> temp = get_all_scc(graph);
    int scc_count = temp.first;
    vector<int> &scc_ids = temp.second;
    Graph scc_graph(scc_count);
    vector<long long> scc_points(scc_count, 0);
    for (int u = 0; u < graph.V(); ++u) {
        scc_points[scc_ids[u]] += points[u];
        for (int v: graph.get_edges(u)) 
            if (scc_ids[u] != scc_ids[v]) 
                scc_graph.add_edge(scc_ids[u], scc_ids[v]);
    }

    long long res = 0;
    vector<long long> memo(scc_graph.V(), -1);
    for (int u = 0; u < scc_graph.V(); ++u) 
        res = max(res, mp(u, scc_graph, scc_points, memo));

    return res;
}
 
 
int main() {
    int n, m;
    cin >> n >> m;
    Graph graph(n);
    vector<int> points(n);
    for (int i = 0; i < n; ++i) 
        cin >> points[i];

    int u, v;
    for (int i = 0; i < m; ++i) {
        cin >> u >> v;
        graph.add_edge(u - 1, v - 1);
    }

    cout << help(graph, points);
    return 0;
}