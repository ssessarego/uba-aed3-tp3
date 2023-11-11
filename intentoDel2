#include <iostream>
#include <vector>

using namespace std;
vector<vector<int>> lista;
vector<vector<int>> resultado;
int N;

string esTupla() {
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (lista[i][j] > lista[i][k] + lista[k][j]) {
                    return "IMPOSIBLE";
                }
            }
        }
    }
    return "POSIBLE";
}

void calcularDistancias() {
    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < i; j++) {
                if (i!=j && i!=k && k!=j && lista[i][j] == lista[i][k] + lista[k][j]) {
                    if (resultado[i][j]==0){
                        resultado[i][j]= 1000; //????????????
                        resultado[j][i]  = resultado[i][j];
                    }

                } else {
                    if(i==j){
                        resultado[i][j] = 0;
                    } else {
                        resultado[i][j] = 1;
                        resultado[j][i] = 1;
                    }
                }
            }
        }
    }
}

vector<vector<int>> resolver () {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            resultado[i][j] = 0;
        }
    }
    calcularDistancias();
    return resultado;
}

int main() {
    int tests;
    cin >> tests;

    while(tests > 0) {
        cin >> N;
        lista = vector<vector<int>> (N, vector<int>());
        lista[0].push_back(0);
        resultado = vector<vector<int>> (N, vector<int>(N));
        for (int i = 1; i < N; i++) {
            for (int j = 0; j < i; j++) {
                int M;
                cin >> M;
                lista[i].push_back(M);
            }
        }
        tests--;
        string res=esTupla();
        vector<vector<int>> rta= resolver();
        if (res == "POSIBLE") {
            cout << res << endl;
            for (int i = 0; i < N; i++) {
                for (int j = 0; j < N; j++) {
                    cout << rta[i][j] << " ";
                }
                cout << endl;  // Agrega un salto de línea después de cada fila
            }
        } else {
            cout << res << endl;
        }
    }
    return 0;
}
