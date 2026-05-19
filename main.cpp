#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <limits>
#include <conio.h>
#include <windows.h>
#include <cctype>
#include <cmath>
using namespace std;

#define MAX_USER 100
#define MAX_PAKET 20
#define MAX_PESANAN 100

struct Billing {
    double jam;
    double masaAktif;
};

struct PesanMenu {
    string makanan;
    string minuman;
    double total;
};

struct User {
    string nama;
    string password;
    Billing billing;
    PesanMenu pesanan;
};

struct Paket {
    string namaPaket;
    double jam;
    double masaAktif;
    double harga;
};

struct PesananBilling {
    string namaUser;
    string namaPaket;
    double jam;
    double masaAktif;
    double harga;
    string status;
};

struct PesananMenuAdmin {
    string namaUser;
    string makanan;
    string minuman;
    double total;
    string status;
};

User daftarUser[MAX_USER];
Paket daftarPaket[MAX_PAKET];
PesananBilling daftarPesanan[MAX_PESANAN];
PesananMenuAdmin daftarPesananMenu[MAX_PESANAN];

int jumlahPesanan = 0;
int jumlahPesananMenu = 0;
int jumlahUser = 0;
int jumlahPaket = 0;

void clearScreen() {
    system("cls");
}

void pauseScreen() {
    cout << "\nTekan tombol apa saja untuk lanjut.";
    _getch();
}

double inputAngka(string prompt) {
    string input;
    double nilai;

    while (true) {
        cout << prompt;
        cin >> input;

        replace(input.begin(), input.end(), ',', '.');

        try {
            nilai = stod(input);
            return nilai;
        }
        catch (...) {
            cout << "Input harus angka!\n";
        }
    }
}

void tampilAngka(double nilai) {
    if (floor(nilai) == nilai)
        cout << (int)nilai;
    else
        cout << nilai;
}

int menuArrow(string title, string options[], int size) {
    int pilih = 0;
    int key;

    while (true) {
        clearScreen();
        cout << "===== " << title << " =====\n\n";

        for (int i = 0; i < size; i++) {
            if (i == pilih)
                cout << " > " << options[i] << endl;
            else
                cout << "   " << options[i] << endl;
        }

        key = _getch();

        if (key == 224) {
            key = _getch();

            if (key == 72 && pilih > 0)
                pilih--;

            else if (key == 80 && pilih < size - 1)
                pilih++;
        }

        else if (key == 13) {
            return pilih + 1;
        }
    }
}

bool cekNama(string namaBaru) {
    for (int i = 0; i < jumlahUser; i++) {
        if (daftarUser[i].nama == namaBaru)
            return true;
    }
    return false;
}

bool cekNamaKecuali(string namaBaru, string namaLama) {
    if (namaBaru == namaLama) return false;
    return cekNama(namaBaru);
}

string inputPassword() {
    string password = "";
    int ch;

    while (true) {
        ch = _getch();

        if (ch == 13) break;

        else if (ch == 8) {
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";
            }
        }

        else if (isprint(ch)) {
            password += ch;
            cout << "*";
        }
    }

    cout << endl;
    return password;
}

string validasiPassword() {
    string pass;

    do {
        cout << "Password (minimal 8 karakter): ";
        pass = inputPassword();

        if (pass.length() < 8) {
            cout << "Password terlalu pendek!\n";
        }

    } while (pass.length() < 8);

    return pass;
}

bool validasiNamaKosong(string nama) {
    if (nama.empty()) {
        cout << "Nama tidak boleh kosong!\n";
        return false;
    }

    return true;
}

void registerUser() {
    if (jumlahUser >= MAX_USER) {
        cout << "Kapasitas user penuh!\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nama: ";
getline(cin, daftarUser[jumlahUser].nama);
if (!validasiNamaKosong(daftarUser[jumlahUser].nama)) {
    return;
}

if (cekNama(daftarUser[jumlahUser].nama)) {
    cout << "Nama sudah digunakan!\n";
    return;
}

daftarUser[jumlahUser].password = validasiPassword();


    daftarUser[jumlahUser].billing.jam = 0;
    daftarUser[jumlahUser].billing.masaAktif = 0;
    daftarUser[jumlahUser].pesanan = {"", "", 0};

    jumlahUser++;
    cout << "Register berhasil!\n";
}

bool login(bool &admin, int &userIndex) {
    string namaInput, passwordInput;

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nama: ";
    getline(cin, namaInput);

    cout << "Password: ";
    passwordInput = inputPassword();

    if (namaInput == "Admin" && passwordInput == "Admin076") {
        admin = true;
        return true;
    }

    for (int i = 0; i < jumlahUser; i++) {
        if (daftarUser[i].nama == namaInput &&
            daftarUser[i].password == passwordInput) {
            admin = false;
            userIndex = i;
            return true;
        }
    }
    
    return false;
}

void tampilkanMember() {
    clearScreen();

    cout << "================ DATA MEMBER ================\n";
    cout << left
        << setw(5)  << "No"
        << setw(20) << "Nama"
        << setw(15) << "Password"
        << setw(10) << "Jam"
        << setw(15) << "Masa Aktif"
        << endl;

    cout << "---------------------------------------------------------\n";

    for (int i = 0; i < jumlahUser; i++) {

    cout << setw(5)  << i + 1
         << setw(20) << daftarUser[i].nama
         << setw(15) << daftarUser[i].password;

    tampilAngka(daftarUser[i].billing.jam);
    cout << " jam\t\t";

    tampilAngka(daftarUser[i].billing.masaAktif);
    cout << " hari" << endl;
}
}
void tambahMember() {
    if (jumlahUser >= MAX_USER) {
        cout << "Kapasitas penuh\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Nama: ";
    getline(cin, daftarUser[jumlahUser].nama);
    if (!validasiNamaKosong(daftarUser[jumlahUser].nama)) {
    return;
}
    if (cekNama(daftarUser[jumlahUser].nama)) {
        cout << "Nama sudah digunakan!\n";
        return;
    }

    daftarUser[jumlahUser].password = validasiPassword();

    daftarUser[jumlahUser].billing.jam = inputAngka("Billing Jam: ");
    daftarUser[jumlahUser].billing.masaAktif = inputAngka("Masa Aktif: ");

    jumlahUser++;
    cout << "Member berhasil ditambahkan!\n";
}

void updateMember() {
    int index;
    tampilkanMember();

    index = inputAngka("Pilih member: ");

    if (index > 0 && index <= jumlahUser) {
        string namaLama = daftarUser[index-1].nama;
        string namaBaru;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nama baru: ";
        getline(cin, namaBaru);
        if (!validasiNamaKosong(namaBaru)) {
    return;
}
        if (cekNamaKecuali(namaBaru, namaLama)) {
            cout << "Nama sudah digunakan!\n";
            return;
        }

        daftarUser[index-1].nama = namaBaru;

        daftarUser[index-1].password = validasiPassword();

        cout << "Member berhasil diupdate!\n";
    }
}

void updateBilling() {
    int index;
    tampilkanMember();

    index = inputAngka("Pilih member: ");

    if (index > 0 && index <= jumlahUser) {
        daftarUser[index-1].billing.jam = inputAngka("Jam baru: ");
        daftarUser[index-1].billing.masaAktif = inputAngka("Masa aktif baru: ");
    }
}

void hapusMember() {
    int index;
    tampilkanMember();

    index = inputAngka("Pilih member: ");

    if (index > 0 && index <= jumlahUser) {
        for (int i = index-1; i < jumlahUser-1; i++) {
            daftarUser[i] = daftarUser[i+1];
        }
        jumlahUser--;
        cout << "Member berhasil dihapus\n";
    }
}

void sortNama() {
    sort(daftarUser, daftarUser + jumlahUser,
        [](User a, User b) { return a.nama < b.nama; });
}

void sortBilling() {
    sort(daftarUser, daftarUser + jumlahUser,
        [](User a, User b) { return a.billing.jam < b.billing.jam; });
}

void sortMasaAktif() {
    sort(daftarUser, daftarUser + jumlahUser,
        [](User a, User b) { return a.billing.masaAktif < b.billing.masaAktif; });
}

void menuSorting() {
    int pilih;

    do {
        string sortingMenu[] = {
            "1. Sort Nama",
            "2. Sort Billing Jam",
            "3. Sort Masa Aktif",
            "4. Kembali"
        };

        pilih = menuArrow("MENU SORTING", sortingMenu, 4);

        switch (pilih) {
            case 1: sortNama(); tampilkanMember(); pauseScreen(); break;
            case 2: sortBilling(); tampilkanMember(); pauseScreen(); break;
            case 3: sortMasaAktif(); tampilkanMember(); pauseScreen(); break;
        }

    } while (pilih != 4);
}

void cariNama() {
    string target;
    bool ditemukan = false;

    clearScreen();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "===== SEARCH MEMBER =====\n";
    cout << "Masukkan nama yang dicari: ";
    getline(cin, target);

    for (int i = 0; i < jumlahUser; i++) {
    if (daftarUser[i].nama == target) {
        clearScreen();
        cout << "===== DATA DITEMUKAN =====\n\n";
        cout << "Nama       : " << daftarUser[i].nama << endl;
        cout << "Password   : " << daftarUser[i].password << endl;
        cout << "Billing    : ";
        tampilAngka(daftarUser[i].billing.jam);
        cout << " jam" << endl;
        cout << "Masa Aktif : ";
        tampilAngka(daftarUser[i].billing.masaAktif);
        cout << " hari" << endl;

        ditemukan = true;
        break;
    }
}

    if (!ditemukan) {
        clearScreen();
        cout << "User tidak ditemukan!\n";
    }

    pauseScreen();
}

void tampilkanPaket() {
    clearScreen();

    if (jumlahPaket == 0) {
        cout << "Belum ada paket tersedia.\n";
        return;
    }

    cout << "================ DAFTAR PAKET =================\n";
    cout << left
        << setw(5)  << "No"
        << setw(20) << "Nama Paket"
        << setw(10) << "Jam"
        << setw(15) << "Masa Aktif"
        << setw(15) << "Harga"
        << endl;

    cout << "------------------------------------------------------------\n";

   for (int i = 0; i < jumlahPaket; i++) {
    cout << setw(5)  << i + 1
         << setw(20) << daftarPaket[i].namaPaket
         << setw(10) << daftarPaket[i].jam
         << setw(15) << daftarPaket[i].masaAktif
         << "Rp" << daftarPaket[i].harga
         << endl;
}
}

void updateProfilUser(User* userAktif) {
    int pilih;

    do {
        string updateMenu[] = {
            "Update Nama",
            "Update Password",
            "Kembali"
        };

        pilih = menuArrow("UPDATE PROFIL", updateMenu, 3);

        switch (pilih) {
            case 1: {
                clearScreen();
                string namaLama = userAktif->nama;
                string namaBaru;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Masukkan nama baru: ";
                getline(cin, namaBaru);
                 if (!validasiNamaKosong(namaBaru)) {
                    return;

            }   
                if (cekNamaKecuali(namaBaru, namaLama)) {
                    cout << "Nama sudah digunakan!\n";
                } else {
                    userAktif->nama = namaBaru;
                    cout << "Nama berhasil diupdate!\n";
                }

                pauseScreen();
                break;
            }

            case 2:
                clearScreen();
               userAktif->password = validasiPassword();
                cout << "Password berhasil diupdate!\n";
                pauseScreen();
                break;
        }

    } while (pilih != 3);
}

void pilihPaket(User* userAktif) {
    if (jumlahPesanan >= MAX_PESANAN) {
        cout << "Kapasitas pesanan penuh!\n";
        pauseScreen();
        return;
    }

    clearScreen();
    tampilkanPaket();

    int pilih = inputAngka("\nPilih paket: ");

    if (pilih > 0 && pilih <= jumlahPaket) {
        Paket p = daftarPaket[pilih-1];

        daftarPesanan[jumlahPesanan] = {
            userAktif->nama,
            p.namaPaket,
            p.jam,
            p.masaAktif,
            p.harga,
            "Pending"
        };

        jumlahPesanan++;
        cout << "Pesanan billing berhasil dibuat\n";
        cout << "Menunggu verifikasi admin.\n";
    }
    else {
        cout << "Pilihan paket tidak valid!\n";
    }

    pauseScreen();
}

void lihatPesanan() {
    clearScreen();

    bool adaPending = false;

    cout << "================ PESANAN BILLING ================\n";
    cout << left
        << setw(5)  << "No"
        << setw(20) << "User"
        << setw(20) << "Paket"
        << setw(15) << "Status"
        << endl;

    cout << "-------------------------------------------------\n";

    for (int i = 0; i < jumlahPesanan; i++) {
        if (daftarPesanan[i].status == "Pending") {
            cout << setw(5)  << i + 1
                << setw(20) << daftarPesanan[i].namaUser
                << setw(20) << daftarPesanan[i].namaPaket
                << setw(15) << daftarPesanan[i].status
                << endl;
            adaPending = true;
        }
    }

    if (!adaPending) cout << "Tidak ada pesanan pending.\n";
}

void verifikasiBilling() {
    cout << "\n===== VERIFIKASI BILLING =====\n";
    lihatPesanan();

    int pilih = inputAngka("Pilih pesanan: ");

    if (pilih > 0 && pilih <= jumlahPesanan) {
        if (daftarPesanan[pilih-1].status == "Verified") {
            cout << "Pesanan sudah diverifikasi!\n";
            return;
        }

        daftarPesanan[pilih-1].status = "Verified";

        for (int i = 0; i < jumlahUser; i++) {
            if (daftarUser[i].nama == daftarPesanan[pilih-1].namaUser) {
                daftarUser[i].billing.jam += daftarPesanan[pilih-1].jam;
                daftarUser[i].billing.masaAktif += daftarPesanan[pilih-1].masaAktif;
            }
        }

        cout << "Pesanan billing berhasil diverifikasi!\n";
    }
    else {
        cout << "Pilihan tidak valid!\n";
    }
}

void verifikasiMenu() {
    clearScreen();
    cout << "===== VERIFIKASI MAKANAN =====\n\n";

    bool adaPending = false;

    for (int i = 0; i < jumlahPesananMenu; i++) {
        if (daftarPesananMenu[i].status == "Pending") {
            cout << i + 1 << ". "
                << daftarPesananMenu[i].namaUser
                << " | " << daftarPesananMenu[i].makanan
                << " | " << daftarPesananMenu[i].minuman
                << endl;
            adaPending = true;
        }
    }

    if (!adaPending) {
        cout << "Tidak ada pesanan menu pending.\n";
        pauseScreen();
        return;
    }

    int pilih = inputAngka("\nPilih pesanan: ");

    if (pilih > 0 && pilih <= jumlahPesananMenu) {
        if (daftarPesananMenu[pilih - 1].status == "Verified") {
            cout << "Pesanan sudah diverifikasi!\n";
            pauseScreen();
            return;
        }

        daftarPesananMenu[pilih - 1].status = "Verified";
        clearScreen();
        cout << "Pesanan makanan berhasil diverifikasi!\n";
    }
    else {
        cout << "Pilihan tidak valid!\n";
    }

    pauseScreen();
}

void lihatRiwayatPesanan() {
    cout << "\n===== RIWAYAT BILLING =====\n";

    bool adaBilling = false;

    for (int i = 0; i < jumlahPesanan; i++) {
        if (daftarPesanan[i].status == "Verified") {
            cout << "User       : " << daftarPesanan[i].namaUser << endl;
            cout << "Paket      : " << daftarPesanan[i].namaPaket << endl;
            cout << "Jam        : ";
            tampilAngka(daftarPesanan[i].jam); cout << endl;
            cout << "Masa Aktif : ";
            tampilAngka(daftarPesanan[i].masaAktif); cout << " hari" << endl;
            cout << "Harga      : Rp" << daftarPesanan[i].harga << endl;
            cout << "--------------------------\n";
            adaBilling = true;
        }
    }

    if (!adaBilling) cout << "Belum ada riwayat billing.\n";

    cout << "\n===== RIWAYAT MAKANAN =====\n";

    bool adaMakanan = false;

    for (int i = 0; i < jumlahPesananMenu; i++) {
        if (daftarPesananMenu[i].status == "Verified") {
            cout << "User     : " << daftarPesananMenu[i].namaUser << endl;
            cout << "Makanan  : " << daftarPesananMenu[i].makanan << endl;
            cout << "Minuman  : " << daftarPesananMenu[i].minuman << endl;
            cout << "Total    : Rp" << daftarPesananMenu[i].total << endl;
            cout << "--------------------------\n";
            adaMakanan = true;
        }
    }

    if (!adaMakanan) cout << "Belum ada riwayat makanan.\n";
}

void menuPesanan() {
    int pilih;

    do {
        string pesananMenu[] = {
            "1. Verifikasi Pesanan Billing",
            "2. Verifikasi Pesanan Menu",
            "3. Lihat Riwayat Pesanan",
            "4. Kembali"
        };

        pilih = menuArrow("KELOLA PESANAN", pesananMenu, 4);

        switch (pilih) {
            case 1: verifikasiBilling(); pauseScreen(); break;
            case 2: verifikasiMenu(); break;
            case 3: lihatRiwayatPesanan(); pauseScreen(); break;
        }

    } while (pilih != 4);
}

void tambahPaket() {
    if (jumlahPaket >= MAX_PAKET) {
        cout << "Kapasitas paket penuh!\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\n===== TAMBAH PAKET =====\n";
    cout << "Nama Paket: ";
    getline(cin, daftarPaket[jumlahPaket].namaPaket);

    daftarPaket[jumlahPaket].jam = inputAngka("Jumlah Jam: ");
    daftarPaket[jumlahPaket].masaAktif = inputAngka("Masa Aktif (hari): ");
    daftarPaket[jumlahPaket].harga = inputAngka("Harga: ");

    jumlahPaket++;
    cout << "Paket berhasil ditambahkan!\n";
}

void updatePaket() {
    if (jumlahPaket == 0) {
        cout << "Belum ada paket.\n";
        return;
    }

    tampilkanPaket();
    int index = inputAngka("Pilih nomor paket yang ingin diupdate: ");

    if (index > 0 && index <= jumlahPaket) {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Nama Paket Baru: ";
        getline(cin, daftarPaket[index - 1].namaPaket);

        daftarPaket[index - 1].jam = inputAngka("Jumlah Jam Baru: ");
        daftarPaket[index - 1].masaAktif = inputAngka("Masa Aktif Baru: ");
        daftarPaket[index - 1].harga = inputAngka("Harga Baru: ");

        cout << "Paket berhasil diupdate!\n";
    }
    else {
        cout << "Nomor paket tidak valid!\n";
    }
}

void hapusPaket() {
    if (jumlahPaket == 0) {
        cout << "Belum ada paket.\n";
        return;
    }

    tampilkanPaket();
    int index = inputAngka("Pilih nomor paket yang ingin dihapus: ");

    if (index > 0 && index <= jumlahPaket) {
        for (int i = index - 1; i < jumlahPaket - 1; i++) {
            daftarPaket[i] = daftarPaket[i + 1];
        }
        jumlahPaket--;
        cout << "Paket berhasil dihapus!\n";
    }
    else {
        cout << "Nomor paket tidak valid!\n";
    }
}

void menuPaketAdmin() {
    int pilih;

    do {
        string paketMenu[] = {
            "1. Lihat Paket",
            "2. Tambah Paket",
            "3. Update Paket",
            "4. Hapus Paket",
            "5. Kembali"
        };

        pilih = menuArrow("KELOLA PAKET", paketMenu, 5);

        switch (pilih) {
            case 1: tampilkanPaket(); pauseScreen(); break;
            case 2: tambahPaket(); pauseScreen(); break;
            case 3: updatePaket(); pauseScreen(); break;
            case 4: hapusPaket(); pauseScreen(); break;
        }

    } while (pilih != 5);
}

void pesanMenu(User* userAktif) {
    if (jumlahPesananMenu >= MAX_PESANAN) {
        cout << "Kapasitas pesanan menu penuh!\n";
        pauseScreen();
        return;
    }

    int pilihMakanan, pilihMinuman;
    userAktif->pesanan = {"", "", 0};

    clearScreen();
    cout << "===== MENU MAKANAN =====\n";
    cout << "1. Nasi Goreng      Rp15000\n";
    cout << "2. Mie Ayam         Rp12000\n";
    cout << "3. Indomie          Rp10000\n";
    cout << "4. Tidak pesan makanan\n";
    cout << "5. Kembali\n";

    pilihMakanan = inputAngka("Pilih makanan: ");
    
    
    switch (pilihMakanan) {
        case 1: userAktif->pesanan.makanan = "Nasi Goreng"; userAktif->pesanan.total += 15000; break;
        case 2: userAktif->pesanan.makanan = "Mie Ayam";    userAktif->pesanan.total += 12000; break;
        case 3: userAktif->pesanan.makanan = "Indomie";     userAktif->pesanan.total += 10000; break;
        case 4: userAktif->pesanan.makanan = "Tidak pesan makanan"; break;
        case 5: return;
        default:
            cout << "Pilihan makanan tidak valid!\n";
            pauseScreen();
            return;
    }
    cout << "Makanan Berhasil Ditambahkan!" << endl;
    pauseScreen();
    clearScreen();
    cout << "===== MENU MINUMAN =====\n";
    cout << "1. Es Teh           Rp5000\n";
    cout << "2. Es Jeruk         Rp8000\n";
    cout << "3. Air Mineral      Rp3000\n";
    cout << "4. Tidak pesan minuman\n";
    cout << "5. Kembali\n";

    pilihMinuman = inputAngka("Pilih minuman: ");

    switch (pilihMinuman) {
        case 1: userAktif->pesanan.minuman = "Es Teh";      userAktif->pesanan.total += 5000; break;
        case 2: userAktif->pesanan.minuman = "Es Jeruk";    userAktif->pesanan.total += 8000; break;
        case 3: userAktif->pesanan.minuman = "Air Mineral"; userAktif->pesanan.total += 3000; break;
        case 4: userAktif->pesanan.minuman = "Tidak pesan minuman"; break;
        case 5: return;
        default:
            cout << "Pilihan minuman tidak valid!\n";
            pauseScreen();
            return;
    }

    daftarPesananMenu[jumlahPesananMenu] = {
        userAktif->nama,
        userAktif->pesanan.makanan,
        userAktif->pesanan.minuman,
        userAktif->pesanan.total,
        "Pending"
    };

    jumlahPesananMenu++;
    cout << "Minuman Berhasil Ditambah.\n";
    cout << "Pesanan berhasil dibuat.\n";
    cout << "Menunggu verifikasi admin.\n";

    pauseScreen();
}

void lihatSemuaPesananUser(User* userAktif) {
    clearScreen();

    bool ditemukan = false;

    cout << "================ RIWAYAT PESANAN =================\n";
    cout << left
        << setw(5)  << "No"
        << setw(20) << "Makanan"
        << setw(20) << "Minuman"
        << setw(15) << "Total"
        << setw(15) << "Status"
        << endl;

    cout << "-------------------------------------------------------------\n";

    for (int i = 0; i < jumlahPesananMenu; i++) {
        if (daftarPesananMenu[i].namaUser == userAktif->nama) {
            cout << setw(5)  << i + 1
                << setw(20) << daftarPesananMenu[i].makanan
                << setw(20) << daftarPesananMenu[i].minuman
                << setw(15) << daftarPesananMenu[i].total
                << setw(15) << daftarPesananMenu[i].status
                << endl;
            ditemukan = true;
        }
    }

    if (!ditemukan) cout << "Belum ada pesanan.\n";

    pauseScreen();
}

void menuAdmin() {
    int pilih;
    cout << "Login Berhasil!" << endl;
    pauseScreen();

    do {
        string adminMenu[] = {
            "1. Tambah Member",
            "2. Lihat Member",
            "3. Update Member",
            "4. Update Billing",
            "5. Hapus Member",
            "6. Sorting",
            "7. Search Nama",
            "8. Kelola Pesanan",
            "9. Kelola Paket",
            "10. Logout"
        };

        pilih = menuArrow("MENU ADMIN", adminMenu, 10);

        switch (pilih) {
            case 1: tambahMember(); pauseScreen(); break;
            case 2: tampilkanMember(); pauseScreen(); break;
            case 3: updateMember(); pauseScreen(); break;
            case 4: updateBilling(); pauseScreen(); break;
            case 5: hapusMember(); pauseScreen(); break;
            case 6: menuSorting(); break;
            case 7: cariNama(); break;
            case 8: menuPesanan(); break;
            case 9: menuPaketAdmin(); break;
            case 10: cout << "Logout berhasil.\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }

    } while (pilih != 10);
}

void menuUser(int userIndex) {
    User* userAktif = &daftarUser[userIndex];
    int pilih;
    cout << "Login Berhasil!" << endl;
    pauseScreen();
    do {
        string userMenu[] = {
            "1. Lihat Profil",
            "2. Pilih Paket Billing",
            "3. Pesan Menu",
            "4. Lihat Pesanan",
            "5. Update Profil",
            "6. Logout"
        };

        pilih = menuArrow("MENU USER", userMenu, 6);

        switch (pilih) {
            case 1:
                clearScreen();
                cout << "========== PROFIL USER ==========\n";
                cout << "Nama        : " << userAktif->nama << endl;
                cout << "Password    : " << userAktif->password << endl;
                cout << "Billing     : ";
                tampilAngka(userAktif->billing.jam);
                cout << " jam\n";
                cout << "Masa Aktif  : ";
                tampilAngka(userAktif->billing.masaAktif);
                cout << " hari\n";
                pauseScreen();
                break;
            case 2: pilihPaket(userAktif); break;
            case 3: pesanMenu(userAktif); break;
            case 4: lihatSemuaPesananUser(userAktif); break;
            case 5: updateProfilUser(userAktif); pauseScreen(); break;
        }

    } while (pilih != 6);
}

int main() {

    daftarUser[0] = {"Aditya", "aditya1234", {10, 30}, {"", "", 0}};
    daftarUser[1] = {"Budi",   "budi1234", {5,  15}, {"", "", 0}};
    daftarUser[2] = {"Citra",  "citra1234", {8,  20}, {"", "", 0}};
    jumlahUser = 3;

    daftarPaket[0] = {"Paket Hemat",   2,  7,  10000};
    daftarPaket[1] = {"Paket Reguler", 5,  14, 25000};
    daftarPaket[2] = {"Paket Sultan",  10, 30, 50000};
    jumlahPaket = 3;

    daftarPesanan[0] = {"Aditya", "Paket Reguler", 5, 14, 25000, "Pending"};
    daftarPesanan[1] = {"Budi",   "Paket Hemat",   2, 7,  10000, "Pending"};
    jumlahPesanan = 2;

    int menu;

    do {
        string menuAwal[] = {
            "1. Register",
            "2. Login",
            "3. Keluar"
        };

        menu = menuArrow("MENU AWAL", menuAwal, 3);

        switch (menu) {
            case 1:
                registerUser();
                pauseScreen();
                break;

            case 2: {
    bool admin = false;
    int userIndex = -1;

    int percobaan = 0;
    bool berhasilLogin = false;

    while (percobaan < 3 && !berhasilLogin) {

        if (login(admin, userIndex)) {
            berhasilLogin = true;

            if (admin)
                menuAdmin();
            else
                menuUser(userIndex);
        }

        else {
            percobaan++;
            cout << "\nLogin gagal!\n"; 
            if (percobaan < 3) {
                cout << "\nSisa percobaan: "
                     << 3 - percobaan << endl;

                pauseScreen();
            }
        }
    }

    if (!berhasilLogin) {
        cout << "\nLogin gagal 3x! Kembali ke menu awal.\n";
        pauseScreen();
    }

    break;
}
        }


    } while (menu != 3);

    cout << "Terima kasih Sudah Menggunakan Program!\n";
    return 0;
}
