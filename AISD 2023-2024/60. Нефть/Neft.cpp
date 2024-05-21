#define _CRT_SECURE_NO_WARNING

#include <iostream>
#include <vector>
#include <limits>
#include <queue>
#include <climits>

using namespace std;
const int INF = INT_MAX;
vector<int> a, b;
int cost;

struct Edge {
    int to;
    int capacity;
    int cost;
    int flow;
    size_t rev;
};

class MCMF {
    int V;
    vector<vector<Edge>> graph;
    vector<int> dist;
    vector<int> prev_edge;
    vector<int> prev_node;

public:
    MCMF(int V) : 
        V(V),
        graph(V),
        dist(V),
        prev_edge(V),
        prev_node(V)
    {
        
    }
    void add_edge(int from, int to, int capacity, int cost) {
        Edge forward_edge = { to, capacity, cost, 0, graph[to].size() };
        Edge backward_edge = { from, 0, -cost, 0, graph[from].size() };
        graph[from].push_back(forward_edge);
        graph[to].push_back(backward_edge);
    }
    pair<int, int> min_cost_max_flow(int source, int sink) {
        int flow = 0;
        int cost = 0;
        while (true) {
            dijkstra(source);
            if (dist[sink] == INF)
                break;
            int f = INF;
            for (int u = sink;
                u != source;
                u = prev_node[u]) {
                f = min(f, graph[prev_node[u]][prev_edge[u]].capacity - 
                    graph[prev_node[u]][prev_edge[u]].flow);
            }

            flow += f;
            for (int u = sink; u != source; u = prev_node[u]) {
                int rev = graph[prev_node[u]][prev_edge[u]].rev;
                graph[prev_node[u]][prev_edge[u]].flow += f;
                graph[u][rev].flow -= f;
                cost += f * graph[prev_node[u]][prev_edge[u]].cost;
            }
        }
        return make_pair(flow, cost);
    }

    /*void AddEdge(int head, int end, int cost, int cap, int name){
    int i = 0, next;
    Head[name] = head;
    End[name] = end;
    Cost[name] = cost;
    Cap[name] = cap;
    if( Y[head]== -1){
        Y[head] = name;
    }else{
        int former = Y[head];
        int next = Next[former];
        while(next!= -1){//TODO change it to get back to head;
            former = next;
            next = Next[former];
        }
        Next[former] = name;
    }
}
*/
    void dijkstra(int source) {
        fill(dist.begin(), dist.end(), INF);
        dist[source] = 0;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push(make_pair(0, source));
        while (!pq.empty()) {
            int d = pq.top().first;
            int u = pq.top().second;
            pq.pop();
            if (d != dist[u])
                continue;
            for (size_t i = 0; i < graph[u].size(); ++i) {
                Edge& e = graph[u][i];
                if (e.capacity - e.flow > 0 && dist[e.to] > dist[u] + e.cost) {
                    dist[e.to] = dist[u] + e.cost;
                    prev_node[e.to] = u;
                    prev_edge[e.to] = i;
                    pq.push(make_pair(dist[e.to], e.to));
                }
            }
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);

    int N, M;
    cin >> N >> M;

    a.resize(N);
    b.resize(M);

    for (int i = 0; i < N; ++i) {
        cin >> a[i];
    }




    for (int i = 0; i < M; ++i) {
        cin >> b[i];
    }




    MCMF USA_DEMOCRACY(N + M + 2);

    for (int i = 0; i < N; ++i) {
        USA_DEMOCRACY.add_edge(0, i + 1, a[i], 0);
    }

    for (int i = 0; i < M; ++i) {
        USA_DEMOCRACY.add_edge(N + 1 + i, N + M + 1, b[i], 0);
    }

    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            
            cin >> cost;
            USA_DEMOCRACY.add_edge(i + 1, N + 1 + j, INF, cost);
        }
    }

    pair<int, int> result = USA_DEMOCRACY.min_cost_max_flow(0, N + M + 1);
    cout << result.second << endl;
}