#include <stdio.h>
#include <assert.h>
#include "my_string_functions.h"
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>

char *my_strdup(const char *str1)
{
    size_t n = (my_strlen(str1) + 1)*sizeof(char); 
    char *str_copy = (char *)malloc(n);

    my_strcpy(str_copy, str1);

    return str_copy;
}

size_t my_strlen(const char *str)
{
    assert(str != NULL);

    size_t length = 0;
    while (*str++ != '\0')
        length++;

    return length;
}

char *my_strcpy(char *dest, const char *src)
{
    return my_strncpy(dest, src, __SIZE_MAX__);
}

char *my_strncpy(char *dest, const char *src, size_t count)
{
    assert(dest != NULL && src != NULL);

    size_t i = 0;
    while (i < count && src[i] != '\0')
    {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';

    return dest;
}

int my_strcmp_from_the_begining(const char *str1, const char *str2)
{
    assert(str1 != NULL);
    assert(str2 != NULL);

    const char *str1_copy = str1;
    const char *str2_copy = str2;

    int difference = 0;

    while (*str1_copy != '\0' && *str2_copy != '\0')
    {
        if (!isalpha(*str1_copy)) 
        {
            str1_copy++;
            continue;
        }
        if (!isalpha(*str2_copy)) 
        {
            str2_copy++;
            continue;
        }
        
        if (tolower(*str1_copy) == tolower(*str2_copy)) 
        {
            str1_copy++;
            str2_copy++;
            continue;
        }
        
        if (tolower(*str1_copy) > tolower(*str2_copy)) difference = 1;
        else difference = -1;
        return difference;
    }

    if (*str1_copy == '\0') return -1;
    if (*str2_copy == '\0') return 1;
    return 0;
}

int my_strcmp_from_the_end(const char *str1, const char *str2)
{
    assert(str1 != NULL);
    assert(str2 != NULL);


    size_t len1 = strlen(str1) - 1;
    size_t len2 = strlen(str2) - 1;

    while (len1 != 0 && len2 != 0)
    {
        if (!isalpha(str1[len1])) 
        {
            len1--;
            continue;
        }

        if (!isalpha(str2[len2])) 
        {
            len2--;
            continue;
        }
        
        if (tolower(str1[len1]) == tolower(str2[len2])) 
        {
            len1--;
            len2--;
            continue;
        }
        
        return (tolower(str1[len1]) > tolower(str2[len2])) ? 1 : -1;
    }

    if (len1 == 0) return -1;
    if (len2 == 0) return 1;
    return 0;
}

int my_strcmp_in_order(const char *str1, const char *str2)
{
    assert(str1 != NULL);
    assert(str2 != NULL);

    if (str1 > str2) return 1;
    else if (str2 < str1) return -1;
    return 0;
}