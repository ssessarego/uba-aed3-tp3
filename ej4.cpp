#include <iostream>
#include <vector>
#include <queue>
#include <tuple>

using namespace std;

int INF = 100000000;
int MAX_CAP;
int N, M, x;
vector<tuple<int, int, int>> edges; // source, destiny, weight
vector<vector<int>> capacity;
vector<vector<int>> adj;


int bfs(int s, int t, vector<int>& parent) {
    fill(parent.begin(), parent.end(), -1);
    parent[s] = -2;
    queue<pair<int, int>> q;
    q.push({s, INF});

    while (!q.empty()) {
        int cur = q.front().first;
        int flow = q.front().second;
        q.pop();

        for (int next : adj[cur]) {
            if (parent[next] == -1 && capacity[cur][next] > 0) {
                parent[next] = cur;
                int new_flow = min(flow, capacity[cur][next]);
                if (next == t)
                    return new_flow;
                q.push({next, new_flow});
            }
        }
    }

    return 0;
}


int maxflow(int s, int t) {
    int flow = 0;
    vector<int> parent(N + 2);
    int new_flow;

    while ((new_flow = bfs(s, t, parent))) {
        flow += new_flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= new_flow;
            capacity[cur][prev] += new_flow;
            cur = prev;
        }
    }

    return flow;
}


int solve() {
    
    /*
    Sea K la max cantidad que se puede transportar por persona (K * x = resultado)
    
    Si divido a la capacidad de c/ arista por K obtengo la cantidad de personas que
    pueden recorrer esa arista. 
    Si se crea un grafo con los mismos nodos y aristas pero con capacidades = cap(e) / K, 
    el valor del flujo máximo es igual a las personas totales que pueden llevar K elementos.
    Si este valor coincide con x, entonces K es una solución probable (en este caso es la óptima).

    IDEA:
    Aproximar el valor de K con búsqueda binaria, hasta un epsilon pequeño.

    Probar un valor K', crear el grafo con capacidades cap(e) / K' y ejecutar flujo max.
    Agregar tambien un nodo s y uno t con capacidades = x para que flujo max <= x.
    Si el flujo el >= x, entonces hago b.b. en la parte alta, para buscar un mayor K'
    Sino, en la baja, ya que significa que K' es muy grande.
    Cortar la búsqueda hasta cierto límite que pueda asegurar un resultado óptimo.
    */

    int mid, low = 0, high = MAX_CAP + 1, res = 0;
    int lim = 25; // lim >= log2(high) y high <= 10^6
    while (lim > 0) {
        lim--;
        mid = (low + high) / 2;

        for (int i = 0; i < M; i++) {
            int v = get<0>(edges[i]);
            int w = get<1>(edges[i]);
            int c = get<2>(edges[i]);
            if (mid != 0) {
                capacity[v][w] = (c / mid) > x ? x : (c / mid);
            } else {
                capacity[v][w] = 0;
            }
        }
        // Capacidad de nodos s y t = x
        capacity[0][1] = x;
        capacity[N][N+1] = x;

        int flow = maxflow(0, N + 1);
        if (flow >= x) {
            low = mid;
            res = mid;
        } else {
            high = mid;
        }
    }
    return res * x;
}


int main() {
    int tests;
    cin >> tests;

    while (tests > 0) {
        // Leer entrada
        cin >> N >> M >> x;

        // Inicializar estructuras
        adj = vector<vector<int>>(N + 2, vector<int>());
        edges = vector<tuple<int, int, int>>(M);
        capacity = vector<vector<int>>(N + 2, vector<int>(N + 2, 0));
        MAX_CAP = 0; // Guardo la capacidad máxima para acotar high en la b.b.
        
        // Agrego dos nodos s y t
        adj[0].push_back(1);
        adj[1].push_back(0);
        adj[N].push_back(N+1);
        adj[N+1].push_back(N);
        for (int i = 0; i < M; i++) {
            int v, w, c;
            cin >> v >> w >> c;
            // v--; w--;
            adj[v].push_back(w);
            adj[w].push_back(v);
            edges[i] = {v, w, c};
            MAX_CAP = max(MAX_CAP, c);
        }
        
        int res = solve();
        cout << res << endl;

        tests--;
    }
}
