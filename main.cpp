#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

#define MAX_USER 100

struct Billing {
    int jam;
    int masaAktif;
};

struct User {
    string nama;
    string nim;
    Billing billing;
};

User daftarUser[MAX_USER];
int jumlahUser = 0;

User* cariUser(User* daftarUser, int jumlahUser, string nama) {
    for (int i = 0; i < jumlahUser; i++) {
        if (daftarUser[i].nama == nama) {
            return &daftarUser[i];
        }
    }
    return nullptr;
}

bool cekNama(User* daftarUser, int jumlahUser, string namaBaru) {
    User* hasil = cariUser(daftarUser, jumlahUser, namaBaru);
    if (hasil != nullptr) {
        return hasil->nama == namaBaru;
    }
    return false;
}

void registerUser(User* daftarUser, int& jumlahUser) {
    if (jumlahUser < MAX_USER) {

        string namaBaru;

        cout << "\n===== REGISTER =====\n";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Masukkan Nama Lengkap : ";
        getline(cin, namaBaru);

        if (cekNama(daftarUser, jumlahUser, namaBaru)) {
            cout << "Nama sudah digunakan!\n";
            return;
        }

        daftarUser[jumlahUser].nama = namaBaru;

        cout << "Masukkan NIM : ";
        cin >> daftarUser[jumlahUser].nim;

        daftarUser[jumlahUser].billing.jam = 0;
        daftarUser[jumlahUser].billing.masaAktif = 0;

        jumlahUser++;

        cout << "Register Berhasil!\n";
    } else {
        cout << "Kapasitas penuh!\n";
    }
}

bool login(User* daftarUser, int jumlahUser, bool& admin, int& userIndex) {
    string namaInput;
    string nimInput;
    int percobaan = 0;

    while (percobaan < 3) {
        cout << "\n===== LOGIN =====\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nMasukkan Nama : ";
        getline(cin, namaInput);

        cout << "Masukkan NIM : ";
        cin >> nimInput;

        if (namaInput == "Admin" && nimInput == "076") {
            admin = true;
            return true;
        }

        for (int i = 0; i < jumlahUser; i++) {
            if (namaInput == daftarUser[i].nama &&
                nimInput == daftarUser[i].nim) {
                admin = false;
                userIndex = i;
                return true;
            }
        }

        percobaan++;
        cout << "Login gagal!\n";
    }

    cout << "Kesempatan login habis.\n";
    return false;
}

void tampilkanMember(User* daftarUser, int jumlahUser) {
    if (jumlahUser == 0) {
        cout << "Belum ada member\n";
    } else {
        cout << "\n===== DATA MEMBER =====\n";
        cout << left
            << setw(5)  << "No"
            << setw(25) << "Nama"
            << setw(15) << "NIM"
            << setw(10) << "Jam"
            << setw(15) << "Masa Aktif"
            << endl;

        for (int i = 0; i < jumlahUser; i++) {
            cout << setw(5)  << i + 1
                << setw(25) << daftarUser[i].nama
                << setw(15) << daftarUser[i].nim
                << setw(10) << daftarUser[i].billing.jam
                << setw(10) << daftarUser[i].billing.masaAktif << " hari"
                << endl;
        }
    }
}

void tambahMember(User* daftarUser, int& jumlahUser) {
    if (jumlahUser < MAX_USER) {

        string namaBaru;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nama : ";
        getline(cin, namaBaru);

        if (cekNama(daftarUser, jumlahUser, namaBaru)) {
            cout << "Nama sudah digunakan!\n";
            return;
        }

        daftarUser[jumlahUser].nama = namaBaru;

        cout << "NIM : ";
        cin >> daftarUser[jumlahUser].nim;

        cout << "Billing Jam : ";
        cin >> daftarUser[jumlahUser].billing.jam;

        cout << "Masa Aktif : ";
        cin >> daftarUser[jumlahUser].billing.masaAktif;

        jumlahUser++;

        cout << "Member berhasil ditambahkan\n";
    } else {
        cout << "Kapasitas penuh\n";
    }
}

void updateIdentitas(User* daftarUser, int jumlahUser) {
    int index;

    cout << "Pilih nomor member : ";
    cin >> index;

    if (index > 0 && index <= jumlahUser) {
        User* target = &daftarUser[index - 1];

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nama baru : ";
        getline(cin, target->nama);

        cout << "NIM baru : ";
        cin >> target->nim;

        cout << "Data Member berhasil diubah\n";
    } else {
        cout << "Nomor tidak valid\n";
    }
}

void updateBilling(User* daftarUser, int jumlahUser) {
    int index;

    cout << "Pilih nomor member : ";
    cin >> index;

    if (index > 0 && index <= jumlahUser) {
        User* target = &daftarUser[index - 1];

        cout << "Billing Jam : ";
        cin >> target->billing.jam;

        cout << "Masa Aktif : ";
        cin >> target->billing.masaAktif;

        cout << "Data billing berhasil diubah\n";
    } else {
        cout << "Nomor tidak valid\n";
    }
}

void hapusMember(User* daftarUser, int& jumlahUser) {
    int index;

    cout << "Pilih nomor member : ";
    cin >> index;

    if (index > 0 && index <= jumlahUser) {
        for (int i = index - 1; i < jumlahUser - 1; i++) {
            daftarUser[i] = daftarUser[i + 1];
        }
        jumlahUser--;
        cout << "Member berhasil dihapus\n";
    } else {
        cout << "Nomor tidak valid\n";
    }
}

void sortNama(User* daftarUser, int jumlahUser) {
    for (int i = 0; i < jumlahUser - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < jumlahUser; j++) {
            if (daftarUser[j].nama > daftarUser[maxIdx].nama)
                maxIdx = j;
        }
        if (maxIdx != i)
            swap(daftarUser[i], daftarUser[maxIdx]);
    }
}

void sortBilling(User* daftarUser, int jumlahUser) {
    for (int i = 1; i < jumlahUser; i++) {
        User key = daftarUser[i];
        int j = i - 1;
        while (j >= 0 && daftarUser[j].billing.jam > key.billing.jam) {
            daftarUser[j + 1] = daftarUser[j];
            j--;
        }
        daftarUser[j + 1] = key;
    }
}

void sortMasaAktif(User* daftarUser, int jumlahUser) {
    for (int i = 0; i < jumlahUser - 1; i++) {
        for (int j = 0; j < jumlahUser - i - 1; j++) {
            if (daftarUser[j].billing.masaAktif < daftarUser[j + 1].billing.masaAktif)
                swap(daftarUser[j], daftarUser[j + 1]);
        }
    }
}

void sortByNim(User* daftarUser, int jumlahUser) {
    for (int i = 0; i < jumlahUser - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < jumlahUser; j++) {
            if (daftarUser[j].nim < daftarUser[minIdx].nim)
                minIdx = j;
        }
        if (minIdx != i)
            swap(daftarUser[i], daftarUser[minIdx]);
    }
}

User* binarySearchNim(User* daftarUser, int jumlahUser, string targetNim) {
    int low = 0, high = jumlahUser - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if ((daftarUser + mid)->nim == targetNim)
            return daftarUser + mid;
        else if ((daftarUser + mid)->nim < targetNim)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return nullptr;
}

User* linearSearchNama(User* daftarUser, int jumlahUser, string targetNama) {
    for (int i = 0; i < jumlahUser; i++) {
        if ((daftarUser + i)->nama == targetNama)
            return daftarUser + i;
    }
    return nullptr;
}

void menuCariNim(User* daftarUser, int jumlahUser) {
    string targetNim;
    cout << "\n===== CARI MEMBER (Binary Search by NIM) =====\n";
    cout << "Masukkan NIM : ";
    cin >> targetNim;

    sortByNim(daftarUser, jumlahUser);

    User* hasil = binarySearchNim(daftarUser, jumlahUser, targetNim);

    if (hasil != nullptr) {
        cout << "\nMember ditemukan:\n";
        cout << left
            << setw(25) << "Nama"
            << setw(15) << "NIM"
            << setw(10) << "Jam"
            << setw(15) << "Masa Aktif"
            << endl;
        cout << setw(25) << hasil->nama
            << setw(15) << hasil->nim
            << setw(10) << hasil->billing.jam
            << setw(10) << hasil->billing.masaAktif << " hari"
            << endl;
    } else {
        cout << "Member dengan NIM " << targetNim << " tidak ditemukan.\n";
    }
}

void menuCariNama(User* daftarUser, int jumlahUser) {
    string targetNama;
    cout << "\n===== CARI MEMBER (Linear Search by Nama) =====\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Masukkan Nama : ";
    getline(cin, targetNama);

    User* hasil = linearSearchNama(daftarUser, jumlahUser, targetNama);

    if (hasil != nullptr) {
        cout << "\nMember ditemukan:\n";
        cout << left
            << setw(25) << "Nama"
            << setw(15) << "NIM"
            << setw(10) << "Jam"
            << setw(15) << "Masa Aktif"
            << endl;
        cout << setw(25) << hasil->nama
            << setw(15) << hasil->nim
            << setw(10) << hasil->billing.jam
            << setw(10) << hasil->billing.masaAktif << " hari"
            << endl;
    } else {
        cout << "Member dengan nama " << targetNama << " tidak ditemukan.\n";
    }
}

void menuAdmin(User* daftarUser, int& jumlahUser) {
    int menuAdmin;

    do {
        cout << "\n===== MENU ADMIN =====\n";
        cout << "1.  Tambah Member\n";
        cout << "2.  Lihat Semua Member\n";
        cout << "3.  Update Nama & NIM\n";
        cout << "4.  Update Billing & Masa Aktif\n";
        cout << "5.  Hapus Member\n";
        cout << "6.  Sort Nama\n";
        cout << "7.  Sort Billing\n";
        cout << "8.  Sort Masa Aktif\n";
        cout << "9.  Cari Member by NIM (Binary Search)\n";
        cout << "10. Cari Member by Nama (Linear Search)\n";
        cout << "11. Logout\n";
        cout << "Pilihan : ";
        cin >> menuAdmin;

        switch (menuAdmin) {
            case 1:  tambahMember(daftarUser, jumlahUser); break;
            case 2:  tampilkanMember(daftarUser, jumlahUser); break;
            case 3:  updateIdentitas(daftarUser, jumlahUser); break;
            case 4:  updateBilling(daftarUser, jumlahUser); break;
            case 5:  hapusMember(daftarUser, jumlahUser); break;
            case 6:  sortNama(daftarUser, jumlahUser);
                     tampilkanMember(daftarUser, jumlahUser); break;
            case 7:  sortBilling(daftarUser, jumlahUser);
                     tampilkanMember(daftarUser, jumlahUser); break;
            case 8:  sortMasaAktif(daftarUser, jumlahUser);
                     tampilkanMember(daftarUser, jumlahUser); break;
            case 9:  menuCariNim(daftarUser, jumlahUser); break;
            case 10: menuCariNama(daftarUser, jumlahUser); break;
            case 11: break;
            default: cout << "Pilihan tidak valid\n";
        }
    } while (menuAdmin != 11);
}

void menuUser(User* daftarUser, int jumlahUser, int userIndex) {
    int menuUser;

    User* userAktif = &daftarUser[userIndex];

    do {
        cout << "\n===== MENU USER =====\n";
        cout << "1. Lihat Profil\n";
        cout << "2. Update Nama\n";
        cout << "3. Update NIM\n";
        cout << "4. Logout\n";
        cout << "Pilihan : ";
        cin >> menuUser;

        switch (menuUser) {
            case 1:
                cout << "\nNama       : " << userAktif->nama << endl;
                cout << "NIM        : " << userAktif->nim << endl;
                cout << "Billing Jam: " << userAktif->billing.jam << endl;
                cout << "Masa Aktif : " << userAktif->billing.masaAktif << " hari" << endl;
                break;

            case 2:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Masukkan nama baru : ";
                getline(cin, userAktif->nama);
                cout << "Nama berhasil diperbarui\n";
                break;

            case 3:
                cout << "Masukkan NIM baru : ";
                cin >> userAktif->nim;
                cout << "NIM berhasil diperbarui\n";
                break;

            case 4:
                break;

            default:
                cout << "Pilihan tidak valid\n";
        }
    } while (menuUser != 4);
}

int main() {
    int menuAwal;

    do {
        cout << "\n===== MENU AWAL =====\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Keluar\n";
        cout << "Pilihan : ";
        cin >> menuAwal;

        switch (menuAwal) {
            case 1:
                registerUser(daftarUser, jumlahUser);
                break;

            case 2: {
                bool admin = false;
                int userIndex = -1;

                if (login(daftarUser, jumlahUser, admin, userIndex)) {
                    if (admin) {
                        menuAdmin(daftarUser, jumlahUser);
                    } else {
                        menuUser(daftarUser, jumlahUser, userIndex);
                    }
                }
                break;
            }

            case 3:
                break;

            default:
                cout << "Pilihan tidak valid\n";
        }
    } while (menuAwal != 3);

    cout << "Terimakasih Sudah Menggunakan Program!\n";

    return 0;
}