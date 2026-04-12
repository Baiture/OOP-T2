#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <string>

using namespace std;

class Point {
private:
    int x, y;
public:
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    void display() const {
        cout << "(" << x << ", " << y << ")";
    }

    Point doiXung() const {
        return Point(-x, -y);
    }

    double khoangCachO() const {
        return sqrt(x * x + y * y);
    }

    double khoangCachDiem(const Point& other) const {
        int dx = x - other.x;
        int dy = y - other.y;
        return sqrt(dx * dx + dy * dy);
    }
};

class SieuNhan {
private:
    string name, vuKhi, mauSac;
    int sucManh;
public:
    SieuNhan(string n, string vk, string m, int sm) 
        : name(n), vuKhi(vk), mauSac(m), sucManh(sm) {}

    void display() const {
        cout << left << setw(15) << name 
             << " | VK: " << setw(12) << vuKhi 
             << " | Mau: " << setw(10) << mauSac 
             << " | SM: " << sucManh << endl;
    }
};

int main() {
    Point A(3, 4);
    int xb, yb;
    cout << "Nhap B (x y): "; 
    cin >> xb >> yb;
    Point B(xb, yb);

    cout << "A: "; A.display(); cout << endl;
    cout << "B: "; B.display(); cout << endl;
    cout << "C (doi xung B): "; B.doiXung().display(); cout << endl;
    
    cout << fixed << setprecision(2);
    cout << "d(B, O) = " << B.khoangCachO() << endl;
    cout << "d(A, B) = " << A.khoangCachDiem(B) << endl;

    cout << "-------------------------------------" << endl;

    vector<SieuNhan> ds;
    char tiepTuc = 'y';

    while (tiepTuc == 'y' || tiepTuc == 'Y') {
        string n, vk, m;
        int sm;
        cout << "Nhap Ten, Vu khi, Mau sac, Suc manh: ";
        cin >> n >> vk >> m >> sm;
        ds.push_back(SieuNhan(n, vk, m, sm));
        cout << "Tiep tuc? (y/n): ";
        cin >> tiepTuc;
    }

    cout << "\nDANH SACH SIEU NHAN:\n";
    for (const auto& sn : ds) {
        sn.display();
    }

    return 0;
}
