// Algorithmic_Solar_Tracker_Arduino.cpp : Test harness for the Tracker library.
// Replaces the default main with a small test for Roorkee, Uttarakhand at 12:00.

#include <iostream>
#include <cmath>
#include "Tracker.h"

#define _ARDUINO_ 0

int main()
{
    Tracker tracker;

    // Roorkee, Uttarakhand
    double lat_deg = 29.8639;     // degrees north
    double lon_deg = 77.8958;     // degrees east
    const double pi = 3.14159265358979323846;

    // Tracker expects latitude in radians; STM and longitude in degrees
    double lat_rad = lat_deg * pi / 180.0;
    double STM_deg = 82.5; // Indian Standard Meridian (82.5°E)

    tracker.set_Loc(lat_rad, STM_deg, lon_deg);

    int day = 172;       // example: ~June 21 (summer solstice)
    double time = 12.0;  // 12:00 local time

    tracker.set_Time(day, time);

    double elev_rad = tracker.get_elev();
    double azim_rad = tracker.get_azim();

    double elev_deg = elev_rad * 180.0 / pi;
    double azim_deg = azim_rad * 180.0 / pi;

    std::cout << "Location: Roorkee (" << lat_deg << " N, " << lon_deg << " E)\n";
    std::cout << "Day: " << day << ", Time: " << time << " hrs\n";
    std::cout << "Elevation: " << elev_deg << " degrees\n";
    std::cout << "Azimuth: " << azim_deg << " degrees\n";

    return 0;
}

