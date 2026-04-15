#ifndef MY_STRING
#define MY_STRING

#include <stddef.h>

char my_strlen(const char *str);
char my_strcmp(const char *str1, const char *str2);
char *my_strcat(char *res, const char *str);
char *my_strdup(const char *res);
char *my_strtok(char *str, char *delim);
char *my_readline();


#endif
