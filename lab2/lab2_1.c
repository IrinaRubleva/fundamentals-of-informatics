#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double row_function_1(double x, int n){
	double ans = 1, a = 1, pow_2 = pow(2, 0.5);
	for (int i = 1; i <= n; i++){
		a *= (pow_2* x)/i;
		ans += a*cos((M_PI*i)/4);
	}
	return ans;
}

int main(){
	double x = 0;
	int n = 0;
	while(1)
	{
		printf("Enter x: ");
		if(!scanf("%lf", &x)){
			printf("1\n");
			exit(1);}
		else{
			printf("0\n");}
		break;
	}

	while(1)
	{
		printf("Enter n: ");
		if(!scanf("%d", &n)){
			printf("1\n");
			exit(1);}
		else{
			printf("0\n");
			break;}
	}
	double s1 = exp(x)*cos(x);
	double s2 = row_function_1(x, n);
	printf("s1: %lf\ns2: %lf\n", s1, s2);
	return 0;
}



