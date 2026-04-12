#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// 1. Custom Exceptions
class TuoiKhongHopLe : public runtime_error {
public:
    TuoiKhongHopLe() : runtime_error("Loi: Tuoi phai nam trong khoang tu 18 den 65!") {}
};

class HeSoLuongKhongHopLe : public runtime_error {
public:
    HeSoLuongKhongHopLe() : runtime_error("Loi: He so luong phai lon hon 0!") {}
};

// 2. Abstract Base Class: NhanVien
class NhanVien {
protected:
    string ma_nv, ho_ten, gioi_tinh, dia_chi;
    int nam_sinh;
    float he_so_luong, luong_toi_da;

public:
    NhanVien(string ma, string ten, int ns, string gt, string dc, float hsl, float ltd)
        : ma_nv(ma), ho_ten(ten), gioi_tinh(gt), dia_chi(dc), luong_toi_da(ltd) {
        setAge(2026 - ns); // Gia su nam hien tai la 2026
        setHeSo(hsl);
    }

    virtual ~NhanVien() = default;

    void setAge(int tuoi) {
        if (tuoi < 18 || tuoi > 65) throw TuoiKhongHopLe();
        this->nam_sinh = 2026 - tuoi;
    }

    void setHeSo(float hsl) {
        if (hsl <= 0) throw HeSoLuongKhongHopLe();
        this->he_so_luong = hsl;
    }

    string getMa() const { return ma_nv; }
    string getTen() const { return ho_ten; }

    virtual float tinh_thu_nhap() const {
        float luong_cb = 1800000.0f;
        return min(he_so_luong * luong_cb, luong_toi_da);
    }

    // Pure virtual method
    virtual string getLoaiNV() const = 0;

    virtual void display(ostream& os) const {
        os << "[" << setw(15) << left << getLoaiNV() << "]"
           << " Ma: " << setw(6) << ma_nv 
           << " | Ten: " << setw(15) << ho_ten 
           << " | Thu nhap: " << fixed << setprecision(0) << setw(10) << tinh_thu_nhap() << " VND";
    }

    // Operator Overloading
    bool operator==(const NhanVien& other) const {
        return this->ma_nv == other.ma_nv;
    }

    friend ostream& operator<<(ostream& os, const NhanVien& nv) {
        nv.display(os);
        return os;
    }
};

// 3. Subclasses
class CongTacVien : public NhanVien {
private:
    string thoi_han_hd;
    float phu_cap_ld;

public:
    CongTacVien(string ma, string ten, int ns, string gt, string dc, float hsl, float ltd, string th, float pc)
        : NhanVien(ma, ten, ns, gt, dc, hsl, ltd), thoi_han_hd(th), phu_cap_ld(pc) {}

    string getLoaiNV() const override { return "Cong Tac Vien"; }

    float tinh_thu_nhap() const override {
        return min(NhanVien::tinh_thu_nhap() + phu_cap_ld, luong_toi_da);
    }

    void display(ostream& os) const override {
        NhanVien::display(os);
        os << " | HD: " << thoi_han_hd;
    }
};

class NhanVienChinhThuc : public NhanVien {
private:
    string vi_tri;

public:
    NhanVienChinhThuc(string ma, string ten, int ns, string gt, string dc, float hsl, float ltd, string vt)
        : NhanVien(ma, ten, ns, gt, dc, hsl, ltd), vi_tri(vt) {}

    string getLoaiNV() const override { return "Chinh Thuc"; }

    void display(ostream& os) const override {
        NhanVien::display(os);
        os << " | Vi tri: " << vi_tri;
    }
};

class TruongPhong : public NhanVien {
private:
    float phu_cap_ql;

public:
    TruongPhong(string ma, string ten, int ns, string gt, string dc, float hsl, float ltd, float pc)
        : NhanVien(ma, ten, ns, gt, dc, hsl, ltd), phu_cap_ql(pc) {}

    string getLoaiNV() const override { return "Truong Phong"; }

    float tinh_thu_nhap() const override {
        return min(NhanVien::tinh_thu_nhap() + phu_cap_ql, luong_toi_da);
    }

    void display(ostream& os) const override {
        NhanVien::display(os);
        os << " | Phu cap QL: " << fixed << setprecision(0) << phu_cap_ql;
    }
};

// 4. Management System
enum class LoaiNV { CTV = 1, ChinhThuc = 2, TruongPhong = 3 };

class QLNV {
private:
    vector<unique_ptr<NhanVien>> dsNhanVien;

    string tolower_str(string s) const {
        transform(s.begin(), s.end(), s.begin(), ::tolower);
        return s;
    }

public:
    void themNhanVien() {
        try {
            int choice;
            cout << "\n--- THEM NHAN VIEN MOI ---\n";
            cout << "1. Cong tac vien | 2. Chinh thuc | 3. Truong phong\nChon: ";
            if (!(cin >> choice)) throw invalid_argument("Lua chon phai la so!");
            cin.ignore();

            string ma, ten, gt, dc;
            int ns; float hsl, ltd;
            cout << "Ma NV: "; getline(cin, ma);
            cout << "Ho ten: "; getline(cin, ten);
            cout << "Nam sinh: "; cin >> ns; cin.ignore();
            cout << "Gioi tinh: "; getline(cin, gt);
            cout << "Dia chi: "; getline(cin, dc);
            cout << "He so luong: "; cin >> hsl;
            cout << "Luong toi da: "; cin >> ltd;
            cin.ignore();

            unique_ptr<NhanVien> nv;
            switch (static_cast<LoaiNV>(choice)) {
                case LoaiNV::CTV: {
                    string th; float pc;
                    cout << "Thoi han HD: "; getline(cin, th);
                    cout << "Phu cap LD: "; cin >> pc;
                    nv = make_unique<CongTacVien>(ma, ten, ns, gt, dc, hsl, ltd, th, pc);
                    break;
                }
                case LoaiNV::ChinhThuc: {
                    string vt;
                    cout << "Vi tri: "; getline(cin, vt);
                    nv = make_unique<NhanVienChinhThuc>(ma, ten, ns, gt, dc, hsl, ltd, vt);
                    break;
                }
                case LoaiNV::TruongPhong: {
                    float pc;
                    cout << "Phu cap QL: "; cin >> pc;
                    nv = make_unique<TruongPhong>(ma, ten, ns, gt, dc, hsl, ltd, pc);
                    break;
                }
                default: cout << "Loai khong hop le!\n"; return;
            }
            dsNhanVien.push_back(move(nv));
            cout << "Da them thanh cong!\n";
        } catch (exception& e) {
            cerr << "Loi: " << e.what() << endl;
            cin.clear(); cin.ignore(1000, '\n');
        }
    }

    void timNhanVien() {
        string keyword;
        cout << "Nhap ten can tim: "; cin.ignore(); getline(cin, keyword);
        string key = tolower_str(keyword);
        bool found = false;
        for (const auto& nv : dsNhanVien) {
            if (tolower_str(nv->getTen()).find(key) != string::npos) {
                cout << *nv << endl;
                found = true;
            }
        }
        if (!found) cout << "Khong tim thay!\n";
    }

    void hienThi() const {
        if (dsNhanVien.empty()) {
            cout << "Danh sach trong!\n";
            return;
        }
        cout << "\n--- DANH SACH NHAN VIEN ---\n";
        for (const auto& nv : dsNhanVien) cout << *nv << endl;
    }

    void menu() {
        int chon;
        while (true) {
            cout << "\n--- QUAN LY NHAN VIEN ---\n";
            cout << "1. Them | 2. Tim kiem | 3. Hien thi | 4. Thoat\nChon: ";
            if (!(cin >> chon)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
            if (chon == 4) break;
            switch (chon) {
                case 1: themNhanVien(); break;
                case 2: timNhanVien(); break;
                case 3: hienThi(); break;
                default: cout << "Lua chon sai!\n";
            }
        }
    }
};

int main() {
    QLNV ql;
    ql.menu();
    return 0;
}
