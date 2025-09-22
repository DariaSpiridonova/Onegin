#ifndef MY_STR_FUNCTIONS
#define MY_STR_FUNCTIONS
#include <stdio.h>

char *my_strdup(const char *str1);
size_t my_strlen(const char *str);
char *my_strcpy(char *dest, const char *src);
char *my_strncpy(char *dest, const char *src, size_t count);
int my_strcmp_from_the_begining(const char *str1, const char *str2);
int my_strcmp_from_the_end(const char *str1, const char *str2);
int my_strcmp_in_order(const char *str1, const char *str2);

#endif