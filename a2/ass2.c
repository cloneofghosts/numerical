#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void floatConversion();

int main() {
	int choice = 0;

	while (choice != 2) {
		printf("1 = convert a float\n2 - quit\n");
		scanf("%d", &choice);
		printf("\n");

		if (choice == 1)
			floatConversion();
	}


	return 0;
}

void floatConversion(){
	float convertedFloat;
	char *ptr;

	printf("Please enter the number to convert: ");
	scanf("%f", &convertedFloat);
	printf("\nfloat number is\t\t%.6e\n", convertedFloat);

	ptr = (char*)&convertedFloat;

	printf("Binary:\t\t\t");
	convertToBinary(convertedFloat);

	for (int i = 3; i >= 0; i--) {
		if (i < 3) printf(" ");
		for (int j = 7; j >= 0; j--) {
			if (j == 3) printf(" ");
			printf("%d", (ptr[i] >> j) & 0x01);
		}
	}

	printf("\nBig-Endian Hex:\t\t");

	for (int i = 3; i >= 0; i--) {
		if (i < 3) printf(" ");
		printf("%02X", (unsigned char)ptr[i]);
	}

	printf("\nLittle-Endian Hex:\t");

	for (int i = 0; i < 4; i++) {
		if (i > 0) printf(" ");
		printf("%02X", (unsigned char)ptr[i]);
	}

	printf("\nexponent = %d", 0);
	printf("\nNormalized mantissa (including the hidden bit)  = 1.%d", (ptr[3] & 0x07));

	printf("\n\n");

	printf("\n");
}
