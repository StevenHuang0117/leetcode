#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef unsigned int	u32;

#define RESULT_SUCCESS		0
#define RESULT_INVALID		-1

int CalcNumberOfOne(u32 Period, u32 Value)
{
	u32 Multiple;
	u32 Mod;
	int Num_Of_1;
	
	if ((Period == 0) || (Period > 0x80000000)) {
		return RESULT_INVALID;
	}

	Multiple = Value / Period;
	Mod = Value & (Period - 1);

	Num_Of_1 = (Period >> 1) * Multiple;
	if (Mod >= (Period >> 1)) {
		Num_Of_1 = Num_Of_1 + (Mod - (Period >> 1) + 1);
	}

	return Num_Of_1;
}

int main(void)
{
	u32 a, b;
	int Num_of_1;
	int Bit_NumOf1[64];
	int bitCarryNum;
	int sumCarryNum;
	int i;

	while (scanf("%u%u", &a, &b) == 2) {
		memset(Bit_NumOf1, 0, sizeof(Bit_NumOf1));
		for (i = 0; i < 32; i++) {
			Bit_NumOf1[i] = CalcNumberOfOne(1 << (i + 1), b) -
					CalcNumberOfOne(1 << (i + 1), a);
		}

		sumCarryNum = 0;
		for (i = 0; i < 64; i++) {
			bitCarryNum = Bit_NumOf1[i] >> 1;
			Bit_NumOf1[i] = Bit_NumOf1[i] & 0x01;
			Bit_NumOf1[i + 1] += bitCarryNum;
			sumCarryNum += bitCarryNum;
		}
		printf("a=%u, b=%u, Carry Number=%d \n", a, b, sumCarryNum);
	}

	return 0;
}

