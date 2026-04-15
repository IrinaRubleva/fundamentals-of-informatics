#include <stdio.h>
#include <string.h>
struct Avto{
	char mark[16];
	char fio[100];
	double mileage;
};



int main(){
	struct Avto car1 = {"Toyota", "Ivanov I.I.", 12345.6};
	struct Avto car2 = {"Honda", "Petrov P.P.", 67890.1};

	FILE *file = fopen("file.bin", "wb");
	fwrite(&car1, sizeof(struct Avto), 1, file);
	fwrite(&car2, sizeof(struct Avto), 1, file);
	fclose(file);
	return 0;
}
