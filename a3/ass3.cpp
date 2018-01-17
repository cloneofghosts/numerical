/***************************************************************************************************
Filename:			ass3.cpp
Version:			1.0
**************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//function prototypes
void calculate(float*, float*, string);

/***************************************************************************************************
Function name:		main
Purpose:		main function
			Menu for the earthquake simulation
In parameters:		none
Out parameters:		0 for sucessful execution
Version:		1.0
***************************************************************************************************/
int main(void) {
	//local variables
	bool running = true;
	int choice;
	string fileName;
	fstream file;
	float time[218];
	float ground_movement[218];
	int rows = 0;

	//loop while the user wants to run the simulation
	while (running) {
		//main menu
		cout << "1. run the simulation" << endl;
		cout << "2. Quit" << endl;
		cin >> choice;

		if (choice == 1) {
			cout << "Please enter the name of the earthquake file to open : ";
			cin >> fileName;

			//opens the file with the earthquake data
			file.open(fileName, fstream::in);

			/* the first number in the data is read to the time and the second to the ground movement
			   contines reading the file until there is no more data in the file */
			while (file >> time[rows] >> ground_movement[rows]) {
				//increments the number of rows
				rows++;
			}

			//closes the file
			file.close();

			cout << "File Opened; " << rows << " rows of data" << endl;
			//promts the user for a file to save the simulation data to
			cout << "OPEN FILE TO SAVE" << endl;
			cout << "Please enter the name of the file to open: ";
			cin >> fileName;

			//calulcates the data
			calculate(time, ground_movement, fileName);

			cout << endl << "Earthquake Simulation" << endl;
		}
		else if (choice == 2)
			running = false;
	}
}

/***************************************************************************************************
Function name:		calculate
Purpose:		Calculates acceleration, building movement, and velocity based on the earthquake data
			Outputs the results to a file
In parameters:		time, ground_movement, name of the file
Out parameters:		none
Version:		1.0
***************************************************************************************************/
void calculate(float* time, float* movement, string fileName) {
	//local variables
	fstream file;
	float acceleration[218];
	float building_movement[218];
	float velocity[218];
	const float k = 20.0f;
	const float b = 10.0f;
	float delta_time = 0;
	float g;

	//set the first ones to be zero
	acceleration[0] = 0.0f;
	building_movement[0] = 0;
	velocity[0] = 0;

	//open the file to write to
	file.open(fileName, fstream::out);

	file << time[0] << "," << movement[0] << "," << acceleration[0] << "," << building_movement[0] << "," << velocity[0] << endl;

	//loop for the number of rows of data
	for (int i = 1; i < 218; ++i) {
		//change in time
		delta_time = time[i] - time[i - 1];
		
		//acceleration calculation
		acceleration[i] = ((movement[i + 1] - (movement[i] *2) + movement[i - 1]) / 100) / (delta_time * delta_time);

		//velocity calculation
		g = acceleration[i - 1] - (k*building_movement[i - 1]) - (b*velocity[i - 1]);
		velocity[i] = velocity[i - 1] + (g * delta_time);

		//building_movement calculation
		building_movement[i] = building_movement[i - 1] + (((velocity[i - 1] + velocity[i]) / 2) * delta_time);

		//output to file
		file << time[i] << "," << movement[i] << "," << acceleration[i] << "," << building_movement[i] << "," << velocity[i] << endl;
	}

	//closes the file
	file.close();
}
