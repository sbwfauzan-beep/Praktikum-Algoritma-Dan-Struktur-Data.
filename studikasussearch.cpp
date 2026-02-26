#include <iostream>
using namespace std;

struct Buku {
    string nama;
    int harga;
};

int main() {

    Buku data[6] = {{"A", 75000},{"B", 90000},{"D", 80000},{"C", 70000},{"E", 85000}};
        //saya bingung ngasih nama bukunya jadi gini aja deh

    int n = 5;
    string cari;
    int menu;

    do {
        cout << "=== MENU TOKO BUKU ===" << endl;
        cout << "1. Sequential Tanpa Sentinel" << endl;
        cout << "2. Sequential Dengan Sentinel" << endl;
        cout << "3. Binary Search" << endl;
        cout << "Pilih metode: ";
        cin >> menu;
        cin.ignore();

        cout << "Masukkan nama buku yang dicari: ";
        getline(cin, cari);

        //tanpa sentinel
        if(menu == 1) {

            bool found = false;
            int i = 0;

            while(i < n && found == false) {
                if(data[i].nama == cari) {
                    found = true;
                } else {
                    i++;
                }
            }

            if(found == true) {
                cout << "Buku ditemukan!\n";
                cout << "Harga: " << data[i].harga << endl;
            } else {
                cout << "Buku tidak ditemukan.\n";
            }
        }
        // dengan sentinel
        else if(menu == 2) {

            bool found = false;
            int i = 0;

            data[n].nama = cari;

            while(found == false) {
                if(data[i].nama == cari) {
                    found = true;
                } else {
                    i++;
                }
            }

            if(i < n) {
                cout << "Buku ditemukan!\n";
                cout << "Harga: " << data[i].harga << endl;
            } else {
                cout << "Buku tidak ditemukan.\n";
            }
        }

        // binary search
        else if(menu == 3) {

            bool found = false;
            int kiri = 0;
            int kanan = n - 1;
            int tengah;

            while(kiri <= kanan && found == false) {
                tengah = (kiri + kanan) / 2;

                if(data[tengah].nama == cari) {
                    found = true;
                }
                else if(data[tengah].nama < cari) {
                    kiri = tengah + 1;
                }
                else {
                    kanan = tengah - 1;
                }
            }

            if(found == true) {
                cout << "Buku Ada" << endl;
                cout << "Harga: " << data[tengah].harga << endl;
            } else {
                cout << "Buku tidak ada." << endl;
            }
        }

        else {
            cout << "Menu tidak valid." << endl;
        }

        cout << "Cari lagi? (1 untuk Ya / 0 untuk Tidak): " << endl;
        cin >> menu;

    } while(menu == 1);

    cout << "Program selesai.\n";
}
