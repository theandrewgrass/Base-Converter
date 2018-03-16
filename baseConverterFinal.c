/****************************************************************************************
 *	Title: 	Base Converter								*
 *	Author:	Andrew Grass								*
 *	Date:	March 16, 2018								*
 *											*
 *	Description:									*
 *		Takes in user number of a specified base and converts it to		*
 *		a base of the user's choice. To convert from non-base10 to		*
 *		non-base10, it converts the number to base10 as an intermediate		*
 *		step, and continues to transform it to the target base. Takes in	*	
 *		only integer type numbers.						*
 *											*
 ****************************************************************************************/

#include <stdio.h>
#include <math.h>

void numToTen(int, int *, int *); // takes the user's number and converts to base 10
void baseTenToTarget(int, int); // takes number of base 10 (original/intermediate) and converts to target base
void printStars(); // make things look nice **sparkle sparkle**

int main() {

	int userNum, numAsBaseTen, numBase, targetBase;
	int finished = 0;

	printf("Enter the number: ");
	scanf("%d", &userNum);
	numAsBaseTen = userNum; // if number is not in base 10 (declared by user), this will change in numToTen()

	printf("Enter the number's current base: ");
	scanf("%d", &numBase);

	printf("Enter the number's target base: ");
	scanf("%d", &targetBase);

	printStars();
	while (finished == 0) {
		if (numBase == 10) {
			printf("convert to desired base...\n");
			baseTenToTarget(numAsBaseTen, targetBase);

			finished = 1;

		} else {
			printf("convert to base 10...\n");
			numToTen(userNum, &numBase, &numAsBaseTen);

			if (targetBase == 10) { // do not proceed to next step if the user wanted to convert to base 10
				finished = 1;

			}
		}
	}

	printf("transformation complete. exiting program...\n");

	return 0;

}

void printStars() {

	int i;

	printf("\n");

	for (i = 0; i < 25; i ++) {
		printf("*");
	}

	printf("\n\n");

}

void numToTen(int userNum, int *numBase, int *baseTen) {

	int i, numDigs, numCarry = 0; // numCarry holds the new variable through each iteration
	int numAsArray[20];
	int tmpNum = userNum; // temporary variable to manipulate to retain original variable

	numDigs = log10(userNum) + 1;

	for (i = 0; i < numDigs; i++) { // store the individual digits of the number
		numAsArray[i] = tmpNum % 10;
		tmpNum /= 10;
	}

	for (i = numDigs - 1; i >= 0; i--) { // perform calculations on incrementing number of digits from original number
		printf("%-10db%d\t-->%d\t+ %d x %-5d\t= ", userNum / (int)pow(10,i), *numBase, numAsArray[i], *numBase, numCarry);
		numCarry = (numCarry * *numBase) + numAsArray[i]; // carry the result to the next iteration
		printf("%d\n", numCarry);
	}

	*baseTen = numCarry; // the final result is the last result of the loop above
	*numBase = 10; 

	printf("\n");
	printf("num as base 10: %d\n", *baseTen);

	printStars();

}

void baseTenToTarget(int userNum, int userBase) {

	int tmpNum = userNum; // intermediate variable to hold the original number
	int answer[25];
	int i, numTimes = 0;

	while (userNum != 0) { // perform calculations below until the result is 0, keep track of times run
		userNum /= userBase;
		printf("div: %d\n", userNum);

		answer[numTimes] = tmpNum % userBase;
		printf("mod: %d\n", answer[numTimes]);

		tmpNum /= userBase;
		numTimes += 1;
	}
	
	printf("\n");
	printf("num in base %d: ", userBase);
	for (i = numTimes - 1; i >= 0; i--) { // output the answer from the array
		printf("%d", answer[i]);
	}
	printf("\n");

	printStars();

}
