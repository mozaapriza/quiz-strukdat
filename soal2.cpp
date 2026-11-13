#include <iostream>
#include <queue>
#include <stack>
#include <string>

using namespace std;

struct NodeBuku {
    int idBuku;
    string judulBuku;
    NodeBuku* left;
    NodeBuku* right;
};

NodeBuku* buatNode(int id, string judul) {
    NodeBuku* baru = new NodeBuku();
    baru->idBuku = id;
    baru->judulBuku = judul;
    baru->left = nullptr;
    baru->right = nullptr;
    return baru;
}

NodeBuku* insertBST(NodeBuku* root, int id, string judul) {
    if (root == nullptr) {
        return buatNode(id, judul);
    }
    if (id < root->idBuku) {
        root->left = insertBST(root->left, id, judul);
    } else if (id > root->idBuku) {
        root->right = insertBST(root->right, id, judul);
    } else {
        cout << "ID Buku " << id << " sudah ada di sistem!\n";
    }
    return root;
}

bool searchBST(NodeBuku* root, int targetId) {
    if (root == nullptr) return false;
    if (root->idBuku == targetId) {
        cout << "Buku Ditemukan -> ID: " << root->idBuku << " | Judul: " << root->judulBuku << endl;
        return true;
    }
    if (targetId < root->idBuku) {
        return searchBST(root->left, targetId);
    }
    return searchBST(root->right, targetId);
}

void preOrder(NodeBuku* root) {
    if (root == nullptr) return;
    cout << "[" << root->idBuku << " - " << root->judulBuku << "] ";
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(NodeBuku* root) {
    if (root == nullptr) return;
    inOrder(root->left);
    cout << "[" << root->idBuku << " - " << root->judulBuku << "] ";
    inOrder(root->right);
}

void postOrder(NodeBuku* root) {
    if (root == nullptr) return;
    postOrder(root->left);
    postOrder(root->right);
    cout << "[" << root->idBuku << " - " << root->judulBuku << "] ";
}

int main() {
    queue<string> antreanPinjam;      
    stack<string> riwayatKembali;     
    NodeBuku* rootBST = nullptr;      

    int pilihan;
    do {
        cout << "\n=== SISTEM ANTREAN & BUKU PERPUSTAKAAN ===\n";
        cout << "1. Tambah Antrean Peminjaman\n";
        cout << "2. Layani Antrean Peminjaman\n";
        cout << "3. Tampilkan Antrean Saat Ini\n";
        cout << "4. Catat Pengembalian Buku\n";
        cout << "5. Tampilkan Riwayat Pengembalian\n";
        cout << "6. Tambah ID Buku ke Katalog\n";
        cout << "7. Cari ID Buku\n";
        cout << "8. Tampilkan Semua ID Buku\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                string namaMhs;
                cin.ignore();
                cout << "Masukkan Nama Mahasiswa yang mengantre: ";
                getline(cin, namaMhs);
                antreanPinjam.push(namaMhs);
                cout << namaMhs << " berhasil masuk antrean.\n";
                break;
            }
            case 2: {
                if (antreanPinjam.empty()) {
                    cout << "Antrean kosong, tidak ada mahasiswa yang dilayani.\n";
                } else {
                    cout << "Melayani peminjaman untuk: " << antreanPinjam.front() << " (Keluar dari antrean)\n";
                    antreanPinjam.pop(); 
                }
                break;
            }
            case 3: {
                if (antreanPinjam.empty()) {
                    cout << "Antrean peminjaman saat ini kosong.\n";
                } else {
                    cout << "Daftar Antrean (Depan -> Belakang): ";
                    queue<string> tempQ = antreanPinjam; 
                    while (!tempQ.empty()) {
                        cout << tempQ.front();
                        tempQ.pop();
                        if (!tempQ.empty()) cout << " -> ";
                    }
                    cout << endl;
                }
                break;
            }
            case 4: {
                string infoKembali;
                cin.ignore();
                cout << "Masukkan Judul/ID Buku yang dikembalikan: ";
                getline(cin, infoKembali);
                riwayatKembali.push(infoKembali);
                cout << "Pengembalian '" << infoKembali << "' tercatat di tumpukan paling atas.\n";
                break;
            }
            case 5: {
                if (riwayatKembali.empty()) {
                    cout << "Belum ada riwayat pengembalian buku.\n";
                } else {
                    cout << "Riwayat Pengembalian (Terbaru/Atas -> Terlama/Bawah):\n";
                    stack<string> tempS = riwayatKembali; 
                    int no = 1;
                    while (!tempS.empty()) {
                        cout << no++ << ". " << tempS.top() << endl; 
                        tempS.pop();
                    }
                }
                break;
            }
            case 6: {
                int id;
                string judul;
                cout << "Masukkan ID Buku (angka): ";
                cin >> id;
                cin.ignore();
                cout << "Masukkan Judul Buku: ";
                getline(cin, judul);
                rootBST = insertBST(rootBST, id, judul);
                cout << "Buku berhasil disimpan ke BST.\n";
                break;
            }
            case 7: {
                int cariId;
                cout << "Masukkan ID Buku yang dicari: ";
                cin >> cariId;
                if (!searchBST(rootBST, cariId)) {
                    cout << "Buku dengan ID " << cariId << " tidak ditemukan.\n";
                }
                break;
            }
            case 8: {
                if (rootBST == nullptr) {
                    cout << "Katalog BST masih kosong.\n";
                } else {
                    cout << "\nPre-Order  : "; preOrder(rootBST);
                    cout << "\nIn-Order   : "; inOrder(rootBST);
                    cout << "\nPost-Order : "; postOrder(rootBST);
                    cout << endl;
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