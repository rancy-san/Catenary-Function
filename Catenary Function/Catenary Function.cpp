
#define _USE_MATH_DEFINES
#include <iostream>
#include <iomanip>
#include <math.h>

using namespace std;
double range(double, double);
double series(int, double, int);
double exact(int, double, int);
double exacterror(double, double);
double truncerror(int, double, int);

int main(void) {

	int powerOfX;
	double minRange;
	double maxRange;
	int scale;
	double x;
	/* series */
	double fx;
	/* exact series */
	double gx;
	/* exact error */
	double ee;
	/* double truncation error */
	double te;

	int selection;

	do {
		do {
			cout << "**********************************" << endl;
			cout << "\t Catenary Series" << endl;
			cout << "1. Evalute the function" << endl;
			cout << "2. Quit" << endl;
			cout << "**********************************" << endl;
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cin >> selection;
			cout << endl;
		} while (selection != 2 && selection != 1 || cin.fail());
		

		if (selection == 2)
			break;

		cout << "EVALUATING THE CATENARY SERIES APPROXIMATION" << endl;
		
		do {
			cout << "Please enter the highest power of X in the catenary series (0,2,4,6,8, or 10): ";
			
			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cin >> powerOfX;
			cout << endl;
		} while ((powerOfX < 0 || powerOfX > 10) || (powerOfX % 2) != 0);

		cout << "CHOOSE THE RANGE OF EVALUATION - low x to high x" << endl;
		
		do {
			cout << "Please enter low x - in the range -10.0 to 0.0: ";

			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cin >> minRange;
			cout << endl;
		} while (minRange > 0.0 || minRange < -10.0);

		do {
			cout << "Please enter high x - in the range 0.0 to +10.0: ";

			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cin >> maxRange;
			cout << endl;
		} while (maxRange < 0.0 || maxRange > 10.0);
		
		do {
			cout << "Please enter the scale factor the range 0.0 to +10.0: ";

			if (cin.fail()) {
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
			}
			cin >> scale;
			cout << endl;
		} while (scale < -2.0 || scale > 2.0);
		
		cout << "CATENARY SERIES TO x^8 from x = " << setprecision(6) << fixed << minRange << " to x = " << setprecision(6) << fixed << maxRange << endl;
		cout << "x\t\tSeries\t\tExact\t\tExact % Error\tTrunc. % Error" << endl;

		x = minRange;
		fx = series(powerOfX, x, scale);
		gx = exact(powerOfX, x, scale);
		ee = exacterror(fx, gx);
		te = 100 * truncerror(powerOfX+1, x, scale) / fx;

		cout << setprecision(3) << scientific  << x;
		cout << "\t";
		cout << setprecision(5) << scientific << fx;
		cout << "\t";
		cout << setprecision(5) << scientific << gx;
		cout << "\t";
		cout << setprecision(5) << scientific << ee;
		cout << "\t";
		cout << setprecision(5) << scientific << te;
		cout << endl;

		for (int i = 0; i < 10; i++) {
			x += range(minRange, maxRange);

			fx = series(powerOfX, x, scale);
			gx = exact(powerOfX, x, scale);
			ee = exacterror(fx, gx);
			te = 100 * truncerror(powerOfX + 1, x, scale) / fx;

			cout << setprecision(3) << scientific << x;
			cout << "\t";
			cout << setprecision(5) << scientific << fx;
			cout << "\t";
			cout << setprecision(5) << scientific << gx;
			cout << "\t";
			cout << setprecision(5) << scientific << ee;
			cout << "\t";
			cout << setprecision(5) << scientific << te;
			cout << endl;
		}

	} while (selection != 2);


	return 0;
}

/******************
Function name: range
Purpose: Calculate range in equivalent distance between each x
Function In parameters: minRange is the minimum range the user picks, and that the range starts at
						maxRange is the end range picked by the user
Function Out parameters: x is the distance between each x from minRange to maxRange
Version: 1.1
******************/
double range(double minRange, double maxRange) {
	double x;
	double min = minRange;
	double max = maxRange;
	if (min < 0) {
		min *= -1;
	}
	x = (min + max) / 10;
	
	return x;
}
/******************
Function name: series
Purpose: calculate the series and the maclaurin series using an approximate of the euler constant
Function In parameters: powerOfX is the exponent number
						range is the evaluated term for x
						scale is the a value of the catenary function
Function Out parameters: series is the series of the catenary function at n
Version: 3.1
******************/
double series(int powerOfX, double range, int scale) {
	/* Euler's Constant */
	double const e = 2.71828;
	double series[12];
	/* exponent */
	int n = powerOfX;
	/* X value */
	double x = range;
	/* Scale */
	double a = (double)scale;

	series[0] = a*((1)+(1)) / 2;
	series[1] = a*((1 + x / a)+(1 - x / a)) / 2;
	series[2] = a*((1 + x / a + (x * x) / (2 * (a*a)))+(1 - x / a + (x*x) / (2 * (a*a)))) / 2;
	series[3] = a*((1 + x / a + (x * x) / (2 * (a*a)) + (x*x*x) / (6*(a*a*a)))+(1 - x / a + (x*x) / (2 * (a*a)) - (x*x*x) / (6 * (a*a*a)))) / 2;
	series[4] = a*((1 + x / a + (x * x) / (2 * (a*a)) + (x*x*x) / (6*(a*a*a)) + (x*x*x*x) / (24 *(a*a*a*a)))+(1 - x / a + (x*x) / (2 * (a*a)) - (x*x*x) / (6 * (a*a*a)) + (x*x*x*x) / (24 * (a*a*a*a)))) / 2;
	series[5] = a*((1 + x / a + (x * x) / (2 * (a*a)) + (x*x*x) / (6*(a*a*a)) + (x*x*x*x) / (24 *(a*a*a*a)) + (x*x*x*x*x) / (120 *(a*a*a*a*a)))+(1 - x / a + (x*x) / (2 * (a*a)) - (x*x*x) / (6 * (a*a*a)) + (x*x*x*x) / (24 * (a*a*a*a)) - (x*x*x*x*x) / (120 * (a*a*a*a*a)))) / 2;
	series[6] = a*((1 + x / a + (x * x) / (2 * (a*a)) + (x*x*x) / (6*(a*a*a)) + (x*x*x*x) / (24 *(a*a*a*a)) + (x*x*x*x*x) / (120 *(a*a*a*a*a)) + (x*x*x*x*x*x) / (720 *(a*a*a*a*a*a)))+(1 - x / a + (x*x) / (2 * (a*a)) - (x*x*x) / (6 * (a*a*a)) + (x*x*x*x) / (24 * (a*a*a*a)) - (x*x*x*x*x) / (120 * (a*a*a*a*a)) + (x*x*x*x*x*x) / (720 * (a*a*a*a*a*a)))) / 2;
	series[7] = a*((1 + x / a + (x * x) / (2 * (a*a)) + (x*x*x) / (6*(a*a*a)) + (x*x*x*x) / (24 *(a*a*a*a)) + (x*x*x*x*x) / (120 *(a*a*a*a*a)) + (x*x*x*x*x*x) / (720 *(a*a*a*a*a*a)) + (x*x*x*x*x*x*x) / (5040 *(a*a*a*a*a*a*a)))+(1 - x / a + (x*x) / (2 * (a*a)) - (x*x*x) / (6 * (a*a*a)) + (x*x*x*x) / (24 * (a*a*a*a)) - (x*x*x*x*x) / (120 * (a*a*a*a*a)) + (x*x*x*x*x*x) / (720 * (a*a*a*a*a*a)) - (x*x*x*x*x*x*x) / (5040 * (a*a*a*a*a*a*a)))) / 2;
	series[8] = a*((1 + x / a + (x * x) / (2 * (a*a)) + (x*x*x) / (6*(a*a*a)) + (x*x*x*x) / (24 *(a*a*a*a)) + (x*x*x*x*x) / (120 *(a*a*a*a*a)) + (x*x*x*x*x*x) / (720 *(a*a*a*a*a*a)) + (x*x*x*x*x*x*x) / (5040 *(a*a*a*a*a*a*a)) + (x*x*x*x*x*x*x*x) / (40320 *(a*a*a*a*a*a*a*a)))+(1 - x / a + (x*x) / (2 * (a*a)) - (x*x*x) / (6 * (a*a*a)) + (x*x*x*x) / (24 * (a*a*a*a)) - (x*x*x*x*x) / (120 * (a*a*a*a*a)) + (x*x*x*x*x*x) / (720 * (a*a*a*a*a*a)) - (x*x*x*x*x*x*x) / (5040 * (a*a*a*a*a*a*a)) + (x*x*x*x*x*x*x*x) / (40320 * (a*a*a*a*a*a*a*a)))) / 2;
	series[9] = a*((1 + x / a + (x * x) / (2 * (a*a)) + (x*x*x) / (6*(a*a*a)) + (x*x*x*x) / (24 *(a*a*a*a)) + (x*x*x*x*x) / (120 *(a*a*a*a*a)) + (x*x*x*x*x*x) / (720 *(a*a*a*a*a*a)) + (x*x*x*x*x*x*x) / (5040 *(a*a*a*a*a*a*a)) + (x*x*x*x*x*x*x*x) / (40320 *(a*a*a*a*a*a*a*a)) + (x*x*x*x*x*x*x*x*x) / (362880 *(a*a*a*a*a*a*a*a*a)))+(1 - x / a + (x*x) / (2 * (a*a)) - (x*x*x) / (6 * (a*a*a)) + (x*x*x*x) / (24 * (a*a*a*a)) - (x*x*x*x*x) / (120 * (a*a*a*a*a)) + (x*x*x*x*x*x) / (720 * (a*a*a*a*a*a)) - (x*x*x*x*x*x*x) / (5040 * (a*a*a*a*a*a*a)) + (x*x*x*x*x*x*x*x) / (40320 * (a*a*a*a*a*a*a*a)) - (x*x*x*x*x*x*x*x*x) / (362880 * (a*a*a*a*a*a*a*a*a)))) / 2;
	series[10] = a*((1 + x / a + (x * x) / (2 * (a*a)) + (x*x*x) / (6*(a*a*a)) + (x*x*x*x) / (24 *(a*a*a*a)) + (x*x*x*x*x) / (120 *(a*a*a*a*a)) + (x*x*x*x*x*x) / (720 *(a*a*a*a*a*a)) + (x*x*x*x*x*x*x) / (5040 *(a*a*a*a*a*a*a)) + (x*x*x*x*x*x*x*x) / (40320 *(a*a*a*a*a*a*a*a)) + (x*x*x*x*x*x*x*x*x) / (362880 *(a*a*a*a*a*a*a*a*a)) + (x*x*x*x*x*x*x*x*x*x) / (3628800 *(a*a*a*a*a*a*a*a*a*a)))+(1 - x / a + (x*x) / (2 * (a*a)) - (x*x*x) / (6 * (a*a*a)) + (x*x*x*x) / (24 * (a*a*a*a)) - (x*x*x*x*x) / (120 * (a*a*a*a*a)) + (x*x*x*x*x*x) / (720 * (a*a*a*a*a*a)) - (x*x*x*x*x*x*x) / (5040 * (a*a*a*a*a*a*a)) + (x*x*x*x*x*x*x*x) / (40320 * (a*a*a*a*a*a*a*a)) - (x*x*x*x*x*x*x*x*x) / (362880 * (a*a*a*a*a*a*a*a*a)) + (x*x*x*x*x*x*x*x*x*x) / (3628800 * (a*a*a*a*a*a*a*a*a*a))))/2;
	
	return series[n];
}

/******************
Function name: series
Purpose: calculate the series and the maclaurin series using the euler constant
Function In parameters: powerOfX is the exponent number
						range is the evaluated term for x
						scale is the a value of the catenary function
Function Out parameters: series is the series of the catenary function at n
Version: 1.1
******************/
double exact(int powerOfX, double range, int scale) {
	/* Euler's Constant */
	double const e = M_E;
	double series;
	/* exponent */
	int n = powerOfX;
	/* X value */
	double x = range;
	/* Scale */
	double a = (double)scale;

	//series[0] = (1)*(int_pow(e, (int)(range)) + int_pow(e, -1*(int)(range)) )/2;
	series = a*cosh(x / a);
	
	
	//series = a * (pow(e, x / a) + pow(e, -1 * (x) / a)) / 2;
	/*
	series[1] = a * (pow(e, x / a) - pow(e, -1 * (x) / a)) / (2 * pow(a, 1)*(1));
	series[2] = a * (pow(e, x / a) + pow(e, -1 * (x) / a)) / (2 * pow(a, 2)*(1 * 2));
	series[3] = a * (pow(e, x / a) - pow(e, -1 * (x) / a)) / (2 * pow(a, 3)*(1 * 2 * 3));
	series[4] = a * (pow(e, x / a) + pow(e, -1 * (x) / a)) / (2 * pow(a, 4)*(1 * 2 * 3 * 4));
	series[5] = a * (pow(e, x / a) - pow(e, -1 * (x) / a)) / (2 * pow(a, 5)*(1 * 2 * 3 * 4 * 5));
	series[6] = a * (pow(e, x / a) + pow(e, -1 * (x) / a)) / (2 * pow(a, 6)*(1 * 2 * 3 * 4 * 5 * 6));
	series[7] = a * (pow(e, x / a) - pow(e, -1 * (x) / a)) / (2 * pow(a, 7)*(1 * 2 * 3 * 4 * 5 * 6 * 7));
	series[8] = a * (pow(e, x / a) + pow(e, -1 * (x) / a)) / (2 * pow(a, 8)*(1 * 2 * 3 * 4 * 5 * 6 * 7 * 8));
	series[9] = a * (pow(e, x / a) - pow(e, -1 * (x) / a)) / (2 * pow(a, 9)*(1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9));
	series[10] = a * (pow(e, x / a) + pow(e, -1 * (x) / a)) / (2 * pow(a, 10)*(1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10));
	series[11] = a * (pow(e, x / a) - pow(e, -1 * (x) / a)) / (2 * pow(a, 11)*(1 * 2 * 3 * 4 * 5 * 6 * 7 * 8 * 9 * 10 * 11));
	*/
	/*
	series[0] = a*((1)+(1)) / 2;
	series[1] = a*((1 + x / a)+(1 - x / a)) / 2;
	series[2] = a*((1 + x / a + pow(x,2) / (2 * pow(a,2)))+(1 - x / a + pow(x,2) / (2 * pow(a,2)))) / 2;
	series[3] = a*((1 + x / a + pow(x,2) / (2 * pow(a,2)) + pow(x,3) / (6*pow(a,3)))+(1 - x / a + pow(x,2) / (2 * pow(a,2)) - pow(x,3) / (6 * pow(a,3)))) / 2;
	series[4] = a*((1 + x / a + pow(x,2) / (2 * pow(a,2)) + pow(x,3) / (6*pow(a,3)) + pow(x,4) / (24 *pow(a,4)))+(1 - x / a + pow(x,2) / (2 * pow(a,2)) - pow(x,3) / (6 * pow(a,3)) + pow(x,4) / (24 * pow(a,4)))) / 2;
	series[5] = a*((1 + x / a + pow(x,2) / (2 * pow(a,2)) + pow(x,3) / (6*pow(a,3)) + pow(x,4) / (24 *pow(a,4)) + pow(x,5) / (120 *pow(a,5)))+(1 - x / a + pow(x,2) / (2 * pow(a,2)) - pow(x,3) / (6 * pow(a,3)) + pow(x,4) / (24 * pow(a,4)) - pow(x,5) / (120 * pow(a,5)))) / 2;
	series[6] = a*((1 + x / a + pow(x,2) / (2 * pow(a,2)) + pow(x,3) / (6*pow(a,3)) + pow(x,4) / (24 *pow(a,4)) + pow(x,5) / (120 *pow(a,5)) + pow(x,6) / (720 *pow(a,6)))+(1 - x / a + pow(x,2) / (2 * pow(a,2)) - pow(x,3) / (6 * pow(a,3)) + pow(x,4) / (24 * pow(a,4)) - pow(x,5) / (120 * pow(a,5)) + pow(x,6) / (720 * pow(a,6)))) / 2;
	series[7] = a*((1 + x / a + pow(x,2) / (2 * pow(a,2)) + pow(x,3) / (6*pow(a,3)) + pow(x,4) / (24 *pow(a,4)) + pow(x,5) / (120 *pow(a,5)) + pow(x,6) / (720 *pow(a,6)) + pow(x,7) / (5040 *pow(a,7)))+(1 - x / a + pow(x,2) / (2 * pow(a,2)) - pow(x,3) / (6 * pow(a,3)) + pow(x,4) / (24 * pow(a,4)) - pow(x,5) / (120 * pow(a,5)) + pow(x,6) / (720 * pow(a,6)) - pow(x,7) / (5040 * pow(a,7)))) / 2;
	series[8] = a*((1 + x / a + pow(x,2) / (2 * pow(a,2)) + pow(x,3) / (6*pow(a,3)) + pow(x,4) / (24 *pow(a,4)) + pow(x,5) / (120 *pow(a,5)) + pow(x,6) / (720 *pow(a,6)) + pow(x,7) / (5040 *pow(a,7)) + pow(x,8) / (40320 *pow(a,8)))+(1 - x / a + pow(x,2) / (2 * pow(a,2)) - pow(x,3) / (6 * pow(a,3)) + pow(x,4) / (24 * pow(a,4)) - pow(x,5) / (120 * pow(a,5)) + pow(x,6) / (720 * pow(a,6)) - pow(x,7) / (5040 * pow(a,7)) + pow(x,8) / (40320 * pow(a,8)))) / 2;
	series[9] = a*((1 + x / a + pow(x,2) / (2 * pow(a,2)) + pow(x,3) / (6*pow(a,3)) + pow(x,4) / (24 *pow(a,4)) + pow(x,5) / (120 *pow(a,5)) + pow(x,6) / (720 *pow(a,6)) + pow(x,7) / (5040 *pow(a,7)) + pow(x,8) / (40320 *pow(a,8)) + pow(x,9) / (362880 *pow(a,9)))+(1 - x / a + pow(x,2) / (2 * pow(a,2)) - pow(x,3) / (6 * pow(a,3)) + pow(x,4) / (24 * pow(a,4)) - pow(x,5) / (120 * pow(a,5)) + pow(x,6) / (720 * pow(a,6)) - pow(x,7) / (5040 * pow(a,7)) + pow(x,8) / (40320 * pow(a,8)) - pow(x,9) / (362880 * pow(a,9)))) / 2;
	series[10] = a*((1 + x / a + pow(x,2) / (2 * pow(a,2)) + pow(x,3) / (6*pow(a,3)) + pow(x,4) / (24 *pow(a,4)) + pow(x,5) / (120 *pow(a,5)) + pow(x,6) / (720 *pow(a,6)) + pow(x,7) / (5040 *pow(a,7)) + pow(x,8) / (40320 *pow(a,8)) + pow(x,9) / (362880 *pow(a,9)) + pow(x,10) / (3628800 *pow(a,10)))+(1 - x / a + pow(x,2) / (2 * pow(a,2)) - pow(x,3) / (6 * pow(a,3)) + pow(x,4) / (24 * pow(a,4)) - pow(x,5) / (120 * pow(a,5)) + pow(x,6) / (720 * pow(a,6)) - pow(x,7) / (5040 * pow(a,7)) + pow(x,8) / (40320 * pow(a,8)) - pow(x,9) / (362880 * pow(a,9)) + pow(x,10) / (3628800 * pow(a,10))))/2;
	
	*/
	return series;
}

/******************
Function name: exacterror
Purpose: calculate the error of the series against the exact series
Function In parameters:  series is the value obtained form the series function
						exact is the value from the exact function
Function Out parameters: returns the error
Version: 1.0
******************/
double exacterror(double series, double exact) {
	return 100 * (exact - series) / exact;
}

/******************
Function name: truncerror
Purpose: calculate the error of the series through the truncation error (last maclaurin series)
Function In parameters: last truncation is the powerOfX
						range is the evaluation of the truncation
						scale is a of the catenary function
Function Out parameters: returns the truncation value
Version: 2.0
******************/
double truncerror(int powerOfX, double range, int scale) {
	/* Euler's Constant */
	double const e = 2.71828;
	double series[12];
	/* exponent */
	int n = powerOfX;
	/* X value */
	double x = range;
	/* Scale */
	double a = (double)scale;

	series[0] = a*((1)+(1)) / 2;
	series[0] = a*((x / a)+(x / a)) / 2;
	series[1] = a*(((x * x) / (2 * (a*a)))+((x*x) / (2 * (a*a)))) / 2;
	series[2] = a*(((x*x*x) / (6*(a*a*a)))+((x*x*x) / (6 * (a*a*a)))) / 2;
	series[3] = a*(((x*x*x*x) / (24 *(a*a*a*a)))+((x*x*x*x) / (24 * (a*a*a*a)))) / 2;
	series[4] = a*(((x*x*x*x*x) / (120 *(a*a*a*a*a)))+((x*x*x*x*x) / (120 * (a*a*a*a*a)))) / 2;
	series[5] = a*(((x*x*x*x*x*x) / (720 *(a*a*a*a*a*a)))+((x*x*x*x*x*x) / (720 * (a*a*a*a*a*a)))) / 2;
	series[6] = a*(((x*x*x*x*x*x*x) / (5040 *(a*a*a*a*a*a*a)))+((x*x*x*x*x*x*x) / (5040 * (a*a*a*a*a*a*a)))) / 2;
	series[7] = a*(((x*x*x*x*x*x*x*x) / (40320 *(a*a*a*a*a*a*a*a)))+((x*x*x*x*x*x*x*x) / (40320 * (a*a*a*a*a*a*a*a)))) / 2;
	series[8] = a*(((x*x*x*x*x*x*x*x*x) / (362880 *(a*a*a*a*a*a*a*a*a)))+((x*x*x*x*x*x*x*x*x) / (362880 * (a*a*a*a*a*a*a*a*a)))) / 2;
	series[9] = a*(((x*x*x*x*x*x*x*x*x*x) / (3628800 *(a*a*a*a*a*a*a*a*a*a)))+((x*x*x*x*x*x*x*x*x*x) / (3628800 * (a*a*a*a*a*a*a*a*a*a))))/2;
	series[10] = a*(((x*x*x*x*x*x*x*x*x*x*x) / (39916800 * (a*a*a*a*a*a*a*a*a*a*a))) + ((x*x*x*x*x*x*x*x*x*x*x) / (39916800 *(a*a*a*a*a*a*a*a*a*a*a))))/2;
	series[11] = a*(((x*x*x*x*x*x*x*x*x*x*x*x) / (479001600 *(a*a*a*a*a*a*a*a*a*a*a*a))) + ((x*x*x*x*x*x*x*x*x*x*x*x) / (479001600 *(a*a*a*a*a*a*a*a*a*a*a*a)))) / 2;

	return series[n];
}