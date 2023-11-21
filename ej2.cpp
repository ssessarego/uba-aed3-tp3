#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;

vector<vector<int>> lat;
vector<vector<int>> dist;
int N;
const int INF = 1000000000;


bool latencias_correctas(){
    // Se verifica que las latencias sean válidas mediante el algoritmo de 
    // Floyd-Warshall
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (lat[i][j] > lat[i][k] + lat[k][j]) return false;
            }
        }
    }
    return true;
}


void minimizar_enlaces(){
    // Se eliminan los enlaces que están de más (no afectan a las latencias) para que 
    // el grafo resultante tenga la mínima cantidad de ejes que cumplen las latencias
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (i == k || j == k) continue;
                // En lugar de borrar el enlace, se le coloca distancia infinita
                if (lat[i][j] == lat[i][k] + lat[k][j]) dist[i][j] = INF;
            }
        }
    }
}


void floyd_warshall() {
    // Se calculan las distancias mínimas entre cada par de nodos
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
        }
    }
}


int main() {
    int tests;
    cin >> tests;

    while (tests > 0) {
        cin >> N;

        // Matriz que contiene las latencias entre cada par de nodos
        lat = vector<vector<int>>(N, vector<int>(N)); 
        // Matriz que contiene la distancia entre cada par de nodos
        dist = vector<vector<int>>(N, vector<int>(N));

        for (int i = 0; i < N; i++){ 
            lat[i][i] = 0;
            dist[i][i] = 0;
        }
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < i; j++) {
                int value;
                cin >> value;
                lat[i][j] = value;
                lat[j][i] = value;
                dist[i][j] = 1;
                dist[j][i] = 1;
            }
        }

        bool possible = latencias_correctas();

        if (!possible) {
            cout << "IMPOSIBLE" << endl;
        } else {
            cout << "POSIBLE" << endl;
            minimizar_enlaces();
            floyd_warshall();
            
            for (int i = 0; i < N; i++){
                for (int j = 0; j < N; j++) {
                    cout << dist[i][j] << " ";
                }
                cout << endl;
            }
        }

        tests--;
    }
}
