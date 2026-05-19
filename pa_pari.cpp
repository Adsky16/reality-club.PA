#include <iostream>
#include <iomanip>
#include <string>
#include <limits>
#include <algorithm>
#include <conio.h>
using namespace std;

#define MAX_USER 100
#define MAX_PAKET 20

struct Billing {
    double jam;
    int masaAktif;
};

struct User {
    string nama;
    string password;
    Billing billing;
};

struct Paket {
    string namaPaket;
    double jam;
    int masaAktif;
    double harga;
};

User daftarUser[MAX_USER];
int jumlahUser = 0;

Paket daftarPaket[MAX_PAKET];
int jumlahPaket = 0;

string inputPassword() {
    string pass = "";
    char ch;
    while ((ch = getch()) != '\r') {
        if (ch == '\b') {
            if (!pass.empty()) {
                pass.pop_back();
                cout << "\b \b";
            }
        } else {
            pass += ch;
            cout << '*';
        }
    }
    cout << endl;
    return pass;
}

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

        cout << "Masukkan Password : ";
        daftarUser[jumlahUser].password = inputPassword();

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
    string passInput;
    int percobaan = 0;

    while (percobaan < 3) {
        cout << "\n===== LOGIN =====\n";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nMasukkan Nama : ";
        getline(cin, namaInput);

        cout << "Masukkan Password : ";
        passInput = inputPassword();

        if (namaInput == "Admin" && passInput == "076") {
            admin = true;
            return true;
        }

        for (int i = 0; i < jumlahUser; i++) {
            if (namaInput == daftarUser[i].nama &&
                passInput == daftarUser[i].password) {
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
             << setw(12) << "Jam"
             << setw(15) << "Masa Aktif"
             << endl;

        for (int i = 0; i < jumlahUser; i++) {
            cout << setw(5)  << i + 1
                 << setw(25) << daftarUser[i].nama
                 << setw(12) << fixed << setprecision(1) << daftarUser[i].billing.jam
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

        cout << "Password : ";
        daftarUser[jumlahUser].password = inputPassword();

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

        cout << "Password baru : ";
        target->password = inputPassword();

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

User* linearSearchNama(User* daftarUser, int jumlahUser, string targetNama) {
    for (int i = 0; i < jumlahUser; i++) {
        if ((daftarUser + i)->nama == targetNama)
            return daftarUser + i;
    }
    return nullptr;
}

User* binarySearchId(User* daftarUser, int jumlahUser, int targetId) {
    int low = 0, high = jumlahUser - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (mid + 1 == targetId)
            return daftarUser + mid;
        else if (mid + 1 < targetId)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return nullptr;
}

void menuCariId(User* daftarUser, int jumlahUser) {
    int targetId;
    cout << "\n===== CARI MEMBER (Binary Search by ID) =====\n";
    tampilkanMember(daftarUser, jumlahUser);
    cout << "Masukkan ID (nomor urut) : ";
    cin >> targetId;

    User* hasil = binarySearchId(daftarUser, jumlahUser, targetId);

    if (hasil != nullptr) {
        cout << "\nMember ditemukan:\n";
        cout << left
             << setw(5)  << "ID"
             << setw(25) << "Nama"
             << setw(12) << "Jam"
             << setw(15) << "Masa Aktif"
             << endl;
        cout << setw(5)  << targetId
             << setw(25) << hasil->nama
             << setw(12) << fixed << setprecision(1) << hasil->billing.jam
             << setw(10) << hasil->billing.masaAktif << " hari"
             << endl;
    } else {
        cout << "Member dengan ID " << targetId << " tidak ditemukan.\n";
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
             << setw(12) << "Jam"
             << setw(15) << "Masa Aktif"
             << endl;
        cout << setw(25) << hasil->nama
             << setw(12) << fixed << setprecision(1) << hasil->billing.jam
             << setw(10) << hasil->billing.masaAktif << " hari"
             << endl;
    } else {
        cout << "Member dengan nama " << targetNama << " tidak ditemukan.\n";
    }
}

void tampilkanPaket(Paket* daftarPaket, int jumlahPaket) {
    if (jumlahPaket == 0) {
        cout << "Belum ada paket tersedia\n";
    } else {
        cout << "\n===== DAFTAR PAKET =====\n";
        cout << left
             << setw(5)  << "No"
             << setw(20) << "Nama Paket"
             << setw(12) << "Jam"
             << setw(15) << "Masa Aktif"
             << setw(15) << "Harga"
             << endl;

        for (int i = 0; i < jumlahPaket; i++) {
            cout << setw(5)  << i + 1
                 << setw(20) << daftarPaket[i].namaPaket
                 << setw(12) << fixed << setprecision(1) << daftarPaket[i].jam
                 << setw(15) << to_string(daftarPaket[i].masaAktif) + " hari"
                 << "Rp " << fixed << setprecision(0) << daftarPaket[i].harga
                 << endl;
        }
    }
}

void tambahPaket(Paket* daftarPaket, int& jumlahPaket) {
    if (jumlahPaket >= MAX_PAKET) {
        cout << "Kapasitas paket penuh\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Nama Paket : ";
    getline(cin, daftarPaket[jumlahPaket].namaPaket);

    cout << "Jam : ";
    cin >> daftarPaket[jumlahPaket].jam;

    cout << "Masa Aktif (hari) : ";
    cin >> daftarPaket[jumlahPaket].masaAktif;

    cout << "Harga : ";
    cin >> daftarPaket[jumlahPaket].harga;

    jumlahPaket++;

    cout << "Paket berhasil ditambahkan\n";
}

void updatePaket(Paket* daftarPaket, int jumlahPaket) {
    if (jumlahPaket == 0) {
        cout << "Belum ada paket tersedia\n";
        return;
    }

    tampilkanPaket(daftarPaket, jumlahPaket);

    int index;
    cout << "Pilih nomor paket yang ingin diupdate : ";
    cin >> index;

    if (index > 0 && index <= jumlahPaket) {
        Paket* target = &daftarPaket[index - 1];

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Nama Paket baru : ";
        getline(cin, target->namaPaket);

        cout << "Jam baru : ";
        cin >> target->jam;

        cout << "Masa Aktif baru (hari) : ";
        cin >> target->masaAktif;

        cout << "Harga baru : ";
        cin >> target->harga;

        cout << "Paket berhasil diupdate\n";
    } else {
        cout << "Nomor tidak valid\n";
    }
}

void hapusPaket(Paket* daftarPaket, int& jumlahPaket) {
    if (jumlahPaket == 0) {
        cout << "Belum ada paket tersedia\n";
        return;
    }

    tampilkanPaket(daftarPaket, jumlahPaket);

    int index;
    cout << "Pilih nomor paket yang ingin dihapus : ";
    cin >> index;

    if (index > 0 && index <= jumlahPaket) {
        for (int i = index - 1; i < jumlahPaket - 1; i++) {
            daftarPaket[i] = daftarPaket[i + 1];
        }
        jumlahPaket--;
        cout << "Paket berhasil dihapus\n";
    } else {
        cout << "Nomor tidak valid\n";
    }
}

void menuPaketAdmin(Paket* daftarPaket, int& jumlahPaket) {
    int pilihan;

    do {
        cout << "\n===== MENU PAKET =====\n";
        cout << "1. Lihat Paket\n";
        cout << "2. Tambah Paket\n";
        cout << "3. Update Paket\n";
        cout << "4. Hapus Paket\n";
        cout << "5. Kembali\n";
        cout << "Pilihan : ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tampilkanPaket(daftarPaket, jumlahPaket); break;
            case 2: tambahPaket(daftarPaket, jumlahPaket); break;
            case 3: updatePaket(daftarPaket, jumlahPaket); break;
            case 4: hapusPaket(daftarPaket, jumlahPaket); break;
            case 5: break;
            default: cout << "Pilihan tidak valid\n";
        }
    } while (pilihan != 5);
}

void menuAdmin(User* daftarUser, int& jumlahUser, Paket* daftarPaket, int& jumlahPaket) {
    int menuAdmin;

    do {
        cout << "\n===== MENU ADMIN =====\n";
        cout << "1.  Tambah Member\n";
        cout << "2.  Lihat Semua Member\n";
        cout << "3.  Update Nama & Password\n";
        cout << "4.  Update Billing & Masa Aktif\n";
        cout << "5.  Hapus Member\n";
        cout << "6.  Sort Nama\n";
        cout << "7.  Sort Billing\n";
        cout << "8.  Sort Masa Aktif\n";
        cout << "9.  Cari Member by ID (Binary Search)\n";
        cout << "10. Cari Member by Nama (Linear Search)\n";
        cout << "11. Kelola Paket\n";
        cout << "12. Logout\n";
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
            case 9:  menuCariId(daftarUser, jumlahUser); break;
            case 10: menuCariNama(daftarUser, jumlahUser); break;
            case 11: menuPaketAdmin(daftarPaket, jumlahPaket); break;
            case 12: break;
            default: cout << "Pilihan tidak valid\n";
        }
    } while (menuAdmin != 12);
}

void pilihPaket(User* userAktif, Paket* daftarPaket, int jumlahPaket) {
    if (jumlahPaket == 0) {
        cout << "Belum ada paket tersedia\n";
        return;
    }

    tampilkanPaket(daftarPaket, jumlahPaket);

    int pilihan;
    cout << "Pilih nomor paket : ";
    cin >> pilihan;

    if (pilihan > 0 && pilihan <= jumlahPaket) {
        Paket* paketDipilih = &daftarPaket[pilihan - 1];

        userAktif->billing.jam += paketDipilih->jam;
        userAktif->billing.masaAktif += paketDipilih->masaAktif;

        cout << "\nPaket \"" << paketDipilih->namaPaket << "\" berhasil diaktifkan!\n";
        cout << "Billing jam sekarang  : " << fixed << setprecision(1) << userAktif->billing.jam << " jam\n";
        cout << "Masa aktif sekarang   : " << userAktif->billing.masaAktif << " hari\n";
    } else {
        cout << "Nomor tidak valid\n";
    }
}

void menuUser(User* daftarUser, int jumlahUser, int userIndex, Paket* daftarPaket, int jumlahPaket) {
    int menuUser;

    User* userAktif = &daftarUser[userIndex];

    do {
        cout << "\n===== MENU USER =====\n";
        cout << "1. Lihat Profil\n";
        cout << "2. Update Nama\n";
        cout << "3. Update Password\n";
        cout << "4. Pilih Paket\n";
        cout << "5. Logout\n";
        cout << "Pilihan : ";
        cin >> menuUser;

        switch (menuUser) {
            case 1:
                cout << "\nNama       : " << userAktif->nama << endl;
                cout << "Billing Jam: " << fixed << setprecision(1) << userAktif->billing.jam << " jam" << endl;
                cout << "Masa Aktif : " << userAktif->billing.masaAktif << " hari" << endl;
                break;

            case 2:
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Masukkan nama baru : ";
                getline(cin, userAktif->nama);
                cout << "Nama berhasil diperbarui\n";
                break;

            case 3:
                cout << "Masukkan password baru : ";
                userAktif->password = inputPassword();
                cout << "Password berhasil diperbarui\n";
                break;

            case 4:
                pilihPaket(userAktif, daftarPaket, jumlahPaket);
                break;

            case 5:
                break;

            default:
                cout << "Pilihan tidak valid\n";
        }
    } while (menuUser != 5);
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
                        menuAdmin(daftarUser, jumlahUser, daftarPaket, jumlahPaket);
                    } else {
                        menuUser(daftarUser, jumlahUser, userIndex, daftarPaket, jumlahPaket);
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