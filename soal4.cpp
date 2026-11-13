#include <iostream>
#include <string>

using namespace std;

const int TABLE_SIZE = 20;

enum StatusSlot {
    KOSONG,
    TERISI,
    DIHAPUS
};

struct EntryMahasiswa {
    long long nim;      
    string nama;        
    StatusSlot status;  
};

class HashTableMahasiswa {
private:
    EntryMahasiswa table[TABLE_SIZE];
    int jumlahData;

    int hash1(long long key) {
        return key % TABLE_SIZE;
    }

    int hash2(long long key) {
        return 19 - (key % 19);
    }

public:
    HashTableMahasiswa() {
        jumlahData = 0;
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i].nim = 0;
            table[i].nama = "";
            table[i].status = KOSONG;
        }
    }

    void insert(long long nim, string nama) {
        if (jumlahData >= TABLE_SIZE) {
            cout << "[GAGAL] Hash Table sudah penuh (20/20)!\n";
            return;
        }

        int h1 = hash1(nim);
        int h2 = hash2(nim);

        for (int i = 0; i < TABLE_SIZE; i++) {
            int indeks = (h1 + i * h2) % TABLE_SIZE;

            
            if (table[indeks].status == TERISI && table[indeks].nim == nim) {
                table[indeks].nama = nama;
                cout << "[UPDATE] NIM " << nim << " sudah ada di indeks [" << indeks << "], nama diperbarui.\n";
                return;
            }

            if (table[indeks].status == KOSONG || table[indeks].status == DIHAPUS) {
                table[indeks].nim = nim;
                table[indeks].nama = nama;
                table[indeks].status = TERISI;
                jumlahData++;

                if (i == 0) {
                    cout << "[INSERT] NIM " << nim << " (" << nama << ") -> masuk ke indeks [" << indeks << "]\n";
                } else {
                    cout << "[COLLISION!] NIM " << nim << " (" << nama << ") bertabrakan di [" << h1
                         << "], dipindah via Double Hashing (i=" << i << ") ke indeks [" << indeks << "]\n";
                }
                return;
            }
        }
        cout << "[GAGAL] Tidak ditemukan slot kosong untuk NIM " << nim << endl;
    }

    void search(long long nim) {
        int h1 = hash1(nim);
        int h2 = hash2(nim);

        for (int i = 0; i < TABLE_SIZE; i++) {
            int indeks = (h1 + i * h2) % TABLE_SIZE;

            if (table[indeks].status == KOSONG) {
                break;
            }

            if (table[indeks].status == TERISI && table[indeks].nim == nim) {
                cout << "[SEARCH] Ditemukan di indeks [" << indeks << "] (langkah ke-" << i + 1 << ") -> "
                     << "NIM: " << table[indeks].nim << " | Nama: " << table[indeks].nama << endl;
                return;
            }
        }
        cout << "[SEARCH] Mahasiswa dengan NIM " << nim << " tidak ditemukan.\n";
    }

    void remove(long long nim) {
        int h1 = hash1(nim);
        int h2 = hash2(nim);

        for (int i = 0; i < TABLE_SIZE; i++) {
            int indeks = (h1 + i * h2) % TABLE_SIZE;

            if (table[indeks].status == KOSONG) {
                break;
            }

            if (table[indeks].status == TERISI && table[indeks].nim == nim) {
                cout << "[REMOVE] Data NIM " << nim << " (" << table[indeks].nama
                     << ") di indeks [" << indeks << "] berhasil dihapus.\n";
                table[indeks].status = DIHAPUS; 
                table[indeks].nim = 0;
                table[indeks].nama = "";
                jumlahData--;
                return;
            }
        }
        cout << "[REMOVE] Gagal menghapus, NIM " << nim << " tidak ditemukan.\n";
    }

    void display() {
        cout << "\n================ ISI HASH TABLE (Ukuran 20) ================\n";
        cout << "Indeks\t| Status\t| NIM (Key)\t| Nama (Value)\n";
        cout << "------------------------------------------------------------\n";
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "[" << i << "]\t| ";
            if (table[i].status == TERISI) {
                cout << "TERISI\t| " << table[i].nim << "\t| " << table[i].nama << endl;
            } else if (table[i].status == DIHAPUS) {
                cout << "DIHAPUS\t| -\t\t| -" << endl;
            } else {
                cout << "KOSONG\t| -\t\t| -" << endl;
            }
        }
        cout << "Total data aktif: " << jumlahData << "/" << TABLE_SIZE << endl;
        cout << "============================================================\n";
    }
};

int main() {
    HashTableMahasiswa ht;
    int pilihan;

    do {
        cout << "\n=== SISTEM DATA MAHASISWA (HASH TABLE - DOUBLE HASHING) ===\n";
        cout << "1. Muat Data\n";
        cout << "2. Insert Data Mahasiswa Baru\n";
        cout << "3. Search Mahasiswa berdasarkan NIM\n";
        cout << "4. Remove Data Mahasiswa berdasarkan NIM\n";
        cout << "5. Display Isi Hash Table\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: {
                cout << "\n--- Memasukkan Data Mahasiswa ---\n";
                ht.insert(251401020, "Moza");      
                ht.insert(251401040, "Elle");      
                ht.insert(251401060, "Raka");      
                ht.insert(251401001, "Budi");      
                ht.insert(251401021, "Siti");      
                ht.insert(251401002, "Andi");      
                ht.insert(251401022, "Dina");      
                ht.insert(251401003, "Fajar");     
                ht.insert(251401004, "Gita");      
                ht.insert(251401005, "Hadi");      
                ht.insert(251401006, "Indah");     
                ht.insert(251401007, "Joko");      
                ht.insert(251401008, "Kiki");      
                ht.insert(251401009, "Lina");      
                ht.insert(251401010, "Mira");      
                break;
            }
            case 2: {
                long long nim;
                string nama;
                cout << "Masukkan NIM (angka): ";
                cin >> nim;
                cin.ignore();
                cout << "Masukkan Nama       : ";
                getline(cin, nama);
                ht.insert(nim, nama);
                break;
            }
            case 3: {
                long long nim;
                cout << "Masukkan NIM yang dicari: ";
                cin >> nim;
                ht.search(nim);
                break;
            }
            case 4: {
                long long nim;
                cout << "Masukkan NIM yang akan dihapus: ";
                cin >> nim;
                ht.remove(nim);
                break;
            }
            case 5:
                ht.display();
                break;

            case 0:
                cout << "Program selesai.\n";
                break;
            default:
                cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);

    return 0;
}