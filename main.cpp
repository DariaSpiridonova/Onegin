#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "my_string_functions.h"
#include "onegin.h"

int main()
{
    FILE *read_strings = fopen("original_strings.txt", "rb");
    FILE *sorted_strings = fopen("sorted_strings.txt", "wb");

    if (!open_files_success(read_strings, sorted_strings))
        return -1;

    struct data_of_buffer data_in_buffer = read_to_buffer_from_file(read_strings);
    if (data_in_buffer.buffer == 0 || data_in_buffer.num_of_bytes_in_file == 0)
        return 2;

    struct strings_info strings = get_num_of_strings_and_array_of_points(data_in_buffer.buffer);
    if (strings.num_of_strings_in_file == 0 || strings.pointers_on_strings == NULL)
        return 3;

    sort_array_of_points(strings.pointers_on_strings, strings.num_of_strings_in_file, my_strcmp_from_the_begining);
    write_data_for_a_file(strings.pointers_on_strings, strings.num_of_strings_in_file, sorted_strings);

    sort_array_of_points(strings.pointers_on_strings, strings.num_of_strings_in_file, my_strcmp_from_the_end);
    write_data_for_a_file(strings.pointers_on_strings, strings.num_of_strings_in_file, sorted_strings);

    my_sort(strings.pointers_on_strings, strings.num_of_strings_in_file, sizeof(char *), compare_str_from_the_begining);
    write_data_for_a_file(strings.pointers_on_strings, strings.num_of_strings_in_file, sorted_strings);

    my_sort(strings.pointers_on_strings, strings.num_of_strings_in_file, sizeof(char *), compare_str_from_the_end);
    write_data_for_a_file(strings.pointers_on_strings, strings.num_of_strings_in_file, sorted_strings);

    sort_array_of_points(strings.pointers_on_strings, strings.num_of_strings_in_file, my_strcmp_in_order);
    write_data_for_a_file(strings.pointers_on_strings, strings.num_of_strings_in_file, sorted_strings);

    if (fclose(read_strings) == EOF)
        return -1;
    if (fclose(sorted_strings) == EOF)
        return -1;

    return 0;
}