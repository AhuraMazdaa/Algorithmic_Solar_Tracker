// Algorithmic_Solar_Tracker_Arduino.cpp : Test harness for the Tracker library.
// Replaces the default main with a small test for Roorkee, Uttarakhand at 12:00.

#include <iostream>
#include <cmath>
#include "Tracker.h"

#define _ARDUINO_ 0

#if _ARDUINO_ == 0

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

#else

#include <Arduino.h>

// Global tracker instance for Arduino sketch
Tracker tracker;

const double pi = 3.14159265358979323846;
const double lat_deg = 29.8639;   // Roorkee latitude (degrees)
const double lon_deg = 77.8958;   // Roorkee longitude (degrees)
const double STM_deg = 82.5;      // Indian Standard Meridian (82.5°E)
const int day = 172;              // example day (~June 21)
const double time_of_day = 12.0;  // 12:00 local time

void setup()
{
    Serial.begin(9600);
	while (!Serial) { ; } // some boards require this to wait for Serial to be ready (on the ATmega328P check RXC0 (bit 7))

    double lat_rad = lat_deg * pi / 180.0;
    tracker.set_Loc(lat_rad, STM_deg, lon_deg);
    tracker.set_Time(day, time_of_day);

    double elev_rad = tracker.get_elev();
    double azim_rad = tracker.get_azim();

    double elev_deg = elev_rad * 180.0 / pi;
    double azim_deg = azim_rad * 180.0 / pi;

    Serial.print("Location: Roorkee (");
    Serial.print(lat_deg);
    Serial.print(" N, ");
    Serial.print(lon_deg);
    Serial.println(" E)");

    Serial.print("Day: ");
    Serial.print(day);
    Serial.print(", Time: ");
    Serial.print(time_of_day);
    Serial.println(" hrs");

    Serial.print("Elevation: ");
    Serial.println(elev_deg, 4); // print with 4 decimal places

    Serial.print("Azimuth: ");
    Serial.println(azim_deg, 4);
}

void loop()
{
    // Keep running; nothing to update for this simple test
    delay(1000);
}

#endif
