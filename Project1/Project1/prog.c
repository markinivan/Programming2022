#include<stdio.h>
int SearchExtr(int* mass, int size) {
	int max = mass[0];
	int min = mass[0];
	printf("%d\n", mass[3]);
	printf("max %d\n", max);
	printf("min %d\n", min);
	for (int i = 0; i < size; i++) {
		if (mass[i] > max) {
			max = mass[i];
			printf("max %d %d %d\n", i, max, mass[i]);
		}
		else if (mass[i] < min) {
			min = mass[i];
			printf("min %d %d %d\n", i, min, mass[i]);
		}
	}
	for (int j = 0; j < size; j++) {
		if (mass[j] == min || mass[j] == max) {
			return j;
	   }
	}
}
int main() {
	int* ma[10] = {3,2,1,11,24,3,11,24,1,13};
	int s = 10;
	printf("%d\n\n", SearchExtr(ma, s));
	for (int z = 2; z < s; z++) {
		printf(ma[z]);
	}
}