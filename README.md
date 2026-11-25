# Traveling Salesman Problem (Brute Force)

Program C++ untuk menyelesaikan **Traveling Salesman Problem (TSP)** dengan metode **Brute Force**. Program mencari rute terpendek yang mengunjungi setiap lokasi tepat satu kali, berangkat dari lokasi pertama, lalu kembali lagi ke lokasi pertama.

## Cara Kerja

1. Program membaca jumlah lokasi (`N`), lalu data setiap lokasi berupa kode dan koordinat `(X, Y)`.
2. Input diperiksa. Jika formatnya salah atau nilainya di luar batas, program langsung menampilkan pesan error.
3. Jarak antara setiap pasang lokasi dihitung sekali di awal dan disimpan dalam tabel jarak (jarak Euclidean).
4. Lokasi pertama dikunci sebagai titik awal dan akhir. Program mencoba semua urutan kunjungan untuk lokasi lainnya, yaitu sebanyak `(N-1)!` kemungkinan.
5. Untuk setiap urutan, program menghitung total jarak perjalanan pulang-pergi. Urutan dengan jarak paling pendek disimpan sebagai rute terbaik.
6. Program menampilkan total jarak dan urutan lokasi yang dikunjungi.

## Struktur File

| File | Keterangan |
|------|------------|
| `Point.h` | Class `Point` (nama dan koordinat titik) serta fungsi `dist` untuk menghitung jarak Euclidean |
| `tsp.cpp` | Class `Tsp_map` (penyimpan lokasi dan solver brute force), pembacaan dan validasi input, serta fungsi `main` |

## Cara Kompilasi dan Menjalankan

Pastikan `Point.h` dan `tsp.cpp` berada dalam folder yang sama.

```bash
g++ -std=c++17 -O2 tsp.cpp -o tsp
./tsp < input.txt
```

Atau jalankan lalu ketik input secara langsung:

```bash
./tsp
```

## Format Input

```
N
Kode1 X1 Y1
Kode2 X2 Y2
...
KodeN XN YN
```

- `N` adalah jumlah lokasi.
- Setiap lokasi ditulis dalam satu baris dengan format `Kode X Y`.
- **Lokasi pertama menjadi titik awal dan titik akhir perjalanan.**
- Baris kosong diabaikan.

### Batasan

| Hal | Batasan |
|-----|---------|
| Jumlah lokasi | `0 <= N <= 11` |
| Koordinat | `-10^6 <= X, Y <= 10^6` |
| Kode lokasi | Tepat 1 karakter dan tidak boleh kembar |
| Koordinat X dan Y | Harus berupa bilangan terhingga (bukan NaN atau Infinity) |

## Format Output

Jika input valid:

```
<total jarak dengan 6 angka di belakang koma>
<urutan kode lokasi, diakhiri kode lokasi pertama>
```

Kasus khusus:

| Kondisi | Output |
|---------|--------|
| `N = 0` | `0.000000` lalu `-` |
| `N = 1` | `0.000000` lalu kode lokasi itu dua kali (misalnya `A A`) |

Jika input tidak valid:

| Pesan | Penyebab |
|-------|----------|
| `INVALID INPUT` | Format salah, data kurang atau berlebih, kode bukan 1 karakter, kode kembar, atau koordinat bukan angka terhingga |
| `OUT OF SCOPE` | `N` atau koordinat berada di luar batas yang diizinkan |

## Contoh

**Input**

```
4
A 0 0
B 0 3
C 4 3
D 4 0
```

**Output**

```
14.000000
A B C D A
```

Rute `A → B → C → D → A` membentuk persegi panjang dengan total jarak `3 + 4 + 3 + 4 = 14`.

## Kompleksitas

- **Waktu:** `O((N-1)! * N)`, karena ada `(N-1)!` urutan dan tiap urutan dihitung dalam `O(N)`.
- **Memori:** `O(N^2)` untuk tabel jarak.

Karena pertumbuhannya sangat cepat, jumlah lokasi dibatasi maksimal 11 agar waktu eksekusi tetap wajar. Untuk jumlah lokasi yang lebih besar, diperlukan pendekatan lain seperti Dynamic Programming (Held-Karp) atau algoritma heuristik.

## Catatan

- Jika ada beberapa rute dengan jarak yang sama, program menampilkan rute yang pertama kali ditemukan dalam urutan pengujian.
- Perbandingan jarak memakai toleransi kecil (`1e-12`) untuk menghindari kesalahan pembulatan bilangan desimal.
