#include <stdio.h>
#include <math.h>
#include <stdlib.h>


double row_function_2(double x, double e, long *q){
	double ans = x+1, y = x;
	long i = 1;
	while (fabs(y) > e)
	{
		if ((++i % 4) == 2)
		{
			y = -y * 2 * x / i;
			continue;
		}
		if (i % 2)
		{
			y = y * x / i;
		}
		else
		{
			y = y * 2 * x / i;
		}
		ans += y;
	}
	*q = i;
	return ans;
}


int main(){
	double x = 0, e = 0;
	long q;

	printf("Enter x: ");
	while(!scanf("%lf", &x))
	{
		scanf("%*[^\n]");
		printf("1\nEnter x: ");
	}
	printf("0\n");

	printf("Enter e: ");
	while(!scanf("%lf", &e))
	{
		scanf("%*[^\n]");
		printf("1\nEnter e: ");
	}
	printf("0\n");

	double s1 = exp(x)*cos(x);
	double s2 = row_function_2(x, e, &q); //where q -number of row members
	printf("s1: %lf\ns2: %lf\nnumber of row members: %li\n", s1, s2, q);
	return 0;
}
