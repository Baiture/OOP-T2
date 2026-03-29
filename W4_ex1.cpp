#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

class NhanVien {
private:
    string tenNhanVien;
    double luongCoBan;
    double heSoLuong;

public:
    static constexpr double LUONG_MAX = 64000000.0;
    NhanVien(string ten, double luong, double heSo) {
        tenNhanVien = ten;
        luongCoBan = luong;
        heSoLuong = heSo;
    }

    string getTenNhanVien() { return tenNhanVien; }
    void setTenNhanVien(string ten) { tenNhanVien = ten; }

    double getLuongCoBan() { return luongCoBan; }
    void setLuongCoBan(double luong) { luongCoBan = luong; }

    double getHeSoLuong() { return heSoLuong; }
    void setHeSoLuong(double heSo) { heSoLuong = heSo; }

   
    double tinhLuong() {
        return luongCoBan * heSoLuong;
    }

    bool tangLuong(double delta) {
        double heSoMoi = heSoLuong + delta;
        double luongMoi = luongCoBan * heSoMoi;

        if (luongMoi > LUONG_MAX) {
            cout << "Thong bao: Khong the tang luong! Luong moi (" << (long long)luongMoi 
                 << ") vuot muc toi da cho phep." << endl;
            return false;
        } else {
            heSoLuong = heSoMoi;
            return true;
        }
    }

    void inTTin() {
        cout << fixed << setprecision(0); 
        cout << "===== THONG TIN NHAN VIEN =====" << endl;
        cout << "Ho ten: " << tenNhanVien << endl;
        cout << "Luong co ban: " << (long long)luongCoBan << " VND" << endl;
        cout << "He so luong: " << heSoLuong << endl;
        cout << "Tong luong hien tai: " << (long long)tinhLuong() << " VND" << endl;
        cout << "===============================" << endl;
    }
};

int main() {
    NhanVien nv("Nguyen Van A", 5000000, 2.5);
    nv.inTTin();
    cout << "\nThuc hien tang he so luong them 1.0..." << endl;
    if (nv.tangLuong(1.0)) {
        cout << "Cap nhat thanh cong!" << endl;
    }
    nv.inTTin();
    cout << "\nThuc hien tang he so luong them 10.0..." << endl;
    nv.tangLuong(10.0);

    return 0;
}
