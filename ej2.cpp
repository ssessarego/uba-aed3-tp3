#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int N;
vector<vector<int>> lat;
const int INF = 1000000000;
vector<vector<int>> adj;
vector<int> d;
vector<bool> visited;


void dijkstra(int s) {
    visited = vector<bool>(N, false);
    d = vector<int>(N, INF);

    d[s] = 0;
    for (int i = 0; i < N; i++) {
        int v = -1;
        for (int j = 0; j < N; j++) {
            if (!visited[j] && (v == -1 || d[j] < d[v]))
                v = j;
        }

        if (d[v] == INF)
            break;

        visited[v] = true;
        for (auto w : adj[v]) {
            int len = lat[v][w];

            if (d[v] + len < d[w]) {
                d[w] = d[v] + len;
            }
        }
    }
}


void bfs(int s) {
    visited = vector<bool>(N, false);
    d = vector<int>(N);
    
    visited[s] = true;
    d[s] = 0;
    queue<int> q;
    q.push(s);

    while (!q.empty()) {
        int v = q.front(); q.pop();
        for (int w : adj[v]) {
            if (!visited[w]) {
                visited[w] = true;
                d[w] = d[v] + 1;
                q.push(w);
            }
        }
    }
}


void insert_edge(int v, int w) {
    for (int i = 0; i < adj[v].size(); i++) {
        if (adj[v][i] > w) {
            adj[v].insert(adj[v].begin() + i, w);
            return;
        }
    }
    adj[v].push_back(w);
}

void remove_edge(int v, int w) {
    for (int i = 0; i < adj[v].size(); i++) {
        if (adj[v][i] == w) {
            adj[v].erase(adj[v].begin() + i);
            break;
        }
    }
}


void solve() {
    /*
    Idea:
    Hacer el grafo con las computadoras como nodos y las latencias como pesos.
    Para todo v->w sacar v->w y correr Dijkstra para encontrar otro camino mínimo de v a w:
    - Si la nueva d(v, w) es igual a latencia[v][w] entonces eliminar v->w del grafo, porque
    significa que ya hay un camino correcto de v a w, y v->w está de más.
    - Si d(v, w) es menor a latencia[v][w] entonces devolver "IMPOSIBLE", ya que significa 
    que latencia[v][w] no era correcta (no era la mínima cantidad)
    - Si es mayor, dejar v->w en el grafo.

    El grafo resultante contiene la mínima cantidad de enlaces que cumplen las latencias.
    Falta calcular la distancia entre estos nodos, que se puede hacer corriendo BFS para c/ nodo.

    Complejidad: M veces Dijkstra + N veces BFS = O(M * min{M log(N), N^2} + M * (N + M))
     = O(M^2*log(M))
    */
    bool impossible = false;
    
    for (int i = 0; i < N && impossible == false; i++) {
        for (int j = 0; adj[i][j] < i; j++) {
            int v = i, w = adj[i][j];

            remove_edge(v, w);
            remove_edge(w, v);

            dijkstra(v);
            if (d[w] < lat[v][w]) {
                impossible = true;
                break;
            } else if (d[w] > lat[v][w]) {
                insert_edge(v, w);
                insert_edge(w, v);
            } // else if equal then dont add v->w again (continue) 
        } 
    }

    if (impossible) {
        cout << "IMPOSIBLE" << endl;
        return;
    }
    cout << "POSIBLE" << endl;
    
    for (int i = 0; i < N; i++) {
        bfs(i);
        for (int j = 0; j < N; j++) {
            cout << d[j] << " ";
        }
        cout << endl;
    }
}


int main() {
    int tests;
    cin >> tests;

    while (tests > 0) {
        cin >> N;

        lat = vector<vector<int>>(N, vector<int>(N)); 
        adj = vector<vector<int>>(N, vector<int>());

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < i; j++) {
                int value;
                cin >> value;
                lat[i][j] = value;
                lat[j][i] = value;
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
        solve();
        tests--;
    }
}
