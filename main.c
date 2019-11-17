#include "push_swap.h"

void error_function()
{
    write(1, "Error\n", 6);
    exit(1);
}

void check_string(char *str)
{
    int i;
    i = -1;
    while(str[++i])
    {
        if (str[i] >= '0' && str[i] <= '9')
            continue;
        if (i == 0 && (str[i] == '-' || str[i] == '+'))
            continue;
        error_function();
    }
}

void memory_allocate(t_info *structure, int length)
{
    structure->stack1 = malloc(sizeof(int) * (length - 1));
    structure->stack2 = malloc(sizeof(int) * (length - 1));
    structure->sorted = malloc(sizeof(int) * (length - 1));
    structure->sorted_i = 0;
    structure->length = length - 1;
    structure->stack1_i = 0;
    structure->stack2_i = length - 1;
    // не нужна ли проверка на отработку маллока?
}

//int check_sort(t_info structure)

void check_double(t_info *structure)
{
    int i;
    int j;
    i = 0;
    while (++i < structure->length)
    {
        j = -1;
        while (++j < i)
        {
            if (structure->stack1[j] == structure->stack1[i])
                error_function();
        }
    }
}

void sort_sorted(t_info *structure)
{
    int i;
    int temp;

    i = -1;
    structure->sorted_i = 0;
    while (++i < structure->length)
        structure->sorted[i] = structure->stack1[i];
    i = 1; 
    while (i < structure->length)
    {
        if (i == 0)
            i = 2;
        else if (structure->sorted[i] < structure->sorted[i - 1])
        {
            temp = structure->sorted[i];
            structure->sorted[i] = structure->sorted[i - 1];
            structure->sorted[i - 1] = temp;
            i--;
        }
        else
            i++;
    }
}

int is_sorted(int *arr, int length)
{
    while (--length > 0)
    {
        if (arr[length] < arr[length - 1])
            return (0);
    }
    return (1);
}

void sort(t_info *structure, int i)
{
    int j;
    j = -1;
    while(++j < structure->length)
    {
        if (structure->stack1[j] == structure->sorted[i])
            break;
    }
    if (j < (structure->length / 2 + structure->length % 2))
}

void go_sort(t_info *structure)
{
    int i;
    check_double(structure);
    sort_sorted(structure);
    i = -1;
    while (++i < structure->length)
    {
        sort(structure, i)
    }
}


int main(int argc, char **argv)
{
    int i;
    t_info *structure;
    if (argc < 2)
        error_function();
    i = 0;
    while (++i < argc)
        check_string(argv[i]);
    structure = malloc(sizeof(t_info));
    i = 0;
    memory_allocate(structure, argc);
    while(++i < argc)
        structure->stack1[i - 1] = ft_atoi(argv[i]);
    go_sort(structure);
    i = -1;
    while (++i < structure->length)
        printf("%d  ", structure->sorted[i]);
    printf("\n %d  %d \n", is_sorted(structure->stack1, structure->length),
                is_sorted(structure->sorted, structure->length));
}
