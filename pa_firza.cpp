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
    cout << "Pilih makanan: ";
    cin >> pilihMakanan;

    switch (pilihMakanan) {
        case 1:
            userAktif->pesanan.makanan = "Nasi Goreng";
            userAktif->pesanan.total += 15000;
            break;
        case 2:
            userAktif->pesanan.makanan = "Mie Ayam";
            userAktif->pesanan.total += 12000;
            break;
        case 3:
            userAktif->pesanan.makanan = "Indomie";
            userAktif->pesanan.total += 10000;
            break;
        case 4:
            userAktif->pesanan.makanan = "Tidak pesan makanan";
            break;
        case 5:
            return;
        default:
            cout << "Pilihan makanan tidak valid!\n";
            pauseScreen();
            return;
    }

    clearScreen();
    cout << "===== MENU MINUMAN =====\n";
    cout << "1. Es Teh           Rp5000\n";
    cout << "2. Es Jeruk         Rp8000\n";
    cout << "3. Air Mineral      Rp3000\n";
    cout << "4. Tidak pesan minuman\n";
    cout << "5. Kembali\n";
    cout << "Pilih minuman: ";
    cin >> pilihMinuman;

    switch (pilihMinuman) {
        case 1:
            userAktif->pesanan.minuman = "Es Teh";
            userAktif->pesanan.total += 5000;
            break;
        case 2:
            userAktif->pesanan.minuman = "Es Jeruk";
            userAktif->pesanan.total += 8000;
            break;
        case 3:
            userAktif->pesanan.minuman = "Air Mineral";
            userAktif->pesanan.total += 3000;
            break;
        case 4:
            userAktif->pesanan.minuman = "Tidak pesan minuman";
            break;
        case 5:
            return;
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

    if (!ditemukan) {
        cout << "Belum ada pesanan.\n";
    }

    pauseScreen();
}