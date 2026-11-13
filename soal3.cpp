#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <climits>
#include <algorithm>
#include <cctype>

using namespace std;

const int V = 6; 
char namaVertex[V] = {'A', 'B', 'C', 'D', 'E', 'F'};

int keIndeks(char huruf) {
    huruf = toupper(huruf);
    if (huruf >= 'A' && huruf <= 'F') {
        return huruf - 'A';
    }
    return -1;
}

void bfs(int adj[V][V], int start) {
    bool visited[V] = {false};
    queue<int> q;

    visited[start] = true;
    q.push(start);

    cout << "Hasil Penelusuran BFS dari " << namaVertex[start] << ": ";
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        cout << namaVertex[curr] << " ";

        for (int i = 0; i < V; i++) {
            if (adj[curr][i] > 0 && !visited[i]) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout << endl;
}

void dfsHelper(int adj[V][V], int curr, bool visited[]) {
    visited[curr] = true;
    cout << namaVertex[curr] << " ";

    for (int i = 0; i < V; i++) {
        if (adj[curr][i] > 0 && !visited[i]) {
            dfsHelper(adj, i, visited);
        }
    }
}

void dfs(int adj[V][V], int start) {
    bool visited[V] = {false};
    cout << "Hasil Penelusuran DFS dari " << namaVertex[start] << ": ";
    dfsHelper(adj, start, visited);
    cout << endl;
}

void dijkstra(int adj[V][V], int start, int target) {
    int dist[V];          
    bool visited[V];      
    int parent[V];        

    for (int i = 0; i < V; i++) {
        dist[i] = INT_MAX;
        visited[i] = false;
        parent[i] = -1;
    }

    dist[start] = 0;

    for (int count = 0; count < V - 1; count++) {
        int minDist = INT_MAX, u = -1;
        for (int v = 0; v < V; v++) {
            if (!visited[v] && dist[v] <= minDist) {
                minDist = dist[v];
                u = v;
            }
        }

        if (u == -1) break;
        visited[u] = true;

        for (int v = 0; v < V; v++) {
            if (!visited[v] && adj[u][v] > 0 && dist[u] != INT_MAX &&
                dist[u] + adj[u][v] < dist[v]) {
                dist[v] = dist[u] + adj[u][v];
                parent[v] = u;
            }
        }
    }

    cout << "\n--- Hasil Pencarian Rute Terpendek (Dijkstra) ---\n";
    if (dist[target] == INT_MAX) {
        cout << "Tidak ada rute dari " << namaVertex[start] << " ke " << namaVertex[target] << ".\n";
        return;
    }

    vector<char> rute;
    for (int curr = target; curr != -1; curr = parent[curr]) {
        rute.push_back(namaVertex[curr]);
    }
    reverse(rute.begin(), rute.end());

    cout << "Rute yang dilalui : ";
    for (size_t i = 0; i < rute.size(); i++) {
        cout << rute[i];
        if (i < rute.size() - 1) cout << " -> ";
    }
    cout << "\nTotal Jarak        : " << dist[target] << endl;
}

void tampilkanMatrix(int adj[V][V]) {
    cout << "\n--- Adjacency Matrix (Bobot Jarak) ---\n   ";
    for (int i = 0; i < V; i++) cout << namaVertex[i] << "  ";
    cout << endl;
    for (int i = 0; i < V; i++) {
        cout << namaVertex[i] << "  ";
        for (int j = 0; j < V; j++) {
            cout << adj[i][j] << "  ";
        }
        cout << endl;
    }
}

int main() {
    int adj[V][V] = {0};

    auto tambahSisi = [&](char v1, char v2, int bobot) {
        int i = keIndeks(v1);
        int j = keIndeks(v2);
        adj[i][j] = bobot;
        adj[j][i] = bobot;
    };

    tambahSisi('A', 'B', 4);
    tambahSisi('A', 'C', 2);
    tambahSisi('B', 'C', 1);
    tambahSisi('B', 'D', 5);
    tambahSisi('B', 'E', 3);
    tambahSisi('C', 'D', 8);
    tambahSisi('C', 'E', 6);
    tambahSisi('D', 'E', 2);
    tambahSisi('D', 'F', 4);
    tambahSisi('E', 'F', 3);

    int pilihan;
    do {
        cout << "\n=== SISTEM PENCARIAN RUTE KAMPUS ===\n";
        cout << "1. Tampilkan Adjacency Matrix\n";
        cout << "2. Penelusuran Graf (BFS & DFS)\n";
        cout << "3. Cari Rute Terpendek (Dijkstra)\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanMatrix(adj);
                break;

            case 2: {
                char awal;
                cout << "Masukkan vertex awal penelusuran (A-F): ";
                cin >> awal;
                int idxAwal = keIndeks(awal);
                if (idxAwal == -1) {
                    cout << "Vertex tidak valid! Gunakan huruf A sampai F.\n";
                } else {
                    bfs(adj, idxAwal);
                    dfs(adj, idxAwal);
                }
                break;
            }
            case 3: {
                char awal, tujuan;
                cout << "Masukkan vertex awal (A-F)   : ";
                cin >> awal;
                cout << "Masukkan vertex tujuan (A-F) : ";
                cin >> tujuan;

                int idxAwal = keIndeks(awal);
                int idxTujuan = keIndeks(tujuan);

                if (idxAwal == -1 || idxTujuan == -1) {
                    cout << "Vertex tidak valid! Gunakan huruf A sampai F.\n";
                } else {
                    dijkstra(adj, idxAwal, idxTujuan);
                }
                break;
            }
            case 0:
                cout << "Program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    return 0;
}