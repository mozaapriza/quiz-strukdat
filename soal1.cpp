#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Mahasiswa {
    string nim;
    string nama;
    float nilai;
    Mahasiswa* next;
};

class LinkedListMahasiswa {
private:
    Mahasiswa* head;

public:
    LinkedListMahasiswa() {
        head = nullptr;
    }

    void tambahMahasiswa(string nim, string nama, float nilai) {
        Mahasiswa* baru = new Mahasiswa();
        baru->nim = nim;
        baru->nama = nama;
        baru->nilai = nilai;
        baru->next = nullptr;

        if (head == nullptr) {
            head = baru;
        } else {
            Mahasiswa* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = baru;
        }
    }

    void tampilkanSemua() {
        if (head == nullptr) {
            cout << "Data mahasiswa masih kosong.\n";
            return;
        }
        Mahasiswa* temp = head;
        cout << "\n--- Daftar Data Mahasiswa ---\n";
        while (temp != nullptr) {
            cout << "NIM: " << temp->nim 
                 << " | Nama: " << temp->nama 
                 << " | Nilai: " << temp->nilai << endl;
            temp = temp->next;
        }
    }

    void cariNIM(string targetNim) {
        Mahasiswa* temp = head;
        int posisi = 1;
        bool ditemukan = false;

        while (temp != nullptr) {
            if (temp->nim == targetNim) {
                cout << "Mahasiswa Ditemukan pada urutan ke-" << posisi << "!\n";
                cout << "NIM: " << temp->nim << " | Nama: " << temp->nama << " | Nilai: " << temp->nilai << endl;
                ditemukan = true;
                break;
            }
            temp = temp->next;
            posisi++;
        }

        if (!ditemukan) {
            cout << "\nMahasiswa dengan NIM " << targetNim << " tidak ditemukan.\n";
        }
    }

    void tampilkanByNilai(float targetNilai) {
        Mahasiswa* temp = head;
        cout << "Detail Mahasiswa dengan nilai " << targetNilai << ":\n";
        while (temp != nullptr) {
            if (temp->nilai == targetNilai) {
                cout << "-> NIM: " << temp->nim << " | Nama: " << temp->nama << endl;
            }
            temp = temp->next;
        }
    }
};

void insertionSort(vector<float>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        float key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int binarySearch(const vector<float>& arr, float targetNilai) {
    int kiri = 0;
    int kanan = arr.size() - 1;

    while (kiri <= kanan) {
        int tengah = kiri + (kanan - kiri) / 2;
        if (arr[tengah] == targetNilai) return tengah;
        if (arr[tengah] < targetNilai) kiri = tengah + 1;
        else kanan = tengah - 1;
    }
    return -1;
}

int main() {
    LinkedListMahasiswa listMhs;
    vector<float> daftarNilai;
    bool sudahUrut = false; 
    int pilihan;

    do {
        cout << "\n=== SISTEM PENGELOLAAN NILAI MAHASISWA ===\n";
        cout << "1. Tambah Data Mahasiswa\n";
        cout << "2. Tampilkan Semua Data Mahasiswa\n";
        cout << "3. Urutkan Nilai\n";
        cout << "4. Cari Mahasiswa berdasarkan NIM\n";
        cout << "5. Cari Nilai Mahasiswa\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                string nim, nama;
                float nilai;
                cout << "NIM   : "; cin >> nim;
                cin.ignore();
                cout << "Nama  : "; getline(cin, nama);
                cout << "Nilai : "; cin >> nilai;

                listMhs.tambahMahasiswa(nim, nama, nilai);
                daftarNilai.push_back(nilai);
                sudahUrut = false; 
                cout << "Data berhasil ditambahkan!\n";
                break;
            }
            case 2:
                listMhs.tampilkanSemua();
                break;

            case 3:
                if (daftarNilai.empty()) {
                    cout << "Data nilai masih kosong!\n";
                } else {
                    insertionSort(daftarNilai);
                    sudahUrut = true;
                    cout << "Nilai setelah diurutkan (Insertion Sort): ";
                    for (float n : daftarNilai) cout << n << " ";
                    cout << endl;
                }
                break;

            case 4: {
                string cariNim;
                cout << "Masukkan NIM yang dicari: ";
                cin >> cariNim;
                listMhs.cariNIM(cariNim);
                break;
            }
            case 5: {
                if (daftarNilai.empty()) {
                    cout << "Data nilai masih kosong!\n";
                    break;
                }
                
                if (!sudahUrut) {
                    cout << "(Mengurutkan data otomatis terlebih dahulu...)\n";
                    insertionSort(daftarNilai);
                    sudahUrut = true;
                }
                float cariNilai;
                cout << "Masukkan Nilai yang dicari: ";
                cin >> cariNilai;

                int indeks = binarySearch(daftarNilai, cariNilai);
                if (indeks != -1) {
                    cout << "\nNilai " << cariNilai << " ditemukan di indeks ke-" << indeks;
                    listMhs.tampilkanByNilai(cariNilai); 
                } else {
                    cout << "\nNilai " << cariNilai << " tidak ditemukan.\n";
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