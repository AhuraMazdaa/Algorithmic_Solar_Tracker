#include "Tracker.h"
#include "Arduino.h"

//set_Loc method to set the location of the tracker in terms of latitude, standard time meridian and longitude
void Tracker::set_Loc(double lat,double STM,double Long)
{
	_Lat=lat;
	_STM=STM;
	_long=Long;
}

//set time in terms of solar time in the location set by the set_Loc method
void Tracker::set_Time(int day,double time)
{
	_B=0.0172*(day-81);
	_LT=time;//in hours of decimal format
}

//returns elevation of the sun
double Tracker::get_elev()
{
	_Eot=9.87*sin(2*_B)-7.53*cos(_B)-1.5*sin(_B);// in mins
	_TC=4*(_long-_STM)+_Eot;//in mins
	_LST=_LT+(_TC/60.0);//in haours decimal
	_HRA=0.2618*(_LST-12.0);//in radians
	_decl=asin(0.397949*sin(_B));
	t1=sin(_decl)*sin(_Lat);
	t2=cos(_Lat)*cos(_decl)*cos(_HRA);
	_elev=asin(t1+t2);
	return _elev;
	
}

//retunrs the azimuth of the sun
double Tracker::get_azim()
{
	t3=sin(_decl)*cos(_Lat);
	t4=cos(_decl)*sin(_Lat)*cos(_HRA);
	t5=cos(_HRA);
	_azim=acos((t3-t4)/t5);
	if(_HRA<=0)return _azim;
	else return (2*3.1415-_azim);
}

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
