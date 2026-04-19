#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdexcept>

using namespace std;

class CanBo {
protected:
    string hoTen, gioiTinh, diaChi, loai;
    int tuoi;

public:
    CanBo(string ten, int t, string gt, string dc, string l)
        : hoTen(ten), tuoi(t), gioiTinh(gt), diaChi(dc), loai(l) {}

    virtual ~CanBo() {}

    string getHoTen() const { return hoTen; }
    string getLoai() const { return loai; }
    virtual string getThongTinRieng() const = 0;
    virtual int getCapBac() const { return 0; }

    virtual void hienThi() const {
        cout << "[" << loai << "] " << hoTen << " | Tuoi: " << tuoi 
             << " | GT: " << gioiTinh << " | DC: " << diaChi;
    }

    virtual string to_json() const {
        return "{\"hoTen\":\"" + hoTen + "\", \"tuoi\":" + to_string(tuoi) + 
               ", \"gioiTinh\":\"" + gioiTinh + "\", \"diaChi\":\"" + diaChi + 
               "\", \"loai\":\"" + loai + "\", \"extra\":\"" + getThongTinRieng() + "\"}";
    }
};

class CongNhan : public CanBo {
    int bac;
public:
    CongNhan(string ten, int t, string gt, string dc, int b) 
        : CanBo(ten, t, gt, dc, "CongNhan"), bac(b) {}
    
    string getThongTinRieng() const override { return to_string(bac); }
    int getCapBac() const override { return bac; }
    void hienThi() const override {
        CanBo::hienThi(); cout << " | Bac: " << bac << "/10" << endl;
    }
};

class KySu : public CanBo {
    string nganh;
public:
    KySu(string ten, int t, string gt, string dc, string n) 
        : CanBo(ten, t, gt, dc, "KySu"), nganh(n) {}
    
    string getThongTinRieng() const override { return nganh; }
    void hienThi() const override {
        CanBo::hienThi(); cout << " | Nganh: " << nganh << endl;
    }
};

class NhanVien : public CanBo {
    string congViec;
public:
    NhanVien(string ten, int t, string gt, string dc, string cv) 
        : CanBo(ten, t, gt, dc, "NhanVien"), congViec(cv) {}
    
    string getThongTinRieng() const override { return congViec; }
    void hienThi() const override {
        CanBo::hienThi(); cout << " | Cong viec: " << congViec << endl;
    }
};

class QuanLyCanBo {
private:
    map<string, CanBo*> danhSach;

    void xoaBoNho() {
        for (auto const& [key, val] : danhSach) delete val;
        danhSach.clear();
    }

public:
    ~QuanLyCanBo() { xoaBoNho(); }

    void saveToJson() {
        ofstream f("canbo.json");
        f << "[\n";
        for (auto it = danhSach.begin(); it != danhSach.end(); ++it) {
            f << "  " << it->second->to_json() << (next(it) == danhSach.end() ? "" : ",") << "\n";
        }
        f << "]";
        f.close();
    }

    void loadFromCSV(string filename) {
        ifstream f(filename);
        if (!f.is_open()) throw runtime_error("Loi: Khong tim thay file " + filename);

        string line;
        while (getline(f, line)) {
            try {
                stringstream ss(line);
                string ten, gt, dc, loai, extra, sTuoi;
                getline(ss, ten, ',');
                getline(ss, sTuoi, ',');
                getline(ss, gt, ',');
                getline(ss, dc, ',');
                getline(ss, loai, ',');
                getline(ss, extra, ',');

                int tuoi = stoi(sTuoi);
                themMoi(loai, ten, tuoi, gt, dc, extra);
            } catch (...) {
                continue;
            }
        }
    }

    void themMoi(string loai, string ten, int tuoi, string gt, string dc, string extra) {
        if (loai == "CongNhan") danhSach[ten] = new CongNhan(ten, tuoi, gt, dc, stoi(extra));
        else if (loai == "KySu") danhSach[ten] = new KySu(ten, tuoi, gt, dc, extra);
        else if (loai == "NhanVien") danhSach[ten] = new NhanVien(ten, tuoi, gt, dc, extra);
        saveToJson();
    }

    void xoa(string ten) {
        if (danhSach.erase(ten)) {
            cout << "Da xoa: " << ten << endl;
            saveToJson();
        } else cout << "Khong tim thay!\n";
    }

    void timTheoLoai(string loai) {
        for (auto const& [ten, cb] : danhSach) {
            if (cb->getLoai() == loai) cb->hienThi();
        }
    }

    void inTop3() {
        vector<CanBo*> v;
        for (auto const& [ten, cb] : danhSach) v.push_back(cb);
        
        sort(v.begin(), v.end(), [](CanBo* a, CanBo* b) {
            return a->getCapBac() > b->getCapBac();
        });

        cout << "--- Top 3 can bo cao nhat ---\n";
        for (int i = 0; i < min(3, (int)v.size()); ++i) v[i]->hienThi();
    }

    void hienThiAll() {
        for (auto const& [ten, cb] : danhSach) cb->hienThi();
    }
};

int main() {
    QuanLyCanBo ql;
    
    try {
        ql.loadFromCSV("canbo.csv");
        cout << "He thong san sang.\n";
    } catch (exception &e) {
        cout << e.what() << endl;
    }

    int choice;
    while (true) {
        try {
            cout << "\n1. Them | 2. Xoa | 3. Tim Loai | 4. Top 3 | 5. Tat ca | 6. Thoat\n";
            cout << "Chon: "; cin >> choice;
            if (cin.fail()) throw invalid_argument("Nhap so!");
            cin.ignore();

            if (choice == 6) break;
            switch (choice) {
                case 1: {
                    string loai, ten, gt, dc, extra; int tuoi;
                    cout << "Loai: "; cin >> loai; cin.ignore();
                    cout << "Ho ten: "; getline(cin, ten);
                    cout << "Tuoi: "; cin >> tuoi; cin.ignore();
                    cout << "GT: "; cin >> gt; cin.ignore();
                    cout << "Dia chi: "; getline(cin, dc);
                    cout << "Extra: "; getline(cin, extra);
                    ql.themMoi(loai, ten, tuoi, gt, dc, extra);
                    break;
                }
                case 2: {
                    string ten; cout << "Ten: "; getline(cin, ten);
                    ql.xoa(ten); break;
                }
                case 3: {
                    string loai; cout << "Loai: "; cin >> loai;
                    ql.timTheoLoai(loai); break;
                }
                case 4: ql.inTop3(); break;
                case 5: ql.hienThiAll(); break;
            }
        } catch (exception &e) {
            cout << "LOI: " << e.what() << endl;
            cin.clear(); cin.ignore(1000, '\n');
        }
    }
    return 0;
}
