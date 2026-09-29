#include "Tracker.h"
#include<math.h>
#if _ARDUINO_
#include "Arduino.h"
#else
#include <iostream>
#endif // Arduino

#define _PI 3.14159265
#define _MINUTES_PER_DEGREE (24 * 60) / 360			//4 minutes per degree of longitude
#define _RADIANS_PER_DAY (2 * _PI) / 365.25			//2*PI/365.25
#define _EARTHS_ANGULAR_VELOCITY (2 * _PI) / 24		//2*PI/24 (rad/hr)
#define _SIN_23p45 0.397949	//sin(23.45 degrees) used in the calculation of declination of the sun

//Sets the location of the tracker
void Tracker::set_Loc(double lat, double STM, double long_minutes)
{
	_Lat = lat;				//in radians
	_STM = STM;				//in minutes
	_long = long_minutes;	//in minutes
}

//set time in terms of solar time in the location set by the set_Loc method
void Tracker::set_Time(int day, double time)
{
	_B = _RADIANS_PER_DAY * (day - 81);		//81st day is the starting day in the year for the calculation elev and azimuth of the sun in the formulae used
	_LT = time;								//Local time at Greenwich meridian (GMT) in 24-hours (decimal format)
}

//returns elevation of the sun
double Tracker::get_elev()
{
	_Eot = 9.87 * sin(2 * _B) - 7.53 * cos(_B) - 1.5 * sin(_B);	// in mins
	_TC = _MINUTES_PER_DEGREE * (_long - _STM) + _Eot;			//in mins
	_LST = _LT + (_TC / 60.0);									//Local Solar time in hours (decimal)
	_HRA = _EARTHS_ANGULAR_VELOCITY * (_LST - 12.0);			//Hour angle of the sun in radians
	_decl = asin(_SIN_23p45 * sin(_B));							//Declination of the sun in radians
	t1 = sin(_decl) * sin(_Lat);								//debug
	t2 = cos(_Lat) * cos(_decl) * cos(_HRA);					//debug
	_elev = asin(t1 + t2);
	return _elev;
}

//returns the azimuth of the sun
double Tracker::get_azim()
{
	t3 = sin(_decl) * cos(_Lat);								//debug (radians)
	t4 = cos(_decl) * sin(_Lat) * cos(_HRA);					//debug (radians
	t5 = cos(_HRA);												//debug	(radians)
	_azim = acos((t3 - t4) / t5);
	if (_HRA <= 0)return _azim;
	else return (2 * 3.1415 - _azim);
}

#if _ARDUINO_
//print function
void Tracker::print_val()
{
	Serial.print("");
	Serial.println();
	Serial.print("");
	Serial.println();
	Serial.print("");
	Serial.println();
	Serial.print("");
	Serial.println();
	Serial.print("");
	Serial.println();
	Serial.print("");
	Serial.println();
	Serial.print("");
	Serial.println();
	Serial.print("");
	Serial.println();
	Serial.print("");
	Serial.println();
	Serial.print("");
	Serial.println();
	Serial.print("");
	Serial.println();
	Serial.print("Hra= ");
	Serial.println(_HRA);
	Serial.print("t1= ");
	Serial.println(t1);
	Serial.print("t2= ");
	Serial.println(t2);
	Serial.print("t3= ");
	Serial.println(t3);
	Serial.print("t4= ");
	Serial.println(t4);
	Serial.print("t5= ");
	Serial.println(t5);
}
#else
void Tracker::debug_print_val()
{
	std::cout << "";
	std::cout << "\n";
	std::cout << "Hra= ";
	std::cout << _HRA;
	std::cout << std::endl;
	std::cout << "t1= ";
	std::cout << t1;
	std::cout << std::endl;
	std::cout << "t2= ";
	std::cout << t2;
	std::cout << std::endl;
	std::cout << "t3= ";
	std::cout << t3;
	std::cout << std::endl;
	std::cout << "t4= ";
	std::cout << t4;
	std::cout << std::endl;
	std::cout << "t5= ";
	std::cout << t5;
	std::cout << std::endl;
}

#endif

