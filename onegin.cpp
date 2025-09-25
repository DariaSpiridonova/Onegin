#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>
#include "my_string_functions.h"
#include "onegin.h"

int open_files_success(FILE *read_strings, FILE *sorted_strings)
{
    if (read_strings == NULL)
    {
        printf("Произошла ошибка при открытии файла \"original_strings.txt\"");
        return 0;
    }
    if (sorted_strings == NULL)
    {
        printf("Произошла ошибка при открытии файла \"sorted_strings.txt\"");
        return 0;
    }
    return 1;
}

size_t return_num_of_bytes_in_file(FILE *fp)
{
    if (fp == NULL)
        return 0;
    fseek(fp, 0, SEEK_END);
    size_t i = (size_t)ftell(fp);
    fseek(fp, 0, SEEK_SET);
    return i;
}

size_t return_num_of_bytes_in_file1(int fd1)
{
    struct stat st1 = {};
    fstat(fd1, &st1);

    return (size_t)st1.st_size;
}

struct data_of_buffer read_to_buffer_from_file(FILE *read_strings)
{
    assert(read_strings != NULL);

    struct data_of_buffer data = {0, 0};

    size_t num_of_bytes_in_file = return_num_of_bytes_in_file1(fileno(read_strings));

    // printf("%d\n", num_of_bytes_in_file); // проверка количества символов в файле

    char *buffer = (char *)calloc(num_of_bytes_in_file + 1, sizeof(char));
    if (buffer == NULL)
        return {0, 0};

    size_t num_success_read_symbols = fread(buffer, sizeof(char), num_of_bytes_in_file, read_strings);
    if (num_success_read_symbols < num_of_bytes_in_file)
        return {0, 0};

    // printf("%d\n", num_success_read_symbols); // проверка количества успешно прочитанных в буфер символов

    buffer[num_success_read_symbols] = '\0';
    // printf("%s\n", buffer); // проверка содержимого буфера

    data.num_of_bytes_in_file = num_of_bytes_in_file;
    data.buffer = buffer;

    return data;
}

size_t return_num_of_strings_in_file(char *buffer)
{
    assert(buffer != NULL);
    size_t num = 1;
    char *point_on_new_row = NULL;
    for (; (point_on_new_row = strchr(buffer, '\n')) != NULL; num++)
    {
        buffer = point_on_new_row + 1;
    }
    return num;
}

void add_pointers_on_strings(char *buffer, char **pointers_on_strings, size_t num_of_strings_in_file)
{
    assert(pointers_on_strings != NULL);
    assert(buffer != NULL);

    char *ptr_on_buffer = buffer;
    char *pointer_on_new_string = NULL;

    if ((pointer_on_new_string = strchr(ptr_on_buffer, '\n')) == NULL)
        return;

    size_t i = 0;
    for (; i < (num_of_strings_in_file - 1) && pointer_on_new_string != NULL; i++)
    {
        *pointer_on_new_string = '\0';
        if (*(pointer_on_new_string - 1) == '\r')
            *(pointer_on_new_string - 1) = '\0';
        pointers_on_strings[i] = ptr_on_buffer;
        ptr_on_buffer = pointer_on_new_string + 1;
        pointer_on_new_string = strchr(ptr_on_buffer, '\n');
    }
    pointers_on_strings[i] = ptr_on_buffer;
}

struct strings_info get_num_of_strings_and_array_of_points(char *buffer)
{
    assert(buffer != NULL);

    struct strings_info strings = {0, NULL};
    size_t num_of_strings_in_file = return_num_of_strings_in_file(buffer);
    // printf("%d\n", num_of_strings_in_file); // проверка количества строк в файле

    char **pointers_on_strings = (char **)calloc(num_of_strings_in_file, sizeof(char *));
    add_pointers_on_strings(buffer, pointers_on_strings, num_of_strings_in_file);

    strings.num_of_strings_in_file = num_of_strings_in_file;
    strings.pointers_on_strings = pointers_on_strings;

    return strings;
}

void sort_array_of_points(char **pointers_on_strings, size_t num_of_strings_in_file, int (*my_strcmp)(const char *str1, const char *str2))
{
    for (size_t i = 0; i < num_of_strings_in_file - 1; i++)
    {
        for (size_t j = i + 1; j < num_of_strings_in_file; j++)
        {
            // printf("%d\n", (*my_strcmp)((const char *)(pointers_on_strings[i]), (const char *)(pointers_on_strings[j])));
            if ((*my_strcmp)((const char *)(pointers_on_strings[i]), (const char *)(pointers_on_strings[j])) > 0)
            {
                char *ptr_help = pointers_on_strings[i];
                pointers_on_strings[i] = pointers_on_strings[j];
                pointers_on_strings[j] = ptr_help;
                // printf("i = %d j = %d\n", i, j);
                // printf("%s\n", pointers_on_strings[i]);
                // printf("%s\n", pointers_on_strings[j]);
            }
        }
    }
}

/******************************************************/
int compare_str_from_the_begining(const void *par1, const void *par2)
{
    const char *s1 = *(const char *const *)par1;
    const char *s2 = *(const char *const *)par2;

    return my_strcmp_from_the_begining(s1, s2);
}

int compare_str_from_the_end(const void *par1, const void *par2)
{
    const char *s1 = *(const char *const *)par1;
    const char *s2 = *(const char *const *)par2;

    return my_strcmp_from_the_end(s1, s2);
}
/******************************************************/

void write_data_for_a_file(char **pointers_on_strings, size_t num_of_strings_in_file, FILE *file_for_recording)
{
    for (size_t i = 0; i < num_of_strings_in_file; i++)
    {
        fprintf(file_for_recording, "%s\n", pointers_on_strings[i]);
    }
    fprintf(file_for_recording, "\n");
}

void my_sort(void *pointers_on_strings, size_t num_of_elements, size_t size, int (*comp)(const void *, const void *))
{
    assert(pointers_on_strings != NULL && comp != NULL);
    assert(num_of_elements != 0 && size != 0);

    for (size_t i = 0; i < num_of_elements - 1; i++)
    {
        for (size_t j = i + 1; j < num_of_elements; j++)
        {
            // printf("%d\n", (*comp)((char *)pointers_on_strings + i * size, (char *)pointers_on_strings + j * size));
            if ((*comp)((char *)pointers_on_strings + i * size, (char *)pointers_on_strings + j * size) > 0)
            {
                for (size_t c = 0; c < size; c++)
                {
                    char ptr_help = *((char *)pointers_on_strings + i * size + c);
                    *((char *)pointers_on_strings + i * size + c) = *((char *)pointers_on_strings + j * size + c);
                    *((char *)pointers_on_strings + j * size + c) = ptr_help;

                    // printf("i = %d j = %d\n", i, j);
                }
            }
        }
    }
}