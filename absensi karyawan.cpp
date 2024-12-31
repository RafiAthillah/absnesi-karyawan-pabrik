#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

// Struktur untuk data karyawan
class Karyawan {
public:
    int id;
    string nama;
    bool hadir;
    string jamAbsen;

    // Konstruktor untuk inisialisasi karyawan
    Karyawan(int idKaryawan, string namaKaryawan) {
        id = idKaryawan;
        nama = namaKaryawan;
        hadir = false;  // default belum hadir
        jamAbsen = "";
    }
};

class Absensi {
private:
    vector<Karyawan> daftarKaryawan;

public:
    // Menambahkan karyawan baru ke dalam daftar
    void tambahKaryawan(int id, const string& nama) {
        daftarKaryawan.push_back(Karyawan(id, nama));
        cout << "Karyawan dengan ID " << id << " dan nama " << nama << " telah ditambahkan.\n";
    }

    // Menandai kehadiran karyawan
    void absen(int id) {
        // Mendapatkan waktu saat absen
        time_t now = time(0);
        tm *ltm = localtime(&now);
        string jamAbsen = to_string(ltm->tm_hour) + ":" + to_string(ltm->tm_min);

        for (auto& karyawan : daftarKaryawan) {
            if (karyawan.id == id) {
                karyawan.hadir = true;
                karyawan.jamAbsen = jamAbsen;
                cout << "Karyawan " << karyawan.nama << " dengan ID " << karyawan.id 
                     << " telah hadir pada jam " << jamAbsen << ".\n";
                return;
            }
        }
        cout << "Karyawan dengan ID " << id << " tidak ditemukan.\n";
    }

    // Menampilkan daftar absensi
    void tampilkanAbsensi() {
        cout << "\nDaftar Kehadiran Karyawan:\n";
        for (const auto& karyawan : daftarKaryawan) {
            cout << "ID: " << karyawan.id << " - Nama: " << karyawan.nama 
                 << " - Status: " << (karyawan.hadir ? "Hadir, Jam Absen: " + karyawan.jamAbsen : "Tidak Hadir") << endl;
        }
    }
};

int main() {
    Absensi absensi;
    int pilihan, id;
    string nama;

    while (true) {
        cout << "\nMenu Absensi Karyawan Pabrik\n";
        cout << "1. Tambah Karyawan\n";
        cout << "2. Absen Karyawan\n";
        cout << "3. Tampilkan Daftar Absensi\n";
        cout << "4. Keluar\n";
        cout << "Pilih opsi (1-4): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan ID Karyawan: ";
                cin >> id;
                cout << "Masukkan Nama Karyawan: ";
                cin.ignore();  // Untuk membersihkan buffer setelah input ID
                getline(cin, nama);
                absensi.tambahKaryawan(id, nama);
                break;
            case 2:
                cout << "Masukkan ID Karyawan yang akan diabsen: ";
                cin >> id;
                absensi.absen(id);
                break;
            case 3:
                absensi.tampilkanAbsensi();
                break;
            case 4:
                cout << "Terima kasih! Program selesai.\n";
                return 0;
            default:
                cout << "Pilihan tidak valid, coba lagi.\n";
        }
    }

    return 0;
}
