#include <iostream>
#include <string>
#include <vector>

using namespace std;

class HangHoa {
protected:
    string maHang;
    string tenHang;
    string nhaSX;
    double gia;

public:
    HangHoa(string ma, string ten, string nsx, double g) 
        : maHang(ma), tenHang(ten), nhaSX(nsx), gia(g) {}

    virtual void xuat() {
        cout << "Ma: " << maHang << " | Ten: " << tenHang 
             << " | NSX: " << nhaSX << " | Gia: " << gia;
    }
};

class HangDienMay : public HangHoa {
private:
    int thoiGianBaoHanh;
    double dienAp;
    double congSuat;

public:
    HangDienMay(string ma, string ten, string nsx, double g, int tgbh, double da, double cs)
        : HangHoa(ma, ten, nsx, g), thoiGianBaoHanh(tgbh), dienAp(da), congSuat(cs) {}

    void xuat() override {
        HangHoa::xuat();
        cout << " | Bao hanh: " << thoiGianBaoHanh << " thang"
             << " | Dien ap: " << dienAp << "V"
             << " | Cong suat: " << congSuat << "W" << endl;
    }
};

class HangSanhSu : public HangHoa {
private:
    string loaiNguyenLieu;

public:
    HangSanhSu(string ma, string ten, string nsx, double g, string lnl)
        : HangHoa(ma, ten, nsx, g), loaiNguyenLieu(lnl) {}

    void xuat() override {
        HangHoa::xuat();
        cout << " | Nguyen lieu: " << loaiNguyenLieu << endl;
    }
};

// Lớp con: Hang Thuc Pham
class HangThucPham : public HangHoa {
private:
    string ngaySX;
    string ngayHetHan;

public:
    HangThucPham(string ma, string ten, string nsx, double g, string nsx_date, string nhh)
        : HangHoa(ma, ten, nsx, g), ngaySX(nsx_date), ngayHetHan(nhh) {}

    void xuat() override {
        HangHoa::xuat();
        cout << " | Ngay SX: " << ngaySX << " | Han dung: " << ngayHetHan << endl;
    }
};

int main() {
    HangDienMay dm("DM01", "Tu lanh panasonic", "panasonic", 15000000, 24, 220, 150);
    HangSanhSu ss("SS01", "Binh gom", "Bat Trang", 500000, "Dat set trang");
    HangThucPham tp("TP01", "Sua tuoi", "Vinamilk", 30000, "01/01/2024", "01/01/2025");
  
    cout << "--- THONG TIN CAC MAT HANG ---" << endl;
    dm.xuat();
    ss.xuat();
    tp.xuat();

    return 0;
}
