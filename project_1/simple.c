#include <stdio.h>
#include <math.h>

int main() {

double array[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
double sqrtcounter = 0;
int i;
double place = 0;

for (i=0; i < 10; i++) {
place = sqrtcounter;
sqrtcounter = place + sqrt(array[i]);

//printf("current sqrt = %f \n", sqrtcounter);
}

double average = sqrtcounter / 10;



printf("The average of the sqrts is = %f \n", average);
return 0;
}

