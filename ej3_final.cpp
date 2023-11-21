#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N;
vector<vector<int>> tablero;
vector<vector<int>> subfilas;
vector<vector<int>> subcolumnas;

int INF = 100000000;
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
            if (parent[next] == -1 && capacity[cur][next]) {
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
    vector<int> parent(N);
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


int calcular_subfilas(){
    int numero_subfila = 0;
    bool marcada = false;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; ++j) {
            if (tablero[i][j]==1){
                subfilas[i][j]=-1;
                if (j!=0 && tablero[i][j-1]!=1){
                    numero_subfila++;
                    marcada = false;
                }
            } else {
                subfilas[i][j]=numero_subfila;
                marcada = true;
            }
        }
        if (marcada) numero_subfila++;
    }
    return numero_subfila;
}


int calcular_subcolumnas(){
    int numero_subcolumna = 0;
    bool marcada = false;
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; ++i) {
            if (tablero[i][j]==1){
                subcolumnas[i][j]=-1;
                if (i!=0 && tablero[i-1][j]!=1 ){
                    numero_subcolumna++;
                    marcada = false;
                }
            } else {
                subcolumnas[i][j]=numero_subcolumna;
                marcada = true;
            }
        }
        if (marcada) numero_subcolumna++;
    }
    return numero_subcolumna;
}


void calcular_aristas(int offset, int s, int t) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int subfila = subfilas[i][j];
            int subcolumna = subcolumnas[i][j];
            if (subfila != -1 && subcolumna != -1) {
                // Agregar arista entre subfila y subcolumna
                adj[subfila].push_back(subcolumna + offset);
                adj[subcolumna + offset].push_back(subfila);
                capacity[subfila][subcolumna + offset] = 1; // Podría ser INF

                // Agregar arista entre subfila y s
                adj[s].push_back(subfila);
                adj[subfila].push_back(s);
                capacity[s][subfila] = 1;

                // Agregar arista entre subcolumna y t
                adj[t].push_back(subcolumna + offset);
                adj[subcolumna + offset].push_back(t);
                capacity[subcolumna + offset][t] = 1;
            }
        }
    }
}

int main() {
    int tests;
    cin >> tests;

    while (tests > 0) {
        // Leer entrada
        cin >> N;

        // Inicializar estructuras
        tablero = vector<vector<int>>(N, vector<int>(N));
        subfilas = vector<vector<int>>(N, vector<int>(N));
        subcolumnas = vector<vector<int>>(N, vector<int>(N));

        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; ++j) {
                cin >> tablero[i][j];
            }
        }

        int cant_subfilas = calcular_subfilas();
        int cant_subcolumnas = calcular_subcolumnas();

        int cant_nodos = cant_subfilas + cant_subcolumnas + 2;
        adj = vector<vector<int>>(cant_nodos, vector<int>());
        capacity = vector<vector<int>>(cant_nodos, vector<int>(cant_nodos, 0));

        int s = cant_nodos - 2, t = cant_nodos - 1;
        calcular_aristas(cant_subfilas, s, t);

        N = cant_nodos; // Actualizar N
        cout << maxflow(s, t) << endl;
        tests--;
    }
}
