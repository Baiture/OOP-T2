#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class CanBo {
protected:
    string hoTen;
    int tuoi;
    string gioiTinh;
    string diaChi;

public:
    CanBo(string ten, int t, string gt, string dc)
        : hoTen(ten), tuoi(t), gioiTinh(gt), diaChi(dc) {}

    virtual ~CanBo() {}

    string getHoTen() { return hoTen; }

    virtual void hienThi() {
        cout << "Ho ten: " << hoTen << " | Tuoi: " << tuoi 
             << " | Gioi tinh: " << gioiTinh << " | Dia chi: " << diaChi;
    }
};

class CongNhan : public CanBo {
private:
    int bac;

public:
    CongNhan(string ten, int t, string gt, string dc, int b)
        : CanBo(ten, t, gt, dc), bac(b) {}

    void hienThi() override {
        CanBo::hienThi();
        cout << " | Bac: " << bac << "/10" << endl;
    }
};

class KySu : public CanBo {
private:
    string nganhDaoTao;

public:
    KySu(string ten, int t, string gt, string dc, string nganh)
        : CanBo(ten, t, gt, dc), nganhDaoTao(nganh) {}

    void hienThi() override {
        CanBo::hienThi();
        cout << " | Nganh: " << nganhDaoTao << endl;
    }
};

class NhanVien : public CanBo {
private:
    string congViec;

public:
    NhanVien(string ten, int t, string gt, string dc, string cv)
        : CanBo(ten, t, gt, dc), congViec(cv) {}

    void hienThi() override {
        CanBo::hienThi();
        cout << " | Cong viec: " << congViec << endl;
    }
};

class QLCB {
private:
    vector<CanBo*> danhSach;

public:
    ~QLCB() {
        for (auto cb : danhSach) delete cb;
    }

    void themMoi(CanBo* cb) {
        danhSach.push_back(cb);
    }

    void hienThiDanhSach() {
        if (danhSach.empty()) {
            cout << "Danh sach trong!" << endl;
            return;
        }
        for (auto cb : danhSach) cb->hienThi();
    }

    void timKiem(string ten) {
        bool found = false;
        for (auto cb : danhSach) {
            if (cb->getHoTen().find(ten) != string::npos) {
                cb->hienThi();
                found = true;
            }
        }
        if (!found) cout << "Khong tim thay can bo: " << ten << endl;
    }
};

int main() {
    QLCB ql;
    int choice;

    while (true) {
        cout << "\n1. Them moi | 2. Tim kiem | 3. Hien thi | 4. Thoat\nChon: ";
        if (!(cin >> choice)) break;
        cin.ignore();

        if (choice == 4) break;

        switch (choice) {
            case 1: {
                int loai, tuoi;
                string ten, gt, dc;
                cout << "Loai (1: CN, 2: KS, 3: NV): "; cin >> loai;
                cin.ignore();
                cout << "Ho ten: "; getline(cin, ten);
                cout << "Tuoi: "; cin >> tuoi; cin.ignore();
                cout << "Gioi tinh: "; getline(cin, gt);
                cout << "Dia chi: "; getline(cin, dc);

                if (loai == 1) {
                    int bac; cout << "Bac (1-10): "; cin >> bac;
                    ql.themMoi(new CongNhan(ten, tuoi, gt, dc, bac));
                } else if (loai == 2) {
                    string nganh; cout << "Nganh: "; getline(cin, nganh);
                    ql.themMoi(new KySu(ten, tuoi, gt, dc, nganh));
                } else if (loai == 3) {
                    string cv; cout << "Cong viec: "; getline(cin, cv);
                    ql.themMoi(new NhanVien(ten, tuoi, gt, dc, cv));
                }
                break;
            }
            case 2: {
                string ten;
                cout << "Nhap ten: "; getline(cin, ten);
                ql.timKiem(ten);
                break;
            }
            case 3:
                ql.hienThiDanhSach();
                break;
            default:
                cout << "Khong hop le!" << endl;
        }
    }
    return 0;
}
