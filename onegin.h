#ifndef ONEGIN
#define ONEGIN
#include <stdio.h>

int open_files_success(FILE *read_strings, FILE *sorted_strings);
size_t return_num_of_bytes_in_file(FILE *fp);
size_t return_num_of_bytes_in_file1(int fd1);
size_t return_num_of_strings_in_file(char *buffer);
struct data_of_buffer read_to_buffer_from_file(FILE *read_strings);
void add_pointers_on_strings(char *buffer, char **pointers_on_strings, size_t num_of_strings_in_file);
struct strings_info get_num_of_strings_and_array_of_points(char *buffer);
void sort_array_of_points(char **pointers_on_strings, size_t num_of_strings_in_file, int (*my_strcmp)(const char *str1, const char *str2));
int compare_str_from_the_begining(const void *par1, const void *par2);
int compare_str_from_the_end(const void *par1, const void *par2);

void write_data_for_a_file(char **pointers_on_strings, size_t num_of_strings_in_file, FILE *file_for_recording);

void my_sort(void *pointers_on_strings, size_t num_of_elements, size_t size, int (*comp)(const void *, const void *));

struct data_of_buffer
{
    size_t num_of_bytes_in_file;
    char *buffer;
};

struct strings_info
{
    size_t num_of_strings_in_file;
    char **pointers_on_strings;
};
#endif