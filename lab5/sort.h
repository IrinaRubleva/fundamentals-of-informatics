#ifndef SORT_H
#define SORT_H


struct Avto{
	char mark[16];
	char fio[100];
	double mileage;
};

void sort(struct Avto *cars, int n, char *type_sort, char *field_sort, char *direction_sort);


#endif
