// tsp.cpp: Program Traveling Salesman Problem (TSP) dengan metode Brute Force.
// Mencari rute terpendek yang mengunjungi setiap lokasi tepat satu kali,
// berangkat dari lokasi pertama, lalu kembali lagi ke lokasi pertama.
#include <bits/stdc++.h> // mengimpor seluruh library standar C++
#include "Point.h"       // mengimpor class Point dan fungsi penghitung jarak

using namespace std;

// Batasan input
const int MAX_N = 11;         // jumlah lokasi maksimal; brute force menguji (N-1)! rute, sehingga N dibatasi agar waktu eksekusi tetap wajar
const double MAX_COORD = 1e6; // batas nilai mutlak koordinat X dan Y (-10^6 <= X, Y <= 10^6)
const double EPS = 1e-12;     // toleransi kecil untuk membandingkan bilangan desimal (floating-point)

// Class Tsp_map menyimpan kumpulan lokasi dan menyediakan fungsi untuk mencari rute terpendek
class Tsp_map {
private:
    vector<Point> cities; // daftar semua lokasi yang akan dikunjungi

public:
    // Menambahkan lokasi baru dalam bentuk objek Point
    void add(const Point& p) {
        cities.push_back(p); // simpan di akhir daftar
    }

    // Menambahkan lokasi baru dari nama/kode dan koordinat x, y
    void add(string name, double x, double y) {
        Point p(name, x, y); // buat objek Point dari data yang diberikan
        add(p);              // masukkan ke daftar lewat fungsi add di atas
    }

    // Mengembalikan jumlah lokasi yang sudah terdaftar
    int size() const {
        return static_cast<int>(cities.size());
    }

    // Mengambil nama/kode lokasi berdasarkan nomor index-nya
    string get_city_name(int index) const {
        return cities[index].getName();
    }

    // Menghitung jarak antara lokasi ke-i dan lokasi ke-j
    double dist_between(int i, int j) const {
        return dist(cities[i], cities[j]);
    }

    // Menghitung total panjang sebuah rute (tour), termasuk perjalanan kembali dari lokasi terakhir ke lokasi pertama
    double score(const vector<int>& tour) const {
        int n = static_cast<int>(tour.size()); // jumlah lokasi dalam rute
        if (n <= 1) return 0.0;                // rute dengan 0 atau 1 lokasi tidak memiliki jarak tempuh

        // mulai dengan jarak penutup rute: dari lokasi terakhir kembali ke lokasi pertama
        double result = dist_between(tour[0], tour[n - 1]);

        // jumlahkan jarak antar lokasi yang berurutan di sepanjang rute
        for (int i = 1; i < n; ++i) {
            result += dist_between(tour[i - 1], tour[i]);
        }

        return result;
    }

    // Membuat rute awal berdasarkan urutan input: 0, 1, 2, ..., n-1
    vector<int> get_default_tour() const {
        vector<int> tour(size());
        for (int i = 0; i < size(); ++i) {
            tour[i] = i;
        }
        return tour;
    }

    // Mencari rute terpendek dengan mencoba seluruh kemungkinan urutan kunjungan (Brute Force).
    // Mengembalikan pasangan (total jarak terpendek, urutan index lokasi pada rute tersebut).
    pair<double, vector<int>> solve_brute_force() const {
        int n = size(); // jumlah lokasi
        if (n == 0) return {0.0, {}};  // tidak ada lokasi: jarak 0 dan rute kosong
        if (n == 1) return {0.0, {0}}; // hanya satu lokasi: jarak 0 dan rute berisi lokasi itu saja

        // Hitung jarak semua pasangan lokasi sekali di awal, sehingga tidak perlu menghitung akar kuadrat
        // berulang kali di dalam perulangan permutasi
        vector<vector<double>> dmat(n, vector<double>(n, 0.0));
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                double d = dist_between(i, j);
                dmat[i][j] = d; // jarak i ke j
                dmat[j][i] = d; // jarak j ke i sama, jadi cukup dihitung sekali
            }
        }

        vector<int> current_tour = get_default_tour();            // rute yang sedang diuji, awalnya 0, 1, ..., n-1
        vector<int> best_tour = current_tour;                     // rute terbaik yang pernah ditemukan
        double min_distance = numeric_limits<double>::infinity(); // jarak terpendek sementara, awalnya tak hingga

        // Uji semua urutan kunjungan. Lokasi pertama (index 0) dikunci sebagai titik awal dan akhir,
        // jadi hanya lokasi lainnya yang disusun ulang. Total ada (n-1)! urutan.
        do {
            // total jarak rute saat ini: mulai dari jarak penutup, lalu tambahkan jarak antar lokasi berurutan
            double current_distance = dmat[current_tour[0]][current_tour[n - 1]];
            for (int i = 1; i < n; ++i) {
                current_distance += dmat[current_tour[i - 1]][current_tour[i]];
            }

            // jika rute ini lebih pendek dari yang terbaik sejauh ini, simpan sebagai rute terbaik
            if (current_distance < min_distance - EPS) {
                min_distance = current_distance;
                best_tour = current_tour;
            }
        } while (next_permutation(current_tour.begin() + 1, current_tour.end())); // lanjut ke urutan berikutnya

        return {min_distance, best_tour};
    }
}; // akhir class Tsp_map

// Membaca satu baris yang tidak kosong (mengabaikan baris yang hanya berisi spasi/enter).
// Mengembalikan true jika baris ditemukan, false jika input sudah habis.
bool read_non_empty_line(istream& in, string& line) {
    while (getline(in, line)) {
        for (char c : line) {
            if (!isspace(static_cast<unsigned char>(c))) {
                return true; // ada karakter selain spasi, baris valid
            }
        }
    }
    return false; // input habis (EOF)
}

int main() {
    string line;

    // 1. Baca baris pertama: jumlah lokasi (N)
    if (!read_non_empty_line(cin, line)) {
        cout << "INVALID INPUT\n";
        return 0;
    }

    long long jumlahLokasi;
    string extraToken;
    istringstream issN(line);

    // N harus berupa satu bilangan bulat saja, tanpa teks tambahan di baris yang sama
    if (!(issN >> jumlahLokasi) || (issN >> extraToken)) {
        cout << "INVALID INPUT\n";
        return 0;
    }

    // 2. Periksa batas N (0 <= N <= MAX_N)
    if (jumlahLokasi < 0 || jumlahLokasi > MAX_N) {
        cout << "OUT OF SCOPE\n";
        return 0;
    }

    Tsp_map petaKonoha;               // peta yang menyimpan seluruh lokasi
    unordered_set<string> daftarKode; // mencatat kode yang sudah dipakai untuk mendeteksi duplikat

    // 3. Baca tepat N baris berikutnya, masing-masing berformat "Kode X Y"
    for (int i = 0; i < jumlahLokasi; ++i) {
        if (!read_non_empty_line(cin, line)) {
            cout << "INVALID INPUT\n"; // jumlah baris kurang dari N
            return 0;
        }

        string kodeLokasi;
        double x, y;
        istringstream issPoint(line);

        // Format harus "Kode X Y" dan tidak boleh ada teks tambahan setelah Y
        if (!(issPoint >> kodeLokasi >> x >> y) || (issPoint >> extraToken)) {
            cout << "INVALID INPUT\n";
            return 0;
        }

        // Tolak koordinat yang bernilai NaN atau tak hingga
        if (!isfinite(x) || !isfinite(y)) {
            cout << "INVALID INPUT\n";
            return 0;
        }

        // Kode harus tepat 1 karakter dan belum pernah dipakai lokasi lain
        if (kodeLokasi.size() != 1 || daftarKode.count(kodeLokasi)) {
            cout << "INVALID INPUT\n";
            return 0;
        }

        // Periksa batas koordinat (-MAX_COORD <= X, Y <= MAX_COORD)
        if (fabs(x) > MAX_COORD || fabs(y) > MAX_COORD) {
            cout << "OUT OF SCOPE\n";
            return 0;
        }

        daftarKode.insert(kodeLokasi);   // catat kode ini sebagai sudah dipakai
        petaKonoha.add(kodeLokasi, x, y); // tambahkan lokasi ke peta
    }

    // 4. Cari rute terpendek dengan Brute Force
    pair<double, vector<int>> hasil = petaKonoha.solve_brute_force();
    double jarakTerbaik = hasil.first;
    vector<int> ruteTerbaik = hasil.second;

    // 5. Cetak hasil: baris pertama total jarak (6 angka desimal), baris kedua urutan rute
    cout << fixed << setprecision(6) << jarakTerbaik << "\n";
    if (ruteTerbaik.empty()) {
        cout << "-\n"; // tidak ada lokasi, jadi tidak ada rute
    } else {
        for (int i = 0; i < static_cast<int>(ruteTerbaik.size()); ++i) {
            cout << petaKonoha.get_city_name(ruteTerbaik[i]) << " ";
        }
        // cetak lagi lokasi pertama di akhir untuk menandai kembali ke titik awal
        cout << petaKonoha.get_city_name(ruteTerbaik[0]) << "\n";
    }

    return 0; // program selesai dengan sukses
}
