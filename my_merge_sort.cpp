#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <sys/stat.h>

void sort_two_elem(int * pointer_on_buffer, size_t first_index, size_t last_index);
void create_a_single_array(int *pointer_on_buffer, size_t first_index, size_t last_index);
void my_merge_sort(int * pointer_on_buffer, size_t first_index, size_t last_index);

int main()
{
    int array[8] = {4, 5, 3, 8, 9, 0, 5, 11};

    my_merge_sort(array, 0, 7);

    for (int i = 0; i < 8; i++)
    {
        printf("%d ", array[i]);
    }
}

void sort_two_elem(int * pointer_on_buffer, size_t first_index, size_t last_index)
{
    assert(pointer_on_buffer != NULL);
    assert(last_index - first_index == 1);
    
    if (pointer_on_buffer[first_index] > pointer_on_buffer[last_index])
    {
        int copy_first = pointer_on_buffer[first_index];
        pointer_on_buffer[first_index] = pointer_on_buffer[last_index];
        pointer_on_buffer[last_index] = copy_first;
    }
}

void create_a_single_array(int *pointer_on_buffer, size_t first_index, size_t last_index)
{
    assert(pointer_on_buffer != NULL);
    assert(first_index != last_index);

    int *ptr_on_sorted_array = (int *)calloc(last_index - first_index + 1, sizeof(int));
    size_t index_1 = first_index, index_2 = (first_index + last_index) / 2 + 1, i = 0;

    while (index_1 <= (first_index + last_index) / 2 && index_2 <= last_index)
    {
        if (pointer_on_buffer[index_1] < pointer_on_buffer[index_2])
        {
            ptr_on_sorted_array[i++] = pointer_on_buffer[index_1++];
        }
        else 
        {
            ptr_on_sorted_array[i++] = pointer_on_buffer[index_2++];
        }
    }

    if (index_1 > (first_index + last_index) / 2)
    {
        memcpy(ptr_on_sorted_array + i, pointer_on_buffer + index_2, (last_index - index_2 + 1)*sizeof(int));
    }

    else if (index_2 > (first_index + last_index) / 2 + 1)
    {
        memcpy(ptr_on_sorted_array + i, pointer_on_buffer + index_1, ((first_index + last_index) / 2 - index_1 + 1)*sizeof(int));
    }

    memcpy(pointer_on_buffer + first_index, ptr_on_sorted_array, (last_index - first_index + 1)*sizeof(int));

    free(ptr_on_sorted_array);
}

void my_merge_sort(int * pointer_on_buffer, size_t first_index, size_t last_index)
{
    assert(pointer_on_buffer != NULL);
    assert(first_index != last_index);

    if (last_index == first_index)
        return;
    if (last_index - first_index == 1)
    {
        sort_two_elem(pointer_on_buffer, first_index, last_index);
        return;
    }

    my_merge_sort(pointer_on_buffer, first_index, (first_index + last_index) / 2);
    my_merge_sort(pointer_on_buffer, (first_index + last_index) / 2 + 1, last_index);

    create_a_single_array(pointer_on_buffer, first_index, last_index);
}

