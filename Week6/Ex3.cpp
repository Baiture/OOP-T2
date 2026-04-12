#include <iostream>
#include <numeric> // Dùng std::gcd (C++17)
#include <stdexcept>
#include <vector>
#include <algorithm>

using namespace std;

class MauSoBangKhong : public runtime_error {
public:
    MauSoBangKhong() : runtime_error("Loi: Mau so phai khac 0!") {}
};

class PhanSo {
private:
    int tu, mau;

    void toi_gian() {
        int ucln = gcd(tu, mau);
        tu /= ucln;
        mau /= ucln;
        if (mau < 0) { tu = -tu; mau = -mau; }
    }

public:
    PhanSo(int t = 0, int m = 1) : tu(t), mau(m) {
        if (mau == 0) throw MauSoBangKhong();
        toi_gian();
    }

    // Operator Overloading (Phép toán)
    PhanSo operator+(const PhanSo& other) const {
        return PhanSo(tu * other.mau + other.tu * mau, mau * other.mau);
    }
    PhanSo operator-(const PhanSo& other) const {
        return PhanSo(tu * other.mau - other.tu * mau, mau * other.mau);
    }
    PhanSo operator*(const PhanSo& other) const {
        return PhanSo(tu * other.tu, mau * other.mau);
    }
    PhanSo operator/(const PhanSo& other) const {
        if (other.tu == 0) throw runtime_error("Khong the chia cho 0");
        return PhanSo(tu * other.mau, mau * other.tu);
    }

    // So sánh (__eq__, __lt__, __gt__)
    bool operator==(const PhanSo& other) const {
        return tu * other.mau == other.tu * mau;
    }
    bool operator<(const PhanSo& other) const {
        return tu * other.mau < other.tu * mau;
    }

    // Xuất luồng (__str__)
    friend ostream& operator<<(ostream& os, const PhanSo& ps) {
        if (ps.mau == 1) os << ps.tu;
        else os << ps.tu << "/" << ps.mau;
        return os;
    }
};

int main() {
    try {
        vector<PhanSo> ds = {PhanSo(1, 2), PhanSo(3, 4), PhanSo(1, 4)};
        
        PhanSo a(1, 2), b(1, 3);
        cout << a << " + " << b << " = " << (a + b) << endl;

        cout << "Danh sach truoc sap xep: ";
        for (auto p : ds) cout << p << " ";
        
        sort(ds.begin(), ds.end()); // Sử dụng operator < đã overload
        
        cout << "\nDanh sach sau sap xep tang dan: ";
        for (auto p : ds) cout << p << " ";
        cout << endl;

    } catch (const exception& e) {
        cerr << e.what() << endl;
    }
    return 0;
}
