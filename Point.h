#pragma once
#include <cmath>  // untuk fungsi matematika, di sini dipakai hypot (menghitung jarak Euclidean dengan aman dari overflow)
#include <string> // agar setiap titik dapat menyimpan nama/kode (misalnya A, B, C, dst)

using namespace std;

// Class Point merepresentasikan sebuah titik pada bidang 2D yang memiliki nama dan koordinat (x, y)
class Point {
private:
    string name; // nama atau kode titik sebagai pengenal (misalnya A, B, C)
    double x;    // koordinat pada sumbu X
    double y;    // koordinat pada sumbu Y

public:
    // Constructor default: dipakai saat titik dibuat tanpa parameter
    Point() {
        name = ""; // nama kosong
        x = 0.0;   // koordinat X awal 0
        y = 0.0;   // koordinat Y awal 0
    }

    // Constructor berparameter: langsung mengisi nama dan koordinat saat titik dibuat
    Point(string pname, double px, double py) {
        name = pname; // simpan nama titik
        x = px;       // simpan koordinat X
        y = py;       // simpan koordinat Y
    }

    // Mengambil nama titik
    string getName() const {
        return name;
    }

    // Mengambil koordinat X
    double getX() const {
        return x;
    }

    // Mengambil koordinat Y
    double getY() const {
        return y;
    }
}; // akhir class Point

// Menghitung jarak Euclidean (garis lurus) antara dua titik
inline double dist(const Point& p1, const Point& p2) {
    // hypot menghitung sqrt(dx^2 + dy^2) tanpa risiko overflow saat selisih koordinat sangat besar
    return hypot(p1.getX() - p2.getX(), p1.getY() - p2.getY());
}
