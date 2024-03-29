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
    length -= 1;
    structure->stack1 = malloc(sizeof(int) * length);
    structure->stack2 = malloc(sizeof(int) * length);
    structure->sorted = malloc(sizeof(int) * length);
    structure->sorted_i = 0;
    structure->length = length;
    structure->stack1_i = 0;
    structure->stack2_i = length;
    // не проще ли будет BUFFSIZE максимальный сделать или вообще вызывать вывод каждый раз
    structure->ret = malloc(sizeof(char) * (length/2 + 1) * length * 4);
    structure->ret[(length/2 + 1) * length * 4 - 1] = '\n';
    structure->ret_i = 0;
    // нужна проверка на отработку маллока!!!!!
}

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

void swap_low_to_up(t_info *structure)
{
    // делает в массиве а rra (нижний элемент наверх)
    int j;
    int temp;

    j = structure->length;
    temp = structure->stack1[j - 1];
    while (--j > structure->stack1_i)
        structure->stack1[j] = structure->stack1[j - 1];
    structure->stack1[j] = temp;
}

void swap_up_to_low(t_info *structure)
{
    // делает в массиве а ra (верхний элемент вниз)
    int j;
    int temp;

    j = structure->stack1_i - 1;
    temp = structure->stack1[structure->stack1_i];
    while (++j < structure-> length - 1)
        structure->stack1[j] = structure->stack1[j + 1];
    structure->stack1[j] = temp;
}

int swap_low_to_up_times(t_info *structure, int i)
{
    // сдвигаем столько раз чтоб элемент i был наверху на месте structure->stack1_i и возвращаем сколько раз был сдвиг
    int j;
    
    j = 0;
    while (i != structure->stack1[structure->stack1_i])
    {
        swap_low_to_up(structure);
        j++;
    }
    return j;
}

int swap_up_to_low_times(t_info *structure, int i)
{
    // сдвигаем столько раз чтоб элемент i был наверху на месте structure->stack1_i и возвращаем сколько раз был сдвиг
    int j;
    
    j = 0;
    while (i != structure->stack1[structure->stack1_i])
    {
        swap_up_to_low(structure);
        j++;
    }
    return j;
}

void append(t_info *structure, char *str, int i)
{
    int j;
    int k;

    j = 0;
    while (j++ != i)
    {
        k = -1;
        while (str[++k])
            structure->ret[structure->ret_i++] = str[k];
        structure->ret[structure->ret_i++] = '\n';
    }
    
}

int check_sort(t_info *structure, int i)
{
    while(i < structure->length)
    {
        if (structure->stack1[i] != structure->sorted[i])
            return 0;
        i++;
    }
    return 1;
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
    if (j >= ((structure->length - structure->stack1_i) / 2 + (structure->length - structure->stack1_i) % 2))
        append(structure, "rra", swap_low_to_up_times(structure, structure->stack1[j]));
    else
        append(structure, "ra", swap_low_to_up_times(structure, structure->stack1[j]));
    if (check_sort(structure, i) == 0)
    {
        append(structure, "pb", 1);
        structure->stack1_i += 1;

    }
    
}

void go_sort(t_info *structure)
{
    int i;
    check_double(structure);
    sort_sorted(structure);
    i = -1;
    while (++i < structure->length)
    {
        if (check_sort(structure, i))
            break;
        sort(structure, i);
    }
    append(structure, "pa", structure->stack1_i);
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
        printf("%d  ", structure->stack1[i]);
    printf("\n");
    i = -1;
    while(++i < structure->ret_i)
        printf("%c", structure->ret[i]);
}
