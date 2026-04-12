#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;

class GiaKhongHopLe : public runtime_error {
public:
    GiaKhongHopLe(const string& msg) : runtime_error(msg) {}
};

class MaHangTrungLap : public runtime_error {
public:
    MaHangTrungLap(const string& msg) : runtime_error(msg) {}
};

class HangHoa {
protected:
    string maHang;
    string tenHang;
    string nhaSX;
    double gia;

public:
    HangHoa(string ma, string ten, string nsx, double g)
        : maHang(ma), tenHang(ten), nhaSX(nsx) {
        setGia(g);
    }

    string getMaHang() const { return maHang; }
    string getTenHang() const { return tenHang; }
    double getGia() const { return gia; }

    void setGia(double g) {
        if (g < 0) {
            throw GiaKhongHopLe("Gia khong the am.");
        }
        this->gia = g;
    }

    virtual string loaiHang() const = 0;
    virtual void display() const = 0;

    bool operator==(const HangHoa& other) const {
        return this->maHang == other.maHang;
    }

    bool operator<(const HangHoa& other) const {
        return this->gia < other.gia;
    }

    virtual ~HangHoa() = default;
};

class HangDienMay : public HangHoa {
private:
    int thoiGianBaoHanh;
    double dienAp, congSuat;
public:
    HangDienMay(string ma, string ten, string nsx, double g, int tgbh, double da, double cs)
        : HangHoa(ma, ten, nsx, g), thoiGianBaoHanh(tgbh), dienAp(da), congSuat(cs) {}

    string loaiHang() const override { return "Dien may"; }
    void display() const override {
        cout << left << setw(12) << "[" + loaiHang() + "]" 
             << " | Ma: " << setw(6) << maHang 
             << " | Ten: " << setw(20) << tenHang 
             << " | Gia: " << fixed << setprecision(0) << gia << " VND" << endl;
    }
};

class HangSanhSu : public HangHoa {
private:
    string loaiNguyenLieu;
public:
    HangSanhSu(string ma, string ten, string nsx, double g, string lnl)
        : HangHoa(ma, ten, nsx, g), loaiNguyenLieu(lnl) {}

    string loaiHang() const override { return "Sanh su"; }
    void display() const override {
        cout << left << setw(12) << "[" + loaiHang() + "]" 
             << " | Ma: " << setw(6) << maHang 
             << " | Ten: " << setw(20) << tenHang 
             << " | Gia: " << fixed << setprecision(0) << gia << " VND" << endl;
    }
};

class HangThucPham : public HangHoa {
private:
    string ngaySX, ngayHetHan;
public:
    HangThucPham(string ma, string ten, string nsx, double g, string nsx_date, string nhh)
        : HangHoa(ma, ten, nsx, g), ngaySX(nsx_date), ngayHetHan(nhh) {}

    string loaiHang() const override { return "Thuc pham"; }
    void display() const override {
        cout << left << setw(12) << "[" + loaiHang() + "]" 
             << " | Ma: " << setw(6) << maHang 
             << " | Ten: " << setw(20) << tenHang 
             << " | Gia: " << fixed << setprecision(0) << gia << " VND" << endl;
    }
};

class QuanLiKho {
private:
    vector<HangHoa*> ds;
    string fileName;

public:
    QuanLiKho(string fName) : fileName(fName) {
        cout << "Phien lam viec bat dau: " << fileName << endl;
    }

    void themHangHoa(HangHoa* hangHoa) {
        for (auto const& item : ds) {
            if (*item == *hangHoa) {
                string maLoi = hangHoa->getMaHang();
                delete hangHoa;
                throw MaHangTrungLap("Ma hang " + maLoi + " da ton tai!");
            }
        }
        ds.push_back(hangHoa);
    }

    void hienThiDanhSach() {
        sort(ds.begin(), ds.end(), [](HangHoa* a, HangHoa* b) {
            return *a < *b;
        });

        for (auto const& hangHoa : ds) {
            hangHoa->display();
        }
    }

    ~QuanLiKho() {
        ofstream f(fileName);
        if (f.is_open()) {
            f << "MA HANG,TEN HANG,GIA,LOAI HANG\n";
            for (auto const& h : ds) {
                f << h->getMaHang() << "," << h->getTenHang() << "," << h->getGia() << "," << h->loaiHang() << "\n";
            }
            f.close();
        }
        for (auto h : ds) delete h; 
    }
};

int main() {
    try {
        QuanLiKho kho("kho_hang.csv");

        kho.themHangHoa(new HangDienMay("DM01", "Tu lanh Samsung", "Samsung", 15000000, 24, 220, 150));
        kho.themHangHoa(new HangSanhSu("SS01", "Binh hoa co", "Bat Trang", 500000, "Gom su"));
        kho.themHangHoa(new HangThucPham("TP01", "Sua tuoi Vinamilk", "Vinamilk", 30000, "01/01/2026", "01/06/2026"));

        cout << "\nDANH SACH HANG HOA:" << endl;
        kho.hienThiDanhSach();

    } catch (const exception& e) {
        cerr << "\nLOI: " << e.what() << endl;
    }
    return 0;
}
