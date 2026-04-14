#include<stdio.h>

int power(int x, int st){
	switch (st){
		case(0):
			return 1;
			break;
		default:
			return(x*power(x, st-1));
			break;
	}
}

int into_oct(int x){
	int  r= 0, k=0;
	while (x!=0){
		k += power(10, r)*(x%8);
		x /= 8;
		r ++;
	}
	return k;
}

int main(){
	printf("Enter number: ");
	int x;
	scanf("%d", &x);
	printf("Answer: %d\n", into_oct(x));
	return 0;
}
