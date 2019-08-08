#include <iostream>
#include <cmath>

#include <stdlib.h>

using namespace std;

/*double around(double num)
{
	//debug
	//cout << "num  : " << num << endl;
	//cout << "num1  : " << floor(num) - num << endl;
	//cout << "num2  : " << ceil(num) - num << endl;
	if (num - floor(num)  > ceil(num) - num)
		return ceil(num);
	else
		return floor(num);
}*/

bool is_leap(int year)
{
	if (year % 4 == 0 && year % 100 == 0 && !year % 400 == 0)
		return true;
	if (year % 4 == 0 && !year % 100 == 0)
		return true;
	return false;
}

int month2days(int month, int year)
{
	if (month == 1)
		return 31;

	if (month == 2 && is_leap(year))
		return 29;
	else
		return 28;

	if (month == 3)
		return 31;
	if (month == 4)
		return 30;
	if (month == 5)
		return 31;
	if (month == 6)
		return 30;
	if (month == 7)
		return 31;
	if (month == 8)
		return 31;
	if (month == 9)
		return 30;
	if (month == 10)
		return 31;
	if (month == 11)
		return 30;
	if (month == 12)
		return 31;
}

int month2days_acc(int month, int year)
{
	int x;
	if (is_leap(year)) {
		x = 1;
	} else {
		x = 0;
	}
	if (month == 1)
		return 31;
	if (month == 2)
		return 59 + x;
	if (month == 3)
		return 90 + x;
	if (month == 4)
		return 120 + x;
	if (month == 5)
		return 151 + x;
	if (month == 6)
		return 181 + x;
	if (month == 7)
		return 212 + x;
	if (month == 8)
		return 243 + x;
	if (month == 9)
		return 273 + x;
	if (month == 10)
		return 304 + x;
	if (month == 11)
		return 334 + x;
	if (month == 12)
		return 365 + x;
}

int year2days(int year)
{
	int x,i = 1;

	
	int tmp = 0;
	while (i < year) {
		if (is_leap(i)) {
			x = 1;
		} else {
			x = 0;
		}
		//cout << i << " is leap " << (x == 1) << endl;
		tmp += 365 + x;
		i++;
	}
	return tmp;
}

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
	}

	int to_days()
	{
		//return year2days(_y) + month2days_acc(_gm-1, _y) + _d;
	}

	void tell_day()
	{
		string weekday[] = {"dimanche", "lundi", "mardi", "mercredi", "jeudi", "vendredi", "samedi"};
		string hijri_month[] = {"Moharam", "Safar", "Rabii I", "Rabii II", "Joumada I", "Joumada II", "Rajab", "Chaaban", "Ramadan", "Chawal", "Dou al Qiida", "Dou al Hijaa"};
		string gregorien_month[] = {"Janvier", "Fevrier", "Mars", "Avril", "Mai", "Juin", "Juillet","Aout","Septembre","Novembre","Decembre"};
/*		int day = _day;
		day += to_days();
		day = day % 7;*/
		//cout << weekday[day] << endl;
		cout << "=============== date converted with sucess ! ===============" << endl;
		cout << endl;
		cout << weekday[_day_week] << " " << _hd << " " << hijri_month[(int)_hm-1] << " " << _hy << endl;
		cout << weekday[_day_week] << " " << _gd << " " << gregorien_month[(int)_gm-1] << " " << _gy << endl;
		cout << endl;
		cout << "============================================================" << endl;
	}

/*	void calculate_absolute()
	{
		//_absolute = 365.25*_y + 30*_m + _d;
		_absolute = (_y-1) + ((_m)/12) + (_d/365.25);
		_days = round(_absolute *365.25);
	}

	void display_absolute()
	{
		double tmp = _absolute;
		while (tmp > 1) {
			tmp -= 1;
		}
		double tmp2 = tmp *365.25;
		while (tmp2 > 30.4375) {
			tmp2 -= 30.4375;
		}

		cout << (int)_absolute << " / " << round((tmp*12)) << " / " << round(tmp2) << endl;
		cout << (int)_absolute << " / " << (tmp*12) << " / " << tmp2 << endl;
		_day = _day + _days;
		_day = _day % 7;
		cout << _day << endl;
		cout << _days << endl;
	}*/

	//grégorien vars
	double _gd,_gm,_gy;
	//hijri vars
	double _hd,_hm,_hy;
	double _julien_day;
	double _days;
	int _day_week = 5;

};

int main()
{
	Date d('h',8,8,2019);
	cout << d.to_days() << endl;
	//cout << year2days(d._y) << endl;
	d.tell_day();

	//double YY=d._y,MM=d._m,DD=d._d,JS;

/*//gregojulien en julien
	double GGG = 1;
	if( YY < 1582 )
		GGG = 0;
	if( YY <= 1582 && MM < 10 )
		GGG = 0;
	if( YY <= 1582 && MM == 10 && DD < 5 )
		GGG = 0;
	double JD = -1 * floor(7 * (floor((MM + 9) / 12) + YY) / 4);
	double S = 1;
	if ((MM - 9)<0)
		S=-1;
	double A = abs(MM - 9);
	double J1 = floor(YY + S * floor(A / 7));
	J1 = -1 * floor((floor(J1 / 100) + 1) * 3 / 4);
	JD = JD + floor(275 * MM / 9) + DD + (GGG * J1);
	JD = JD + 1721027 + 2 * GGG + 367 * YY - 0.5;
	double K1 = (JD + 1.5);
	double K2 = (K1/7);
	double K3 = K2 - floor(K2);
	JS = round(K3*7 + 0.000000000317);
	cout << DD << " " << MM << " " << YY << endl;

//julien en hijri
	//JD = "" ???
	double Z = (JD + 0.5);
	double AH = floor((Z * 30 - 58442554)/10631);
	double R2 = Z - floor((AH * 10631 + 58442583)/30);
	double M = floor((R2 * 11 + 330)/325);
	double R1 = R2 - floor((M * 325 - 320)/11);
	double J = R1 +1;
	cout << J << " " << M << " " << AH << endl;*/
	cout << d._hy << " " << endl;
	cout << d._day_week << " " << endl;

//hijri en julien
/*	KH1 = floor((YYH * 10631 + 58442583)/30);
	KH2 = floor((MMH * 325 - 320)/11);
	KH3 = DDH - 1;
	JDH = KH1 + KH2 + KH3;
	KHS1 = (JDH + 1.5);
	KHS2 = (KHS1/7);
	KHS3 = KHS2 - floor(KHS2);
	JSH = round(KHS3*7 + 0.000000000317) - 1;*/
	//cout << J << " " << M << " " << AH << endl;

//juline en grego julien
/*	double Z = floor(JDH+0.5);
	double F = JDH+0.5 - Z;
	double A,MM,AA;
	if (Z < 2299161) {
		A = Z
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
		AA = C - 4716 
	} else { 
		if (MM < 2.5) 
			AA = C - 4715;
	}*/

/*	
cout << d._absolute << endl;
	d.display_absolute();

	d._y = 20;
	d.calculate_absolute();
	d._absolute -= 0.0833333333333;
	cout << d._absolute << endl;
	d.display_absolute();
*/
	system("pause");
}

//12.36874634
//365.242190
