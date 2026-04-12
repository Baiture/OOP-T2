#include <iostream>
#include <chrono>

using namespace std;

int main() {
    auto now = chrono::system_clock::now();
    
    auto duration = now.time_since_epoch();
    long long total_seconds = chrono::duration_cast<chrono::seconds>(duration).count();

    const int SECONDS_IN_DAY = 86400;
    const int SECONDS_IN_HOUR = 3600;
    const int SECONDS_IN_MINUTE = 60;

    long long days_since_epoch = total_seconds / SECONDS_IN_DAY;
    long long seconds_remaining = total_seconds % SECONDS_IN_DAY;

    int hours = seconds_remaining / SECONDS_IN_HOUR;
    int minutes = (seconds_remaining % SECONDS_IN_HOUR) / SECONDS_IN_MINUTE;
    int seconds = seconds_remaining % SECONDS_IN_MINUTE;

    cout << "Current time: " << hours << " hours, " 
         << minutes << " minutes, and " 
         << seconds << " seconds." << endl;
    cout << "Number of days since the epoch: " << days_since_epoch << " days." << endl;

    return 0;
}
