/***************************************************************************************************
Filename:			ass2.c
Version:			1.0
**************************************************************************************************/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void floatConversion();

/***************************************************************************************************
Function name:		main
Purpose:		main function
			Menu for the floating point inspector
In parameters:		none
Out parameters:		0 for sucessful execution
Version:		1.0
***************************************************************************************************/
int main() {
	int choice = 0;

	//main menu of the program, keeps looping while 2 is not input
	while (choice != 2) {
		printf("1 = convert a float\n2 - quit\n");
		scanf("%d", &choice);
		printf("\n");

		//converts the float if 1 is input
		if (choice == 1)
			floatConversion();
	}
	return 0;
}

/***************************************************************************************************
Function name:		floatConversion
Purpose:		Converts the float into binary
			Prints out the bits in Little-Endian or Big-Endian hex
			Gets and prints the exponent and mantissa of the float
In parameters:		none
Out parameters:		none
Version:		1.0
***************************************************************************************************/
void floatConversion() {
	//local variable declarations
	float convertedFloat;
	char *ptr;
	int *dec;
	unsigned int decimal;
	float sum = 1.0f;

	printf("Please enter the number to convert: ");
	scanf("%f", &convertedFloat);
	printf("\nfloat number is\t\t%.6e\n", convertedFloat);
	printf("Binary:\t\t\t");

	//convert the float to be a char* so that you can access the bits of the float
	ptr = (char*)&convertedFloat;
	//convert the float to a int* to get the values of the exponent and mantissa
	dec = (int*)&convertedFloat;

	//loop through each eight bit section of the float
	for (int i = 3; i >= 0; i--) {
		if (i < 3) printf(" ");
		//loops through each eight bit section bit by bit
		for (int j = 7; j >= 0; j--) {
			if (j == 3) printf(" ");
			//right shift the ptr by j, and using a bitmask of 1 to get the bit at j
			printf("%d", (ptr[i] >> j) & 0x01);
		}
	}

	printf("\nBig-Endian Hex:\t\t");

	//loops through the float and prints out the big-endian hex
	for (int i = 3; i >= 0; i--) {
		if (i < 3) printf(" ");
		//for every eight bits in the float convert it to hex
		printf("%02X", (unsigned char)ptr[i]);
	}

	printf("\nLittle-Endian Hex:\t");

	//loops through the float and prints out the little-endian hex
	for (int i = 0; i < 4; i++) {
		if (i > 0) printf(" ");
		//for every eight bits in the float convert it to hex
		printf("%02X", (unsigned char)ptr[i]);
	}

	//using a bitmask and a right shift of 23 to get the exponent
	decimal = (*dec & 0x7f800000) >> 23;

	printf("\nexponent = %d", decimal);

	//loops through the mantissa bit by bit to get the decimal value of the mantissa
	for (int i = 22; i >= 0; i--) {
		float currValue;
		//gets the mantissa of the floating point number
		decimal = *dec & 0x007FFFFF;
		//uses a right shift and a bitmask of 1 to get the current bit of the mantissa
		decimal = (decimal >> i) & 0x01;

		//converts the int value to a float
		currValue = (float)decimal;

		//gets the decimal value by subtracting 23 from the current position in the mantissa
		for (int j = 23 - i; j > 0; j--) {
			//multiplies the current value by 2^-1 to get the decimal value
			currValue *= 0.5;
		}
		//adds the value to the value of the mantissa
		sum += currValue;
	}

	//prints out the mantissa
	printf("\nNormalized mantissa (including the hidden bit)  = %0.7f", sum);

	printf("\n\n\n");
}
