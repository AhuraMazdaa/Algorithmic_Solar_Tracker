/*Library for creating a Tracker Object    *
* that can track the sun based on time and *
* location of the Tracker                  */

//Created on 20-2-2015
//Nishanth IITRoorkee

#ifndef Tracker_H
#define Tracker_H

class Tracker
{
	public:
		void set_Loc(double lat,double STM,double Long);
		void set_Time(int day,double time);
		double get_elev(); //claculate and returns the elevation
		double get_azim();	//the elav calculated by the first function must be available to calculate Azimuth
		void print_val();
		
	private:
		double _Lat;//Latitude of location in radians
		double _STM; //floatitude value of Allahabad in degrees
		double _long;//floatitude of Roorkee in degrees
		double _elev;
		double _azim;
		double _B;
		double _Eot;
		double _TC;
		double _decl;
		double _HRA;
		double _LT;//Local time
		double _LST;
		double t1,t2,t3,t4,t5;
};

#endif
