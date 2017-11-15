/***************************************************************************************************
Filename:			ass1.cpp
Version:			1.0
Purpose:			To calculate a Maclaurin series of Oscillations up to 6 non-zero terms and
					4 seconds after the Oscillations start
**************************************************************************************************/

#include <math.h>
#include <iostream>
#include <iomanip>

//function declarations
void calculate(int, double);

using namespace std;

/***************************************************************************************************
Function name:		main
Purpose:			main function
					Menu for the Maclaurin Series
In parameters:		none
Out parameters:		0 for sucessful execution
Version:			1.0
***************************************************************************************************/
int main(void) {
	int choice = 0, nonZero = 0;
	bool running = true;
	double timeRange = 0.0;

	do {
		cout << "Evaluate the Maclaurin Series approximation to D(t) = exp(t)*cos(t)" << endl << endl;
		cout << "1: Evaluate the series" << endl;
		cout << "2: quit" << endl << endl;
		cin >> choice;

		if (choice == 1) {
			do {
				cout << endl << "Evaluating the series" << endl;
				cout << "Please enter the number of (non-zero) terms in the series (1, 2, 3, 4, 5 or 6):" << endl;
				cin >> nonZero;

				//check for valid input for the number of non-zero terms
				if (nonZero > 0 && nonZero < 7)
					break;
			} while (1);

			do {
				cout << endl << "Please enter the range of t to evaluate in 10 increments (0.0 < t < +4.0): ";
				cin >> timeRange;

				//check for valid input for the range to run the Maclaurin series
				if (timeRange > 0.0 && timeRange <= 4.0)
					break;
			} while (1);

			//calculate the Maclaurin series with number of non-zero terms and the range
			calculate(nonZero, timeRange);
		}
		else if (choice == 2)
			running = false;
	} while (running);

	return 0;
}

/***************************************************************************************************
Function name:		calculate
Purpose:			Calculates the Maclaurin series for e^t * cos(t)
In parameters:		number of non-zero terms, range that the function will be run
Out parameters:		none
Version:			1.0
***************************************************************************************************/
void calculate(int nonZero, double range) {
	double time = 0.0;
	double increment = range / 10;
	int i = 0;
	double exact = 1.0, series = 1.0, exactErr = 0.0, serErr = 0.0, truncTerm = 0.0;

	cout << endl << "MACLAURIN SERIES" << endl;
	cout << "  t\t\tD(t) Series\tD(t) Exact\t%RExactE\t%RSerE" << endl;
	//makes sure the numbers always print out as scientific numbers and always show the decimal point
	cout << setiosflags(ios::scientific | ios::showpoint);

	for (i = 0; i <= 10; i++) {
		//sets the decimal precision of cout to be 3
		cout.precision(3);
		cout << time << "\t";
		//sets the decimal precision of cout to be 5
		cout.precision(5);
		cout << series << "\t";
		cout << exact << "\t";
		cout << exactErr << "\t";
		cout << serErr << endl;

		time += increment;

		//calculates the series and the next term (the truncated term) if non-zero terms is one
		if (nonZero == 1) {
			series = 1;
			truncTerm = time;
		}
		//calculates the series and the next term (the truncated term) if non-zero terms is two
		else if (nonZero == 2) {
			series = 1 + time;
			truncTerm = -2 * ((time*time*time) / 6);
		}
		//calculates the series and the next term (the truncated term) if non-zero terms is three
		else if (nonZero == 3) {
			series = 1 + time - 2 * ((time*time*time) / 6);
			truncTerm = -4 * ((time*time*time*time) / 24);
		}
		//calculates the series and the next term (the truncated term) if non-zero terms is four
		else if (nonZero == 4) {
			series = 1 + time - 2 * ((time*time*time) / 6) - 4 * ((time*time*time*time) / 24);
			truncTerm = -4 * ((time*time*time*time*time) / 120);
		}
		//calculates the series and the next term (the truncated term) if non-zero terms is five
		else if (nonZero == 5) {
			series = 1 + time - 2 * ((time*time*time) / 6) - 4 * ((time*time*time*time) / 24) - 4 * ((time*time*time*time*time) / 120);
			truncTerm = 8 * ((time*time*time*time*time*time*time) / 5040);
		}
		//calculates the series and the next term (the truncated term) if non-zero terms is six
		else if (nonZero == 6) {
			series = 1 + time - 2 * ((time*time*time) / 6) - (4 * (time*time*time*time) / 24) - 4 * ((time*time*time*time*time) / 120)
				+ 8 * ((time*time*time*time*time*time*time) / 5040);
			truncTerm = 16 * (time*time*time*time*time*time*time*time) / 40320;
		}

		//e^t * cos(t) calculated using the math library
		exact = exp(time) * cos(time);
		//comparison of the Maclaurin series to the math library
		exactErr = 100 * (exact - series) / exact;
		//series error from first truncated term
		serErr = 100 * truncTerm / series;
	}

	cout << endl;

	return;
}