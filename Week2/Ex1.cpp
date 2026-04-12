#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    int total_seconds = 42 * 60 + 42;
    cout << "1. Total seconds: " << total_seconds << "s" << endl;

    double miles = 10 / 1.61;
    cout << "2. Miles in 10km: " << fixed << setprecision(2) << miles << " miles" << endl;

    double total_minutes = 42.0 + 42.0 / 60.0;
    double pace_per_mile = total_minutes / miles;
    
    int pace_min = (int)pace_per_mile;
    int pace_sec = (int)((pace_per_mile - pace_min) * 60);
    
    double total_hours = total_minutes / 60.0;
    double avg_speed = miles / total_hours;

    cout << "3. Average pace: " << pace_min << "m " << pace_sec << "s per mile" << endl;
    cout << "   Average speed: " << avg_speed << " mph" << endl;

    return 0;
}
