/*************************************
 *  AUTHOR  :   alahem monsef (based on Dr. aly abbara work)
 *  EMAIL   :   m.alahem09@gmail.com
 *  VERSION :   1.0
 *  DATE    :   8-aug-2019
 *
 *************************************/

#include <iostream>
#include <cmath>
#include <stdlib.h>

using namespace std;


class Date {
	public :

	Date(){}
	~Date(){}

	Date(char type, int d, int m, int y)
	{
		//calculate_absolute();
		if (type == 'h') {	
			_hd = d;
			_hm = m;
			_hy = y;
			hijri_to_julien();
			julien_to_gregorien();
		}
		if (type == 'g') {
			_gd = d;
			_gm = m;
			_gy = y;
			gregorien_to_julien();
			julien_to_hijri();
		}
	}

	void gregorien_to_julien()
	{
		double YY=_gy;
		double MM=_gm;
		double DD=_gd;
		double JS;
		double GGG = 1;
		if( YY < 1582 )
			GGG = 0;
		if( YY <= 1582 && MM < 10 )
			GGG = 0;
		if( YY <= 1582 && MM == 10 && DD < 5 )
			GGG = 0;
		_julien_day = -1 * floor(7 * (floor((MM + 9) / 12) + YY) / 4);
		double S = 1;
		if ((MM - 9)<0)
			S=-1;
		double A = abs(MM - 9);
		double J1 = floor(YY + S * floor(A / 7));
		J1 = -1 * floor((floor(J1 / 100) + 1) * 3 / 4);
		_julien_day = _julien_day + floor(275 * MM / 9) + DD + (GGG * J1);
		_julien_day = _julien_day + 1721027 + 2 * GGG + 367 * YY - 0.5;
		double K1 = (_julien_day + 1.5);
		double K2 = (K1/7);
		double K3 = K2 - floor(K2);
		_day_week = round(K3*7 + 0.000000000317);
		_gy = YY;
		_gm = MM;
		_gd = DD;
		//cout << DD << " " << MM << " " << YY << endl;
	}

	void julien_to_hijri()
	{
		double Z = (_julien_day + 0.5);
		double AH = floor((Z * 30 - 58442554)/10631);
		double R2 = Z - floor((AH * 10631 + 58442583)/30);
		double M = floor((R2 * 11 + 330)/325);
		double R1 = R2 - floor((M * 325 - 320)/11);
		double J = R1 +1;
		_hy = AH;
		_hm = M;
		_hd = J;
	}
	
	void hijri_to_julien()
	{
		double YYH=_hy;
		double MMH=_hm;
		double DDH=_hd;
		double KH1 = floor((YYH * 10631 + 58442583)/30);
		double KH2 = floor((MMH * 325 - 320)/11);
		double KH3 = DDH - 1;
		_julien_day = KH1 + KH2 + KH3;
		double KHS1 = (_julien_day + 1.5);
		double KHS2 = (KHS1/7);
		double KHS3 = KHS2 - floor(KHS2);
		_day_week = round(KHS3*7 + 0.000000000317) - 1;
		_hy = YYH;
		_hm = MMH;
		_hd = DDH;
		//cout << _hd << endl;
		//cout << _hy << endl;
		//cout << _hm << endl;
	}

	void julien_to_gregorien()
	{
		double Z = floor(_julien_day+0.5);
		double F = _julien_day+0.5 - Z;
		double A,MM,AA;
		if (Z < 2299161) {
			A = Z;
		} else {
			double I = floor((Z - 1867216.25)/36524.25);
			A = Z + 1 + I - floor(I/4);
		}
		double B = A + 1524;
		double C = floor((B - 122.1)/365.25);
		double D = floor(365.25 * C);
		double T = floor((B - D)/ 30.6001);
		double RJ = B - D - floor(30.6001 * T) + F;
		double JJ = floor(RJ);
		if (T < 13.5) {
			MM = T - 1;
		} else { 
			if (T > 13.5)
				MM = T - 13; 
		} 
		if (MM > 2.5) {
			AA = C - 4716 ;
		} else { 
			if (MM < 2.5) 
				AA = C - 4715;
		}

		_gd = JJ;
		_gm = MM;
		_gy = AA;
	}

	void tell_day()
	{
		string weekday[] = {"dimanche", "lundi", "mardi", "mercredi", "jeudi", "vendredi", "samedi"};
		string hijri_month[] = {"Moharam", "Safar", "Rabii I", "Rabii II", "Joumada I", "Joumada II", "Rajab", "Chaaban", "Ramadan", "Chawal", "Dou al Qiida", "Dou al Hijaa"};
		string gregorien_month[] = {"Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet","Aout","Septembre","Novembre","Decembre"};

		cout << "=============== date converted with sucess ! ===============" << endl;
		cout << endl;
		cout << weekday[_day_week] << " " << _hd << " " << hijri_month[(int)_hm-1] << " " << _hy << endl;
		cout << weekday[_day_week] << " " << _gd << " " << gregorien_month[(int)_gm-1] << " " << _gy << endl;
		cout << endl;
		cout << "============================================================" << endl;
	}

	double _gd,_gm,_gy;
	double _hd,_hm,_hy;
	double _julien_day;
	double _days;
	int _day_week = 5;

};

int main()
{
	cout << "======================= date converter =====================" << endl;
	cout << "enter the date you want to convert preceeded by it type" << endl;
	cout << "h for hegire and g for gregorien." << endl;
	cout << "example --> g 25-11-2005 or h 5-7-1425" << endl;
	cout << "============================================================" << endl;

	while (1) {
		int d,m,y;
		char type;
		scanf("%c %d-%d-%d", &type , &d, &m, &y);
		Date date(type,d,m,y);
		date.tell_day();
	}
}