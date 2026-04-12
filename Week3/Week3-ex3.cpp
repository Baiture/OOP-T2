#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

class NhanVien {
private:
    string tenNhanVien;
    double luongCoBan;
    double heSoLuong;

public:
    static constexpr double LUONG_MAX = 500000000;

    NhanVien(string ten, double luong, double heSo)
        : tenNhanVien(ten), luongCoBan(luong), heSoLuong(heSo) {}

    string getTenNhanVien() const { return tenNhanVien; }
    double getLuongCoBan() const { return luongCoBan; }
    double getHeSoLuong() const { return heSoLuong; }

    void setTenNhanVien(string ten) {
        if (!ten.empty()) tenNhanVien = ten;
    }

    void setLuongCoBan(double luong) {
        if (luong >= 0) luongCoBan = luong;
    }

    void setHeSoLuong(double heSo) {
        if (heSo > 0) heSoLuong = heSo;
    }

    double tinhLuong() const {
        return luongCoBan * heSoLuong;
    }

    void inTTin() const {
        cout << fixed << setprecision(0);
        cout << "[" << tenNhanVien << "] - LCB: " << luongCoBan
             << " - HSL: " << heSoLuong
             << " -> Total: " << tinhLuong() << " VND" << endl;
    }

    bool tangLuong(double delta) {
        double luongMoi = (luongCoBan + delta) * heSoLuong;
        if (luongMoi > LUONG_MAX) {
            cout << "[!] Luong moi vuot LUONG_MAX. Khong thuc hien." << endl;
            return false;
        }
        luongCoBan += delta;
        return true;
    }
};

int main() {
    NhanVien nv1("Tran Duc Anh Minh", 630000000, 4.0);
    NhanVien nv2("Nguyen Thi Nguyet Huong", 00000000, 6.4);

    nv1.inTTin();
    nv2.inTTin();

    cout << "\n--- Thu nghiem tang luong ---" << endl;
    if (nv1.tangLuong(5000000)) {
        nv1.inTTin();
    }

    return 0;
}
