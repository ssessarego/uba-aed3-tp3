#include <iostream>
#include <vector>
#include <math.h>

using namespace std;


vector<vector<int>> aristasIn;
vector<vector<int>> distancia;
int INF = 1000000000;


int d(int w, int t) {
  if (w == 0) return 0; // w es el nodo inicial
  if (t < 0) return INF; // Se usaron mas pasadizos de los permitidos

  if (distancia[w][t] != INF) return distancia[w][t];

  for (int v : aristasIn[w]) {
    int siguiente;
    if (w == v + 1) { // v -> w NO es un pasadizo
      siguiente = d(v, t) + 1;
    } else {
      siguiente = d(v, t - 1) + 2;
    }
    distancia[w][t] = min(distancia[w][t], siguiente);
  }
  return distancia[w][t];
}


int main() {
  int tests;
  cin >> tests;

  while(tests > 0){
    int N, M;
    cin >> N >> M;

    // Para cada nodo w se guardan los nodos v tales que v -> w 
    // Agregar un nodo 0 inicial
    aristasIn = vector<vector<int>>(N + 1, vector<int>());

    // Inicializar cada nodo siendo "apuntado" por el anterior
    for(int i = 1; i <= N; i++) {
      aristasIn[i].push_back(i - 1);
    }

    // Agregar los pasadizos
    for(int i = 0; i < M; i++) {
      int comPasadizo, finPasadizo;
      cin >> comPasadizo >> finPasadizo;
      aristasIn[finPasadizo].push_back(comPasadizo);
    }
    
    // Inicializar las distancias en infinito
    distancia = vector<vector<int>>(N + 1, vector<int>(4, INF));

    int res = d(N, 3);
    cout << res << endl;

    tests--;
  }
  
  return 0;
}
