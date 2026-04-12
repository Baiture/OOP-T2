#include <iostream>
#include <string>

using namespace std;

void draw_line(int cols) {
    for (int i = 0; i < cols; ++i) {
        cout << "+ - - - - ";
    }
    cout << "+" << endl;
}

void draw_space(int cols) {
    for (int j = 0; j < 4; ++j) { // 4 dòng trống mỗi ô
        for (int i = 0; i < cols; ++i) {
            cout << "|         ";
        }
        cout << "|" << endl;
    }
}

void draw_grid(int rows, int cols) {
    for (int i = 0; i < rows; ++i) {
        draw_line(cols);
        draw_space(cols);
    }
    draw_line(cols);
}

int main() {
    cout << "Grid 2x2:" << endl;
    draw_grid(2, 2);
    
    cout << "\nGrid 4x4:" << endl;
    draw_grid(4, 4);
    
    return 0;
}
