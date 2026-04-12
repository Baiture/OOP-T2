#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main() {
    cout << fixed << setprecision(2);

    double r = 5.0;
    double pi = M_PI; 
    double volume = (4.0 / 3.0) * pi * pow(r, 3);
    cout << "1. Volume of a sphere with radius 5: " << volume << endl;

    double cover_price = 24.95;
    double discount = 0.40;
    double discounted_price = cover_price * (1 - discount);
    
    int num_copies = 60;
    double total_book_cost = discounted_price * num_copies;
    double shipping_cost = 3.0 + (num_copies - 1) * 0.75;
    double total_wholesale_cost = total_book_cost + shipping_cost;
    
    cout << "2. Total wholesale cost for 60 copies: $" << total_wholesale_cost << endl;

    int start_hour = 6, start_min = 52;
    int start_time_seconds = (start_hour * 3600) + (start_min * 60);

    int easy_pace_seconds = (8 * 60) + 15;
    int tempo_pace_seconds = (7 * 60) + 12;
    
    int total_run_seconds = (1 * easy_pace_seconds) + (3 * tempo_pace_seconds) + (1 * easy_pace_seconds);

    int arrival_time_seconds = start_time_seconds + total_run_seconds;

    int arrival_hour = arrival_time_seconds / 3600;
    int arrival_min = (arrival_time_seconds % 3600) / 60;
    int arrival_sec = arrival_time_seconds % 60;

    cout << "3. Time you get home for breakfast: " 
         << arrival_hour << ":" 
         << setfill('0') << setw(2) << arrival_min << " AM" << endl;

    return 0;
}
