#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

class NhanVien {
protected:
    string ma_nv, ho_ten, gioi_tinh, dia_chi;
    int nam_sinh;
    float he_so_luong, luong_toi_da;

public:
    NhanVien(string ma, string ten, int ns, string gt, string dc, float hsl, float ltd)
        : ma_nv(ma), ho_ten(ten), nam_sinh(ns), gioi_tinh(gt), dia_chi(dc), luong_toi_da(ltd) {
        he_so_luong = (hsl > 0) ? hsl : 1.0f;
    }

    virtual float tinh_thu_nhap() {
        float luong_cb = 1800000.0f;
        float thu_nhap = he_so_luong * luong_cb;
        return min(thu_nhap, luong_toi_da);
    }

    virtual void xuat() {
        cout << "Ma: " << ma_nv << " | Ten: " << ho_ten 
             << " | Thu nhap: " << fixed << setprecision(0) << tinh_thu_nhap() << " VND";
    }

    virtual ~NhanVien() {}
};

class CongTacVien : public NhanVien {
private:
    string thoi_han_hd;
    float phu_cap_ld;

public:
    CongTacVien(string ma, string ten, int ns, string gt, string dc, float hsl, float ltd, string th, float pc)
        : NhanVien(ma, ten, ns, gt, dc, hsl, ltd), thoi_han_hd(th), phu_cap_ld(pc) {}

    float tinh_thu_nhap() override {
        float thu_nhap_goc = NhanVien::tinh_thu_nhap();
        return min(thu_nhap_goc + phu_cap_ld, luong_toi_da);
    }

    void xuat() override {
        NhanVien::xuat();
        cout << " (Cong tac vien - HD: " << thoi_han_hd << ")" << endl;
    }
};

class NhanVienChinhThuc : public NhanVien {
private:
    string vi_tri_cong_viec;

public:
    NhanVienChinhThuc(string ma, string ten, int ns, string gt, string dc, float hsl, float ltd, string vt)
        : NhanVien(ma, ten, ns, gt, dc, hsl, ltd), vi_tri_cong_viec(vt) {}

    void xuat() override {
        NhanVien::xuat();
        cout << " (Chinh thuc - Vi tri: " << vi_tri_cong_viec << ")" << endl;
    }
};

class TruongPhong : public NhanVien {
private:
    string ngay_bat_dau_ql;
    float phu_cap_ql;

public:
    TruongPhong(string ma, string ten, int ns, string gt, string dc, float hsl, float ltd, string ngay, float pc)
        : NhanVien(ma, ten, ns, gt, dc, hsl, ltd), ngay_bat_dau_ql(ngay), phu_cap_ql(pc) {}

    float tinh_thu_nhap() override {
        float thu_nhap_goc = NhanVien::tinh_thu_nhap();
        return min(thu_nhap_goc + phu_cap_ql, luong_toi_da);
    }

    void xuat() override {
        NhanVien::xuat();
        cout << " (Truong phong - Tu: " << ngay_bat_dau_ql << ")" << endl;
    }
};

int main() {
    CongTacVien ctv("CTV01", "Nguyen Van A", 2000, "Nam", "HN", 2.0, 10000000, "6 thang", 500000);
    NhanVienChinhThuc nvct("NV01", "Le Van C", 1995, "Nam", "DN", 3.5, 15000000, "Lap trinh vien");
    TruongPhong tp("TP01", "Tran Thi B", 1985, "Nu", "HCM", 5.0, 30000000, "01/01/2020", 2000000);

    ctv.xuat();
    nvct.xuat();
    tp.xuat();

    return 0;
}
